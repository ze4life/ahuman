#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlHMind::XmlHMind() {
	tracts = new XmlTracts( this );
	spinalCord = new XmlSpinalCord( this );
}

XmlHMind::~XmlHMind() {
	nodeInfo.destroy();
	delete spinalCord;
	delete tracts;
}

void XmlHMind::load() {
	// read hierarchy
	EnvService *es = EnvService::getService();
	xml = es -> loadXml( "hmind.xml" );
	ASSERTMSG( xml.exists() , "unable to read file hmind.xml" );

	// read categories
	loadCategories( xml );

	// scan
	for( Xml xmlChild = xml.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		createDivisionElement( xmlChild );
	}

	// read tracts
	Xml xmltracts = xml.getFirstChild( "tracts" );
	ASSERTMSG( xmltracts.exists() , "unable to find tract information" );
	String xmlFileName = xmltracts.getAttribute( "xmlfile" );
	Xml xmlFile = es -> loadXml( xmlFileName );
	ASSERTMSG( xmlFile.exists() , "unable to read file " + xmlFileName );
	tracts -> load( xmlFile );
}

void XmlHMind::loadCategories( Xml xml ) {
	Xml xmltracts = xml.getFirstChild( "categories" );
	for( Xml xmlChild = xmltracts.getFirstChild( "category" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "category" ) ) {
		XmlBrainCategory *category = new XmlBrainCategory( this );
		category -> load( xmlChild );
		categories.add( category -> getId() , category );
	}
}

void XmlHMind::createDivisionElement( Xml item ) {
	String xmlFileName = item.getAttribute( "xmlfile" );
	String divname = item.getAttribute( "name" );

	EnvService *es = EnvService::getService();
	Xml xmlFile = es -> loadXml( xmlFileName );
	ASSERTMSG( xmlFile.exists() , "unable to read file " + xmlFileName );
	Xml div = xmlFile.getChildNamedNode( "division" , divname );
	ASSERTMSG( div.exists() , "unable to find division name=" + divname );
	String mapId = div.getAttribute( "id" );

	XmlHMindElementInfo *info = new XmlHMindElementInfo( NULL );
	createElementInfo( mapId , div , *info );
	nodeInfo.add( mapId , info );
	divs.add( mapId , info );

	scanChildItems( div , info );

	if( mapId.equals( "SPC" ) )
		spinalCord -> load( div );
}

