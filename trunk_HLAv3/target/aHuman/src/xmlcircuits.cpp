#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlCircuits::XmlCircuits() {
}

XmlCircuits::~XmlCircuits() {
}

void XmlCircuits::load() {
	// read circuits
	EnvService *es = EnvService::getService();
	xml = es -> loadXml( "circuits.xml" );
	ASSERTMSG( xml.exists() , "unable to read file circuits.xml" );

	// scan
	for( Xml xmlCategory = xml.getFirstChild( "category" ); xmlCategory.exists(); xmlCategory = xmlCategory.getNextChild( "category" ) ) {
		for( Xml xmlChild = xmlCategory.getFirstChild( "circuit" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "circuit" ) ) {
			String id = xmlChild.getAttribute( "id" , "" );
			bool ignore = xmlChild.getBooleanAttribute( "id" , false );

			if( id.isEmpty() ) {
				ASSERTMSG( ignore == true , "circuit is not ignored but has no ID attribute" );
			}
			else
				nodes.add( id , xmlChild.getNode() );
		}
	}
}

void XmlCircuits::getCircuitList( StringList& circuits ) {
	// scan
	for( int k = 0; k < nodes.count(); k++ ) {
		String id = nodes.getKeyByIndex( k );
		circuits.add( id );
	}
}

Xml XmlCircuits::getCircuitXml( String id ) {
	void *nodePtr = nodes.get( id );
	ASSERTMSG( nodePtr != NULL , "unable to find circuit with ID=" + id );

	Xml xmlitem;
	xmlitem.attach( xml.getDoc() , nodePtr );
	return( xmlitem );
}

void XmlCircuits::getCircuitInfo( String circuit , XmlCircuitInfo& info ) {
	Xml xmlitem = getCircuitXml( circuit );
	info.xml = xmlitem;

	info.id = xmlitem.getAttribute( "id" , "" );
	info.ignore = xmlitem.getBooleanAttribute( "ignore" , false );
	info.name = xmlitem.getAttribute( "name" , "" );
	info.image = xmlitem.getAttribute( "image" , "" );
	info.reference = xmlitem.getAttribute( "reference" , "" );

	info.componentMapping.destroy();
	String mapping = xmlitem.getAttribute( "components" , "" );
	StringList pairs;
	mapping.split( pairs , " " );
	for( int k = 0; k < pairs.count(); k++ ) {
		String pair = pairs.get( k );
		pair.trim();

		StringList parts;
		pair.split( parts , "=" );
		ASSERTMSG( parts.count() == 2 , "invalid format pair=" + pair );
		
		info.componentMapping.add( parts.get( 0 ) , parts.get( 1 ) );
	}
}

void XmlCircuits::getCircuitLinks( String circuit , FlatList<Xml>& links ) {
	Xml xmlitem = getCircuitXml( circuit );
	for( Xml xmlChild = xmlitem.getFirstChild( "link" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "link" ) )
		links.add( xmlChild );
}

void XmlCircuits::getCircuitLinkInfo( Xml link , XmlCircuitLinkInfo& info ) {
	info.compSrc = link.getAttribute( "src" );
	info.compDst = link.getAttribute( "dst" );
	info.function = link.getAttribute( "function" , "" );
}

String XmlCircuits::mapComponent( XmlCircuitInfo& circuit , String circuitComponent ) {
	String value = circuit.componentMapping.get( circuitComponent );
	ASSERTMSG( !value.isEmpty() , "unknown circuit link component=" + circuitComponent );
	return( value );
}
