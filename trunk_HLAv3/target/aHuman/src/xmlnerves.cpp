#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlNerves::XmlNerves() {
}

XmlNerves::~XmlNerves() {
	nodes.destroy();
	nerves.destroy();
}

void XmlNerves::load() {
	// read circuits
	EnvService *es = EnvService::getService();
	Xml xml = es -> loadXml( "hpns.xml" );
	ASSERTMSG( xml.exists() , "unable to read file hpns.xml" );

	// scan
	for( Xml xmlDivision = xml.getFirstChild( "division" ); xmlDivision.exists(); xmlDivision = xmlDivision.getNextChild( "division" ) ) {
		String name = xmlDivision.getAttribute( "name" );
		String file = xmlDivision.getAttribute( "xmlfile" );
		String page = xmlDivision.getAttribute( "page" );

		Xml xmlFile = es -> loadXml( file );
		Xml xmlDivisionFile = xmlFile.getChildNamedNode( "division" , name );

		XmlNerveInfo *division = new XmlNerveInfo;
		division -> name = name;
		division -> xml = xmlDivisionFile;
		division -> origin = page;
		divisions.add( division );

		addChilds( division , division );
	}
}

void XmlNerves::addChilds( XmlNerveInfo *division , XmlNerveInfo *parent ) {
	for( Xml item = parent -> xml.getFirstChild( "element" ); item.exists(); item = item.getNextChild( "element" ) ) {
		String id = item.getAttribute( "name" );
		ASSERTMSG( nodes.get( id ) == NULL , "Duplicate nerve division=" + division -> name + ", name=" + id );

		// add item
		nodes.addnew( id , new Xml( item ) );
		XmlNerveInfo *nerveInfo = createNerveInfo( id , item );
		nerves.add( id , nerveInfo );
		parent -> childs.add( id , nerveInfo );

		addChilds( division , nerveInfo );
	}
}

void XmlNerves::getNerveList( StringList& list ) {
	// scan
	for( int k = 0; k < nodes.count(); k++ ) {
		String id = nodes.getKeyByIndex( k );
		list.add( id );
	}
}

Xml XmlNerves::getNerveXml( String id ) {
	Xml *nodeXml = nodes.get( id );
	ASSERTMSG( nodeXml != NULL , "unable to find circuit with ID=" + id );

	return( *nodeXml );
}

XmlNerveInfo& XmlNerves::getNerveInfo( String nerve ) {
	XmlNerveInfo *pinfo = nerves.get( nerve );
	ASSERTMSG( pinfo != NULL , "unable to find nerve=" + nerve );
	return( *pinfo );
}

XmlNerveInfo *XmlNerves::createNerveInfo( String nerve , Xml xmlitem ) {
	XmlNerveInfo *pinfo = new XmlNerveInfo;

	XmlNerveInfo& info = *pinfo;
	info.xml = xmlitem;

	info.name = xmlitem.getAttribute( "name" );
	info.synonyms = xmlitem.getAttribute( "synonyms" , "" );
	info.origin = xmlitem.getAttribute( "origin" , "" );
	info.branches = xmlitem.getAttribute( "branches" , "" );
	info.distribution = xmlitem.getAttribute( "distribution" , "" );
	info.imgsrc = xmlitem.getAttribute( "imgsrc" , "" );
	info.imgheight = xmlitem.getAttribute( "imgheight" , "" );
	info.modality = xmlitem.getAttribute( "modality" , "" );
	
	for( Xml item = xmlitem.getFirstChild( "fibers" ); item.exists(); item = item.getNextChild( "fibers" ) ) {
		XmlNerveFiberInfo *nf = new XmlNerveFiberInfo;
		info.fibers.add( nf );

		nf -> type = item.getAttribute( "type" );
		nf -> src = item.getAttribute( "src" );
		nf -> dst = item.getAttribute( "dst" );

		for( Xml mid = item.getFirstChild( "mid" ); mid.exists(); mid = mid.getNextChild( "mid" ) ) {
			String id = mid.getAttribute( "id" );
			nf -> mids.add( id );
		}
	}

	return( pinfo );
}
