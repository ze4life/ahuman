#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionTypeDef::~MindRegionTypeDef() {
	connectorSet.destroy();
}

void MindRegionTypeDef::createFromXml( Xml xml ) {
	if( !xml.exists() )
		return;

	// attributes
	name = xml.getAttribute( "name" );

	// childs
	createConnectorSetFromXml( xml.getFirstChild( "MindRegionConnectorSet" ) );
}

void MindRegionTypeDef::createConnectorSetFromXml( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "MindRegionConnector" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindRegionConnector" ) ) {
		// construct MindArea from attributes
		MindRegionConnectorDef *connector = new MindRegionConnectorDef;
		connector -> createFromXml( xmlChild );

		String id = connector -> getId();
		ASSERTMSG( !id.isEmpty() , "region type connector is not well-defined: " + xmlChild.serialize() );

		// add to set and map
		connectorSet.add( connector );
		connectorMap.add( id , connector );
	}
}

String MindRegionTypeDef::getName() {
	return( name );
}

MindRegionConnectorDef *MindRegionTypeDef::getConnector( String p_id ) {
	MindRegionConnectorDef *connector = connectorMap.get( p_id );
	ASSERTMSG( connector != NULL , "unknown connector id=" + p_id );
	return( connector );
}
