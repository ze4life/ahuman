#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindArea *MindTarget::createEffectorArea() {
	return( new EffectorArea() );
}

/*#########################################################################*/
/*#########################################################################*/

EffectorArea::EffectorArea() {
}

EffectorArea::~EffectorArea() {
}

// mind area lifecycle
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
