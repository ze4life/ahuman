#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroSignal::NeuroSignal() {
}

NeuroSignal::NeuroSignal( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

NeuroSignal::NeuroSignal( NeuroSignal *src ) {
	data.copy( src -> getVectorData() );
}

NeuroSignal::~NeuroSignal() {
}

void NeuroSignal::create( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

neurovt_signal *NeuroSignal::getRawData() {
	return( data.getData() );
}

TwoIndexArray<neurovt_signal>& NeuroSignal::getVectorData() {
	return( data );
}

void NeuroSignal::getSizeInfo( int *nx , int *ny ) {
	*nx = data.getN1();
	*ny = data.getN2();
}

