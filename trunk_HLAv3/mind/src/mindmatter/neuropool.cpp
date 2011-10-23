#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroPool::NeuroPool() {
	cellPotentials = NULL;
	cellOutputs = NULL;
	lastExecutionTicks = ( RFC_INT64 )0;
}

NeuroPool::~NeuroPool() {
	if( cellPotentials != NULL )
		delete cellPotentials;
	if( cellOutputs != NULL )
		delete cellOutputs;
}

void NeuroPool::createNeurons( int nx , int ny ) {
	cellPotentials = new NeuroState( nx , ny );
	cellOutputs = new NeuroState( nx , ny );
}

void NeuroPool::getNeuronDimensions( int *px , int *py ) {
	cellOutputs -> getSizeInfo( px , py );
}

NeuroState *NeuroPool::getCellPotentials() {
	return( cellPotentials );
}

NeuroState *NeuroPool::getCellOutputs() {
	return( cellOutputs );
}

void NeuroPool::startProjection( NeuroLink *link ) {
}

void NeuroPool::finishProjection( NeuroLink *link ) {
}

RFC_INT64 NeuroPool::getLastExecutionTimeTicks() {
	return( lastExecutionTicks );
}

void NeuroPool::setLastExecutionTimeTicks( RFC_INT64 p_ticks ) {
	lastExecutionTicks = p_ticks;
}
