#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlHMind::XmlHMind() {
}

XmlHMind::~XmlHMind() {
}

void XmlHMind::load() {
	// read hierarchy
	EnvService *es = EnvService::getService();
	xml = es -> loadXml( "hmind.xml" );
	ASSERTMSG( xml.exists() , "unable to read file hmind.xml" );

	// scan
	for( Xml xmlChild = xml.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		String name = xmlChild.getAttribute( "name" );
		nodes.add( name , xmlChild.getNode() );

		scanChildItems( xmlChild );
	}
}

void XmlHMind::scanChildItems( Xml xmlItem ) {
	// childs
	for( Xml xmlChild = xmlItem.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		String id = xmlChild.getAttribute( "id" , "" );
		if( !id.isEmpty() )
			nodes.add( id , xmlChild.getNode() );

		scanChildItems( xmlChild );
	}
}

Xml XmlHMind::getNodeXml( String node ) {
	void *nodePtr = nodes.get( node );
	ASSERTMSG( nodePtr != NULL , "unable to find node with ID=" + node );

	Xml xmlitem;
	xmlitem.attach( xml.getDoc() , nodePtr );
	return( xmlitem );
}

bool XmlHMind::isComponent( String node ) {
	void *nodePtr = nodes.get( node );
	if( nodePtr == NULL )
		return( false );
	return( true );
}

void XmlHMind::getDivisions( StringList& divisions ) {
	for( Xml xmlChild = xml.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		String name = xmlChild.getAttribute( "name" );
		divisions.add( name );
	}
}

void XmlHMind::getElements( String parentNode , StringList& elements ) {
	Xml xmlParent = getNodeXml( parentNode );
	for( Xml xmlChild = xmlParent.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		String id = xmlChild.getAttribute( "id" , "" );
		if( !id.isEmpty() )
			elements.add( id );
	}
}

void XmlHMind::getElementInfo( String node , XmlHMindElementInfo& info ) {
	Xml item = getNodeXml( node );
	info.ignore = item.getBooleanAttribute( "ignore" , false );
	info.id = item.getAttribute( "id" , "" );
	info.mapped = item.getBooleanAttribute( "mapped" , false );
	info.name = item.getAttribute( "name" , "" );
	info.refs = item.getAttribute( "refs" , "" );
	info.comment = item.getAttribute( "comment" , "" );
	info.brodmannid = item.getAttribute( "brodmannid" , "" );
	info.type = item.getAttribute( "type" , "" );
	info.function = item.getAttribute( "function" , "" );
	info.notes = item.getAttribute( "notes" , "" );
	info.dotdef = item.getAttribute( "dotdef" , "" );
}

String XmlHMind::getMappedRegion( String node ) {
	Xml item = getNodeXml( node );
	while( item.exists() ) {
		if( item.getBooleanAttribute( "mapped" , false ) == true )
			return( item.getAttribute( "id" ) );

		// go up
		item = item.getParentNode();
	}

	return( "" );
}

void XmlHMind::getChildRegions( String node , StringList& regions ) {
	Xml item = getNodeXml( node );
	scanChildRegions( item , regions );
}

void XmlHMind::scanChildRegions( Xml item , StringList& regions ) {
	for( Xml xmlChild = item.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		String id = xmlChild.getAttribute( "id" , "" );
		if( id.isEmpty() )
			continue;

		if( xmlChild.getBooleanAttribute( "mapped" , false ) == true )
			regions.add( id );
		else
			scanChildRegions( xmlChild , regions );
	}
}

String XmlHMind::getDotDef( String node ) {
	Xml item = getNodeXml( node );
	while( item.exists() ) {
		String dotdef = item.getAttribute( "dotdef" , "" );
		if( !dotdef.isEmpty() )
			return( dotdef );

		// go up
		item = item.getParentNode();
	}

	return( "" );
}

