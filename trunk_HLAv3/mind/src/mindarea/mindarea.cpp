#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindArea::MindArea() {
	info = NULL;
	regionSet = NULL;
	regionLinkSet = NULL;
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
}

MindRegionSet *MindArea::getRegionSet() {
	return( regionSet );
}

MindRegion *MindArea::openRegion( String group , String id ) {
	// generate id
	String regionId = group + "." + id;

	// check exists
	MindRegion *region = regionSet -> getSetItemById( regionId );
	if( region != NULL )
		return( region );

	// create region - delegate to specific area
	region = createGroupRegion( group );
	region -> create( this , regionId );

	regionSet -> addSetItem( region );
	return( region );
}

