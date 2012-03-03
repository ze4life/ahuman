#include <ah_mind.h>
#include <ah_mind_impl.h>

static int lastRegionId = 0;

/*#########################################################################*/
/*#########################################################################*/

MindRegionLink::MindRegionLink( MindAreaLink *p_areaLink ) {
	attachLogger();

	areaLink = p_areaLink;
	linkType = areaLink -> getLinkInfo() -> getLinkType();

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

void MindRegionLink::createRegionLink( MindNet *net , MindRegion *srcRegion , MindRegion *dstRegion ) {
	id = String( "RL" ) + ++lastRegionId;
	src = srcRegion;
	dst = dstRegion;

	// create neuro links
	MindNetInfo *netInfo = net -> getInfo();
	for( int k = 0; k < linkType -> getNeuroLinkCount(); k++ ) {
		NeuroLinkInfo *linkInfo = linkType -> getNeuroLinkInfo( k );
		NeuroLink *link = createNeuroLink( net , linkInfo );

		if( link != NULL )
			links -> addSetItem( link );
	}
	logger.logInfo( "createRegionLink: region link created id=" + id + " from region id=" + srcRegion -> getFullRegionId() + " to region id=" + dstRegion -> getFullRegionId()  );
}

void MindRegionLink::exitRegionLink() {
}

void MindRegionLink::destroyRegionLink() {
	delete links;
	links = NULL;
}

NeuroLink *MindRegionLink::createNeuroLink( MindNet *net , NeuroLinkInfo *linkInfo ) {
	bool forward = linkInfo -> getForward();
	MindRegion *srcRegion = ( forward )? getSrcRegion() : getDstRegion();
	MindRegion *dstRegion = ( forward )? getDstRegion() : getSrcRegion();
	String sourceEntity = ( forward )? linkInfo -> getMasterEntity() : linkInfo -> getSlaveEntity();
	String targetEntity = ( forward )? linkInfo -> getSlaveEntity() : linkInfo -> getMasterEntity();

	// check neurolink is required
	MindNetInfo *netInfo = net -> getInfo();
	NeuroLinkSource *srcData = srcRegion -> getNeuroLinkSource( sourceEntity , netInfo , linkInfo );
	if( srcData == NULL )
		return( NULL );

	NeuroLinkTarget *dstData = dstRegion -> getNeuroLinkTarget( targetEntity , netInfo , linkInfo );
	if( dstData == NULL )
		return( NULL );

	NeuroLink *link = linkInfo -> createNeuroLink( this , srcData , dstData );

	// add to link source
	srcData -> addNeuroLink( link );

	return( link );
}
