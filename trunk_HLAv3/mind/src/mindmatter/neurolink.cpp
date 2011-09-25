#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLink::NeuroLink( MindRegionLink *p_regionLink ) {
	regionLink = p_regionLink;
	src = NULL;
	dst = NULL;
}

void NeuroLink::create( NeuroVector *p_src , NeuroPool *p_dst ) {
	src = p_src;
	dst = p_dst;

	// call final class
	createNeuroLink();
}

NeuroVector *NeuroLink::getSourceData() {
	return( src );
}
