#ifndef	INCLUDE_AH_MINDMATTER_H
#define INCLUDE_AH_MINDMATTER_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class NeuroSignal;
class NeuroState;
class NeuroPool;
class NeuroPoolSet;
class NeuroLink;
class NeuroLinkSet;
class NeuroLinkSource;
class NeuroLinkTarget;

/*#########################################################################*/
/*#########################################################################*/

class NeuroSignal : public Object {
public:
	virtual const char *getClass() { return( "NeuroSignal" ); };

	NeuroSignal();
	NeuroSignal( int sizeX , int sizeY );
	NeuroSignal( NeuroSignal *src );
	~NeuroSignal();

public:
	void create( int sizeX , int sizeY );

	neurovt_signal *getRawData();
	TwoIndexArray<neurovt_signal>& getVectorData();
	void getSizeInfo( int *nx , int *ny );

private:
// utility
	TwoIndexArray<neurovt_signal> data;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroState : public Object {
public:
	virtual const char *getClass() { return( "NeuroState" ); };

	NeuroState();
	NeuroState( int sizeX , int sizeY );
	NeuroState( NeuroState *src );
	~NeuroState();

public:
	void create( int sizeX , int sizeY );

	neurovt_state *getRawData();
	TwoIndexArray<neurovt_state>& getVectorData();
	void getSizeInfo( int *nx , int *ny );

private:
// utility
	TwoIndexArray<neurovt_state> data;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPool : public Object {
public:
	NeuroPool();
	virtual ~NeuroPool();
	virtual const char *getClass() { return( "NeuroPool" ); };

	void createNeurons( int nx , int ny );

	RFC_INT64 getLastExecutionTimeTicks();
	void setLastExecutionTimeTicks( RFC_INT64 p_ticks );

	void getNeuronDimensions( int *nx , int *ny );
	NeuroState *getCellPotentials();
	NeuroState *getCellOutputs();

	void startProjection( NeuroLink *link );
	void finishProjection( NeuroLink *link );

private:
// own data
	NeuroState *cellPotentials;
	NeuroState *cellOutputs;

// utilities
	RFC_INT64 lastExecutionTicks;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPoolSet : public Object {
public:
	virtual const char *getClass() { return( "NeuroPoolSet" ); };

private:
// own data
	ClassList<NeuroPool> list;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionLink;
class NeuroLinkInfo;

class NeuroLink : public Object {
public:
	NeuroLink( MindRegionLink *regionLink );
	const char *getClass() { return( "NeuroLink" ); };

	// parameters
	String getId();
	NeuroLinkSource *getSource();
	NeuroLinkTarget *getTarget();
	MindRegionLink *getRegionLink() { return( regionLink ); };

	void setNeuroLinkInfo( NeuroLinkInfo *linkInfo );
	void setTransmitter( String transmitter );
	void create( NeuroLinkSource *p_source , NeuroLinkTarget *p_target );

	virtual void apply( NeuroSignal *srcData , NeuroPool *dstPool ) = 0;

public:
// utilities
	String id;
	String transmitter;

// references
	MindRegionLink *regionLink;
	NeuroLinkInfo *linkInfo;
	NeuroLinkSource *source;
	NeuroLinkTarget *target;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkSet : public Object {
public:
	const char *getClass() { return( "NeuroLinkSet" ); };

	void addSetItem( NeuroLink *link );

public:
// own data
	ClassList<NeuroLink> list;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkSource : public Object {
public:
	NeuroLinkSource( MindRegion *region );
	virtual const char *getClass() { return( "NeuroLinkSource" ); };

public:
	void setHandler( MindRegion::NeuroLinkSourceHandler pfn );
	MindRegion *getRegion() { return( region ); };

	void addNeuroLink( NeuroLink *link );
	void setSourceSignal( NeuroSignal *data );
	NeuroSignal *getSourceSignal( NeuroLink *link );

	void sendMessage();

private:
// references
	MindRegion *region;
	NeuroSignal *data;
	ClassList<NeuroLink> links;

// utilities
	MindRegion::NeuroLinkSourceHandler pfn;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkTarget : public Object {
public:
	NeuroLinkTarget( MindRegion *region );
	virtual const char *getClass() { return( "NeuroLinkTarget" ); };

public:
	void setHandler( MindRegion::NeuroLinkTargetHandler pfn );
	MindRegion *getRegion() { return( region ); };

	void execute( NeuroLink *link , NeuroSignal *sourceData );

public:
	MindRegion *region;
	MindRegion::NeuroLinkTargetHandler pfn;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDMATTER_H
