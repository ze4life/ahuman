#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

TargetCircuitConnectionDef::TargetCircuitConnectionDef( TargetCircuitDef *circuitInfo ) : MindLocalCircuitConnectionDef( circuitInfo ) {
	regionConnection = NULL;
	connectionTypeDef = NULL;
}

TargetCircuitConnectionDef::~TargetCircuitConnectionDef() {
	if( connectionTypeDef != NULL )
		delete connectionTypeDef;
}

void TargetCircuitConnectionDef::defineCircuitConnectorDef( TargetRegionConnectorDef *p_regionConnection , Xml xml ) {
	regionConnection = p_regionConnection;
	TargetCircuitDef *circuitInfoTarget = ( TargetCircuitDef * )MindLocalCircuitConnectionDef::circuitDef;

	// check direction
	if( regionConnection -> getType().equals( "target" ) ) {
		MindLocalCircuitConnectionDef::srcRegion = regionConnection -> getRegion();
		MindLocalCircuitConnectionDef::dstRegion = circuitInfoTarget -> getActuatorId();
	}
	else {
		MindLocalCircuitConnectionDef::srcRegion = circuitInfoTarget -> getActuatorId();
		MindLocalCircuitConnectionDef::dstRegion = regionConnection -> getRegion();
	}

	// create unique connection type
	connectionTypeDef = new TargetConnectionTypeDef();
	connectionTypeDef -> defineConnectionTypeDef( circuitInfoTarget , regionConnection , xml );

	MindLocalCircuitConnectionDef::typeName = connectionTypeDef -> getName();
	Object::setInstance( MindLocalCircuitConnectionDef::typeName );
	MindLocalCircuitConnectionDef::type = connectionTypeDef;
	MindLocalCircuitConnectionDef::primary = xml.getBooleanAttribute( "primary" , false );
}
