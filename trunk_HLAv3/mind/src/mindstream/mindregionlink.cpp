#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionLink::MindRegionLink( MindAreaLink *p_areaLink ) {
	areaLink = p_areaLink;
	linkType = areaLink -> getLinkInfo() -> getLinkType();

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

void MindRegionLink::createRegionLink( MindNet *net , MindRegion *srcRegion , MindRegion *dstRegion ) {
	src = srcRegion;
	dst = dstRegion;

	// create neuro links
	MindNetInfo *netInfo = net -> getInfo();
	for( int k = 0; k < linkType -> getNeuroLinkCount(); k++ ) {
		NeuroLinkInfo *linkInfo = linkType -> getNeuroLinkInfo( k );
		NeuroLink *link = createNeuroLink( net , linkInfo );
		links -> addSetItem( link );
	}
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

	// check neurolink is required
	MindNetInfo *netInfo = net -> getInfo();
	NeuroLinkSource *srcData = srcRegion -> getNeuroLinkSource( netInfo , linkInfo );
	if( srcData == NULL )
		return( NULL );

	NeuroLinkTarget *dstData = dstRegion -> getNeuroLinkTarget( netInfo , linkInfo );
	if( dstData == NULL )
		return( NULL );

	NeuroLink *link = linkInfo -> createNeuroLink( this );
	srcData -> addNeuroLink( link );
	link -> create( srcData , dstData );

	logger.logInfo( "createNeuroLink: NeuroLink created name=" + linkInfo -> getName() + ", type=" + linkInfo -> getTypeName() + ", id=" + link -> getId() );
	return( link );
}
