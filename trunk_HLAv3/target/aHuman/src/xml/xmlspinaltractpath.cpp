#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalTractPath::XmlSpinalTractPath() {
}

XmlSpinalTractPath::~XmlSpinalTractPath() {
}

void XmlSpinalTractPath::load( Xml xml ) {
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

	String fibersvalue = xml.getAttribute( "fibers" );
	fibersvalue.split( fibers , "," );
	String value = xml.getAttribute( "endings" );
	value.split( endings , "," );

	for( Xml xmlChild = xml.getFirstChild( "path" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "path" ) ) {
		XmlSpinalTractPath *path = new XmlSpinalTractPath();
		path -> load( xmlChild );
		childs.add( path );
	}
}
