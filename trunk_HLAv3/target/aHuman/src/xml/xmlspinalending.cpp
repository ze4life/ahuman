#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalEnding::XmlSpinalEnding() {
}

XmlSpinalEnding::~XmlSpinalEnding() {
}

void XmlSpinalEnding::load( Xml xml ) {
	id = xml.getAttribute( "id" );
	name = xml.getAttribute( "name" );
	function = xml.getAttribute( "function" );
	notes = xml.getAttribute( "notes" );

	for( Xml xmlChild = xml.getFirstChild( "fiber" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "fiber" ) ) {
		XmlSpinalEnding *ending = new XmlSpinalEnding();
		ending -> load( xmlChild );
		childs.add( ending );
	}
}
