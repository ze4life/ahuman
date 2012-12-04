#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitConnectionDef::MindCircuitConnectionDef( MindCircuitDef *p_circuit ) {
	attachLogger();

	circuitInfo = p_circuit;
}

void MindCircuitConnectionDef::createFromXml( Xml xml ) {
	// attributes are properties
	typeName = xml.getAttribute( "type" );
	srcRegion = xml.getAttribute( "src" );
	dstRegion = xml.getAttribute( "dst" );
}

