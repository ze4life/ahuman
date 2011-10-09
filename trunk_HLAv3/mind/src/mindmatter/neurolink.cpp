#include <ah_mind.h>
#include <ah_mind_impl.h>

static int sequence_NL = 0;

/*#########################################################################*/
/*#########################################################################*/

NeuroLink::NeuroLink( MindRegionLink *p_regionLink ) {
	regionLink = p_regionLink;

	linkInfo = NULL;
	target = NULL;
}

NeuroLinkSource *NeuroLink::getSource() {
	return( source );
}

NeuroLinkTarget *NeuroLink::getTarget() {
	return( target );
}

void NeuroLink::setNeuroLinkInfo( NeuroLinkInfo *p_linkInfo ) {
	linkInfo = p_linkInfo;
}

void NeuroLink::setTransmitter( String p_transmitter ) {
	transmitter = p_transmitter;
}

void NeuroLink::create( NeuroLinkSource *p_source , NeuroLinkTarget *p_target ) {
	id = String( "NL" ) + ( ++sequence_NL );
	source = p_source;
	target = p_target;
}

String NeuroLink::getId() {
	return( id );
}

