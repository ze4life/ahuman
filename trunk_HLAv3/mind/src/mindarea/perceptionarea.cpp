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

	// create regions for target
	MindService *ms = MindService::getService();
	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );

		// create region for cortex
		MindRegion *region = ms -> createCortexRegion( this );
		MindArea::addRegion( getClass() , sensor -> getClass() , region );

		// add to network
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

	// add the only region
	net -> addRegion( sensor );
}
