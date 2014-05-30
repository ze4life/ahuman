#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlBrainTractPath::XmlBrainTractPath( XmlBrainTract& p_tract , XmlBrainTractPath *p_parent ) 
: tract( p_tract ) , parent( p_parent ) {
}

XmlBrainTractPath::~XmlBrainTractPath() {
}

void XmlBrainTractPath::load( Xml xml ) {
	id = xml.getAttribute( "id" );
	type = xml.getAttribute( "type" );
	function = xml.getAttribute( "function" );
	pathway = xml.getAttribute( "pathway" );

	String src = xml.getAttribute( "src" );
	String dst = xml.getAttribute( "dst" );
	String mids = xml.getAttribute( "mids" , "" );

	items.add( src );
	StringList midlist;
	mids.split( midlist , "," );
	items.add( &midlist );
	items.add( dst );

	tract.addPath( this );

	String fibersvalue = xml.getAttribute( "fibers" );
	fibersvalue.split( fibers , "," );
	String value = xml.getAttribute( "endings" );
	value.split( endings , "," );

	for( Xml xmlChild = xml.getFirstChild( "path" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "path" ) ) {
		XmlBrainTractPath *path = new XmlBrainTractPath( tract , this );
		path -> load( xmlChild );
		childs.add( path -> id , path );
	}
}
