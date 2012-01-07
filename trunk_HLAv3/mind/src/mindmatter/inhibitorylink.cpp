#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class InhibitoryLink : public NeuroLink {
public:
	InhibitoryLink( MindRegionLink *regionLink );
	virtual const char *getClass() { return( "InhibitoryLink" ); };

public:
	virtual NeuroSignal *apply( NeuroSignal *srcData , NeuroPool *dstPool );

private:
	int opid;
};

/*#########################################################################*/
/*#########################################################################*/

NeuroLink *MindService::createInhibitoryLink( MindRegionLink *link ) { return( new InhibitoryLink( link ) ); };

/*#########################################################################*/
/*#########################################################################*/

InhibitoryLink::InhibitoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
	opid = 0;
}

NeuroSignal *InhibitoryLink::apply( NeuroSignal *srcData , NeuroPool *dstPool ) {
	opid++;

	// project source to target
	dstPool -> startProjection( this );

	// log 
	LOGDEBUG( String( "apply: projected NeuroLink id=" ) + getId() + ", NeuroSignal id=" + srcData -> getId() + "..." );

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

	// no feed forward signal will be generated
	for( int k = 0; k < n; k++ ) {
		// get value and project
		int sk = *sv++;
		int dk = ( int )( ( sk * (RFC_INT64)dn ) / sn );

		// get current potential and handle timestamps
		NEURON_DATA *dv = dvdata + dk;
		neurovt_state lastCharge = dv -> potential;
		RFC_INT64 msPassed = msNow - dv -> updated_mp;
		dv -> updated_mp = msNow;

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
		currentCharge -= NEURON_FIRE_POTENTIAL_THRESHOLD_pQ;

		// save new value
		dv -> potential = currentCharge;

		LOGDEBUG( String( "apply: projected NeuroLink id=" ) + getId() + ", NeuroSignal id=" + srcData -> getId() + ", spos=" + sk + ", dpos=" + dk + ", lastCharge=" + lastCharge + ", newCharge=" + currentCharge + ", msPassed=" + ( int )msPassed );
	}

	// log 
	logger.logInfo( String( "apply: projected NeuroLink id=" ) + getId() + ", NeuroSignal id=" + srcData -> getId() + ", signalCount=" + srcData -> getDataSize() );

	// finish projection
	dstPool -> finishProjection( this , NULL );
	return( NULL );
}
