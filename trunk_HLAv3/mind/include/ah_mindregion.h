#ifndef	INCLUDE_AH_MINDREGION_H
#define INCLUDE_AH_MINDREGION_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindRegion;
class MindRegionSet;

/*#########################################################################*/
/*#########################################################################*/

class NeuroNet;

class MindRegion : public Object {
public:
	virtual const char *getClass() = 0;

public:
	String getId();
	void setId( String p_id );

private:
	String id;

	NeuroNet *net;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionSet : public Object {
public:
	virtual const char *getClass() { return( "MindRegionSet" ); };

	void addMindRegion( MindRegion *region );

public:
	ClassList<MindRegion> regionList;
	MapStringToClass<MindRegion> regionMap;
};

/*#########################################################################*/
/*#########################################################################*/

class CortexRegion : public MindRegion {
public:
	virtual const char *getClass() { return( "CortexRegion" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class NucleiRegion : public MindRegion {
public:
	virtual const char *getClass() { return( "NucleiRegion" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class NerveRegion : public MindRegion {
public:
	virtual const char *getClass() { return( "NerveRegion" ); };
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDREGION_H
