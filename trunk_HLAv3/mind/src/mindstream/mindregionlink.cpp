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
	links.destroy();
}

void MindRegionLink::createNeuroLinks( MindCircuitConnectionDef *linkDef ) {
	connectionDef = linkDef;

	MindService *service = MindService::getService();
	String linkType = linkDef -> getTypeName();
	MindMap *map = service -> getMindMap();
	MindCircuitConnectionTypeDef *connectionTypeDef = map -> getConnectionTypeDefByName( linkType );

	// create links
	ClassList<MindCircuitLinkTypeDef>& linkDefs = connectionTypeDef -> getLinks();
	for( int k = 0; k < links.count(); k++ ) {
		MindCircuitLinkTypeDef *linkDef = linkDefs.get( k );
		NeuroLink *link = createNeuroLink( linkDef );
		links.add( link );
	}
}

NeuroLink *MindRegionLink::createNeuroLink( MindCircuitLinkTypeDef *linkDef ) {
	String sourceEntity = linkDef -> getSrcConnector();
	String targetEntity = linkDef -> getDstConnector();

	MindRegion *xsrc = src;
	MindRegion *xdst = dst;
	if( linkDef -> isBackward() ) {
		xsrc = dst;
		xdst = src;
	}

	// check connectors
	NeuroLinkSource *srcData = xsrc -> getNeuroLinkSource( sourceEntity );
	if( srcData == NULL )
		return( NULL );

	NeuroLinkTarget *dstData = xdst -> getNeuroLinkTarget( targetEntity );
	if( dstData == NULL )
		return( NULL );

	// check neurotransmitter
	MindService *service = MindService::getService();
	NeuroLink *link = NULL;
	if( linkDef -> isExcitatory() )
		link = service -> createExcitatoryLink( this );
	else if( linkDef -> isInhibitory() )
		link = service -> createInhibitoryLink( this );
	else
		link = service -> createModulatoryLink( this );

	link -> create( linkDef , srcData , dstData );

	// add to link source
	srcData -> addNeuroLink( link );

	return( link );
}
