#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitLinkTypeDef::MindCircuitLinkTypeDef() {
}

MindCircuitLinkTypeDef::~MindCircuitLinkTypeDef() {
}

void MindCircuitLinkTypeDef::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );
}

bool MindCircuitLinkTypeDef::isExcitatory() {
	return( true );
}

bool MindCircuitLinkTypeDef::isInhibitory() {
	return( false );
}

bool MindCircuitLinkTypeDef::isModulatory() {
	return( false );
}

