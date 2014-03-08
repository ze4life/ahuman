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

void XmlSpinalTract::load( Xml xml ) {
	final = xml.getBooleanAttribute( "final" , false );
	name = xml.getAttribute( "name" );
	link = xml.getAttribute( "link" , "" );
	synonyms = xml.getAttribute( "synonyms" , "" );
	function = xml.getAttribute( "function" );
	source = xml.getAttribute( "source" , "" );
	target = xml.getAttribute( "target" , "" );
	notes = xml.getAttribute( "notes" , "" );
	imgsrc = xml.getAttribute( "imgsrc" , "" );
	imgheight = xml.getAttribute( "imgheight" , "" );

	if( final ) {
		for( Xml xmlChild = xml.getFirstChild( "path" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "path" ) ) {
			XmlSpinalTractPath *path = new XmlSpinalTractPath();
			path -> load( xmlChild );
			paths.add( path );
		}
	}
	else {
		for( Xml xmlChild = xml.getFirstChild( "tract" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tract" ) ) {
			XmlSpinalTract *tract = new XmlSpinalTract();
			tract -> load( xmlChild );
			tracts.add( tract -> name , tract );
		}
	}
}
	
