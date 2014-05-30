#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalEnding::XmlSpinalEnding( XmlSpinalEndingSet& p_es , XmlSpinalEnding *p_parent ) 
: es( p_es ) , parent( p_parent ) {
}

XmlSpinalEnding::~XmlSpinalEnding() {
}

void XmlSpinalEnding::load( Xml xml , String element ) {
	id = xml.getAttribute( "id" );
	type = element;
	name = xml.getAttribute( "name" );
	function = xml.getAttribute( "function" , "" );
	notes = xml.getAttribute( "notes" , "" );
	es.sc.addEnding( this );

	for( Xml xmlChild = xml.getFirstChild( element ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( element ) ) {
		XmlSpinalEnding *ending = new XmlSpinalEnding( es , this );
		ending -> load( xmlChild , element );
		childs.add( ending -> name , ending );
	}
}

void XmlSpinalEnding::addFiber( XmlSpinalFiber *fiber ) {
	fibers.add( fiber -> id );
}

void XmlSpinalEnding::addTract( XmlSpinalTract *tract ) {
	tracts.addnew( tract -> name , tract );
}

