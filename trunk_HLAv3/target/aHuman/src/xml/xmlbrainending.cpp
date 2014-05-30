#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlBrainEnding::XmlBrainEnding( XmlBrainEndingSet& p_es , XmlBrainEnding *p_parent ) 
: es( p_es ) , parent( p_parent ) {
}

XmlBrainEnding::~XmlBrainEnding() {
}

void XmlBrainEnding::load( Xml xml , String element ) {
	id = xml.getAttribute( "id" );
	type = element;
	name = xml.getAttribute( "name" );
	function = xml.getAttribute( "function" , "" );
	notes = xml.getAttribute( "notes" , "" );
	es.sc.addEnding( this );

	for( Xml xmlChild = xml.getFirstChild( element ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( element ) ) {
		XmlBrainEnding *ending = new XmlBrainEnding( es , this );
		ending -> load( xmlChild , element );
		childs.add( ending -> name , ending );
	}
}

void XmlBrainEnding::addFiber( XmlBrainFiber *fiber ) {
	fibers.add( fiber -> id );
}

void XmlBrainEnding::addTract( XmlBrainTract *tract ) {
	tracts.addnew( tract -> name , tract );
}

