#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlHMind::XmlHMind() {
}

XmlHMind::~XmlHMind() {
	nodeInfo.destroy();
}

void XmlHMind::load() {
	// read hierarchy
	EnvService *es = EnvService::getService();
	xml = es -> loadXml( "hmind.xml" );
	ASSERTMSG( xml.exists() , "unable to read file hmind.xml" );

	// scan
	for( Xml xmlChild = xml.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		createDivisionElement( xmlChild );
		scanChildItems( xmlChild );
	}
}

void XmlHMind::scanChildItems( Xml xmlItem ) {
	// childs
	for( Xml xmlChild = xmlItem.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		createRegionElement( xmlChild );
		scanChildItems( xmlChild );
	}
}

Xml XmlHMind::getNodeXml( String node ) {
	XmlHMindElementInfo *info = nodeInfo.get( node );
	ASSERTMSG( info != NULL , "unable to find node with ID=" + node );
	return( info -> xml );
}

bool XmlHMind::isComponent( String node ) {
	XmlHMindElementInfo *info = nodeInfo.get( node );
	ASSERTMSG( info != NULL , "unable to find node with ID=" + node );

	if( info -> id.isEmpty() )
		return( false );
	return( true );
}

void XmlHMind::getDivisions( StringList& divisions ) {
	for( Xml xmlChild = xml.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		String name = xmlChild.getAttribute( "name" );
		divisions.add( name );
	}
}

void XmlHMind::getElements( String parentNode , StringList& elements ) {
	Xml xmlParent = getNodeXml( parentNode );
	for( Xml xmlChild = xmlParent.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		String mapId = getRegionMapId( xmlChild );
		elements.add( mapId );
	}
}

void XmlHMind::getIdentifiedElements( String parentNode , StringList& elements ) {
	Xml xmlParent = getNodeXml( parentNode );
	for( Xml xmlChild = xmlParent.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		String id = xmlChild.getAttribute( "id" , "" );
		if( !id.isEmpty() )
			elements.add( id );
	}
}

String XmlHMind::createDivisionElement( Xml item ) {
	String mapId = item.getAttribute( "name" );
	XmlHMindElementInfo *info = new XmlHMindElementInfo();
	createElementInfo( mapId , item , *info );
	nodeInfo.add( mapId , info );
	return( mapId );
}

String XmlHMind::getRegionMapId( Xml item ) {
	String mapId = item.getAttribute( "id" , "" );
	if( mapId.isEmpty() )
		mapId = String( "auto-" ) + ( unsigned )item.getNode();
	return( mapId );
}

String XmlHMind::createRegionElement( Xml item ) {
	String mapId = getRegionMapId( item );
	XmlHMindElementInfo *info = new XmlHMindElementInfo();
	createElementInfo( mapId , item , *info );
	nodeInfo.add( mapId , info );
	return( mapId );
}

void XmlHMind::createElementInfo( String mapId , Xml item , XmlHMindElementInfo& info ) {
	info.mapId = mapId;
	info.xml = item;

	info.id = item.getAttribute( "id" , "" );
	info.ignore = item.getBooleanAttribute( "ignore" , false );
	info.mapped = item.getBooleanAttribute( "mapped" , false );
	info.name = item.getAttribute( "name" , "" );
	ASSERTMSG( !info.name.isEmpty() , "name attribute is not set for item xpath=" + item.getXPath() );

	info.refs = item.getAttribute( "refs" , "" );
	info.comment = item.getAttribute( "comment" , "" );
	info.brodmannid = item.getAttribute( "brodmannid" , "" );
	info.type = item.getAttribute( "type" , "" );
	info.function = item.getAttribute( "function" , "" );
	info.notes = item.getAttribute( "notes" , "" );
	info.dotdef = item.getAttribute( "dotdef" , "" );

	if( info.brodmannid.isEmpty() )
		info.batype = info.type;
	else
		info.batype = info.type + ", BA " + info.brodmannid;
}

const XmlHMindElementInfo& XmlHMind::getElementInfo( String node ) {
	XmlHMindElementInfo *ni = nodeInfo.get( node );
	return( *ni );
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
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

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

