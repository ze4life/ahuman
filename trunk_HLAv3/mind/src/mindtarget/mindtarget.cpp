#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindTarget::MindTarget() {
	attachLogger();

	sensorArea = NULL;
	sensors = NULL;
	sensorsOffline = NULL;
	sensorTracker = NULL;

	effectorArea = NULL;
	effectors = NULL;
}

void MindTarget::configureSensors( Xml xml ) {
	configSensors = xml;
}

void MindTarget::configureEffectors( Xml xml ) {
	configEffectors = xml;
}

void MindTarget::configureService( Xml config ) {
	configureSensors( config.getChildNode( "sensors" ) );
	configureEffectors( config.getChildNode( "effectors" ) );
}

void MindTarget::createService() {
	sensorArea = MindTarget::createSensorArea();
	sensors = new MindSensorSet();
	sensorsOffline = new MindSensorSet();
	sensorTracker = new MindSensorSetTracker( sensors );

	effectorArea = MindTarget::createEffectorArea();
	effectors = new MindEffectorSet();

	// call final target
	createTarget();
}

void MindTarget::initService() {
	MindService *ms = MindService::getService();
	ms -> setMindTarget( this );
	ms -> addMindArea( sensorArea );
	ms -> addMindArea( effectorArea );

	// call final target
	initSensorsTarget( sensorArea );
	initEffectorsTarget( effectorArea );
}

void MindTarget::runService() {
	startSensors();

	// call final target
	runTarget();
}

void MindTarget::stopService() {
	stopSensors();

	// call final target
	stopTarget();
}

void MindTarget::exitService() {
	// call final target
	exitTarget();
}

void MindTarget::destroyService() {
	// call final target
	destroyTarget();
}

void MindTarget::startSensors() {
	// start sensors
	sensors -> startSensorSet();

	// start poller
	sensorTracker -> startTracker();
}

void MindTarget::stopSensors() {
	// stop poller
	sensorTracker -> stopTracker();

	// stop sensors
	sensors -> stopSensorSet();
}

void MindTarget::addSensor( MindSensor *sensor ) {
	String name = sensor -> getClass();
	Xml config = configSensors.getChildNamedNode( "sensor" , name );

	if( config.exists() && config.getBooleanAttribute( "run" , true ) ) {
		sensors -> addSensor( sensor );
		logger.logInfo( "addSensor: sensor added - name=" + name );
	}
	else {
		sensorsOffline -> addSensor( sensor );
		logger.logInfo( "addSensor: sensor is not configured to run - name=" + name );
	}
}

MindSensor *MindTarget::getSensor( String name ) {
	return( sensors -> getSensor( name ) );
}
