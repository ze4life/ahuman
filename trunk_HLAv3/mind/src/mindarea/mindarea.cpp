#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindArea::MindArea() {
	info = NULL;
	regionSet = NULL;
	regionLinkSet = NULL;
	areaMasterLinkSet = NULL;
	areaSlaveLinkSet = NULL;

	iosession = NULL;
	iopub = NULL;
}

MindArea::~MindArea() {
}

void MindArea::configure( MindAreaDef *p_info ) {
	info = p_info;
	areaId = info -> getAreaId();
}

MindAreaDef *MindArea::getMindAreaDef() {
	return( info );
}

void MindArea::create( MindTarget *target ) {
	regionSet = new MindRegionSet;
	regionLinkSet = new MindRegionLinkSet;
	areaMasterLinkSet = new MindAreaLinkSet;
	areaSlaveLinkSet = new MindAreaLinkSet;

	MessagingService *ms = MessagingService::getService();
	iosession = ms -> createSession();

	String channel = info -> getChannelId();
	iopub = ms -> createPublisher( iosession , channel ,  getClass() , "MindMessage" );

	// create regions
}

void MindArea::wakeupArea( MindActiveMemory *activeMemory ) {
}

void MindArea::suspendArea() {
}

void MindArea::exit() {
	if( regionSet != NULL )
		regionSet -> exitRegionSet();
	if( regionLinkSet != NULL )
		regionLinkSet -> exitRegionLinkSet();
}

void MindArea::destroy() {
	if( regionSet != NULL ) {
		regionSet -> destroyRegionSet();
		delete regionSet;
		regionSet = NULL;
	}
	if( regionLinkSet != NULL ) {
		regionLinkSet -> destroyRegionLinkSet();
		delete regionLinkSet;
		regionLinkSet = NULL;
	}
	if( areaMasterLinkSet != NULL ) {
		delete areaMasterLinkSet;
		areaMasterLinkSet = NULL;
	}
	if( areaSlaveLinkSet != NULL ) {
		delete areaSlaveLinkSet;
		areaSlaveLinkSet = NULL;
	}
}

String MindArea::getId() {
	return( info -> getAreaId() );
}

MindRegionSet *MindArea::getRegionSet() {
	return( regionSet );
}

void MindArea::addRegion( MindRegion *region ) {
	regionSet -> addSetItem( region );
}

MindRegion *MindArea::getRegion( String group , String id ) {
	String regionId = group + "." + id;
	return( regionSet -> getSetItemById( regionId ) );
}

void MindArea::sendMessage( MindMessage *msg ) {
	iopub -> publish( iosession , msg );
}

void MindArea::addMasterLink( MindAreaLink *link ) {
	areaMasterLinkSet -> addSetItem( link );
}

void MindArea::addSlaveLink( MindAreaLink *link ) {
	areaSlaveLinkSet -> addSetItem( link );
}
