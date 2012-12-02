#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionTypeDef::~MindRegionTypeDef() {
	connectorSet.destroy();
	linkSet.destroy();
}

void MindRegionTypeDef::createFromXml( Xml xml ) {
	if( !xml.exists() )
		return;

	// attributes
	name = xml.getAttribute( "name" );

	// childs
	createConnectorSetFromXml( xml.getFirstChild( "MindRegionConnectorSet" ) );
	createLinkSetFromXml( xml.getFirstChild( "MindRegionInternalLinkSet" ) );
}

void MindRegionTypeDef::createConnectorSetFromXml( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "MindRegionConnector" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindRegionConnector" ) ) {
		// construct MindArea from attributes
		MindRegionConnector *connector = new MindRegionConnector;
		connector -> createFromXml( xmlChild );

		String id = connector -> getId();
		ASSERTMSG( !id.isEmpty() , "region type connector is not well-defined: " + xmlChild.serialize() );

		// add to set and map
		connectorSet.add( connector );
		connectorMap.add( id , connector );
	}
}

void MindRegionTypeDef::createLinkSetFromXml( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "NeuroLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "NeuroLink" ) ) {
		// construct MindArea from attributes
		MindCircuitLinkDef *info = new MindCircuitLinkDef( this );
		info -> createFromXml( xmlChild );

		String id = info -> getId();
		ASSERTMSG( !id.isEmpty() , "region type link is not well-defined: " + xmlChild.serialize() );

		// add to set and map
		linkSet.add( info );
		linkMap.add( id , info );
	}
}

String MindRegionTypeDef::getName() {
	return( name );
}

MindRegionConnector *MindRegionTypeDef::getConnector( String p_id ) {
	MindRegionConnector *connector = connectorMap.get( p_id );
	ASSERTMSG( connector != NULL , "unknown connector id=" + p_id );
	return( connector );
}

MindCircuitLinkDef *MindRegionTypeDef::getLink( String p_id ) {
	MindCircuitLinkDef *info = linkMap.get( p_id );
	ASSERTMSG( info != NULL , "unknown NeuroLink id=" + p_id );
	return( info );
}
