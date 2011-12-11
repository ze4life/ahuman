#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

SpatialPooler::SpatialPooler() {
}

void SpatialPooler::create( int p_poolSize , int sizeX , int sizeY ) {
	poolSize = p_poolSize;
	patternSizeX = sizeX;
	patternSizeY = sizeY;
}

void SpatialPooler::setMatchTolerance( int matchTolerance ) {
}

void SpatialPooler::setProtectedUsage( int usage ) {
}

int SpatialPooler::matchPattern( NeuroPool *pool , int *patternForgotten ) {
	return( -1 );
}

bool SpatialPooler::getPattern( int pattern , NeuroPool *feedbackPool ) {
	return( false );
}

