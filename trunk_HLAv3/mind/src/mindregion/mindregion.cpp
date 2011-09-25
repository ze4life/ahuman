#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegion::MindRegion() {
	attachLogger();

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
	logger.logDebug( "create: region created - id=" + p_id + ", area=" + area -> getClass() );

	// call virtual
	createRegion();
}

void MindRegion::exit() {
	exitRegion();
}

void MindRegion::destroy() {
	destroyRegion();

	if( regionLinkSet != NULL ) {
		delete regionLinkSet;
		regionLinkSet = NULL;
	}
	if( net != NULL ) {
		delete net;
		net = NULL;
	}
}

String MindRegion::getRegionId() {
	return( id );
}

void MindRegion::addNeuroLink( MindRegionLink *link , NeuroLink *nt ) {
	// add link to set
	link -> addNeuroLink( nt );
}

void MindRegion::sendMessage( MindMessage *msg ) {
	area -> sendMessage( msg );
}
