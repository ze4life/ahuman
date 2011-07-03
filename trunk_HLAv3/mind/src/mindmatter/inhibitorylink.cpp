#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

InhibitoryLink::InhibitoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void InhibitoryLink::createNeuroLink( MindRegionLink *regionLink ) {
	logger.logDebug( "createNeuroLink" );
}

void InhibitoryLink::projectData( neurovt *data , int size ) {
	logger.logDebug( "projectData" );
}
