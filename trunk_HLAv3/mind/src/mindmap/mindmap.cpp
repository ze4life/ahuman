#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindMap::~MindMap() {
	regionTypeSet.destroy();
	mindAreaSet.destroy();
	linkTypeSet.destroy();
}

MindRegionTypeDef *MindMap::getRegionTypeDefByName( String regionTypeName ) {
	MindRegionTypeDef *info = regionTypeMap.get( regionTypeName );
	ASSERTMSG( info != NULL , "Wrong region type name=" + regionTypeName );
	return( info );
}

MindAreaDef *MindMap::getAreaDefById( String areaId ) {
	MindAreaDef *info = mindAreaMap.get( areaId );
	ASSERTMSG( info != NULL , "Wrong area id=" + areaId );
	return( info );
}

void MindMap::createFromXml( Xml xml ) {
	createRegionTypeDefSet( xml.getFirstChild( "MindRegionTypeSet" ) );
	createAreaDefSet( xml.getFirstChild( "MindAreaSet" ) );
	createCircuitLinkTypeDefSet( xml.getFirstChild( "MindCircuitLinkTypeSet" ) );
}

void MindMap::createRegionTypeDefSet( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "MindRegionType" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindRegionType" ) ) {
		// construct MindRegionType from attributes
		MindRegionTypeDef *info = new MindRegionTypeDef;
		regionTypeSet.add( info );

		info -> createFromXml( xmlChild );

		// get region type name
		String name = info -> getName();
		ASSERTMSG( !name.isEmpty() , "region type is not defined: " + xmlChild.serialize() );
		ASSERTMSG( regionTypeMap.get( name ) == NULL , name + ": region type duplicate found for name=" + name );

		// add
		regionTypeMap.add( name , info );
	}
}

void MindMap::createAreaDefSet( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "MindArea" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindArea" ) ) {
		// construct MindArea from attributes
		MindAreaDef *info = new MindAreaDef;
		mindAreaSet.add( info );

		info -> createFromXml( xmlChild );

		// get areaId
		String id = info -> getAreaId();
		ASSERTMSG( !id.isEmpty() , "area is not defined: " + xmlChild.serialize() );
		ASSERTMSG( mindAreaMap.get( id ) == NULL , id + ": area duplicate found for id=" + id );

		// add
		mindAreaMap.add( id , info );
	}
}

void MindMap::createCircuitLinkTypeDefSet( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "MindCircuitLinkTypeDef" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "MindCircuitLinkTypeDef" ) ) {
		// construct MindArea from attributes
		MindCircuitLinkTypeDef *linkType = new MindCircuitLinkTypeDef;
		linkType -> createFromXml( xmlChild );
		linkTypeSet.add( linkType );
		linkTypeMap.add( linkType -> getName() , linkType );
	}
}

MindCircuitLinkTypeDef *MindMap::getLinkTypeDefByName( String typeName ) {
	return( linkTypeMap.get( typeName ) );
}

