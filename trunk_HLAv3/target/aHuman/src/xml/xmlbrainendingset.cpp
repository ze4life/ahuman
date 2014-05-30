#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlBrainEndingSet::XmlBrainEndingSet( XmlTracts& p_sc ) 
: sc( p_sc ) {
}

XmlBrainEndingSet::~XmlBrainEndingSet() {
}

void XmlBrainEndingSet::load( Xml xml ) {
	name = xml.getAttribute( "name" );
	type = xml.getAttribute( "type" );
	imgsrc = xml.getAttribute( "imgsrc" , "" );
	imgheight = xml.getAttribute( "imgheight" , "" );

	String element;
	if( type.equals( "sensory" ) )
		element = "receptor";
	else if( type.equals( "motor" ) )
		element = "effector";

	for( Xml xmlChild = xml.getFirstChild( element ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( element ) ) {
		XmlBrainEnding *ending = new XmlBrainEnding( *this , NULL );
		ending -> load( xmlChild , element );
		childs.add( ending -> name , ending );
	}
}
