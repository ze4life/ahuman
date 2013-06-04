#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

TargetConnectionTypeDef::TargetConnectionTypeDef() {
	linkInfo = NULL;
}

TargetConnectionTypeDef::~TargetConnectionTypeDef() {
}

void TargetConnectionTypeDef::defineConnectionTypeDef( TargetCircuitDef *circuitInfoTarget , TargetRegionConnectorDef *regionConnection , Xml xml ) {
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();

	String actuatorId = circuitInfoTarget -> getActuatorId();
	String linkedRegion = regionConnection -> getRegion();
	MindConnectionTypeDef::name = "actuator." + actuatorId + "-" + regionConnection -> getConnector();

	MindRegionDef *regionInfo = mm -> getRegionDefById( linkedRegion );
	if( regionConnection -> isTarget() ) {
		// dst will be actuator
		MindConnectionTypeDef::srcRegionType = regionInfo -> getTypeName();
		MindConnectionTypeDef::dstRegionType = actuatorId;
	}
	else {
		// src will be actuator
		MindConnectionTypeDef::srcRegionType = actuatorId;
		MindConnectionTypeDef::dstRegionType = regionInfo -> getTypeName();
	}

	// add single connection
	linkInfo = new TargetConnectionLinkTypeDef( this );
	linkInfo -> defineConnectionLinkTypeDef( circuitInfoTarget , regionConnection , xml );
	MindConnectionTypeDef::links.add( linkInfo );
	MindConnectionTypeDef::linkMap.add( regionConnection -> getConnector() , linkInfo );
}
