#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

TargetCircuitDef::TargetCircuitDef( TargetAreaDef *areaDef , TargetRegionDef *p_regionInfo ) : MindLocalCircuitDef( areaDef ) {
	regionInfo = p_regionInfo;
}

TargetCircuitDef::~TargetCircuitDef() {
}

void TargetCircuitDef::defineCircuit( bool p_isSensorOption , Xml xmlRegion ) {
	// circuit for the only sensor/effector
	isSensorOption = p_isSensorOption;
	actuatorId = xmlRegion.getAttribute( "id" );

	// circuit data
	MindLocalCircuitDef::id = actuatorId + ".CIRCUIT";
	MindLocalCircuitDef::name = actuatorId  + " Circuit";
	Object::setInstance( MindLocalCircuitDef::id );
	MindLocalCircuitDef::enabled = true;

	MindLocalCircuitDef::regionMap.add( regionInfo -> getId() , regionInfo );
}

void TargetCircuitDef::defineCircuitConnection( TargetRegionConnectorDef *regionConnection , Xml xml ) {
	TargetCircuitConnectionDef *connectionInfo = new TargetCircuitConnectionDef( this );
	connectionInfo -> defineCircuitConnectorDef( regionConnection , xml );
	MindLocalCircuitDef::connections.add( connectionInfo -> getId() , connectionInfo );
}

