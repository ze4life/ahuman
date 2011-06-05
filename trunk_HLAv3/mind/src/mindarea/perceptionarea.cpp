#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class PerceptionArea : public MindArea {
public:
	PerceptionArea();
	virtual const char *getClass() { return( "PerceptionArea" ); };

public:
	// mind area lifecycle
	virtual MindRegion *createGroupRegion( String group );
	virtual void initRegionsInArea();
	virtual void initMasterLinkToArea( MindAreaLink *link , String slaveAreaId ) {};
	virtual void initSlaveLinkToArea( MindAreaLink *link , String masterAreaId ) {};
	virtual void wakeupArea( MindActiveMemory *activeMemory ) {};
	virtual void asleepArea() {};
};

/*#########################################################################*/
/*#########################################################################*/

PerceptionArea::PerceptionArea() {
}

void PerceptionArea::initRegionsInArea() {
}

MindRegion *PerceptionArea::createGroupRegion( String group ) {
	// all groups are cortex regions
	return( new CortexRegion() );
}

/*#########################################################################*/
/*#########################################################################*/

MindArea *MindService::createPerceptionArea() { return( new PerceptionArea() ); };

