#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitLinkTypeDef::MindCircuitLinkTypeDef( MindCircuitConnectionTypeDef *p_connectionDef ) {
	connectionDef = p_connectionDef;
	back = true;
}

MindCircuitLinkTypeDef::~MindCircuitLinkTypeDef() {
}

void MindCircuitLinkTypeDef::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );
	neurotransmitter = xml.getAttribute( "nt" );
	srcConnector = xml.getAttribute( "src" );
	dstConnector = xml.getAttribute( "dst" );
	back = xml.getBooleanAttribute( "dst" , false );
}

bool MindCircuitLinkTypeDef::isBackward() {
	return( back );
}

bool MindCircuitLinkTypeDef::isExcitatory() {
	if( neurotransmitter.equals( "GLU" ) )
		return( true );
	return( false );
}

bool MindCircuitLinkTypeDef::isInhibitory() {
	if( neurotransmitter.equals( "GABA" ) )
		return( true );
	return( false );
}

bool MindCircuitLinkTypeDef::isModulatory() {
	if( isExcitatory() || isInhibitory() )
		return( false );
	return( true );
}

