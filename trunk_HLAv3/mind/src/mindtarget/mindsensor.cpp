#include <ah_mind.h>

/*#########################################################################*/
/*#########################################################################*/

MindSensor::MindSensor( SensorArea *p_area )
:	MindRegion( p_area )
{
	pollState = false;
	pollNextMs = 0;
	pollIntervalMs = 0;

	memorySensorySignal = NULL;
	memorySensoryFeedbackSignal = NULL;

	sourceSensoryData = NULL;
	sourceSensoryControlFeedback = NULL;
	targetSensoryControl = NULL;
}

void MindSensor::setPollState( bool state ) {
	pollState = state;
}

void MindSensor::createSensorySignal( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0 , "createSensorySignal: invalid value" );
	memorySensorySignal = new NeuroSignal( sizeX , sizeY );
	sourceSensoryData -> setSourceSignal( memorySensorySignal );
}

void MindSensor::createControlFeedbackSignal( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0 , "createControlFeedbackSignal: invalid value" );
	memorySensoryFeedbackSignal = new NeuroSignal( sizeX , sizeY );
	sourceSensoryControlFeedback -> setSourceSignal( memorySensoryFeedbackSignal );
}

void MindSensor::createRegion() {
	sourceSensoryData = new NeuroLinkSource( this );
	sourceSensoryControlFeedback = new NeuroLinkSource( this );
	targetSensoryControl = new NeuroLinkTarget( this );
	targetSensoryControl -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&MindSensor::applySensorControl );

	// call sensor creation
	createSensor();
}

void MindSensor::exitRegion() {
}

void MindSensor::destroyRegion() {
	if( memorySensorySignal != NULL )
		delete memorySensorySignal;
	if( memorySensoryFeedbackSignal != NULL )
		delete memorySensoryFeedbackSignal;

	memorySensorySignal = NULL;
	memorySensoryFeedbackSignal = NULL;

	if( sourceSensoryData != NULL )
		delete sourceSensoryData;
	if( sourceSensoryControlFeedback != NULL )
		delete sourceSensoryControlFeedback;
	if( targetSensoryControl != NULL )
		delete targetSensoryControl;

	sourceSensoryData = NULL;
	sourceSensoryControlFeedback = NULL;
	targetSensoryControl = NULL;
}

void MindSensor::processSensorData() {
	sourceSensoryData -> sendMessage();
}

bool MindSensor::getPollState() {
	return( pollState );
}

int MindSensor::getPollIntervalMs( int timeNowMs ) {
	return( pollNextMs - timeNowMs );
}

NeuroSignal *MindSensor::getSensorySignal() {
	return( memorySensorySignal );
}

NeuroLinkSource *MindSensor::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "data" ) )
		return( sourceSensoryData );
	if( entity.equals( "control-feedback" ) )
		return( sourceSensoryControlFeedback );

	return( NULL );
}

NeuroLinkTarget *MindSensor::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "control" ) )
		return( targetSensoryControl );

	return( NULL );
}

void MindSensor::applySensorControl( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	// TBD: process control signal
	// generate control feedback message
	sourceSensoryControlFeedback -> sendMessage();
}

int MindSensor::getSignalSize() {
	int nx , ny;
	memorySensorySignal -> getSizeInfo( &nx , &ny );
	return( nx * ny );
}
