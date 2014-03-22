#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlSpinalTractSet::XmlSpinalTractSet() {
}

XmlSpinalTractSet::~XmlSpinalTractSet() {
	tracts.destroy();
}

void XmlSpinalTractSet::load( XmlSpinalCord& sc , Xml xml ) {
	name = xml.getAttribute( "name" );
	imgsrc = xml.getAttribute( "imgsrc" , "" );
	imgheight = xml.getAttribute( "imgheight" , "" );

	for( Xml xmlChild = xml.getFirstChild( "tract" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tract" ) ) {
		XmlSpinalTract *tract = new XmlSpinalTract();
		tract -> load( sc , xmlChild );
		tracts.add( tract -> name , tract );
	}
}

