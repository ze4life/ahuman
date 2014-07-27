#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindLocalCircuitDef::MindLocalCircuitDef( MindAreaDef *p_area ) {
	attachLogger();
	area = p_area;
	enabled = false;
}

MindLocalCircuitDef::~MindLocalCircuitDef() {
};

void MindLocalCircuitDef::createFromXml( Xml xml ) {
	// attributes are properties
	id = xml.getAttribute( "id" );
	name = xml.getAttribute( "name" );
	Object::setInstance( id );

	enabled = xml.getBooleanAttribute( "enabled" , true );
	if( !enabled )
		return;

	// read circuit items
	for( Xml xmlChild = xml.getFirstChild( "region" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "region" ) ) {
		// construct MindArea from attributes
		MindRegionDef *region = new MindRegionDef( area , this );
		region -> createFromXml( xmlChild );
		area -> addRegion( region );
	}

	// read connections
	for( Xml xmlChild = xml.getFirstChild( "connection" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "connection" ) ) {
		// construct MindArea from attributes
		MindLocalCircuitConnectionDef *connection = new MindLocalCircuitConnectionDef( this );
		connection -> createFromXml( xmlChild );
		area -> addConnection( connection );
		connections.add( connection -> getId() , connection );
	}
}

void MindLocalCircuitDef::resolveReferences( MindMap *map ) {
	for( int k = 0; k < connections.count(); k++ ) {
		MindLocalCircuitConnectionDef *connection = connections.getClassByIndex( k );
		connection -> resolveReferences( map );
	}
}

