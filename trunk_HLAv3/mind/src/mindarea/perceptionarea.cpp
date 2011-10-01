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

PerceptionArea::PerceptionArea() {
	target = NULL;
}

void PerceptionArea::initRegionsInArea( MindTarget *p_target ) {
	target = p_target;
	MindSensorSet *sensorSet = target -> getSensorSet();

	// create regions for target
	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );

		// create region for cortex
		CortexRegion *region = new CortexRegion();
		MindArea::addRegion( getClass() , sensor -> getClass() , region );
	}

	// create networks
	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );
		createSensoryNetwork( sensor );
	}
}

void PerceptionArea::createSensoryNetwork( MindSensor *sensor ) {
	// create separate network for sensor - by its name
	MindService *ms = MindService::getService();

	// find mind network
	String name = sensor -> getClass();
	MindNet *net = ms -> getMindNet( name );

	// create mind area network
	MindAreaNet *areaNet = new MindAreaNet( net );

	// find and add the only region
	MindRegion *region = MindArea::getRegion( getClass() , sensor -> getClass() );
	areaNet -> addRegion( region );

	// add network to area network set
	MindArea::addNet( areaNet );
}

/*#########################################################################*/
/*#########################################################################*/

MindArea *MindService::createPerceptionArea() { return( new PerceptionArea() ); };
