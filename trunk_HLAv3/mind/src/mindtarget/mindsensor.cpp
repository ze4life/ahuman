#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

MindSensor::MindSensor( SensorArea *p_area )
:	MindRegion( p_area ) {
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

NeuroLinkSource *MindSensor::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "data" ) )
		return( &sourceSensoryData );
	if( entity.equals( "control-feedback" ) )
		return( &sourceSensoryControlFeedback );

	return( NULL );
}

NeuroLinkTarget *MindSensor::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "control" ) )
		return( &targetSensoryControl );

	return( NULL );
}

void MindSensor::applySensorControl( NeuroLink *link , NeuroVector *srcData ) {
}
