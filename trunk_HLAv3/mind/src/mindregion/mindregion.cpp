#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegion::MindRegion() {
	area = NULL;
	net = NULL;
	regionLinkSet = NULL;
}

MindRegion::~MindRegion() {
}

void MindRegion::create( MindArea *p_area , String p_id ) {
	area = p_area;
	id = p_id;

	regionLinkSet = new MindRegionLinkSet();
}

void MindRegion::exit() {
	exitRegion();
}

void MindRegion::destroy() {
	destroyRegion();

	delete regionLinkSet;
	if( net != NULL )
		delete net;
}

String MindRegion::getRegionId() {
	return( id );
}

void MindRegion::sendOutputData( neurovt *data , int size ) {
}

