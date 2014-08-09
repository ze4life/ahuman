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
	Object::setInstance( id );

	name = xml.getAttribute( "name" );
	imgheight = xml.getAttribute( "imgheight" , "" );
	enabled = xml.getBooleanAttribute( "enabled" , true );

	if( !enabled )
		return;

	// read circuit items
	for( Xml xmlChild = xml.getFirstChild( "region" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "region" ) ) {
		// construct MindArea from attributes
		MindRegionDef *region = new MindRegionDef( area , this );
		region -> createFromXml( xmlChild );
		regionMap.add( region -> getId() , region );
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

void MindLocalCircuitDef::getInternalConnections( ClassList<MindLocalCircuitConnectionDef>& links ) {
	for( int k = 0; k < connections.count(); k++ ) {
		MindLocalCircuitConnectionDef *connection = connections.getClassByIndex( k );
		if( regionMap.get( connection -> getSrcRegion() ) != NULL &&
			regionMap.get( connection -> getDstRegion() ) != NULL )
			links.add( connection );
	}
}

void MindLocalCircuitDef::getExternalConnections( ClassList<MindLocalCircuitConnectionDef>& links , bool isin ) {
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();

	ClassList<MindLocalCircuitDef>& circuits = mm -> getMindLocalCircuits();
	for( int k = 0; k < circuits.count(); k++ ) {
		MindLocalCircuitDef *circuit = circuits.get( k );
		MapStringToClass<MindLocalCircuitConnectionDef>& extlinks = circuit -> getConnections();

		for( int m = 0; m < extlinks.count(); m++ ) {
			MindLocalCircuitConnectionDef *link = extlinks.getClassByIndex( m );
			if( isin ) {
				if( regionMap.get( link -> getSrcRegion() ) == NULL &&
					regionMap.get( link -> getDstRegion() ) != NULL )
					links.add( link );
			}
			else {
				if( regionMap.get( link -> getSrcRegion() ) != NULL &&
					regionMap.get( link -> getDstRegion() ) == NULL )
					links.add( link );
			}
		}
	}
}
