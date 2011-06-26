#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

InhibitoryLink::InhibitoryLink() {
	attachLogger();
}

void InhibitoryLink::createNeuroLink( MindRegionLink *regionLink ) {
	logger.logDebug( "createNeuroLink" );
}

void InhibitoryLink::sendData( neurovt *data , int size ) {
	logger.logDebug( "sendData" );
}
