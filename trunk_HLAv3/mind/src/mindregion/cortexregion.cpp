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
void CortexRegion::createNeuroLinks( MindRegion *dst ) {
	dst -> createNeuroLinksFromCortexRegion( this );
}

void CortexRegion::createNeuroLinksFromCortexRegion( CortexRegion *src ) {
	logger.logDebug( "createNeuroLinksFromCortexRegion" );
}

void CortexRegion::createNeuroLinksFromNucleiRegion( NucleiRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNucleiRegion" );
}

void CortexRegion::createNeuroLinksFromNerveRegion( NerveRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNerveRegion" );
}

void CortexRegion::createNeuroLinksFromSensorRegion( MindSensor *src ) {
	logger.logDebug( "createNeuroLinksFromSensorRegion" );
}

