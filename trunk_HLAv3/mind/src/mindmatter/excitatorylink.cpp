#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class ExcitatoryLink : public NeuroLink {
public:
	ExcitatoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "ExcitatoryLink" ); };

public:
	virtual NeuroSignal *apply( NeuroSignal *srcData , NeuroPool *dstPool );

private:
	int opid;
};

/*#########################################################################*/
/*#########################################################################*/

NeuroLink *MindService::createExcitatoryLink( MindRegionLink *link ) { return( new ExcitatoryLink( link ) ); };

/*#########################################################################*/
/*#########################################################################*/

ExcitatoryLink::ExcitatoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
	opid = 0;
}

NeuroSignal *ExcitatoryLink::apply( NeuroSignal *srcData , NeuroPool *dstPool ) {
	opid++;

	// signal value is encoded strength of neural impulse
	// in biology neuron it is frequency of spikes while signal itself has fixed electric voltage
	// value equals to number of impulses combined in specific message
	// spike increases cell potential and cell fires if potentials is greater that certain threshold
	// cell discharges if no spikes arrived
	// reaching threshold takes a time
	// assuming linear rate of charge and discharge
	// charge parameters
	// spike: I=Q/t=~200mkA, U=100mV, t=10ms, charge threshold=I*t=0.0002A*10ms=0.000002Q=0.002Q/ms
	// frequency: 0-100Hz
	// discharge speed=charge speed=NEURON_CHARGE_SPEED=0.002Q/ms
	// last charge change timestamp lastChargeChangeTimestamp
	// last charge state=lastCharge
	// current timestamp=currentTimestamp
	// current charge=max( lastCharge - chargeSpeed * (currentTimestamp-lastChargeChangeTimestamp) , 0 )
	// action potential charge= (50mV*1ms) 0.002Q/ms*0.5*0.1 = ...
	// arrived charge=value * 
	// new potential=current charge + arrived charge

	// data:
	// msTimePassed
	// lastCharge
	// NEURON_DISCHARGE_RATE_pQ_per_ms

	// calculation:
	// currentCharge=max( lastCharge - NEURON_DISCHARGE_RATE_pQ_per_ms * msTimePassed , 0 )

	// project source to target
	dstPool -> startProjection( this );

	// log 
	LOGDEBUG( String( "apply " ) + opid + ": projecting NeuroLink, id=" + getId() + "..." );

	// current timestamp
	RFC_INT64 msNow = Timer::getCurrentTimeMillis();

	// map source surface to target surface - as linear arrays
	int dnx , dny;
	dstPool -> getNeuronDimensions( &dnx , &dny );
	int dn = dnx * dny;
	TwoIndexArray<NEURON_DATA>& dstDataNeurons = dstPool -> getNeuronData();
	NEURON_DATA *dvdata = dstDataNeurons.getData();

	// project specific values
	int snx , sny;
	srcData -> getSizeInfo( &snx , &sny );
	int sn = snx * sny;

	// read activated indexes
	int n = srcData -> getDataSize();
	int *sv = srcData -> getIndexRawData();

	NeuroSignal *ffSignal = new NeuroSignal( dnx , dny );
	for( int k = 0; k < n; k++ ) {
		// get value and project
		int sk = *sv++;
		int dk = ( int )( ( sk * (RFC_INT64)dn ) / sn );

		// get current potential and handle timestamps
		NEURON_DATA *dv = dvdata + dk;
		neurovt_state lastCharge = dv -> potential;
		RFC_INT64 msPassed = msNow - dv -> updated;
		dv -> updated = msNow;

		// calculate current value of action potential
		neurovt_state currentCharge = lastCharge;
			
		if( msPassed < NEURON_FULL_RELAX_ms ) {
			currentCharge -= ( ( neurovt_state )msPassed ) * NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms;
			if( currentCharge < 0 )
				currentCharge = 0;
		}
		else
			currentCharge = 0;

		// add action potential
		currentCharge += NEURON_FIRE_POTENTIAL_THRESHOLD_pQ;

		// save new value
		dv -> potential = currentCharge;

		// check need to generate feed-forward
		if( currentCharge >= NEURON_FIRE_POTENTIAL_THRESHOLD_pQ )
			ffSignal -> addIndexData( dk );

		LOGDEBUG( String( "apply " ) + opid + ": spos=" + sk + ", dpos=" + dk + ", lastCharge=" + lastCharge + ", newCharge=" + currentCharge + ", msPassed=" + ( int )msPassed );
	}

	// log 
	LOGDEBUG( String( "apply " ) + opid + ": NeuroLink projected, id=" + getId() + ", neurons affected count=" + ffSignal -> getDataSize() );

	// finish projection
	dstPool -> finishProjection( this , ffSignal );

	// check signal is required
	if( ffSignal -> getDataSize() == 0 ) {
		delete ffSignal;
		return( NULL );
	}

	return( ffSignal );
}
