#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindMap::~MindMap() {
	regionTypeSet.destroy();
	mindAreaSet.destroy();
	linkTypeSet.destroy();
}

void MindMap::createFromXml( Xml xml ) {
	// load mind definition
	createRegionTypeDefSet( xml.getFirstChild( "region-type-set" ) );
	createAreaDefSet( xml.getFirstChild( "component-set" ) );
	createCircuitLinkTypeDefSet( xml.getFirstChild( "link-type-set" ) );
	createCircuitDefSet( xml.getFirstChild( "circuit-set" ) );
}

void MindMap::createRegionTypeDefSet( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "region-type" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "region-type" ) ) {
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

	for( Xml xmlChild = xml.getFirstChild( "area" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "area" ) ) {
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

		// add regions to map
		createRegionMap( info );
	}
}

void MindMap::createCircuitLinkTypeDefSet( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "connection-type" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "connection-type" ) ) {
		// construct MindArea from attributes
		MindCircuitLinkTypeDef *linkType = new MindCircuitLinkTypeDef;
		linkType -> createFromXml( xmlChild );
		linkTypeSet.add( linkType );
		linkTypeMap.add( linkType -> getName() , linkType );
	}
}

void MindMap::createCircuitDefSet( Xml xml ) {
	if( !xml.exists() )
		return;

	for( Xml xmlChild = xml.getFirstChild( "circuit" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "circuit" ) ) {
		// construct MindArea from attributes
		MindCircuitDef *circuit = new MindCircuitDef;
		circuit -> createFromXml( xmlChild );
		mindCircuitSet.add( circuit );
		mindCircuitMap.add( circuit -> getName() , circuit );
	}
}

void MindMap::createRegionMap( MindAreaDef *info ) {
	ClassList<MindRegionDef>& regions = info -> getRegions();
	for( int k = 0; k < regions.count(); k++ ) {
		MindRegionDef *region = regions.get( k );
		mindRegionMap.add( region -> getName() , region );
	}
}

MindCircuitLinkTypeDef *MindMap::getLinkTypeDefByName( String typeName ) {
	return( linkTypeMap.get( typeName ) );
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

