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

	// create generated feed forward signal
	NeuroSignal *ffSignal = new NeuroSignal( dnx , dny );
	ffSignal -> setId( srcData -> getId() );

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
			if( currentCharge >= 0 ) {
				currentCharge -= ( ( neurovt_state )msPassed ) * NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms;
				if( currentCharge < 0 )
					currentCharge = 0;
			}
			else {
				currentCharge += ( ( neurovt_state )msPassed ) * NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms;
				if( currentCharge > 0 )
					currentCharge = 0;
			}
		}
		else
			currentCharge = 0;

		// add action potential
		currentCharge += NEURON_FIRE_OUTPUT_BY_POTENTIAL_pQ;

		// save new value
		dv -> potential = currentCharge;

		// check need to generate feed-forward
		if( currentCharge >= NEURON_FIRE_POTENTIAL_THRESHOLD_pQ )
			ffSignal -> addIndexData( dk );

		LOGDEBUG( String( "apply: projected NeuroLink id=" ) + getId() + ", NeuroSignal id=" + srcData -> getId() + ", spos=" + sk + ", dpos=" + dk + ", lastCharge=" + lastCharge + ", newCharge=" + currentCharge + ", msPassed=" + ( int )msPassed );
	}

	// finish projection
	dstPool -> finishProjection( this , ffSignal );

	// log 
	logger.logInfo( String( "apply: projected NeuroLink id=" ) + getId() + ", NeuroSignal id=" + srcData -> getId() + ", signalCount=" + srcData -> getDataSize() + ", affectedCount=" + ffSignal -> getDataSize() );

	// check signal is required
	if( ffSignal -> getDataSize() == 0 ) {
		delete ffSignal;
		return( NULL );
	}

	return( ffSignal );
}
