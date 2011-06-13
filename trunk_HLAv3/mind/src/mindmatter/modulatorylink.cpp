#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ModulatoryLink::ModulatoryLink() {
	attachLogger();
}

void ModulatoryLink::sendData( neurovt *data , int size ) {
	logger.logDebug( "sendData" );
}
