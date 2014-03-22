#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalEnding::XmlSpinalEnding() {
}

XmlSpinalEnding::~XmlSpinalEnding() {
}

void XmlSpinalEnding::load( XmlSpinalCord& sc , Xml xml , String element ) {
	id = xml.getAttribute( "id" );
	type = element;
	name = xml.getAttribute( "name" );
	function = xml.getAttribute( "function" , "" );
	notes = xml.getAttribute( "notes" , "" );
	sc.addEnding( this );

	for( Xml xmlChild = xml.getFirstChild( element ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( element ) ) {
		XmlSpinalEnding *ending = new XmlSpinalEnding();
		ending -> load( sc , xmlChild , element );
		childs.add( ending -> name , ending );
	}
}

void XmlSpinalEnding::addFiber( XmlSpinalFiber *fiber ) {
	fibers.add( fiber -> id );
}

void XmlSpinalEnding::addTract( XmlSpinalTract *tract ) {
	tracts.add( tract );
}

