#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlBrainFiber::XmlBrainFiber( XmlTracts& p_sc , XmlBrainFiber *p_parent ) 
: sc( p_sc ) , parent( p_parent ) {
}

XmlBrainFiber::~XmlBrainFiber() {
}

void XmlBrainFiber::load( Xml xml ) {
	id = xml.getAttribute( "id" );
	name = xml.getAttribute( "name" , "" );
	type = xml.getAttribute( "type" , "mixed" );
	mcm = xml.getAttribute( "mcm" , "" );
	msec = xml.getAttribute( "msec" , "" );
	function = xml.getAttribute( "function" , "" );
	notes = xml.getAttribute( "notes" , "" );
	sc.addFiber( this );

	String value = xml.getAttribute( "endings" , "" );
	value.split( endings , "," );

	for( Xml xmlChild = xml.getFirstChild( "fiber" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "fiber" ) ) {
		XmlBrainFiber *fiber = new XmlBrainFiber( sc , this );
		fiber -> load( xmlChild );
		childs.add( fiber -> id , fiber );
	}
}

void XmlBrainFiber::addTract( XmlBrainTract *tract ) {
	tracts.addnew( tract -> name , tract );
}
