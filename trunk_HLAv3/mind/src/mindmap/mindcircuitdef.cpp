#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindCircuitDef::MindCircuitDef() {
	attachLogger();
	enabled = false;
}

MindCircuitDef::~MindCircuitDef() {
	connections.destroy();
};

void MindCircuitDef::createFromXml( Xml xml ) {
	// attributes are properties
	id = xml.getAttribute( "id" );
	name = xml.getAttribute( "name" );
	Object::setInstance( name );

	enabled = xml.getBooleanAttribute( "enabled" , true );
	if( !enabled )
		return;

	// read circuit items
	for( Xml xmlChild = xml.getFirstChild( "region" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "region" ) ) {
		// construct MindArea from attributes
		MindCircuitRegionDef *region = new MindCircuitRegionDef( this );
		region -> createFromXml( xmlChild );
		regionMap.add( region -> getId() , region );
	}
}

void MindCircuitDef::resolveReferences( MindMap *map ) {
	for( int k = 0; k < regionMap.count(); k++ ) {
		MindCircuitRegionDef *region = regionMap.getClassByIndex( k );
		String id = region -> getId();
		addConnectons( map , id );
	}
}

void MindCircuitDef::addConnectons( MindMap *map , String region ) {
	MindRegionDef *regdef = map -> getRegionDefById( id );
	MindLocalCircuitDef *circuit = regdef -> getCircuit();
	MapStringToClass<MindCircuitConnectionDef>& connections = circuit -> getConnections();

	for( int k = 0; k < connections.count(); k++ ) {
		MindCircuitConnectionDef *c = connections.getClassByIndex( k );
		if( !region.equals( c -> getSrcRegion() ) )
			continue;

		if( regionMap.get( c -> getDstRegion() ) != NULL )
			continue;

		connections.addnew( c -> getId() , c );
	}
}

