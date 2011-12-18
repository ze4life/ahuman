#include <ah_mind.h>
#include <ah_mind_impl.h>

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
}

void MindSensor::createControlFeedbackSignal( int sizeX , int sizeY ) {
	ASSERTMSG( sizeX > 0 && sizeY > 0 , "createControlFeedbackSignal: invalid value" );
	memorySensoryFeedbackSignal = new NeuroSignal( sizeX , sizeY );
}

void MindSensor::getSourceSizes( String entity , int *sizeX , int *sizeY ) {
	if( entity.equals( "data" ) ) {
		memorySensorySignal -> getSizeInfo( sizeX , sizeY );
		return;
	}

	if( entity.equals( "control-feedback" ) ) {
		memorySensoryFeedbackSignal -> getSizeInfo( sizeX , sizeY );
		return;
	}
}

void MindSensor::createRegion() {
	// call sensor creation
	createSensor();

	// construct event handlers
	sourceSensoryData = new NeuroLinkSource( this , "data" );
	sourceSensoryControlFeedback = new NeuroLinkSource( this , "control-feedback" );
	targetSensoryControl = new NeuroLinkTarget( this );
	targetSensoryControl -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&MindSensor::applySensorControl );

	sourceSensoryData -> setSourceSignal( memorySensorySignal );
	sourceSensoryControlFeedback -> setSourceSignal( memorySensoryFeedbackSignal );

	int sizeX , sizeY;
	memorySensorySignal -> getSizeInfo( &sizeX , &sizeY );
	logger.logDebug( String( "createRegion: created sensor region: signalSize=" ) + getSignalSize() );
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
	// log sensor message
	neurovt_signal *s = memorySensorySignal -> getRawData();
	int sn = memorySensorySignal -> getSize();
	String logmsg = "processSensorData: send signal=";
	for( int k = 0; k < sn; k++ ) {
		char x;
		if( s[ k ] == 0 )
			x = '0';
		else
		if( s[ k ] < NEURON_FIRE_IMPULSE_pQ )
			x = 'l';
		else
			x = 'h';

		logmsg += x;
	}
	logmsg.trimTrailing( '0' );

	logger.logDebug( logmsg );
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
	return( memorySensorySignal -> getSize() );
}
