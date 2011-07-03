#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NerveRegion::NerveRegion() {
	attachLogger();
}

void NerveRegion::createRegion() {
}

void NerveRegion::exitRegion() {
}

void NerveRegion::destroyRegion() {
}

// link creation
void NerveRegion::createNeuroLinks( MindRegionLink *link , MindRegion *dst ) {
	dst -> createNeuroLinksFromNerveRegion( link , this );
}

void NerveRegion::createNeuroLinksFromCortexRegion( MindRegionLink *link , CortexRegion *src ) {
	logger.logDebug( "createNeuroLinksFromCortexRegion" );
}

void NerveRegion::createNeuroLinksFromNucleiRegion( MindRegionLink *link , NucleiRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNucleiRegion" );
}

void NerveRegion::createNeuroLinksFromNerveRegion( MindRegionLink *link , NerveRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNerveRegion" );
}

void NerveRegion::createNeuroLinksFromSensorRegion( MindRegionLink *link , MindSensor *src ) {
	logger.logDebug( "createNeuroLinksFromSensorRegion" );
}

