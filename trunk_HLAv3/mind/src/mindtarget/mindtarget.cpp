#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindTarget::MindTarget() {
	attachLogger();

	sensorArea = NULL;
	sensors = NULL;
	sensorsOffline = NULL;
	effectorsOffline = NULL;
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
	effectorsOffline = new MindEffectorSet();
	sensorTracker = new MindSensorSetTracker( sensors );

	effectorArea = MindTarget::createEffectorArea();
	effectors = new MindEffectorSet();

	// call target with sensors and effectors
	createTarget( sensorArea , effectorArea );
}

void MindTarget::initService() {
	MindService *ms = MindService::getService();
	ms -> setMindTarget( this );

	// create areas
	effectorArea -> createEffectorArea( this );

	// init areas
	sensorArea -> initSensorArea();
	effectorArea -> initEffectorArea();

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
		sensors -> addSetItem( sensor );
		sensor -> configureSensor( config );
		logger.logInfo( "addSensor: sensor added - name=" + name );
	}
	else {
		sensorsOffline -> addSetItem( sensor );
		logger.logInfo( "addSensor: sensor is not configured to run - name=" + name );
	}
}

void MindTarget::addEffector( MindEffector *effector ) {
	String name = effector -> getClass();
	Xml config = configEffectors.getChildNamedNode( "effector" , name );

	if( config.exists() && config.getBooleanAttribute( "run" , true ) ) {
		effectors -> addSetItem( effector );
		effector -> configureEffector( config );
		logger.logInfo( "addEffector: effector added - name=" + name );
	}
	else {
		effectorsOffline -> addSetItem( effector );
		logger.logInfo( "addEffector: effector is not configured to run - name=" + name );
	}
}

MindSensorSet *MindTarget::getSensorSet() {
	return( sensors );
}

MindSensor *MindTarget::getSensor( String name ) {
	return( sensors -> getSensor( name ) );
}
