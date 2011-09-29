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
void EffectorArea::initRegionsInArea( MindTarget *target ) {
}

void EffectorArea::wakeupArea( MindActiveMemory *activeMemory ) {
}

void EffectorArea::suspendArea() {
}
