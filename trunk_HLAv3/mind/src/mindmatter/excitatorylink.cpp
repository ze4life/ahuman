#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class ExcitatoryLink : public NeuroLink {
public:
	ExcitatoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "ExcitatoryLink" ); };

public:
	virtual void apply( NeuroSignal *srcData , NeuroPool *dstPool );
};

/*#########################################################################*/
/*#########################################################################*/

NeuroLink *MindService::createExcitatoryLink( MindRegionLink *link ) { return( new ExcitatoryLink( link ) ); };

/*#########################################################################*/
/*#########################################################################*/

ExcitatoryLink::ExcitatoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void ExcitatoryLink::apply( NeuroSignal *srcData , NeuroPool *dstPool ) {
	// value is encoded strength of neural impulse
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

	const neurovt_state NEURON_FIRE_THRESHOLD_pQ = ( neurovt_state )100;
	const neurovt_state NEURON_FIRE_IMPULSE_pQ = ( neurovt_state )10;
	const neurovt_state NEURON_DISCHARGE_RATE_pQ_per_ms = ( neurovt_state )10;

	// current timestamp
	RFC_INT64 ticksLast = dstPool -> getLastExecutionTimeTicks();
	RFC_INT64 ticksNow;
	rfc_hpt_setpoint( &ticksNow );
	dstPool -> setLastExecutionTimeTicks( ticksNow );

	int msPassed = 0;
	if( ticksLast )
		msPassed = rfc_hpt_ticks2ms( ( int )( ticksNow - ticksLast ) );

	// map source surface to target surface
	int dnx , dny;
	dstPool -> getNeuronDimensions( &dnx , &dny );

	// project source to target
	dstPool -> startProjection( this );

	// project specific values
	int snx , sny;
	srcData -> getSizeInfo( &snx , &sny );
	neurovt_signal *sv = srcData -> getRawData();

	NeuroState *dstPotentials = dstPool -> getCellPotentials();
	neurovt_state *dv = dstPotentials -> getRawData();

	NeuroState *dstOutputs = dstPool -> getCellOutputs();
	neurovt_state *ov = dstOutputs -> getRawData();

	bool generateOutputs = false;

	bool srcDrivenX = ( snx < dnx );
	bool srcDrivenY = ( sny < dny );
	int maxX = ( srcDrivenX )? snx : dnx;
	int maxY = ( srcDrivenY )? sny : dny;
	for( int kx = 0; kx < maxX; kx++ ) {
		// map x position
		int sx = ( srcDrivenX )? kx : ( kx * snx / dnx );
		int dx = ( srcDrivenX )? ( kx * dnx / snx ) : kx;

		for( int ky = 0; ky < maxY; ky++ ) {
			// map y position
			int sy = ( srcDrivenY )? ky : ( ky * sny / dny );
			int dy = ( srcDrivenY )? ( ky * dny / sny ) : ky;

			// get value and project
			neurovt_signal actionPotential = sv[ sy * snx + sx ];

			// get current potential
			neurovt_state lastCharge = dv[ dy * dnx + dx ];

			// calculate current value of action potential
			neurovt_state currentCharge = lastCharge - msPassed * NEURON_DISCHARGE_RATE_pQ_per_ms;
			if( currentCharge < 0 )
				currentCharge = 0;

			// add action potential
			currentCharge += actionPotential * NEURON_FIRE_IMPULSE_pQ;

			// save new value
			dv[ dy * dnx + dx ] = currentCharge;

			// check need to generate feed-forward
			if( currentCharge > NEURON_FIRE_THRESHOLD_pQ )
				generateOutputs = true;
		}
	}

	// log 
	logger.logDebug( "apply: NeuroLink projected, id=" + getId() + ", generateOutpus=" + generateOutputs );

	// finish projection
	dstPool -> finishProjection( this );
}
