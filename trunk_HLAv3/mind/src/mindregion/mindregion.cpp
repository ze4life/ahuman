#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegion::MindRegion( MindArea *p_area ) {
	attachLogger();

	area = p_area;

	regionType = NULL;
	regionLinkSet = new MindRegionLinkSet();
	poolSet = NULL;
	linkSet = NULL;
	location = NULL;
}

MindRegion::~MindRegion() {
}

void MindRegion::exit() {
	exitRegion();
}

void MindRegion::destroy() {
	destroyRegion();

	delete regionLinkSet;
	regionLinkSet = NULL;
}

String MindRegion::getFullRegionId() {
	return( area -> getId() + "." + id );
}

void MindRegion::addPrivateNeuroLink( NeuroLink *nt ) {
	// add link to set
	linkSet -> addSetItem( nt );
}

NeuroLinkSource *MindRegion::getNeuroLinkSource( String entity ) {
	NeuroLinkSource *connector = sourceConnectorMap.get( entity );
	return( connector );
}

NeuroLinkTarget *MindRegion::getNeuroLinkTarget( String entity ) {
	NeuroLinkTarget *connector = targetConnectorMap.get( entity );
	return( connector );
}

void MindRegion::addSourceEntity( String entity , NeuroLinkSource *connector ) {
	ASSERTMSG( sourceConnectorMap.get( entity ) == NULL , "Duplicate entity=" + entity + " in region id=" + id );
	// check metadata
	MindRegionConnectorDef *connectorInfo = regionType -> getConnector( entity );
	sourceConnectorMap.add( entity , connector );
}

void MindRegion::addTargetEntity( String entity , NeuroLinkTarget *connector ) {
	ASSERTMSG( targetConnectorMap.get( entity ) == NULL , "Duplicate entity=" + entity + " in region id=" + id );
	// check metadata
	MindRegionConnectorDef *connectorInfo = regionType -> getConnector( entity );
	targetConnectorMap.add( entity , connector );
}

void MindRegion::sendMessage( MindMessage *msg ) {
}

void MindRegion::addRegionLink( MindRegionLink *link ) {
	regionLinkSet -> addSetItem( link );
}

bool MindRegion::checkLinkedTo( MindRegion *dst ) {
	for( int k = 0; k < regionLinkSet -> getCount(); k++ ) {
		MindRegionLink *link = regionLinkSet -> getSetItem( k );
		if( link -> getSrcRegion() == this && link -> getDstRegion() == dst )
			return( true );
	}

	return( false );
}
