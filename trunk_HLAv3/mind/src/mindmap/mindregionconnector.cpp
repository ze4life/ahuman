#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionConnector::MindRegionConnector() {
	sourceConnector = true;
}

void MindRegionConnector::createFromXml( Xml xml ) {
	// attributes
	id = xml.getAttribute( "id" );
	sourceConnector = xml.getBooleanAttribute( "source" );
}

String MindRegionConnector::getId() {
	return( id );
}

bool MindRegionConnector::isSourceConnector() {
	return( sourceConnector );
}

