#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroPool::NeuroPool() {
	attachLogger();
}

NeuroPool::~NeuroPool() {
}

void NeuroPool::createNeurons( int nx , int ny ) {
	neurons.create( nx , ny );
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

void NeuroPool::finishProjection( NeuroLink *link , NeuroSignal *signal ) {
	// check potential, fire neurons
	NEURON_DATA *data = neurons.getData();
	int n = signal -> getDataSize();
	int *sv = signal -> getIndexRawData();
	RFC_INT64 msNow = Timer::getCurrentTimeMillis();

	for( int k = 0; k < n; k++ , sv++ ) {
		int index = *sv;

		// fire, keep update timestamp not changed - the same for action potential and state
		NEURON_DATA *dv = data + index;
		RFC_INT64 msPassed = msNow - dv -> updated_fs;

		neurovt_state currentCharge = dv -> output;
		if( msPassed < NEURON_FULL_RELAX_ms ) {
			currentCharge -= ( ( neurovt_state )msPassed ) * NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
			if( currentCharge < 0 )
				currentCharge = 0;
		}
		else
			currentCharge = 0;

		dv -> output = currentCharge + NEURON_FIRE_OUTPUT_BY_POTENTIAL_pQ;
		dv -> updated_fs = msNow;
		dv -> potential = 0;
		dv -> updated_mp = msNow;

		// fire or do not fire
		if( dv -> output > NEURON_FIRE_OUTPUT_THRESHOLD_pQ )
			dv -> output = -NEURON_FIRE_OUTPUT_SILENT_ms * NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
		else
			*sv = -1;
	}

	MindArea *area = region -> getArea();
	LOGDEBUG( "finishProjection: MindArea id=" + area -> getId() + " NeuroPool id=" + id + " state after signal id=" + signal -> getId() + " data=" + getNumberedPoolState() );

	// exclude not firing neurons
	signal -> removeNotFiringIndexes();
}

String NeuroPool::getNumberedPoolState() {
	String ps;

	NEURON_DATA *data = neurons.getData();
	int n = neurons.count();
	RFC_INT64 msNow = Timer::getCurrentTimeMillis();

	bool first = true;
	for( int k = 0; k < n; k++ ) {
		NEURON_DATA *dv = data + k;

		RFC_INT64 msPassed = msNow - dv -> updated_fs;

		neurovt_state currentCharge = dv -> output;
		if( msPassed < NEURON_FULL_RELAX_ms ) {
			currentCharge -= ( ( neurovt_state )msPassed ) * NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
			if( currentCharge < 0 )
				currentCharge = 0;
		}
		else
			currentCharge = 0;

		if( currentCharge ) {
			if( first  )
				first = false;
			else
				ps += ".";

			ps += k;
			if( currentCharge < 0 )
				ps += "i";
			else
			if( currentCharge >= NEURON_FIRE_OUTPUT_THRESHOLD_pQ )
				ps += "h";
			else
				ps += "l";
		}
	}

	return( ps );
}
