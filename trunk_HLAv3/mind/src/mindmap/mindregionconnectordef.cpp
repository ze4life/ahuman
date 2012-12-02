#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionConnectorDef::MindRegionConnectorDef() {
	sourceConnector = true;
}

void MindRegionConnectorDef::createFromXml( Xml xml ) {
	// attributes
	id = xml.getAttribute( "id" );
	sourceConnector = xml.getBooleanAttribute( "source" );
}

String MindRegionConnectorDef::getId() {
	return( id );
}

bool MindRegionConnectorDef::isSourceConnector() {
	return( sourceConnector );
}

