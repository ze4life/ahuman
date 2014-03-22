#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalFiber::XmlSpinalFiber() {
}

XmlSpinalFiber::~XmlSpinalFiber() {
}

void XmlSpinalFiber::load( XmlSpinalCord& sc , Xml xml ) {
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
		XmlSpinalFiber *fiber = new XmlSpinalFiber();
		fiber -> load( sc , xmlChild );
		childs.add( fiber -> id , fiber );
	}
}

void XmlSpinalFiber::addTract( XmlSpinalTract *tract ) {
	tracts.addnew( tract -> name , tract );
}

