#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalTract::XmlSpinalTract() {
}

XmlSpinalTract::~XmlSpinalTract() {
	tracts.destroy();
	paths.destroy();
}

void XmlSpinalTract::load( XmlSpinalCord& sc , Xml xml ) {
	final = xml.getBooleanAttribute( "final" , false );
	index = xml.getAttribute( "index" , "" );
	name = xml.getAttribute( "name" );
	link = xml.getAttribute( "link" , "" );
	synonyms = xml.getAttribute( "synonyms" , "" );
	function = xml.getAttribute( "function" );
	source = xml.getAttribute( "source" , "" );
	target = xml.getAttribute( "target" , "" );
	notes = xml.getAttribute( "notes" , "" );
	imgsrc = xml.getAttribute( "imgsrc" , "" );
	imgheight = xml.getAttribute( "imgheight" , "" );

	sc.addTract( this );

	if( final ) {
		for( Xml xmlChild = xml.getFirstChild( "path" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "path" ) ) {
			XmlSpinalTractPath *path = new XmlSpinalTractPath();
			path -> load( this , xmlChild );
			paths.add( path );
		}
	}
	else {
		for( Xml xmlChild = xml.getFirstChild( "tract" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tract" ) ) {
			XmlSpinalTract *tract = new XmlSpinalTract();
			tract -> load( sc , xmlChild );
			tracts.add( tract -> name , tract );
		}
	}
}

void XmlSpinalTract::addPath( XmlSpinalTractPath *path ) {
	allpaths.add( path );
}

bool XmlSpinalTract::referencesRegion( String region ) {
	for( int k = 0; k < allpaths.count(); k++ ) {
		XmlSpinalTractPath& path = allpaths.getRef( k );
		if( path.items.find( region ) >= 0 )
			return( true );
	}

	return( false );
}
