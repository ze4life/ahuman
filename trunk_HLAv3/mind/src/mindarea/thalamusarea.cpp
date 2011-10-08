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

	// create regions for target
	MindService *ms = MindService::getService();
	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );

		// create nucleous region for sensor
		MindRegion *region = ms -> createNucleiRegion( this );
		MindArea::addRegion( getClass() , sensor -> getClass() , region );

		// add to network
		createSensoryNetwork( sensor );
	}
}

void ThalamusArea::createSensoryNetwork( MindSensor *sensor ) {
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
