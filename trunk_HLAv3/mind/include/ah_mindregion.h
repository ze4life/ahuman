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

	// NeuroLink support
	virtual NeuroLinkSource *getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) = 0;
	virtual NeuroLinkTarget *getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) = 0;

public:
	void create( String id );
	void exit();
	void destroy();
	void sendMessage( MindMessage *msg );

	MindArea *getArea() { return( area ); };
	String getRegionId();

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
	MindArea *area;
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
	void setColumnCount( int nCols );
	void setUsingSpatialPooler( bool useSpatialPooler );
	void setUsingTemporalPooler( bool useTemporalPooler );
	void setTemporalDepth( int nDepth );

	int getColumnCount();
	int getRegionSideSize();
	bool isUsingSpatialPooler();
	bool isUsingTemporalPooler();
	int getTemporalDepth();

private:
	int nCols;
	int regionSideSize;
	bool useSpatialPooler;
	bool useTemporalPooler;
	int nTemporalDepth;
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
	int getSideSize();

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
