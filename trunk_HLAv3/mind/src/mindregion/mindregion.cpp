#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegion::MindRegion() {
	attachLogger();

	area = NULL;
	regionLinkSet = NULL;
	poolSet = NULL;
	linkSet = NULL;
	location = NULL;
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
}

String MindRegion::getRegionId() {
	return( id );
}

void MindRegion::addPrivateNeuroLink( NeuroLink *nt ) {
	// add link to set
	linkSet -> addSetItem( nt );
}

void MindRegion::sendMessage( MindMessage *msg ) {
	area -> sendMessage( msg );
}
