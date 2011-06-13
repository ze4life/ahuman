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
	virtual void initMasterLinkToArea( MindAreaLink *link , String slaveAreaId ) {};
	virtual void initSlaveLinkToArea( MindAreaLink *link , String masterAreaId ) {};
	virtual void wakeupArea( MindActiveMemory *activeMemory ) {};
	virtual void asleepArea() {};

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
}

/*#########################################################################*/
/*#########################################################################*/

MindArea *MindService::createPerceptionArea() { return( new PerceptionArea() ); };

