#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionConnectorDef::MindRegionConnectorDef() {
}

void MindRegionConnectorDef::createFromXml( Xml xml ) {
	// attributes
	id = xml.getAttribute( "id" );
	type = xml.getAttribute( "type" );
}
