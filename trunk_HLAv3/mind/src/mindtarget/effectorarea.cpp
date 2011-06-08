#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

EffectorArea *MindTarget::createEffectorArea() {
	return( new EffectorArea() );
}

/*#########################################################################*/
/*#########################################################################*/

EffectorArea::EffectorArea() {
}

EffectorArea::~EffectorArea() {
}

// own functions
void EffectorArea::createEffectorArea( MindTarget *p_target ) {
	target = p_target;
}

void EffectorArea::initEffectorArea() {
}

MindTarget *EffectorArea::getTarget() {
	return( target );
}

// mind area lifecycle
MindRegion *EffectorArea::createGroupRegion( String group ) {
	return( NULL );
}

void EffectorArea::initRegionsInArea() {
}

void EffectorArea::initMasterLinkToArea( MindAreaLink *link , String slaveAreaId ) {
}

void EffectorArea::initSlaveLinkToArea( MindAreaLink *link , String masterAreaId ) {
}

void EffectorArea::wakeupArea( MindActiveMemory *activeMemory ) {
}

void EffectorArea::asleepArea() {
}
