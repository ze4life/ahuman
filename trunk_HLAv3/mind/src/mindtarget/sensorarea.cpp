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

