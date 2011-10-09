#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class ThalamusArea : public MindArea {
public:
	ThalamusArea();
	virtual const char *getClass() { return( "ThalamusArea" ); };

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

MindArea *MindService::createThalamusArea() { return( new ThalamusArea() ); };

/*#########################################################################*/
/*#########################################################################*/

ThalamusArea::ThalamusArea() {
	target = NULL;
}

void ThalamusArea::initRegionsInArea( MindTarget *p_target ) {
	target = p_target;
	MindSensorSet *sensorSet = target -> getSensorSet();

	// create regions for sensors
	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );
		createSensoryNetwork( sensor );
	}
}

void ThalamusArea::createSensoryNetwork( MindSensor *sensor ) {
	// create separate network for sensor - by its name
	String name = sensor -> getClass();

	// create area network if network is available and permitted in this area
	MindAreaNet *net = MindArea::createAreaNetwork( name );
	if( net == NULL )
		return;

	// create nucleous region for sensor
	MindService *ms = MindService::getService();
	MindRegion *region = ms -> createNucleiRegion( this );
	MindArea::addRegion( getClass() , sensor -> getClass() , region );

	// add the only region
	net -> addRegion( region );
}
