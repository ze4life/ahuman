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

MindRegionSet *MindArea::getRegionSet() {
	return( regionSet );
}

String MindArea::addRegion( String group , String id , MindRegion *region ) {
	// generate id
	String regionId = group + "." + id;

	// check exists
	ASSERTMSG( regionSet -> getSetItemById( regionId ) == NULL , "region id=" + regionId + " already exists" );

	// create region internals
	region -> create( this , regionId );

	regionSet -> addSetItem( region );
	return( regionId );
}

MindRegion *MindArea::getRegion( String group , String id ) {
	String regionId = group + "." + id;
	return( regionSet -> getSetItemById( regionId ) );
}

void MindArea::sendMessage( MindMessage *msg ) {
	iopub -> publish( iosession , msg );
}

void MindArea::getNetworks( StringList& list ) {
	for( int k = 0; k < nets.count(); k++ ) {
		String key = nets.getKeyByIndex( k );
		list.add( key );
	}
}

MindAreaNet *MindArea::getMindNet( String net ) {
	return( nets.get( net ) );
}

void MindArea::addNet( MindAreaNet *areaNet ) {
	MindNet *net = areaNet -> getNet();
	nets.add( net -> getName() , areaNet );
}

void MindArea::addMasterLink( MindAreaLink *link ) {
	areaMasterLinkSet -> addSetItem( link );
}

void MindArea::addSlaveLink( MindAreaLink *link ) {
	areaSlaveLinkSet -> addSetItem( link );
}
