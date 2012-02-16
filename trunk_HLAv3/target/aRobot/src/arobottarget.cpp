#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

ARobotTarget::ARobotTarget() {
}

void ARobotTarget::configureTarget( Xml config ) {
}

void ARobotTarget::createTarget( SensorArea *sensorArea , EffectorArea *effectorArea ) {
	MindTarget::addSensor( ARobotTarget::createEye( sensorArea ) );
	MindTarget::addEffector( ARobotTarget::createWheeledLegs( effectorArea ) );
}

void ARobotTarget::initSensorsTarget( SensorArea *sensorArea ) {
}

void ARobotTarget::initEffectorsTarget( EffectorArea *effectorArea ) {
}

void ARobotTarget::runTarget() {
}

void ARobotTarget::stopTarget() {
}

void ARobotTarget::exitTarget() {
}

void ARobotTarget::destroyTarget() {
}

