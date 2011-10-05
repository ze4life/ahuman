#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ModulatoryLink::ModulatoryLink( MindRegionLink *p_regionLink ) : NeuroLink( p_regionLink ) {
	attachLogger();
}

void ModulatoryLink::apply( NeuroVector *srcData ) {
}

