#ifndef	INCLUDE_AH_MINDAREA_H
#define INCLUDE_AH_MINDAREA_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindArea;
class MindAreaSet;
class MindAreaNet;

/*#########################################################################*/
/*#########################################################################*/

class MindTarget;
class MindAreaInfo;
class MindAreaLinkInfo;
class MindRegionSet;
class MindRegionLinkSet;
class MindAreaLink;
class MessageSession;
class MindMessage;

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
	virtual void initRegionsInArea( MindTarget *target ) = 0;
	virtual void wakeupArea( MindActiveMemory *activeMemory ) = 0;
	virtual void suspendArea() = 0;

public:
	void configure( MindAreaInfo *info );
	void create();
	void exit();
	void destroy();

	MindAreaInfo *getMindAreaInfo();
	void getNetworks( StringList& list );
	MindAreaNet *getMindNet( String net );

	void addNet( MindAreaNet *net );
	MindRegionSet *getRegionSet();
	void sendMessage( MindMessage *msg );
	void addMasterLink( MindAreaLink *link );
	void addSlaveLink( MindAreaLink *link );

protected:
	String addRegion( String group , String id , MindRegion *region );

private:
// utility
	MessageSession *iosession;
	MessagePublisher *iopub;

// own data
	MapStringToClass<MindAreaNet> nets;
	MindRegionSet *regionSet;
	MindRegionLinkSet *regionLinkSet;

// references
	MindAreaInfo *info;
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

class MindAreaNet : public Object {
public:
	MindAreaNet( MindNet *net );
	virtual const char *getClass() { return( "MindAreaNet" ); };

public:
	MindNet *getNet();
	void addRegion( MindRegion *region );
	ClassList<MindRegion>& getRegions();

private:
// references
	MindNet *net;
	ClassList<MindRegion> regions;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDAREA_H
