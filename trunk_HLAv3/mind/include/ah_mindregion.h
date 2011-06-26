#ifndef	INCLUDE_AH_MINDREGION_H
#define INCLUDE_AH_MINDREGION_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindRegion;
class MindRegionSet;
class CortexRegion;
class NucleiRegion;
class NerveRegion;

/*#########################################################################*/
/*#########################################################################*/

class NeuroNet;
class MindRegionLink;

class MindRegion : public Object {
public:
	MindRegion();
	virtual ~MindRegion();
	virtual const char *getClass() { return( "MindRegion" ); };

	virtual void createRegion() = 0;
	virtual void exitRegion() = 0;
	virtual void destroyRegion() = 0;

	// link creation
	virtual void createNeuroLinks( MindRegion *dst ) = 0;
	virtual void createNeuroLinksFromCortexRegion( CortexRegion *src ) = 0;
	virtual void createNeuroLinksFromNucleiRegion( NucleiRegion *src ) = 0;
	virtual void createNeuroLinksFromNerveRegion( NerveRegion *src ) = 0;
	virtual void createNeuroLinksFromSensorRegion( MindSensor *src ) = 0;

public:
	void create( MindArea *area , String p_id );
	void exit();
	void destroy();
	void addRegionLink( MindRegion *src , MindRegion *dst , MindRegionLink *link );

	String getRegionId();
	void sendOutputData( neurovt *data , int size );

private:
	MindArea *area;
	String id;

	NeuroNet *net;
	MindRegionLinkSet *regionLinkSet;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionSet : public Object {
public:
	virtual const char *getClass() { return( "MindRegionSet" ); };

	int getCount();
	MindRegion *getSetItem( int k );

	MindRegion *getSetItemById( String regionId );
	void addSetItem( MindRegion *region );

	void exitRegionSet();
	void destroyRegionSet();

public:
	ClassList<MindRegion> list;
	MapStringToClass<MindRegion> map;
};

/*#########################################################################*/
/*#########################################################################*/

class CortexRegion : public MindRegion {
public:
	CortexRegion();
	virtual const char *getClass() { return( "CortexRegion" ); };

public:
	// MindRegion interface
	virtual void createRegion();
	virtual void exitRegion();
	virtual void destroyRegion();

	// link creation
	virtual void createNeuroLinks( MindRegion *dst );
	virtual void createNeuroLinksFromCortexRegion( CortexRegion *src );
	virtual void createNeuroLinksFromNucleiRegion( NucleiRegion *src );
	virtual void createNeuroLinksFromNerveRegion( NerveRegion *src );
	virtual void createNeuroLinksFromSensorRegion( MindSensor *src );
};

/*#########################################################################*/
/*#########################################################################*/

class NucleiRegion : public MindRegion {
public:
	NucleiRegion();
	virtual const char *getClass() { return( "NucleiRegion" ); };

public:
	// MindRegion interface
	virtual void createRegion();
	virtual void exitRegion();
	virtual void destroyRegion();

	// link creation
	virtual void createNeuroLinks( MindRegion *dst );
	virtual void createNeuroLinksFromCortexRegion( CortexRegion *src );
	virtual void createNeuroLinksFromNucleiRegion( NucleiRegion *src );
	virtual void createNeuroLinksFromNerveRegion( NerveRegion *src );
	virtual void createNeuroLinksFromSensorRegion( MindSensor *src );
};

/*#########################################################################*/
/*#########################################################################*/

class NerveRegion : public MindRegion {
public:
	NerveRegion();
	virtual const char *getClass() { return( "NerveRegion" ); };

public:
	// MindRegion interface
	virtual void createRegion();
	virtual void exitRegion();
	virtual void destroyRegion();

	// link creation
	virtual void createNeuroLinks( MindRegion *dst );
	virtual void createNeuroLinksFromCortexRegion( CortexRegion *src );
	virtual void createNeuroLinksFromNucleiRegion( NucleiRegion *src );
	virtual void createNeuroLinksFromNerveRegion( NerveRegion *src );
	virtual void createNeuroLinksFromSensorRegion( MindSensor *src );
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDREGION_H
