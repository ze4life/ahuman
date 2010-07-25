#include "brain_impl.h"

void MindMap::createFromXml( Xml xml )
{
	// child elements are MindAreaInfo
	for( Xml xmlChild = xml.getFirstChild( "MindArea" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindArea" ) ) {
		// construct MindArea from attributes
		MindAreaInfo *info = new MindAreaInfo;
		mindAreas.add( info );

		info -> createFromXml( xmlChild );

		// get areaId
		String id = info -> getAreaId();
		ASSERTMSG( !id.isEmpty() , "area is not defined: " + xmlChild.serialize() );
		ASSERTMSG( mindAreaMap.get( id ) == NULL , id + ": area duplicate found for id=" + id );

		// add
		mindAreaMap.add( id , info );
	}

	// resolve links
	for( int k = mindAreaMap.count() - 1; k >= 0; k-- ) {
		MindAreaInfo *info = mindAreaMap.getClassByIndex( k );
		info -> resolveLinks( this );
	}
}
