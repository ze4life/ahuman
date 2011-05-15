#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindArea *MindTarget::createSensorArea() {
	return( new SensorArea() );
}

/*#########################################################################*/
/*#########################################################################*/

SensorArea::SensorArea() {
}

SensorArea::~SensorArea() {
}

// mind area lifecycle
void SensorArea::initRegionsInArea() {
}

void SensorArea::initMasterLinkToArea( MindAreaLink *link , String slaveAreaId ) {
}

void SensorArea::initSlaveLinkToArea( MindAreaLink *link , String masterAreaId ) {
}

void SensorArea::wakeupArea( MindActiveMemory *activeMemory ) {
}

void SensorArea::asleepArea() {
}

