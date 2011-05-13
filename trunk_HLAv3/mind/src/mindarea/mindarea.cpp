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
	regionSet -> exitRegionSet();
	regionLinkSet -> exitRegionLinkSet();
}

void MindArea::destroy() {
	regionSet -> destroyRegionSet();
	regionLinkSet -> destroyRegionLinkSet();
	delete regionSet;
	regionSet = NULL;
	delete regionLinkSet;
	regionLinkSet = NULL;
}
