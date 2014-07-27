#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindGlobalCircuitRegionDef::MindGlobalCircuitRegionDef( MindGlobalCircuitDef *p_circuit ) {
	circuit = p_circuit;
}

void MindGlobalCircuitRegionDef::createFromXml( Xml xml ) {
	id = xml.getAttribute( "id" );
	role = xml.getAttribute( "role" );
}

