#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlBrainTract::XmlBrainTract( XmlBrainTractSet& p_ts , XmlBrainTract *p_parent ) 
: ts( p_ts ) , parent( p_parent ) {
}

XmlBrainTract::~XmlBrainTract() {
	childs.destroy();
	paths.destroy();
}

void XmlBrainTract::load( Xml xml ) {
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
		XmlBrainTractPath *path = new XmlBrainTractPath(  *this , NULL );
		path -> load( xmlChild );
		paths.add( path -> id , path );
		ts.sc.addPath( path );
	}

	for( Xml xmlChild = xml.getFirstChild( "tract" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tract" ) ) {
		XmlBrainTract *tract = new XmlBrainTract( ts , this );
		tract -> load( xmlChild );
		childs.add( tract -> name , tract );
	}
}

void XmlBrainTract::addPath( XmlBrainTractPath *path ) {
	allpaths.add( path -> id , path );
}

bool XmlBrainTract::referencesRegion( String region ) {
	for( int k = 0; k < allpaths.count(); k++ ) {
		XmlBrainTractPath& path = allpaths.getClassRefByIndex( k );
		if( path.items.find( region ) >= 0 )
			return( true );
	}

	return( false );
}