void XmlHMind::scanChildItems( Xml xmlItem , XmlHMindElementInfo *parent ) {
	// childs
	for( Xml xmlChild = xmlItem.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		XmlHMindElementInfo *child = createRegionElement( xmlChild , parent );
		scanChildItems( xmlChild , child );
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

XmlBrainCategory *XmlHMind::getCategory( String category ) {
	XmlBrainCategory *ct = categories.get( category );
	ASSERTMSG( ct != NULL , "unknown brain category=" + category );
	return( ct );
}

void XmlHMind::getDivisions( StringList& divisions ) {
	for( int k = 0; k < divs.count(); k++ )
		divisions.add( divs.getKeyByIndex( k ) );
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

void XmlHMind::getConnectors( String parentNode , StringList& elements ) {
	Xml xmlParent = getNodeXml( parentNode );
	for( Xml xmlChild = xmlParent.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		if( xmlChild.getBooleanAttribute( "ignore" , false ) )
			continue;

		String id = xmlChild.getAttribute( "id" , "" );
		if( !id.isEmpty() ) {
			String type = xmlChild.getAttribute( "type" , "" );
			if( type.equals( "connector" ) )
				elements.add( id );
			else
				getConnectors( id , elements );
		}
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

String XmlHMind::getRegionMapId( Xml item ) {
	String mapId = item.getAttribute( "id" , "" );
	if( mapId.isEmpty() )
		mapId = String( "auto-" ) + ( unsigned )item.getNode();
	return( mapId );
}

XmlHMindElementInfo *XmlHMind::createRegionElement( Xml item , XmlHMindElementInfo *parent ) {
	String mapId = getRegionMapId( item );
	XmlHMindElementInfo *info = new XmlHMindElementInfo( parent );
	createElementInfo( mapId , item , *info );
	nodeInfo.add( mapId , info );

	// add connectors to the map
	if( info -> isConnector() )
		connectorInfo.add( info -> name , info );

	return( info );
}

void XmlHMind::createElementInfo( String mapId , Xml item , XmlHMindElementInfo& info ) {
	info.mapId = mapId;
	info.xml = item;

	info.id = item.getAttribute( "id" , "" );
	String parentCategory = ( info.parent == NULL )? "" : info.parent -> category;
	info.category = item.getAttribute( "category" , parentCategory );
	info.index = item.getAttribute( "index" , "" );
	if( !info.index.isEmpty() )
		mapIndex.add( info.index , &info );

	info.ignore = item.getBooleanAttribute( "ignore" , false );
	info.mapped = item.getBooleanAttribute( "mapped" , false );
	info.name = item.getAttribute( "name" , "" );
	ASSERTMSG( !info.name.isEmpty() , "name attribute is not set for item xpath=" + item.getXPath() );

	info.refs = item.getAttribute( "refs" , "" );
	info.comment = item.getAttribute( "comment" , "" );
	info.brodmannid = item.getAttribute( "brodmannid" , "" );
	info.eltypename = item.getAttribute( "type" , "" );
	info.fgroup = item.getAttribute( "fgroup" , "" );
	info.function = item.getAttribute( "function" , "" );
	info.notes = item.getAttribute( "notes" , "" );
	info.dotdef = item.getAttribute( "dotdef" , "" );

	if( info.brodmannid.isEmpty() )
		info.batype = info.eltypename;
	else
		info.batype = info.eltypename + ", BA " + info.brodmannid;

	// ensure types
	if( info.eltypename.isEmpty() )
		info.eltype = HMIND_ELEMENT_NOTYPE;
	else if( info.eltypename.equals( "connector" ) )
		info.eltype = HMIND_ELEMENT_CONNECTOR;
	else if( info.eltypename.equals( "sensor" ) )
		info.eltype = HMIND_ELEMENT_SENSOR;
	else if( info.eltypename.equals( "effector" ) )
		info.eltype = HMIND_ELEMENT_EFFECTOR;
	else if( info.eltypename.equals( "sensory ganglion" ) )
		info.eltype = HMIND_ELEMENT_GANGLION_SENSORY;
	else if( info.eltypename.equals( "sympathetic ganglion" ) )
		info.eltype = HMIND_ELEMENT_GANGLION_SYMP;
	else if( info.eltypename.equals( "parasympathetic ganglion" ) )
		info.eltype = HMIND_ELEMENT_GANGLION_PSYMP;
	else if( info.eltypename.equals( "cortex" ) )
		info.eltype = HMIND_ELEMENT_CORTEX;
	else if( info.eltypename.equals( "nucleus" ) )
		info.eltype = HMIND_ELEMENT_NUCLEUS;
	else if( info.eltypename.equals( "gland" ) )
		info.eltype = HMIND_ELEMENT_GLAND;
	else
		ASSERTFAILED( "invalid element type id=" + info.id + ", name=" + info.name + ", type=" + info.eltypename );

	if( !info.category.isEmpty() ) {
		XmlBrainCategory *category = categories.get( info.category );
		ASSERTMSG( category != NULL , "region " + info.id + ": unknown category - " + info.category );
		category -> addElement( &info );
	}
}

XmlHMindElementInfo& XmlHMind::getElementInfo( String node ) {
	XmlHMindElementInfo *ni = nodeInfo.get( node );
	ASSERTMSG( ni != NULL , "unknown node=" + node );
	return( *ni );
}

const XmlHMindElementInfo *XmlHMind::getConnectorInfo( String name ) {
	XmlHMindElementInfo *ni = connectorInfo.get( name );
	ASSERTMSG( ni != NULL , "unknown connector - " + name );
	return( ni );
}

XmlHMindElementInfo *XmlHMind::getIndexedElement( String index ) {
	XmlHMindElementInfo *ni = mapIndex.get( index );
	ASSERTMSG( ni != NULL , "unknown indexed element - " + index );
	return( ni );
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

bool XmlHMind::checkAbstractLinkCoveredByRegionLink( String compSrc , String compDst , String linkRegionSrc , String linkRegionDst ) {
	// find mapped regions
	String regionSrcId = getMappedRegion( compSrc );
	String regionDstId = getMappedRegion( compDst );
	if( regionSrcId.isEmpty() == false && regionDstId.isEmpty() == false )
		return( regionSrcId.equals( linkRegionSrc ) && regionDstId.equals( linkRegionDst ) );

	// collect sets of child regions
	StringList srcRegions;
	if( regionSrcId.isEmpty() )
		getChildRegions( compSrc , srcRegions );
	else
		srcRegions.add( regionSrcId );

	StringList dstRegions;
	if( regionDstId.isEmpty() )
		getChildRegions( compDst , dstRegions );
	else
		dstRegions.add( regionDstId );

	// check mapping
	for( int k1 = 0; k1 < srcRegions.count(); k1++ ) {
		regionSrcId = srcRegions.get( k1 );
		for( int k2 = 0; k2 < dstRegions.count(); k2++ ) {
			regionDstId = dstRegions.get( k2 );
			if( regionSrcId.equals( linkRegionSrc ) && regionDstId.equals( linkRegionDst ) )
				return( true );
		}
	}

	return( false );
}

