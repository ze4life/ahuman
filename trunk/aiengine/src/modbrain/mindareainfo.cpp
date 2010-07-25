#include "brain_impl.h"

void MindAreaInfo::createFromXml( Xml xml )
{
	// attributes are properties
	areaId = xml.getAttribute( "id" );

	// child elements are MindLink
	for( Xml xmlChild = xml.getFirstChild( "MindLink" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindLink" ) ) {
		// construct MindArea from attributes
		MindLinkInfo *info = new MindLinkInfo;
		info -> createFromXml( xmlChild );

		// add
		links.add( info );
	}
}

void MindAreaInfo::resolveLinks( MindMap *map )
{
	for( int k = links.count() - 1; k >= 0; k-- ) {
		MindLinkInfo *info = links.get( k );
		info -> resolveLinks( map );
	}
}

