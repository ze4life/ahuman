#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlNerves::XmlNerves() {
}

XmlNerves::~XmlNerves() {
	nodes.destroy();
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
		Xml xmlFile = es -> loadXml( file );
		Xml division = xmlFile.getChildNamedNode( "division" , name );

		addChilds( division , division );
	}
}

void XmlNerves::addChilds( Xml division , Xml parent ) {
	for( Xml item = parent.getFirstChild( "element" ); item.exists(); item = item.getNextChild( "element" ) ) {
		String id = item.getAttribute( "name" );
		ASSERTMSG( nodes.get( id ) == NULL , "Duplicate nerve division=" + division.getAttribute( "name" ) + ", name=" + id );

		// add item
		nodes.addnew( id , new Xml( item ) );
		addChilds( division , item );
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
	if( pinfo != NULL )
		return( *pinfo );

	pinfo = new XmlNerveInfo;
	nerves.add( nerve , pinfo );

	XmlNerveInfo& info = *pinfo;
	Xml xmlitem = getNerveXml( nerve );
	info.xml = xmlitem;

	info.name = xmlitem.getAttribute( "name" );
	info.synonyms = xmlitem.getAttribute( "synonyms" , "" );
	info.origin = xmlitem.getAttribute( "origin" , "" );
	info.branches = xmlitem.getAttribute( "branches" , "" );
	info.distribution = xmlitem.getAttribute( "distribution" , "" );
	info.imginfo = xmlitem.getAttribute( "imginfo" , "" );
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

	return( info );
}
