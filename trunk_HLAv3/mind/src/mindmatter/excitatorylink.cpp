#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ExcitatoryLink::ExcitatoryLink() {
	attachLogger();
}

void ExcitatoryLink::createNeuroLink( MindRegionLink *regionLink ) {
	logger.logDebug( "createNeuroLink" );
}

void ExcitatoryLink::sendData( neurovt *data , int size ) {
	logger.logDebug( "sendData" );
}
