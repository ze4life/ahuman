#include "body_impl.h"

Sensors::Sensors()
:	engine( AIEngine::getInstance() ) {

	// init variables
	threadSensesTracker = ( RFC_HND )NULL;
	runSensesTracker = true;
}

void Sensors::onCreateArea() {
	createSensors();
};
void Sensors::onLoadArea() {
	// for body areas create and load are the same
	onCreateArea();
}
void Sensors::onBrainStart() {
	// start sensors
	for( int k = 0; k < sensors.count(); k++ ) {
		Sensor *sensor = sensors.getClassByIndex( k );
		sensor -> startSensor();
	}

	// start poller
	startTracker();
}
void Sensors::onBrainStop() {
	// stop poller
	runSensesTracker = false;
	if( threadSensesTracker != NULL ) {
		engine.waitThreadExited( threadSensesTracker );
		threadSensesTracker = ( RFC_HND )NULL;
	}

	// stop sensors
	for( int k = 0; k < sensors.count(); k++ ) {
		Sensor *sensor = sensors.getClassByIndex( k );
		sensor -> stopSensor();
	}
}

void Sensors::createSensors() {
	addSensor( Sensor::createFileSysWalker( this ) );
}

void Sensors::addSensor( Sensor *att ) {
	sensors.add( att -> getName() , att );

	// generate cortex dimentions - square-like
	BrainLocation cortexLocation;
	int nInputs = att -> getNInputs();
	int nOutputs = att -> getNOutputs();
	int dz = 2;
	int dx = min( nInputs , nOutputs );
	int dy = ( ( nInputs + nOutputs ) / dx ) / dz;
	if( ( dx * dy * dz ) < ( nInputs + nOutputs ) )
		dy++;

	cortexLocation.setDimensions( dx , dy , dz );
	BrainLocation areaLocation = MindArea::getLocation();
	areaLocation.placeLocation( coverLocation , cortexLocation );

	// add to brain
	AIBrain brain;
	brain.addHardcodedCortex( this , areaLocation , att );
}

Sensor *Sensors::getSensor( String name ) {
	return( sensors.get( name ) );
}

void Sensors::startTracker() {
	// start tracking thread
	threadSensesTracker = engine.runThread( "SensesTracker" , this , ( ObjectThreadFunction )&Sensors::onRunSensesTracker , NULL );
}

void Sensors::onRunSensesTracker( void *p_arg ) {
	logger.attach( "SensesTracker" );

	// run until stop signal
	int sleepRemained = 0;
	while( runSensesTracker ) {
		pollIteration( sleepRemained );
	}
}

void Sensors::pollIteration( int& sleepRemained ) {
	int timeNow = Timer::timeNow();

	// iterate sensors and find sleep time required
	int minMs = 0;
	for( int k = sensors.count() - 1; k >= 0; k-- ) {
		Sensor *sensor = sensors.getClassByIndex( k );

		// get poll status and time to next poll
		bool poll = sensor -> getPollState();
		if( poll ) {
			int ms = sensor -> getPollInterval( timeNow );

			// run all in poll state
			if( ms <= 0 )
				sensor -> runPoll();

			if( minMs == 0 || ( ms > 0 && ms < minMs ) )
				minMs = ms;
		}
	}

	// check need sleep
	if( minMs == 0 )
		rfc_thr_sleep( 1 );
	else {
		// buffered sleep time
		sleepRemained += minMs;
		int sleepSeconds = sleepRemained / 1000;
		if( sleepSeconds > 0 ) {
			rfc_thr_sleep( sleepSeconds );
			sleepRemained %= 1000;
		}
	}
}

MindArea *AIBodyImpl::createSensors()
{
	Sensors *area = new Sensors();
	return( area );
}

Sensors *Sensors::getSensors()
{
	AIBrain brain;
	MindArea *area = brain.getMindArea( "Sensors" );
	Sensors *sensors = static_cast<Sensors *>( area );
	return( sensors );
}

