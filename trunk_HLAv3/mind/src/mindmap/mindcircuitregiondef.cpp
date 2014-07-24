#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitRegionDef::MindCircuitRegionDef( MindCircuitDef *p_circuit ) {
	circuit = p_circuit;
}

void MindCircuitRegionDef::createFromXml( Xml xml ) {
	id = xml.getAttribute( "id" );
	role = xml.getAttribute( "role" );
}

