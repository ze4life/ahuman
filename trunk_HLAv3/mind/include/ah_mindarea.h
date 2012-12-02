#ifndef	INCLUDE_AH_MINDAREA_H
#define INCLUDE_AH_MINDAREA_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindArea;
class MindAreaSet;

/*#########################################################################*/
/*#########################################################################*/

class MindTarget;
class MindRegionSet;
class MindRegionLinkSet;
class MindAreaLink;
class MindMessage;

/*#########################################################################*/
/*#########################################################################*/

class MindAreaDef;
class MessageSession;

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
	virtual const char *getClass() { return areaId; };

public:
	// mind area lifecycle
	void createAreaRegions( MindTarget *target );
	void wakeupArea( MindActiveMemory *activeMemory );
	void suspendArea();

public:
	void configure( MindAreaDef *info );
	void create();
	void exit();
	void destroy();

	String getId();
	MindAreaDef *getMindAreaDef();

	MindRegionSet *getRegionSet();
	void sendMessage( MindMessage *msg );
	void addMasterLink( MindAreaLink *link );
	void addSlaveLink( MindAreaLink *link );

protected:
	void addRegion( MindRegion *region );
	MindRegion *getRegion( String group , String groupId );

private:
// utility
	MessageSession *iosession;
	MessagePublisher *iopub;

// own data
	String areaId;
	MindRegionSet *regionSet;
	MindRegionLinkSet *regionLinkSet;

// references
	MindAreaDef *info;
	MindAreaLinkSet *areaMasterLinkSet;
	MindAreaLinkSet *areaSlaveLinkSet;
};

/*#########################################################################*/
/*#########################################################################*/

class MindActiveMemory;

class MindAreaSet : public Object {
public:
	virtual const char *getClass() { return( "MindAreaSet" ); };

	void addMindArea( MindArea *area );
	MindArea *getMindArea( String id );

	void initRegionsInAreaSet( MindTarget *target );
	void wakeupAreaSet( MindActiveMemory *activeMemory );
	void suspendAreaSet();
	void exitAreaSet();
	void destroyAreaSet();

public:
// own data
	ClassList<MindArea> list;

// references
	MapStringToClass<MindArea> map;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDAREA_H
