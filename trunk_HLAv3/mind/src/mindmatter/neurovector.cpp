#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroVector::NeuroVector( int sizeX , int sizeY ) {
	data.create( sizeX , sizeY );
}

NeuroVector::NeuroVector( NeuroVector *src ) {
	data.copy( src -> getVectorData() );
}

NeuroVector::~NeuroVector() {
}

neurovt *NeuroVector::getRawData() {
	return( data.getData() );
}

TwoIndexArray<neurovt>& NeuroVector::getVectorData() {
	return( data );
}
