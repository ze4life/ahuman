#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

SensorArea::SensorArea( MindTarget *p_target ) {
	attachLogger();

	target = p_target;
	sensors = NULL;
	sensorsOffline = NULL;
}

SensorArea::~SensorArea() {
}

void SensorArea::createSensorArea() {
	sensors = new MindSensorSet( this );
	sensorsOffline = new MindSensorSet( this );
}

void SensorArea::startSensorArea() {
	// start sensors
	sensors -> startSensorSet();
}

void SensorArea::stopSensorArea() {
	// stop sensors
	sensors -> stopSensorSet();
}

void SensorArea::initSensorArea() {
	MindService *ms = MindService::getService();

	// add regions
	for( int k = 0; k < sensors -> getCount(); k++ ) {
		MindSensor *sensor = sensors -> getSetItem( k );
		createSensor( sensor );
	}

	ms -> addArea( this );

	// add links
	for( int k = 0; k < sensors -> getCount(); k++ ) {
		MindSensor *sensor = sensors -> getSetItem( k );
		createSensorLinks( sensor );
	}
}

void SensorArea::createSensor( MindSensor *sensor ) {
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();

	TargetRegionDef *regioninfo = mm -> getTargetRegionDefById( sensor -> getSensorName() );

	MindRegionCreateInfo regionInfo;
	MindRegionTypeDef *regiontype = regioninfo -> getType();
	regionInfo.setId( sensor -> getSensorName() );
	regionInfo.setType( regiontype );

	sensor -> setSensorInfo( regioninfo );
	sensor -> setRegionType( regiontype );

	// create sensor data
	MindRegion *region = ( MindRegion * )sensor;
	region -> createRegion( &regionInfo );
	MindArea::addRegion( region );
}

void SensorArea::createSensorLinks( MindSensor *sensor ) {
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();

	TargetRegionDef *regioninfo = sensor -> getSensorInfo();
	TargetCircuitDef *circuitinfo = regioninfo -> getCircuitDef();
	ms -> createCircuitLinks( circuitinfo );
}

void SensorArea::addSensor( MindSensor *sensor , bool offline ) {
	sensor -> setRegionId( sensor -> getSensorName() );

	if( !offline ) {
		sensors -> addSetItem( sensor );
		logger.logInfo( "addSensor: sensor added - name=" + sensor -> getSensorName() );
	}
	else {
		sensorsOffline -> addSetItem( sensor );
		logger.logInfo( "addSensor: sensor is not configured to run - name=" + sensor -> getSensorName() );
	}
}

MindSensor *SensorArea::getSensor( String name ) {
	return( sensors -> getSensor( name ) );
}

