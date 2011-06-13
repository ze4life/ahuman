#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindArea::MindArea() {
	info = NULL;
	regionSet = NULL;
	regionLinkSet = NULL;
	areaLinkSet = NULL;
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
	areaLinkSet = new MindAreaLinkSet;
}

// mind area links
MindAreaLink *MindArea::createMindLink( MindArea *slaveArea , MindAreaLinkInfo *linkInfo , MessageSession *session ) {
	// create link
	MindAreaLink *link = new MindAreaLink( linkInfo );
	link -> open( session );

	initMasterLinkToArea( link , linkInfo -> getSlaveAreaId() );
	slaveArea -> initSlaveLinkToArea( link , linkInfo -> getMasterAreaId() );

	areaLinkSet -> addSetItem( link );
	return( link );
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
	if( areaLinkSet != NULL ) {
		delete areaLinkSet;
		areaLinkSet = NULL;
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

void MindArea::sendOutputData( MindRegion *region , neurovt *data , int size ) {
	// by efferent links
	areaLinkSet -> sendOutputData( region , data , size );
}

