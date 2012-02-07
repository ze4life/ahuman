#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroPool::NeuroPool() {
	attachLogger();
	pendingSignal = NULL;
}

NeuroPool::~NeuroPool() {
}

void NeuroPool::createNeurons( int nx , int ny ) {
	neurons.create( nx , ny );
	pendingSignal = new NeuroSignal( nx , ny );
}

void NeuroPool::setParent( MindRegion *p_region ) {
	region = p_region;
}

MindRegion *NeuroPool::getRegion() {
	return( region );
}

void NeuroPool::setId( String p_id ) {
	id = p_id;
}

String NeuroPool::getId() {
	return( id );
}

void NeuroPool::getNeuronDimensions( int *px , int *py ) {
	*px = neurons.getN1();
	*py = neurons.getN2();
}

TwoIndexArray<NEURON_DATA>& NeuroPool::getNeuronData() {
	return( neurons );
}

void NeuroPool::startProjection( NeuroLink *link ) {
}

void NeuroPool::finishProjection( NeuroLink *link , NeuroSignal *p_signal ) {
	// process new and pending signals
	if( p_signal != NULL ) {
		applySignal( p_signal , false );
		applySignal( pendingSignal , true );

		// update pending signal
		updatePendingData( p_signal );

		MindArea *area = region -> getArea();
		LOGDEBUG( "finishProjection: MindArea id=" + area -> getId() + " NeuroPool id=" + id + " state after signal id=" + p_signal -> getId() + " data=" + getNumberedPoolState( p_signal ) );
	}
}

void NeuroPool::applySignal( NeuroSignal *signal , bool pending ) {
	// fire neurons
	NEURON_DATA *data = neurons.getData();
	int n = signal -> getDataSize();
	int *sv = signal -> getIndexRawData();
	RFC_INT64 msNow = Timer::getCurrentTimeMillis();

	for( int k = 0; k < n; k++ , sv++ ) {
		int index = *sv;
		NEURON_DATA *dv = data + index;
		RFC_INT64 msSilentTill = dv -> silent_till;

		// do not fire ifin silent time
		if( msNow < msSilentTill ) {
			LOGDEBUG( String( "apply pending: do not fire index=" ) + index + ", msRemained=" + ( int )( msSilentTill - msNow ) );
			continue;
		}

		// update values if process pending
		if( pending ) {
			// recalculate potential
			RFC_INT64 msPassed = msNow - dv -> updated_mp;
			dv -> potential -= ( ( neurovt_state )msPassed ) * NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms;

			// check dissolved
			if( dv -> potential < NEURON_FIRE_OUTPUT_THRESHOLD_pQ ) {
				dv -> firestate = -1;
				LOGDEBUG( String( "apply pending: forget too late index=" ) + index + ", msPassed=" + ( int )msPassed );
				continue;
			}
		}

		// fire
		dv -> silent_till = msNow + NEURON_FIRE_OUTPUT_SILENT_ms;
		dv -> firestate = NEURON_FIRE_OUTPUT_BY_POTENTIAL_pQ;
		LOGDEBUG( String( "apply pending: fire index=" ) + index );
	}
}

void NeuroPool::updatePendingData( NeuroSignal *p_signal ) {
	// set both signals to union
	p_signal -> addIndexDataSorted( pendingSignal );
	pendingSignal -> copyDataFromSignal( p_signal );

	// reset index data
	NEURON_DATA *data = neurons.getData();
	int n = p_signal -> getDataSize();
	int *sv = p_signal -> getIndexRawData();
	int *pv = pendingSignal -> getIndexRawData();

	for( int k = 0; k < n; k++ , sv++ , pv++ ) {
		int index = *sv;
		NEURON_DATA *dv = data + index;

		if( dv -> firestate == 0 )
			*sv = -1;
		else {
			if( dv -> firestate < 0 )
				*sv = *pv = -1;
			else
				*pv = -1;
			dv -> firestate = 0;
		}
	}

	p_signal -> removeNotFiringIndexData();
	pendingSignal -> removeNotFiringIndexData();
}

String NeuroPool::getNumberedPoolState( NeuroSignal *p_signal ) {
	NeuroSignal data;
	data.addIndexDataSorted( p_signal );
	data.addIndexDataSorted( pendingSignal );

	String ps;

	int *sd = p_signal -> getIndexRawData();
	int sdn = p_signal -> getDataSize();

	int *pd = pendingSignal -> getIndexRawData();
	int pdn = pendingSignal -> getDataSize();

	bool first = true;
	int ks = 0;
	int kp = 0;
	for( ; ks < sdn || kp < pdn; ) {
		if( first  )
			first = false;
		else
			ps += ".";

		if( ks >= sdn ) {
			ps += pd[ kp++ ];
			ps += "p";
		}
		else
		if( kp >= pdn )
			ps += sd[ ks++ ];
		else {
			if( pd[ kp ] < sd[ ks ] ) {
				ps += pd[ kp++ ];
				ps += "p";
			}
			else
			if( pd[ kp ] > sd[ ks ] )
				ps += sd[ ks++ ];
			else {
				ps += sd[ ks++ ];
				kp++;
			}
		}
	}

	return( ps );
}
