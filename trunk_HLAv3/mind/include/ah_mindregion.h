#ifndef	INCLUDE_AH_MINDREGION_H
#define INCLUDE_AH_MINDREGION_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindRegion;
class MindRegionSet;
class MindRegionCreateInfo;

/*#########################################################################*/
/*#########################################################################*/

class MindRegionLink;
class MindMessage;
class NeuroPoolSet;
class NeuroLink;
class NeuroLinkSet;
class MindLocation;
class NeuroSignal;
class NeuroSignalSet;
class NeuroLinkSource;
class NeuroLinkTarget;

class MindRegion : public Object {
public:
	typedef NeuroSignal *(MindRegion::*NeuroLinkSourceHandler)( NeuroLink *link , NeuroLinkSource *point );
	typedef NeuroSignalSet *(MindRegion::*NeuroLinkTargetHandler)( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData );

public:
	MindRegion( MindArea *area );
	virtual ~MindRegion();
	virtual const char *getClass() { return( "MindRegion" ); };

	// MindRegion lifecycle
public:
	virtual void createRegion( MindRegionCreateInfo *info ) = 0;
	virtual void exitRegion() = 0;
	virtual void destroyRegion() = 0;

public:
	void exit();
	void destroy();

	void setRegionType( MindRegionTypeDef *info ) { regionType = info; };
	MindRegionTypeDef *getRegionType() { return( regionType ); };
	void setRegionId( String p_id ) { id = p_id; };
	String getRegionId() { return( id ); };

	void addRegionLink( MindRegionLink *link );
	String getFullRegionId();
	void sendMessage( MindMessage *msg );

	MindArea *getArea() { return( area ); };
	MindRegionTypeDef *getRegionTypeInfo() { return( regionType ); };
	MapStringToClass<NeuroLinkSource>& getSourceConnectorMap() { return( sourceConnectorMap ); };
	MapStringToClass<NeuroLinkTarget>& getTargetConnectorMap() { return( targetConnectorMap ); };
	MindRegionLinkSet *getRegionLinkSet() { return( regionLinkSet ); };

	void addSourceEntity( String entity , NeuroLinkSource *connector );
	void addTargetEntity( String entity , NeuroLinkTarget *connector );
	NeuroLinkSource *getNeuroLinkSource( String entity );
	NeuroLinkTarget *getNeuroLinkTarget( String entity );

	bool checkLinkedTo( MindRegion *dst );

private:

	void addPrivateNeuroLink( NeuroLink *nt );

private:
// utility
	String id;

// own data
	NeuroPoolSet *poolSet;
	NeuroLinkSet *linkSet;
	MindLocation *location;

// references
	MindRegionTypeDef *regionType;
	MindArea *area;
	MindRegionLinkSet *regionLinkSet;
	MapStringToClass<NeuroLinkSource> sourceConnectorMap;
	MapStringToClass<NeuroLinkTarget> targetConnectorMap;
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
	void addRegionSet( MindRegionSet *regions );

	void exitRegionSet();
	void destroyRegionSet();

public:
// own data
	ClassList<MindRegion> list;

// references
	MapStringToClass<MindRegion> map;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDREGION_H
