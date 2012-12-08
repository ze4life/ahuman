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
	type = xml.getAttribute( "type" );
	neurotransmitter = xml.getAttribute( "nt" );
	srcConnector = xml.getAttribute( "src" );
	dstConnector = xml.getAttribute( "dst" );
	back = xml.getBooleanAttribute( "back" , false );
}

bool MindConnectionLinkTypeDef::isBackward() {
	return( back );
}
