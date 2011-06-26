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
void NucleiRegion::createNeuroLinks( MindRegion *dst ) {
	dst -> createNeuroLinksFromNucleiRegion( this );
}

void NucleiRegion::createNeuroLinksFromCortexRegion( CortexRegion *src ) {
	logger.logDebug( "createNeuroLinksFromCortexRegion" );
}

void NucleiRegion::createNeuroLinksFromNucleiRegion( NucleiRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNucleiRegion" );
}

void NucleiRegion::createNeuroLinksFromNerveRegion( NerveRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNerveRegion" );
}

void NucleiRegion::createNeuroLinksFromSensorRegion( MindSensor *src ) {
	logger.logDebug( "createNeuroLinksFromSensorRegion" );
}

