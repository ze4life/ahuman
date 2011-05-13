#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

MindSensor::MindSensor() {
	pollState = false;
	pollNextMs = 0;
	pollIntervalMs = 0;

	memorySensoryData = NULL;
	memorySensoryControl = NULL;
}

void MindSensor::setPollState( bool state ) {
	pollState = state;
}

neurovt *MindSensor::createSensoryDataMemoryNVT( int sizeNVT ) {
	ASSERTMSG( sizeNVT > 0 , "createSensoryDataMemoryNVT: invalid value" );
	memorySensoryData = ( neurovt * )calloc( sizeNVT , sizeof( neurovt ) );
	return( memorySensoryData );
}

neurovt *MindSensor::createSensoryControlMemoryNVT( int sizeNVT ) {
	ASSERTMSG( sizeNVT > 0 , "createSensoryControlMemoryNVT: invalid value" );
	memorySensoryControl = ( neurovt * )calloc( sizeNVT , sizeof( neurovt ) );
	return( memorySensoryControl );
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
}

bool MindSensor::getPollState() {
	return( pollState );
}

int MindSensor::getPollIntervalMs( int timeNowMs ) {
	return( pollNextMs - timeNowMs );
}
