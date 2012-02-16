#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindEffector::MindEffector( EffectorArea *p_area )
:	MindRegion( p_area ) {
}

String MindEffector::getRegionType() {
	return( "MindEffector" );
}

void MindEffector::getSourceSizes( String entity , int *sizeX , int *sizeY ) {
}

void MindEffector::createRegion() {
	// call effector creation
	createEffector();
	logger.logDebug( String( "createRegion: created effector region" ) );
}

void MindEffector::exitRegion() {
}

void MindEffector::destroyRegion() {
}

