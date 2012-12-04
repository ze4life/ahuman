#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitConnectionTypeDef::MindCircuitConnectionTypeDef() {
}

MindCircuitConnectionTypeDef::~MindCircuitConnectionTypeDef() {
}

void MindCircuitConnectionTypeDef::createFromXml( Xml xml ) {
	// attributes
	name = xml.getAttribute( "name" );
}

bool MindCircuitConnectionTypeDef::isExcitatory() {
	return( true );
}

bool MindCircuitConnectionTypeDef::isInhibitory() {
	return( false );
}

bool MindCircuitConnectionTypeDef::isModulatory() {
	return( false );
}

