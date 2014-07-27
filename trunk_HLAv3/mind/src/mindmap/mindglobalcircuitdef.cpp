#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindGlobalCircuitDef::MindGlobalCircuitDef() {
	attachLogger();
	enabled = false;
}

MindGlobalCircuitDef::~MindGlobalCircuitDef() {
	connections.destroy();
};

void MindGlobalCircuitDef::createFromXml( Xml xml ) {
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
		MindGlobalCircuitRegionDef *region = new MindGlobalCircuitRegionDef( this );
		region -> createFromXml( xmlChild );
		regionMap.add( region -> getId() , region );
	}
}

void MindGlobalCircuitDef::resolveReferences( MindMap *map ) {
	for( int k = 0; k < regionMap.count(); k++ ) {
		MindGlobalCircuitRegionDef *region = regionMap.getClassByIndex( k );
		String id = region -> getId();
		addConnectons( map , id );
	}
}

void MindGlobalCircuitDef::addConnectons( MindMap *map , String region ) {
	MindRegionDef *regdef = map -> getRegionDefById( id );
	MindLocalCircuitDef *circuit = regdef -> getCircuit();
	MapStringToClass<MindLocalCircuitConnectionDef>& connections = circuit -> getConnections();

	for( int k = 0; k < connections.count(); k++ ) {
		MindLocalCircuitConnectionDef *c = connections.getClassByIndex( k );
		if( !region.equals( c -> getSrcRegion() ) )
			continue;

		if( regionMap.get( c -> getDstRegion() ) != NULL )
			continue;

		connections.addnew( c -> getId() , c );
	}
}

