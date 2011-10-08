#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

MindSensor::MindSensor() {
	pollState = false;
	pollNextMs = 0;
	pollIntervalMs = 0;

	memorySensoryData = NULL;
	memorySensoryControlState = NULL;
	memorySensoryControlFeedback = NULL;
}

void MindSensor::setPollState( bool state ) {
	pollState = state;
}

NeuroVector *MindSensor::createSensoryData( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0 , "createSensoryData: invalid value" );
	memorySensoryData = new  NeuroVector( sizeX , sizeY );

	sourceSensoryData.setSourceVector( memorySensoryData );
	return( memorySensoryData );
}

NeuroVector *MindSensor::createSensoryControlState( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0  , "createSensoryControl: invalid value" );
	memorySensoryControlState = new  NeuroVector( sizeX , sizeY );

	return( memorySensoryControlState );
}

NeuroVector *MindSensor::createControlFeedbackData( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0 , "createControlFeedbackData: invalid value" );
	memorySensoryControlFeedback = new  NeuroVector( sizeX , sizeY );

	sourceSensoryData.setSourceVector( memorySensoryControlFeedback );
	return( memorySensoryData );
}

void MindSensor::createRegion() {
	targetSensoryControl.setHandler( this , ( MindRegion::NeuroLinkHandler )&MindSensor::applySensorControl );
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
	sourceSensoryData.sendMessage( this );
}

bool MindSensor::getPollState() {
	return( pollState );
}

int MindSensor::getPollIntervalMs( int timeNowMs ) {
	return( pollNextMs - timeNowMs );
}

NeuroVector *MindSensor::getSensoryData() {
	return( memorySensoryData );
}

NeuroLinkSource *MindSensor::getNeuroLinkSource( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( !linkInfo -> getLinkType() -> getName().equals( "sensor-stream" ) )
		return( NULL );

	String name = linkInfo -> getName();
	if( name.equals( "data" ) )
		return( &sourceSensoryData );
	if( name.equals( "control-feedback" ) )
		return( &sourceSensoryControlFeedback );

	return( NULL );
}

NeuroLinkTarget *MindSensor::getNeuroLinkTarget( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( !linkInfo -> getLinkType() -> getName().equals( "sensor-stream" ) )
		return( NULL );

	String name = linkInfo -> getName();
	if( name.equals( "control" ) )
		return( &targetSensoryControl );

	return( NULL );
}

void MindSensor::applySensorControl( NeuroLink *link , NeuroVector *srcData ) {
}
