#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ModulatoryLink::ModulatoryLink() {
	attachLogger();
}

void ModulatoryLink::createNeuroLink( MindRegionLink *regionLink ) {
	logger.logDebug( "createNeuroLink" );
}

void ModulatoryLink::sendData( neurovt *data , int size ) {
	logger.logDebug( "sendData" );
}
