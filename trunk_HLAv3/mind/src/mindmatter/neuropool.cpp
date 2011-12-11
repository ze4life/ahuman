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

void NeuroPool::finishProjection( NeuroLink *link ) {
	// check potential, fire neurons
	NEURON_DATA *data = neurons.getData();
	int n = neurons.count();

	for( int k = 0; k < n; k++ , data++ ) {
		if( data -> potential > NEURON_FIRE_THRESHOLD_pQ ) {
			// fire
			data -> output = NEURON_FIRE_THRESHOLD_pQ;
			data -> potential = 0;
		}
	}
}

