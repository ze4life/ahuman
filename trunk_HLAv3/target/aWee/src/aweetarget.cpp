#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

AWeeTarget::AWeeTarget() {
}

void AWeeTarget::configureTarget( Xml config ) {
}

void AWeeTarget::createTarget() {
	MindTarget::addSensor( AWeeTarget::createFileSysWalker() );
}

void AWeeTarget::initSensorsTarget( MindArea *sensorArea ) {
}

void AWeeTarget::initEffectorsTarget( MindArea *effectorArea ) {
}

void AWeeTarget::runTarget() {
}

void AWeeTarget::stopTarget() {
}

void AWeeTarget::exitTarget() {
}

void AWeeTarget::destroyTarget() {
}
