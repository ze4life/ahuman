#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

MindSensor::MindSensor() {
	pollState = false;
	pollNextMs = 0;
	pollIntervalMs = 0;

	memorySensoryData = NULL;
	memorySensoryControlState = NULL;
}

void MindSensor::setPollState( bool state ) {
	pollState = state;
}

NeuroVector *MindSensor::createSensoryData( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0 , "createSensoryData: invalid value" );
	memorySensoryData = new  NeuroVector( sizeX , sizeY );
	return( memorySensoryData );
}

NeuroVector *MindSensor::createSensoryControlState( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0  , "createSensoryControl: invalid value" );
	memorySensoryControlState = new  NeuroVector( sizeX , sizeY );
	return( memorySensoryControlState );
}

void MindSensor::createRegion() {
}

void MindSensor::exitRegion() {
}

void MindSensor::destroyRegion() {
	if( memorySensoryData != NULL )
		free( memorySensoryData );
	memorySensoryData = NULL;
	if( memorySensoryControlState != NULL )
		free( memorySensoryControlState );
	memorySensoryControlState = NULL;
}

void MindSensor::processSensorData() {
	NeuroVector *data = new NeuroVector( memorySensoryData );
	MindMessage *msg = new MindMessage( linkFeedForward , data );
	MindRegion::sendMessage( msg );
}

bool MindSensor::getPollState() {
	return( pollState );
}

int MindSensor::getPollIntervalMs( int timeNowMs ) {
	return( pollNextMs - timeNowMs );
}

void MindSensor::setFeedForwardLink( NeuroLink *link ) {
	linkFeedForward = link;
}

NeuroVector *MindSensor::getSensoryData() {
	return( memorySensoryData );
}

