#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

SensorArea *MindTarget::createSensorArea() {
	return( new SensorArea() );
}

/*#########################################################################*/
/*#########################################################################*/

SensorArea::SensorArea() {
	target = NULL;
}

SensorArea::~SensorArea() {
}

// own functions
void SensorArea::initSensorArea() {
}

MindTarget *SensorArea::getTarget() {
	return( target );
}

// mind area lifecycle
void SensorArea::initRegionsInArea( MindTarget *p_target ) {
	target = p_target;
	MindSensorSet *sensorSet = target -> getSensorSet();

	// create sensors
	sensorSet -> createSensorSet( this );

	// create networks
	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );
		createSensoryNetwork( sensor );
	}
}

void SensorArea::wakeupArea( MindActiveMemory *activeMemory ) {
}

void SensorArea::suspendArea() {
}

void SensorArea::createSensoryNetwork( MindSensor *sensor ) {
	// create separate network for sensor - by its name
	String name = sensor -> getClass();

	// create area network if network is available and permitted in this area
	MindAreaNet *net = MindArea::createAreaNetwork( name );
	if( net == NULL )
		return;

	// add the only region
	net -> addRegion( sensor );
}
