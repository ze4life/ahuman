#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroPool::NeuroPool() {
	cellPotentials = NULL;
	cellOutputs = NULL;
}

NeuroPool::~NeuroPool() {
	if( cellPotentials != NULL )
		delete cellPotentials;
	if( cellOutputs != NULL )
		delete cellOutputs;
}

void NeuroPool::createNeurons( int nx , int ny ) {
	cellPotentials = new NeuroVector( nx , ny );
	cellOutputs = new NeuroVector( nx , ny );
}

void NeuroPool::getNeuronDimensions( int *px , int *py ) {
	cellOutputs -> getSizeInfo( px , py );
}

void NeuroPool::startProjection( NeuroLink *link ) {
}

void NeuroPool::finishProjection( NeuroLink *link ) {
}

void NeuroPool::executeProjection( NeuroLink *link , int  x , int y , neurovt v ) {
}

