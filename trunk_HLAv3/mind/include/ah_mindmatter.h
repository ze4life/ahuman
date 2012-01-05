#ifndef	INCLUDE_AH_MINDMATTER_H
#define INCLUDE_AH_MINDMATTER_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class NeuroSignal;
class NeuroPool;
class NeuroPoolSet;
class NeuroLink;
class NeuroLinkSet;
class NeuroLinkSource;
class NeuroLinkTarget;

/*#########################################################################*/
/*#########################################################################*/

typedef struct {
	neurovt_state potential;
	neurovt_state output;
	RFC_INT64 updated_mp;	// membrane potential updated timestamp
	RFC_INT64 updated_fs;	// fire state updated timestamp
} NEURON_DATA;

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
	void createFromPool( NeuroPool *pool );

	void setTs( RFC_INT64 ts );
	void setId( String id );
	String getId();
	void getSizeInfo( int *nx , int *ny );
	int getMaxSize();
	int getDataSize();
	String getBinaryDataString();
	String getNumberDataString();
	int *getIndexRawData();

	void clearData();
	void addIndexData( int index );
	void removeNotFiringIndexes();

private:
// utility
	String id;
	RFC_INT64 ts;

	// original 2D index space
	int sizeX;
	int sizeY;

	// sorted list of activated 1D-indexes in source data
	FlatList<int> data;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroPool : public Object {
public:
	NeuroPool();
	virtual ~NeuroPool();
	virtual const char *getClass() { return( "NeuroPool" ); };

	void createNeurons( int nx , int ny );
	void setParent( MindRegion *p_region );
	void setId( String id );
	String getId();
	MindRegion *getRegion();

	TwoIndexArray<NEURON_DATA>& getNeuronData();
	void getNeuronDimensions( int *nx , int *ny );
	void startProjection( NeuroLink *link );
	void finishProjection( NeuroLink *link , NeuroSignal *signal );

	String getNumberedPoolState();

private:
// references
	MindRegion *region;

// utilities
	String id;
	TwoIndexArray<NEURON_DATA> neurons;
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
	int getSize();
	int getSizeX();
	int getSizeY();

	void setNeuroLinkInfo( NeuroLinkInfo *linkInfo );
	void setTransmitter( String transmitter );
	void create( NeuroLinkSource *p_source , NeuroLinkTarget *p_target );

	virtual NeuroSignal *apply( NeuroSignal *srcData , NeuroPool *dstPool ) = 0;

public:
// utilities
	String id;
	String transmitter;
	int sizeX;
	int sizeY;

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
	NeuroLinkSource( MindRegion *region , String entity );
	virtual const char *getClass() { return( "NeuroLinkSource" ); };

public:
	void setHandler( MindRegion::NeuroLinkSourceHandler pfn );
	MindRegion *getRegion() { return( region ); };
	int getSizeX();
	int getSizeY();

	void addNeuroLink( NeuroLink *link );
	void setSourcePool( NeuroPool *pool );
	void sendMessage( NeuroSignal *sourceSignal );
	NeuroSignal *getLinkSignal( NeuroLink *link );

private:
// references
	MindRegion *region;
	String entity;
	int sizeX;
	int sizeY;
	NeuroPool *sourcePool;
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
