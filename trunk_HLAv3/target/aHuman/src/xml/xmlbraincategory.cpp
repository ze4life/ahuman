#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlBrainCategory::XmlBrainCategory( XmlHMind *p_hmind ) {
	hmind = p_hmind;
}

void XmlBrainCategory::load( Xml xml ) {
	id = xml.getAttribute( "id" );
	name = xml.getAttribute( "name" );
}

void XmlBrainCategory::addElement( XmlHMindElementInfo *item ) {
	if( item -> mapped )
		mappedElements.add( item -> id , item );
}

void XmlBrainCategory::getMappedItems( StringList& items ) {
	for( int k = 0; k < mappedElements.count(); k++ )
		items.add( mappedElements.getKeyByIndex( k ) );
}
