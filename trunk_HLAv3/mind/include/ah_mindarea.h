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
class MindLink;

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
	virtual void onCreateArea() = 0;
	virtual void onLoadArea() = 0;
	virtual void onBrainStart() {};
	virtual void onBrainStop() {};

	// runtime mind link events
	virtual void onOpenMindLinkSource( MindLink *link , String channelId ) {};
	virtual void onOpenMindLinkDestination( MindLink *link , String channelId ) {};

public:
	void setMindAreaInfo( MindAreaInfo *info );
	MindAreaInfo *getMindAreaInfo();

private:
	void lock() { rfc_hnd_semlock( lockHandle ); };
	void unlock() { rfc_hnd_semunlock( lockHandle ); };

private:
	RFC_HND lockHandle;

	MindAreaInfo *info;
	MindRegionSet *regionSet;
	MindRegionLinkSet *regionLinkSet;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaSet : public Object {
public:
	virtual const char *getClass() { return( "MindAreaSet" ); };

	void addMindArea( MindArea *area );

public:
	ClassList<MindArea> list;
	MapStringToClass<MindArea> map;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDAREA_H
