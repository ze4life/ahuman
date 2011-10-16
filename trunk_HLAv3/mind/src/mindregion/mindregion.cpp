#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegion::MindRegion( MindArea *p_area ) {
	attachLogger();

	area = p_area;

	regionLinkSet = NULL;
	poolSet = NULL;
	linkSet = NULL;
	location = NULL;
}

MindRegion::~MindRegion() {
}

void MindRegion::create( String p_id ) {
	regionLinkSet = new MindRegionLinkSet();

	// call virtual
	createRegion();

	logger.logDebug( "create: region created - id=" + p_id + ", area=" + area -> getClass() );
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
