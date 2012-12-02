#ifndef	INCLUDE_AH_MINDREGION_H
#define INCLUDE_AH_MINDREGION_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindRegion;
class MindRegionSet;
class CortexRegionInfo;
class NucleiRegionInfo;
class NerveRegionInfo;

/*#########################################################################*/
/*#########################################################################*/

class MindRegionLink;
class MindMessage;
class NeuroPoolSet;
class NeuroLink;
class NeuroLinkSet;
class MindLocation;
class NeuroSignal;
class NeuroLinkSource;
class NeuroLinkTarget;

class MindRegion : public Object {
public:
	typedef NeuroSignal *(MindRegion::*NeuroLinkSourceHandler)( NeuroLink *link , NeuroLinkSource *point );
	typedef void (MindRegion::*NeuroLinkTargetHandler)( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *srcData );

public:
	MindRegion( MindArea *area );
	virtual ~MindRegion();
	virtual const char *getClass() { return( "MindRegion" ); };

	// MindRegion lifecycle
public:
	virtual void createRegion() = 0;
	virtual void exitRegion() = 0;
	virtual void destroyRegion() = 0;

	virtual String getRegionType() = 0;
	virtual void getSourceSizes( String entity , int *sizeX , int *sizeY ) = 0;

public:
	void create( String id );
	void exit();
	void destroy();
	void sendMessage( MindMessage *msg );

	MindArea *getArea() { return( area ); };
	String getRegionId();
	String getFullRegionId();
	MindRegionTypeDef *getRegionTypeInfo() { return( regionType ); };

	void addSourceEntity( String entity , NeuroLinkSource *connector );
	void addTargetEntity( String entity , NeuroLinkTarget *connector );
	NeuroLinkSource *getNeuroLinkSource( String entity , MindCircuitLinkDef *linkInfo );
	NeuroLinkTarget *getNeuroLinkTarget( String entity , MindCircuitLinkDef *linkInfo );

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

class CortexRegionInfo : public Object {
public:
	CortexRegionInfo();
	virtual ~CortexRegionInfo();
	virtual const char *getClass() { return( "CortexRegionInfo" ); };

public:
	void setSizeInfo( int nx , int ny );
	void getSizeInfo( int *nx , int *ny );
	void setTemporalDepth( int nDepth );
	void setUsingSpatialPooler( bool useSpatialPooler );
	void setUsingTemporalPooler( bool useTemporalPooler );
	void setSpatialPoolerSize( int spatialPoolerSize );
	void setTemporalPoolerSize( int temporalPoolerSize );
	int getSpatialPoolerSize();
	int getTemporalPoolerSize();

	bool isUsingSpatialPooler();
	bool isUsingTemporalPooler();
	int getTemporalDepth();

private:
	int sizeX;
	int sizeY;
	bool useSpatialPooler;
	bool useTemporalPooler;
	int temporalDepth;
	int spatialPoolerSize;
	int temporalPoolerSize;
};

/*#########################################################################*/
/*#########################################################################*/

class NucleiRegionInfo : public Object {
public:
	NucleiRegionInfo();
	virtual ~NucleiRegionInfo();
	virtual const char *getClass() { return( "NucleiRegionInfo" ); };

public:
	void setTotalSize( int nNeurons );
	int getTotalSize();

private:
	int totalNeurons;
};

/*#########################################################################*/
/*#########################################################################*/

class NerveRegionInfo : public Object {
public:
	NerveRegionInfo();
	virtual ~NerveRegionInfo();
	virtual const char *getClass() { return( "NerveRegionInfo" ); };
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDREGION_H
