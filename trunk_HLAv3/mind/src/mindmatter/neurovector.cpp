#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroVector::NeuroVector() {
}

NeuroVector::NeuroVector( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

NeuroVector::NeuroVector( NeuroVector *src ) {
	data.copy( src -> getVectorData() );
}

NeuroVector::~NeuroVector() {
}

void NeuroVector::create( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

neurovt *NeuroVector::getRawData() {
	return( data.getData() );
}

TwoIndexArray<neurovt>& NeuroVector::getVectorData() {
	return( data );
}

void NeuroVector::getSizeInfo( int *nx , int *ny ) {
	*nx = data.getN1();
	*ny = data.getN2();
}

