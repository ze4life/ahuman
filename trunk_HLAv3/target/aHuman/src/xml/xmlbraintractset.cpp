#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlBrainTractSet::XmlBrainTractSet( XmlTracts& p_sc ) 
: sc ( p_sc ) {
}

XmlBrainTractSet::~XmlBrainTractSet() {
	tracts.destroy();
}

void XmlBrainTractSet::load( Xml xml ) {
	name = xml.getAttribute( "name" );
	imgsrc = xml.getAttribute( "imgsrc" , "" );
	imgheight = xml.getAttribute( "imgheight" , "" );

	for( Xml xmlChild = xml.getFirstChild( "tract" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tract" ) ) {
		XmlBrainTract *tract = new XmlBrainTract( *this , NULL );
		tract -> load( xmlChild );
		tracts.add( tract -> name , tract );
	}
}

