#include <ah_mind.h>
#include <ah_mind_impl.h>

static int sequence_NL = 0;

/*#########################################################################*/
/*#########################################################################*/

NeuroLink::NeuroLink( NeuroLinkSource *src , NeuroLinkTarget *dst ) {
	region = NULL;
	source = src;
	target = dst;
	sizeX = 0;
	sizeY = 0;
}

void NeuroLink::createNeuroLink( NeuroLinkInfo *info ) {
}

NeuroLinkSource *NeuroLink::getSource() {
	return( source );
}

NeuroLinkTarget *NeuroLink::getTarget() {
	return( target );
}

void NeuroLink::createInternal( MindRegion *p_region ) {
	id = String( "NL" ) + ( ++sequence_NL );
	region = p_region;
}

void NeuroLink::create( MindConnectionLinkTypeDef *p_linkType , NeuroLinkSource *p_source , NeuroLinkTarget *p_target ) {
	id = String( "NL" ) + ( ++sequence_NL );

	linkType = p_linkType;
	source = p_source;
	target = p_target;

	// set sizes if not defined by MindCircuitLinkDef
	sizeX = source -> getSizeX();
	sizeY = source -> getSizeY();
}

String NeuroLink::getId() {
	return( id );
}

int NeuroLink::getSizeX() {
	return( sizeX );
}

int NeuroLink::getSizeY() {
	return( sizeY );
}

int NeuroLink::getSize() {
	return( sizeX * sizeY );
}
