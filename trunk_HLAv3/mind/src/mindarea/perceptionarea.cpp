#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class PerceptionArea : public MindArea {
public:
	PerceptionArea();
	virtual const char *getClass() { return( "PerceptionArea" ); };

public:
	// mind area lifecycle
	virtual void initRegionsInArea( MindTarget *target );
	virtual void wakeupArea( MindActiveMemory *activeMemory ) {};
	virtual void suspendArea() {};

private:
	void createSensoryNetwork( MindSensor *sensor );

private:
	MindTarget *target;
};

/*#########################################################################*/
/*#########################################################################*/

MindArea *MindService::createPerceptionArea() { return( new PerceptionArea() ); };

/*#########################################################################*/
/*#########################################################################*/

PerceptionArea::PerceptionArea() {
	target = NULL;
}

void PerceptionArea::initRegionsInArea( MindTarget *p_target ) {
	target = p_target;
	MindSensorSet *sensorSet = target -> getSensorSet();

	// create regions for sensors
	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );
		createSensoryNetwork( sensor );
	}
}

void PerceptionArea::createSensoryNetwork( MindSensor *sensor ) {
	// create separate network for sensor - by its name
	String name = sensor -> getClass();

	// create area network if network is available and permitted in this area
	MindAreaNet *net = MindArea::createAreaNetwork( name );
	if( net == NULL )
		return;

	// create cortex region for sensor
	MindService *ms = MindService::getService();
	CortexRegionInfo info;
	MindRegion *region = ms -> createCortexRegion( this , name , &info );
	MindArea::addRegion( region );

	// add the only region
	net -> addRegion( region );
}
