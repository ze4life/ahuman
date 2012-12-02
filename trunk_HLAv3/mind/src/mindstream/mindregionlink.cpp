#include <ah_mind.h>
#include <ah_mind_impl.h>

static int lastRegionId = 0;

/*#########################################################################*/
/*#########################################################################*/

MindRegionLink::MindRegionLink( MindAreaLink *p_areaLink ) {
	attachLogger();

	areaLink = p_areaLink;

	src = NULL;
	dst = NULL;
	links = new NeuroLinkSet();
}

MindRegion *MindRegionLink::getSrcRegion() {
	return( src );
}

MindRegion *MindRegionLink::getDstRegion() {
	return( dst );
}

void MindRegionLink::createRegionLink( MindRegion *srcRegion , MindRegion *dstRegion ) {
	id = String( "RL" ) + ++lastRegionId;
	src = srcRegion;
	dst = dstRegion;

	logger.logInfo( "createRegionLink: region link created id=" + id + " from region id=" + srcRegion -> getFullRegionId() + " to region id=" + dstRegion -> getFullRegionId()  );
}

void MindRegionLink::exitRegionLink() {
}

void MindRegionLink::destroyRegionLink() {
	delete links;
	links = NULL;
}

NeuroLink *MindRegionLink::createNeuroLink() {
	String sourceEntity = "default";
	String targetEntity = "default";

	// check neurolink is required
	NeuroLinkSource *srcData = src -> getNeuroLinkSource( sourceEntity , linkType );
	if( srcData == NULL )
		return( NULL );

	NeuroLinkTarget *dstData = dst -> getNeuroLinkTarget( targetEntity , linkType );
	if( dstData == NULL )
		return( NULL );

	MindService *service = MindService::getService();
	NeuroLink *link = service -> createNeuroLink( this , srcData , dstData );

	// add to link source
	srcData -> addNeuroLink( link );

	return( link );
}
