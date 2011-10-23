#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroState::NeuroState() {
}

NeuroState::NeuroState( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

NeuroState::NeuroState( NeuroState *src ) {
	data.copy( src -> getVectorData() );
}

NeuroState::~NeuroState() {
}

void NeuroState::create( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

neurovt_state *NeuroState::getRawData() {
	return( data.getData() );
}

TwoIndexArray<neurovt_state>& NeuroState::getVectorData() {
	return( data );
}

void NeuroState::getSizeInfo( int *nx , int *ny ) {
	*nx = data.getN1();
	*ny = data.getN2();
}

