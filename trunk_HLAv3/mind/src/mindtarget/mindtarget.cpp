#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindTarget::MindTarget() {
	attachLogger();
}

void MindTarget::configureSensors( Xml xml ) {
	configSensors = xml;
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

	if( config.exists() && config.getBooleanAttribute( "run" ) ) {
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

void MindTarget::configureService( Xml config ) {
}

void MindTarget::createService() {
}

void MindTarget::initService() {
}

void MindTarget::runService() {
}

void MindTarget::stopService() {
}

void MindTarget::exitService() {
}

void MindTarget::destroyService() {
}
