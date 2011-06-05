#ifndef	INCLUDE_AH_MINDAREA_H
#define INCLUDE_AH_MINDAREA_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindArea;
class MindAreaSet;

/*#########################################################################*/
/*#########################################################################*/

class MindAreaInfo;
class MindRegionSet;
class MindRegionLinkSet;
class MindAreaLink;

// brain provides implementation for mind areas
// each mind area is implemented by module components - next level folder under mod...
// each mind area has own name and own location in the brain
// mind area has pre-defined size as number of neurons, no matter of neuron type
// inter-area connections have own lifecycle, controlled by brain
// mind area consists a set of cortexes, where each cortex is neural or belief network of any type
// a number of cortexes, their types and inter-connections are defined dynamically by related modules

class MindArea : public Object {
public:
	MindArea();
	virtual ~MindArea();
	virtual const char *getClass() = 0;

public:
	// mind area lifecycle
	virtual MindRegion *createGroupRegion( String group ) = 0;
	virtual void initRegionsInArea() = 0;
	virtual void initMasterLinkToArea( MindAreaLink *link , String slaveAreaId ) = 0;
	virtual void initSlaveLinkToArea( MindAreaLink *link , String masterAreaId ) = 0;
	virtual void wakeupArea( MindActiveMemory *activeMemory ) = 0;
	virtual void asleepArea() = 0;

public:
	MindAreaInfo *getMindAreaInfo();
	void configure( MindAreaInfo *info );
	void create();
	void exit();
	void destroy();
	MindRegion *openRegion( String group , String id );

protected:
	MindRegionSet *getRegionSet();

private:
	MindAreaInfo *info;
	MindRegionSet *regionSet;
	MindRegionLinkSet *regionLinkSet;
};

/*#########################################################################*/
/*#########################################################################*/

class MindActiveMemory;

class MindAreaSet : public Object {
public:
	virtual const char *getClass() { return( "MindAreaSet" ); };

	void addMindArea( MindArea *area );
	MindArea *getMindArea( String id );

	void initRegionsInAreaSet();
	void wakeupAreaSet( MindActiveMemory *activeMemory );
	void asleepAreaSet();
	void exitAreaSet();
	void destroyAreaSet();

public:
	ClassList<MindArea> list;
	MapStringToClass<MindArea> map;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDAREA_H
