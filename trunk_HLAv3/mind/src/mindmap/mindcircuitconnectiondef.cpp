#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitLinkDef::MindCircuitLinkDef( MindCircuitDef *p_circuit ) {
	attachLogger();

	circuitInfo = p_circuit;
}

void MindCircuitLinkDef::createFromXml( Xml xml ) {
	// attributes are properties
	typeName = xml.getAttribute( "type" );
	srcRegion = xml.getAttribute( "src" );
	dstRegion = xml.getAttribute( "dst" );
}

