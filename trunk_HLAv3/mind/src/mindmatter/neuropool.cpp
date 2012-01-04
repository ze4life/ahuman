#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroPool::NeuroPool() {
}

NeuroPool::~NeuroPool() {
}

void NeuroPool::createNeurons( int nx , int ny ) {
	neurons.create( nx , ny );
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
	NEURON_DATA *dv = neurons.getData();
	int n = signal -> getDataSize();
	int *sv = signal -> getIndexRawData();

	for( int k = 0; k < n; k++ ) {
		int index = *sv++;

		// fire, keep update timestamp not changed - the same for action potential and state
		NEURON_DATA *data = dv + index;
		data -> output = NEURON_FIRE_OUTPUT_BY_POTENTIAL_pQ;
		data -> potential = 0;
	}
}

