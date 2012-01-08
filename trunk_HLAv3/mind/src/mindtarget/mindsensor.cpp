#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindSensor::MindSensor( SensorArea *p_area )
:	MindRegion( p_area )
{
	msgId = 0;
	pollState = false;
	pollNextMs = 0;
	pollIntervalMs = 0;

	memorySensorySignal = NULL;
	memorySensoryFeedbackSignal = NULL;
}

String MindSensor::getRegionType() {
	return( "MindSensor" );
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
	if( entity.equals( "sensor.data" ) ) {
		memorySensorySignal -> getSizeInfo( sizeX , sizeY );
		return;
	}

	if( entity.equals( "sensor.control-feedback" ) ) {
		memorySensoryFeedbackSignal -> getSizeInfo( sizeX , sizeY );
		return;
	}
}

void MindSensor::createRegion() {
	// call sensor creation
	createSensor();

	// construct event handlers
	sourceSensoryData.create( this , "sensor.data" );
	sourceSensoryControlFeedback.create( this , "sensor.control-feedback" );
	targetSensoryControl.create( this , "sensor.control" );
	targetSensoryControl.setHandler( ( MindRegion::NeuroLinkTargetHandler )&MindSensor::applySensorControl );

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
}

void MindSensor::processSensorData( String id ) {
	++msgId;
	memorySensorySignal -> setId( id );
	memorySensorySignal -> setTs( Timer::getCurrentTimeMillis() );

	// log sensor message
	logger.logInfo( "processSensorData: send signal id=" + id );
	if( logger.isLogAll() ) {
		String logmsg = "processSensorData: send data signal id=" + id + ", data=" + memorySensorySignal -> getNumberDataString();
		logger.logDebug( logmsg );
	}

	sourceSensoryData.sendMessage( memorySensorySignal );
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

void MindSensor::applySensorControl( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData ) {
	// TBD: process control signal
	// generate control feedback message
	sourceSensoryControlFeedback.sendMessage( memorySensoryFeedbackSignal );
}

int MindSensor::getSignalSize() {
	return( memorySensorySignal -> getMaxSize() );
}
