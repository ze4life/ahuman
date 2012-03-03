#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegion::MindRegion( MindArea *p_area ) {
	attachLogger();

	area = p_area;

	regionLinkSet = NULL;
	poolSet = NULL;
	linkSet = NULL;
	location = NULL;
}

MindRegion::~MindRegion() {
}

void MindRegion::create( String p_id ) {
	id = p_id;
	regionLinkSet = new MindRegionLinkSet();

	// map region type
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();
	regionType = mm -> getRegionTypeByName( getRegionType() );
	ASSERTMSG( regionType != NULL , String( "Unknown region type name=" ) + getClass() );

	// call virtual
	createRegion();

	logger.logDebug( "create: region created - id=" + p_id + ", area=" + area -> getClass() );
}

void MindRegion::exit() {
	exitRegion();
}

void MindRegion::destroy() {
	destroyRegion();

	if( regionLinkSet != NULL ) {
		delete regionLinkSet;
		regionLinkSet = NULL;
	}
}

String MindRegion::getRegionId() {
	return( id );
}

String MindRegion::getFullRegionId() {
	return( area -> getId() + "." + id );
}

void MindRegion::addPrivateNeuroLink( NeuroLink *nt ) {
	// add link to set
	linkSet -> addSetItem( nt );
}

void MindRegion::sendMessage( MindMessage *msg ) {
	area -> sendMessage( msg );
}

NeuroLinkSource *MindRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	NeuroLinkSource *connector = sourceConnectorMap.get( entity );
	return( connector );
}

NeuroLinkTarget *MindRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	NeuroLinkTarget *connector = targetConnectorMap.get( entity );
	return( connector );
}

void MindRegion::addSourceEntity( String entity , NeuroLinkSource *connector ) {
	ASSERTMSG( sourceConnectorMap.get( entity ) == NULL , "Duplicate entity=" + entity + " in region id=" + id );
	// check metadata
	MindRegionConnector *connectorInfo = regionType -> getConnector( entity );
	ASSERTMSG( connectorInfo -> isSourceConnector() == true , "connector exists but is not source, entity=" + entity );
	sourceConnectorMap.add( entity , connector );
}

void MindRegion::addTargetEntity( String entity , NeuroLinkTarget *connector ) {
	ASSERTMSG( targetConnectorMap.get( entity ) == NULL , "Duplicate entity=" + entity + " in region id=" + id );
	// check metadata
	MindRegionConnector *connectorInfo = regionType -> getConnector( entity );
	ASSERTMSG( connectorInfo -> isSourceConnector() == false , "connector exists but is not target, entity=" + entity );
	targetConnectorMap.add( entity , connector );
}

