#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalTract::XmlSpinalTract( XmlSpinalTractSet& p_ts , XmlSpinalTract *p_parent ) 
: ts( p_ts ) , parent( p_parent ) {
}

XmlSpinalTract::~XmlSpinalTract() {
	childs.destroy();
	paths.destroy();
}

void XmlSpinalTract::load( Xml xml ) {
	index = xml.getAttribute( "index" , "" );
	brief = xml.getAttribute( "brief" , "" );
	name = xml.getAttribute( "name" );
	link = xml.getAttribute( "link" , "" );
	synonyms = xml.getAttribute( "synonyms" , "" );
	function = xml.getAttribute( "function" );
	source = xml.getAttribute( "source" , "" );
	target = xml.getAttribute( "target" , "" );
	notes = xml.getAttribute( "notes" , "" );
	imgsrc = xml.getAttribute( "imgsrc" , "" );
	imgheight = xml.getAttribute( "imgheight" , "" );

	ts.sc.addTract( this );

	for( Xml xmlChild = xml.getFirstChild( "path" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "path" ) ) {
		XmlSpinalTractPath *path = new XmlSpinalTractPath(  *this , NULL );
		path -> load( xmlChild );
		paths.add( path -> id , path );
		ts.sc.addPath( path );
	}

	for( Xml xmlChild = xml.getFirstChild( "tract" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tract" ) ) {
		XmlSpinalTract *tract = new XmlSpinalTract( ts , this );
		tract -> load( xmlChild );
		childs.add( tract -> name , tract );
	}
}

void XmlSpinalTract::addPath( XmlSpinalTractPath *path ) {
	allpaths.add( path -> id , path );
}

bool XmlSpinalTract::referencesRegion( String region ) {
	for( int k = 0; k < allpaths.count(); k++ ) {
		XmlSpinalTractPath& path = allpaths.getClassRefByIndex( k );
		if( path.items.find( region ) >= 0 )
			return( true );
	}

	return( false );
}
