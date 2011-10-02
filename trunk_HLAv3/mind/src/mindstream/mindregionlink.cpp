#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionLink::MindRegionLink( MindAreaLink *p_areaLink ) {
	areaLink = p_areaLink;
	src = NULL;
	dst = NULL;
	links = new NeuroLinkSet();

	attachLogger();
}

MindRegion *MindRegionLink::getSrcRegion() {
	return( src );
}

MindRegion *MindRegionLink::getDstRegion() {
	return( dst );
}

void MindRegionLink::createRegionLink( MindNet *net , MindAreaLink *areaLink , MindRegion *srcRegion , MindRegion *dstRegion ) {
	src = srcRegion;
	dst = dstRegion;

	// create neuro links
}

void MindRegionLink::exitRegionLink() {
}

void MindRegionLink::destroyRegionLink() {
	delete links;
	links = NULL;
}

void MindRegionLink::addNeuroLink( NeuroLink *nt ) {
	links -> addSetItem( nt );
}

