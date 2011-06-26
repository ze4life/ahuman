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
void NerveRegion::createNeuroLinks( MindRegion *dst ) {
	dst -> createNeuroLinksFromNerveRegion( this );
}

void NerveRegion::createNeuroLinksFromCortexRegion( CortexRegion *src ) {
	logger.logDebug( "createNeuroLinksFromCortexRegion" );
}

void NerveRegion::createNeuroLinksFromNucleiRegion( NucleiRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNucleiRegion" );
}

void NerveRegion::createNeuroLinksFromNerveRegion( NerveRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNerveRegion" );
}

void NerveRegion::createNeuroLinksFromSensorRegion( MindSensor *src ) {
	logger.logDebug( "createNeuroLinksFromSensorRegion" );
}

