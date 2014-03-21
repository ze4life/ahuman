#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalEnding::XmlSpinalEnding() {
}

XmlSpinalEnding::~XmlSpinalEnding() {
}

void XmlSpinalEnding::load( Xml xml , String element ) {
	id = xml.getAttribute( "id" );
	type = element;
	name = xml.getAttribute( "name" );
	function = xml.getAttribute( "function" , "" );
	notes = xml.getAttribute( "notes" , "" );

	for( Xml xmlChild = xml.getFirstChild( element ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( element ) ) {
		XmlSpinalEnding *ending = new XmlSpinalEnding();
		ending -> load( xmlChild , element );
		childs.add( ending -> name , ending );
	}
}
