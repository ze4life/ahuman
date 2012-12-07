#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindConnectionLinkTypeDef::MindConnectionLinkTypeDef( MindConnectionTypeDef *p_connectionDef ) {
	connectionDef = p_connectionDef;
	back = true;
}

MindConnectionLinkTypeDef::~MindConnectionLinkTypeDef() {
}

void MindConnectionLinkTypeDef::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );
	neurotransmitter = xml.getAttribute( "nt" );
	srcConnector = xml.getAttribute( "src" );
	dstConnector = xml.getAttribute( "dst" );
	back = xml.getBooleanAttribute( "dst" , false );
}

bool MindConnectionLinkTypeDef::isBackward() {
	return( back );
}

bool MindConnectionLinkTypeDef::isExcitatory() {
	if( neurotransmitter.equals( "GLU" ) )
		return( true );
	return( false );
}

bool MindConnectionLinkTypeDef::isInhibitory() {
	if( neurotransmitter.equals( "GABA" ) )
		return( true );
	return( false );
}

bool MindConnectionLinkTypeDef::isModulatory() {
	if( isExcitatory() || isInhibitory() )
		return( false );
	return( true );
}

