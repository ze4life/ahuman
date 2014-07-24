#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

TargetCircuitDef::TargetCircuitDef( MindAreaDef *areaDef ) : MindLocalCircuitDef( areaDef ) {
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
}

void TargetCircuitDef::defineCircuitConnection( TargetRegionConnectorDef *regionConnection , Xml xml ) {
	TargetCircuitConnectionDef *connectionInfo = new TargetCircuitConnectionDef( this );
	connectionInfo -> defineCircuitConnectorDef( regionConnection , xml );
	MindLocalCircuitDef::connections.add( connectionInfo -> getId() , connectionInfo );
}

