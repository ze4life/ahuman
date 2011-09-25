#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ExcitatoryLink::ExcitatoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void ExcitatoryLink::createNeuroLink() {
	logger.logDebug( "createNeuroLink" );
}

void ExcitatoryLink::projectData( neurovt *data , int size ) {
	logger.logDebug( "projectData" );
}
