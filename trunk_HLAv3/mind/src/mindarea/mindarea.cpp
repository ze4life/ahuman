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

void MindArea::configure( MindAreaInfo *p_info ) {
	info = p_info;
}

MindAreaInfo *MindArea::getMindAreaInfo() {
	return( info );
}

void MindArea::create() {
	regionSet = new MindRegionSet;
	regionLinkSet = new MindRegionLinkSet;
	areaMasterLinkSet = new MindAreaLinkSet;
	areaSlaveLinkSet = new MindAreaLinkSet;

	MessagingService *ms = MessagingService::getService();
	iosession = ms -> createSession();
	iopub = ms -> createPublisher( iosession , getClass() ,  getClass() , "MindMessage" );
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

MindAreaNet *MindArea::getMindNet( String net ) {
	return( netSet.get( net ) );
}

MindAreaNet *MindArea::createAreaNetwork( String name ) {
	MindService *ms = MindService::getService();
	MindNet *net = ms -> getMindNet( name );
	MindAreaNetInfo *netInfo = getMindAreaNetInfo( name );

	// check that network is available and registered in given area
	if( net == NULL || netInfo == NULL )
		return( NULL );

	// create mind area network
	MindAreaNet *areaNet = new MindAreaNet( this , net , netInfo );

	// add network to area network set
	netSet.add( name , areaNet );
	return( areaNet );
}

void MindArea::addMasterLink( MindAreaLink *link ) {
	areaMasterLinkSet -> addSetItem( link );
}

void MindArea::addSlaveLink( MindAreaLink *link ) {
	areaSlaveLinkSet -> addSetItem( link );
}

MindAreaNetInfo *MindArea::getMindAreaNetInfo( String netName ) {
	return( info -> getNetInfo( netName ) );
}

