#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindMap::~MindMap() {
	mindAreas.destroy();
}

MindAreaInfo *MindMap::getAreaById( String areaId ) {
	MindAreaInfo *info = mindAreaMap.get( areaId );
	ASSERTMSG( info != NULL , "Wrong area id=" + areaId );
	return( info );
}

void MindMap::createFromXml( Xml xml ) {
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

	// child elements are MindAreaInfo
	Xml xmlLinks = xml.getFirstChild( "MindLinks" );

	Xml xmlChild;
	if( xmlLinks.exists() )
		xmlChild = xmlLinks.getFirstChild( "MindLink" );
	for( ; xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindLink" ) ) {
		// construct MindArea from attributes
		MindAreaLinkInfo *info = new MindAreaLinkInfo;
		info -> createFromXml( xmlChild );
		mindLinks.add( info );
	}
}
