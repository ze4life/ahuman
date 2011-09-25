#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

CortexRegion::CortexRegion() {
	attachLogger();
}

void CortexRegion::createRegion() {
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
}

// link creation
void CortexRegion::createNeuroLinks( MindRegionLink *link , MindRegion *dst ) {
	dst -> createNeuroLinksFromCortexRegion( link , this );
}

void CortexRegion::createNeuroLinksFromCortexRegion( MindRegionLink *link , CortexRegion *src ) {
	logger.logDebug( "createNeuroLinksFromCortexRegion" );
}

void CortexRegion::createNeuroLinksFromNucleiRegion( MindRegionLink *link , NucleiRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNucleiRegion" );
}

void CortexRegion::createNeuroLinksFromNerveRegion( MindRegionLink *link , NerveRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNerveRegion" );
}

void CortexRegion::createNeuroLinksFromSensorRegion( MindRegionLink *link , MindSensor *src ) {
	logger.logDebug( "createNeuroLinksFromSensorRegion" );

	NeuroLink *linkFeedForward = new ExcitatoryLink( link );
	src -> setFeedForwardLink( linkFeedForward );

	MindRegion::addNeuroLink( link , linkFeedForward );
}

NeuroPool *CortexRegion::getFeedForwardInputPool() {
	return( NULL );
}

