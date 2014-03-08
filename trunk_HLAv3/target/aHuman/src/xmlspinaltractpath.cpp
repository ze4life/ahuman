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
	source = xml.getAttribute( "source" );
	target = xml.getAttribute( "target" );

	String src = xml.getAttribute( "src" );
	String dst = xml.getAttribute( "dst" );
	String mids = xml.getAttribute( "mids" );

	items.add( src );
	StringList midlist;
	mids.split( midlist , "," );
	items.add( &midlist );
	items.add( dst );

	String fibersvalue = xml.getAttribute( "fibers" );
	fibersvalue.split( fibers , "," );
}
