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

	MindSensorSet *sensors = target -> getSensorSet();

	// for each sensor create region link
	MindRegionSet *srcset = MindArea::getRegionSet();
	MindRegionSet *dstset = dstArea -> getRegionSet();
	for( int k = 0; k < sensors -> getCount(); k++ ) {
		// get regions
		MindSensor *sensor = sensors -> getSetItem( k );
		MindRegion *srcRegion = srcset -> getSetItemById( String( getClass() ) + "." + sensor -> getClass() );
		ASSERTMSG( srcRegion != NULL , "initLinksToPerceptionArea: unknown source region for sensor=" + String( sensor -> getClass() ) );
		MindRegion *dstRegion = dstset -> getSetItemById( String( dstArea -> getClass() ) + "." + sensor -> getClass() );
		ASSERTMSG( dstRegion != NULL , "initLinksToPerceptionArea: unknown destination region for sensor=" + String( sensor -> getClass() ) );

		// creater link
		MindRegionLink *regionLink = new MindRegionLink();
		regionLink -> createRegionLink( srcRegion , dstRegion );
		link -> addRegionLink( regionLink );
	}
}
