#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalFiber::XmlSpinalFiber() {
}

XmlSpinalFiber::~XmlSpinalFiber() {
}

void XmlSpinalFiber::load( Xml xml ) {
	id = xml.getAttribute( "id" );
	name = xml.getAttribute( "name" , id );
	type = xml.getAttribute( "type" , "mixed" );
	mcm = xml.getAttribute( "mcm" , "" );
	msec = xml.getAttribute( "msec" , "" );
	endings = xml.getAttribute( "endings" , "" );
	function = xml.getAttribute( "function" , "" );
	notes = xml.getAttribute( "notes" , "" );

	for( Xml xmlChild = xml.getFirstChild( "fiber" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "fiber" ) ) {
		XmlSpinalFiber *fiber = new XmlSpinalFiber();
		fiber -> load( xmlChild );
		childs.add( fiber );
	}
}
