#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaDef::MindAreaDef() {
	attachLogger();
	enabled = false;
}

MindAreaDef::~MindAreaDef() {
	services.destroy();
	regions.destroy();
	circuits.destroy();
	connections.destroy();
};

void MindAreaDef::createFromXml( Xml xml ) {
	// attributes are properties
	areaId = xml.getAttribute( "id" );
	areaType = xml.getAttribute( "type" );
	areaName = xml.getAttribute( "name" );
	areaFunction = xml.getAttribute( "function" );
	Object::setInstance( areaId );

	enabled = xml.getBooleanAttribute( "enabled" , true );
	if( !enabled )
		return;

	// read services
	for( Xml xmlChild = xml.getFirstChild( "service" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "service" ) ) {
		// construct MindArea from attributes
		MindServiceDef *service = new MindServiceDef( this );
		service -> createFromXml( xmlChild );
		services.add( service );
		serviceMap.add( service -> getServiceId() , service );
	}

	// read circuits
	for( Xml xmlChild = xml.getFirstChild( "circuit" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "circuit" ) ) {
		// construct MindArea from attributes
		MindLocalCircuitDef *circuit = new MindLocalCircuitDef( this );
		circuit -> createFromXml( xmlChild );
		circuits.add( circuit );
		circuitMap.add( circuit -> getId() , circuit );
	}
}

void MindAreaDef::resolveReferences( MindMap *map ) {
	for( int k = 0; k < regions.count(); k++ )
		regions.get( k ) -> resolveReferences( map );
}

MindRegionDef *MindAreaDef::findRegion( String region ) {
	return( regionMap.get( region ) );
}

void MindAreaDef::addRegion( MindRegionDef *region ) {
	regions.add( region );
	regionMap.add( region -> getId() , region );
}

void MindAreaDef::addConnection( MindCircuitConnectionDef *connection ) {
	connections.add( connection );
}
