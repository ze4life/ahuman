#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

EffectorArea::EffectorArea( MindTarget *p_target ) {
	target = p_target;
	effectors = NULL;
	effectorsOffline = NULL;
}

EffectorArea::~EffectorArea() {
}

// own functions
void EffectorArea::createEffectorArea() {
	effectors = new MindEffectorSet( this );
	effectorsOffline = new MindEffectorSet( this );
}

void EffectorArea::startEffectorArea() {
	// start sensors
	effectors -> startEffectorSet();
}

void EffectorArea::stopEffectorArea() {
	// stop sensors
	effectors -> stopEffectorSet();
}

void EffectorArea::initEffectorArea() {
}

void EffectorArea::addEffector( MindEffector *effector , bool offline ) {
	if( !offline ) {
		effectors -> addSetItem( effector );
		logger.logInfo( "addEffector: effector added - name=" + effector -> getEffectorName() );
	}
	else {
		effectorsOffline -> addSetItem( effector );
		logger.logInfo( "addEffector: effector is not configured to run - name=" + effector -> getEffectorName() );
	}
}

