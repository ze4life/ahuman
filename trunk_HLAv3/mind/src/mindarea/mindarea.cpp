#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindArea::MindArea() {
	info = NULL;
	regionSet = new MindRegionSet;
	regionLinkSet = new MindRegionLinkSet;
	areaMasterLinkSet = new MindAreaLinkSet;
	areaSlaveLinkSet = new MindAreaLinkSet;
}

MindArea::~MindArea() {
	delete regionSet;
	delete regionLinkSet;
	delete areaMasterLinkSet;
	delete areaSlaveLinkSet;
}

void MindArea::configure( MindAreaDef *p_info ) {
	info = p_info;
	areaId = info -> getAreaId();
}

MindAreaDef *MindArea::getMindAreaDef() {
	return( info );
}

void MindArea::createRegions( MindTarget *target ) {
	// create regions
	ClassList<MindRegionDef>& regionDefs = info -> getRegions();
	for( int k = 0; k < regionDefs.count(); k++ )
		createRegion( target , regionDefs.get( k ) );
}

void MindArea::createRegion( MindTarget *target , MindRegionDef *regionDef ) {
	MindService *ms = MindService::getService();
	MindRegionTypeDef *typeDef = regionDef -> getType();

	String type = typeDef -> getName();

	// create region depending from type
	MindRegion *region = NULL;
	MindRegionInfo info;
	info.setId( regionDef -> getName() );
	info.setType( regionDef -> getType() );
	region = ms -> createRegion( type , this , &info );

	if( region == NULL )
		return;

	// add to collections
	regionSet -> addSetItem( region );
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
	if( regionSet != NULL )
		regionSet -> destroyRegionSet();
	if( regionLinkSet != NULL )
		regionLinkSet -> destroyRegionLinkSet();
}

String MindArea::getId() {
	return( info -> getAreaId() );
}

MindRegionSet *MindArea::getRegionSet() {
	return( regionSet );
}

MindRegion *MindArea::getRegion( String group , String id ) {
	String regionId = group + "." + id;
	return( regionSet -> getSetItemById( regionId ) );
}

void MindArea::addMasterLink( MindAreaLink *link ) {
	areaMasterLinkSet -> addSetItem( link );
}

void MindArea::addSlaveLink( MindAreaLink *link ) {
	areaSlaveLinkSet -> addSetItem( link );
}
