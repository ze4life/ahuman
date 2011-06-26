#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

MindSensor::MindSensor() {
	pollState = false;
	pollNextMs = 0;
	pollIntervalMs = 0;

	memorySensoryData = NULL;
	memorySensoryControl = NULL;

	sizeSensoryData = 0;
	sizeControlData = 0;
	sizeControlFeedbackData = 0;
}

void MindSensor::setPollState( bool state ) {
	pollState = state;
}

neurovt *MindSensor::createSensoryDataMemoryNVT( int sizeNVT ) {
	ASSERTMSG( sizeNVT > 0 , "createSensoryDataMemoryNVT: invalid value" );
	sizeSensoryData = sizeNVT;

	memorySensoryData = ( neurovt * )calloc( sizeNVT , sizeof( neurovt ) );
	return( memorySensoryData );
}

neurovt *MindSensor::createSensoryControlMemoryNVT( int sizeNVT ) {
	ASSERTMSG( sizeNVT > 0 , "createSensoryControlMemoryNVT: invalid value" );
	sizeControlData = sizeNVT;

	memorySensoryControl = ( neurovt * )calloc( sizeNVT , sizeof( neurovt ) );
	return( memorySensoryControl );
}

void MindSensor::createRegion() {
}

void MindSensor::exitRegion() {
}

void MindSensor::destroyRegion() {
	if( memorySensoryData != NULL )
		free( memorySensoryData );
	memorySensoryData = NULL;
	if( memorySensoryControl != NULL )
		free( memorySensoryControl );
	memorySensoryControl = NULL;
}

void MindSensor::processSensorData() {
	MindRegion::sendOutputData( memorySensoryData , sizeSensoryData );
}

bool MindSensor::getPollState() {
	return( pollState );
}

int MindSensor::getPollIntervalMs( int timeNowMs ) {
	return( pollNextMs - timeNowMs );
}

// link creation
void MindSensor::createNeuroLinks( MindRegion *dst ) {
	dst -> createNeuroLinksFromSensorRegion( this );
}

void MindSensor::createNeuroLinksFromCortexRegion( CortexRegion *src ) {
	logger.logDebug( "createNeuroLinksFromCortexRegion" );
}

void MindSensor::createNeuroLinksFromNucleiRegion( NucleiRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNucleiRegion" );
}

void MindSensor::createNeuroLinksFromNerveRegion( NerveRegion *src ) {
	logger.logDebug( "createNeuroLinksFromNerveRegion" );
}

void MindSensor::createNeuroLinksFromSensorRegion( MindSensor *src ) {
	ASSERTFAILED( String( "Invalid sensor/sensor link requested - src=" ) + src -> getRegionId() + ", dst=" + getRegionId() );
}

