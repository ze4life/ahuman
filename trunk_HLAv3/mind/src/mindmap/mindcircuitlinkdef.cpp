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
	srcArea = xml.getAttribute( "srcArea" , "" );
	srcRegion = xml.getAttribute( "srcRegion" , "" );
	dstArea = xml.getAttribute( "dstArea" , "" );
	dstRegion = xml.getAttribute( "dstRegion" , "" );
}

