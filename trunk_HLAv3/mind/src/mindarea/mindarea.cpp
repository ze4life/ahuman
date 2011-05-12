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

void MindArea::configureArea( MindAreaInfo *p_info ) {
	info = p_info;
}

MindAreaInfo *MindArea::getMindAreaInfo() {
	return( info );
}

void MindArea::createArea() {
	regionSet = new MindRegionSet;
	regionLinkSet = new MindRegionLinkSet;
}

void MindArea::exitArea() {
	regionSet -> exitRegionSet();
	regionLinkSet -> exitRegionLinkSet();
}

void MindArea::destroyArea() {
	regionSet -> destroyRegionSet();
	regionLinkSet -> destroyRegionLinkSet();
	delete regionSet;
	regionSet = NULL;
	delete regionLinkSet;
	regionLinkSet = NULL;
}
