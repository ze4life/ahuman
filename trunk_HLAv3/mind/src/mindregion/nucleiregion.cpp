#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NucleiRegion::NucleiRegion() {
	attachLogger();
}

void NucleiRegion::createRegion() {
}

void NucleiRegion::exitRegion() {
}

void NucleiRegion::destroyRegion() {
}

// link creation
void NucleiRegion::createNeuroLinks( MindRegionLink *link , MindRegion *dst ) {
	dst -> createNeuroLinksFromNucleiRegion( link , this );
}

void NucleiRegion::createNeuroLinksFromCortexRegion( MindRegionLink *link , CortexRegion *src ) {
	logger.logDebug( "createNeuroLinksFromCortexRegion" );
}

void NucleiRegion::createNeuroLinksFromNucleiRegion( MindRegionLink *link , NucleiRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNucleiRegion" );
}

void NucleiRegion::createNeuroLinksFromNerveRegion( MindRegionLink *link , NerveRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNerveRegion" );
}

void NucleiRegion::createNeuroLinksFromSensorRegion( MindRegionLink *link , MindSensor *src ) {
	logger.logDebug( "createNeuroLinksFromSensorRegion" );
}

