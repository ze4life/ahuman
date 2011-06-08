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
void SensorArea::createSensorArea( MindTarget *p_target , MindSensorSet *sensorSet ) {
	target = p_target;
	MindRegionSet *set = MindArea::getRegionSet();

	for( int k = 0; k < sensorSet -> getCount(); k++ ) {
		MindSensor *sensor = sensorSet -> getSetItem( k );
		set -> addSetItem( sensor );
	}
}

void SensorArea::initSensorArea() {
}

MindTarget *SensorArea::getTarget() {
	return( target );
}

MindRegion *SensorArea::createGroupRegion( String group ) {
	return( NULL );
}

// mind area lifecycle
void SensorArea::initRegionsInArea() {
}

void SensorArea::initMasterLinkToArea( MindAreaLink *link , String slaveAreaId ) {
	if( slaveAreaId.equals( "PerceptionArea" ) )
		initLinksToPerceptionArea( link );
}

void SensorArea::initSlaveLinkToArea( MindAreaLink *link , String masterAreaId ) {
}

void SensorArea::wakeupArea( MindActiveMemory *activeMemory ) {
}

void SensorArea::asleepArea() {
}

void SensorArea::initLinksToPerceptionArea( MindAreaLink *link ) {
	MindArea *dstArea = link -> getDestinationArea();

	// for each sensor create region link
	MindRegionSet *set = MindArea::getRegionSet();
	for( int k = 0; k < set -> getCount(); k++ ) {
		// get regions
		MindRegion *srcRegion = set -> getSetItem( k );
		MindRegion *dstRegion = dstArea -> openRegion( "sensor" , srcRegion -> getRegionId() );

		// creater link
		MindRegionLink *regionLink = new MindRegionLink();
		link -> addRegionLink( regionLink );
	}
}
