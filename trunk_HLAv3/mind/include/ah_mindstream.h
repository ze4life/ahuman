#ifndef	INCLUDE_AH_MINDSTREAM_H
#define INCLUDE_AH_MINDSTREAM_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindAreaLink;
class MindAreaLinkSet;
class MindRegionLink;
class MindRegionLinkSet;
class MindMessage;

/*#########################################################################*/
/*#########################################################################*/

class MindArea;
class MindRegion;

// created by static setup on start
// however each inter-area connection has its own lifecycle in terms of connection details
// connection details declare which cortexes are connected, and specific interneuron connections in these intercortex connections can emerge or disappear
// inter-area connection connects outputs of one area and inputs of another area
// dynamics of connection is directed by brain
// how inputs/outputs are connected to cortexes - it is defined by related component
class MindAreaLink : public Object , public MessageSubscriber {
public:
	MindAreaLink( MindAreaLinkInfo *p_info );
	~MindAreaLink();
	const char *getClass() { return( "MindAreaLink" ); };

// operations
public:
	virtual void onMessage( Message *msg );

	void open( MessageSession *session );
	MessageSubscription *subscribe( MessageSubscriber *handler , String name );
	MessageSubscription *subscribeSelector( MessageSubscriber *handler , String name , String selector );

	MindArea *getSourceArea() { return( sourceArea ); };
	MindArea *getDestinationArea() { return( destinationArea ); };

	void addRegionLink( MindRegionLink *link );
	void sendOutputData( MindRegion *region , neurovt *data , int size );

private:
	MindAreaLinkInfo *info;

	MindArea *sourceArea;
	MindArea *destinationArea;
	MindRegionLinkSet *links;

	MessageSession *session;
	MessageSubscription *iosub;
	MessagePublisher *iopub;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaLinkSet : public Object {
public:
	const char *getClass() { return( "MindAreaLinkSet" ); };

	void addSetItem( MindAreaLink *link );
	void sendOutputData( MindRegion *region , neurovt *data , int size );

public:
	ClassList<MindAreaLink> list;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkSet;
class MindRegion;

class MindRegionLink : public Object {
public:
	MindRegionLink();
	const char *getClass() { return( "MindRegionLink" ); };

	MindRegion *getSrcRegion();
	MindRegion *getDstRegion();

	void createRegionLink( MindRegion *srcRegion , MindRegion *dstRegion );
	void exitRegionLink();
	void destroyRegionLink();
	void sendOutputData( neurovt *data , int size );

public:
	MindRegion *src;
	MindRegion *dst;
	NeuroLinkSet *links;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegion;

class MindRegionLinkSet : public Object {
public:
	const char *getClass() { return( "MindRegionLinkSet" ); };

	void addSetItem( MindRegionLink *link );

	void sendOutputData( MindRegion *region , neurovt *data , int size );
	void exitRegionLinkSet();
	void destroyRegionLinkSet();

public:
	ClassList<MindRegionLink> list;
};

/*#########################################################################*/
/*#########################################################################*/

// class to snapshot outputs from cortex and transfer to other cortexes
class MindMessage : public Message {
private:
	unsigned size;
	neurovt *data;
	MindRegion *region;

public:
	MindMessage( MindRegion *p_region );
	virtual ~MindMessage();
	virtual const char *getClass() { return( "MindMessage" ); };

public:
	MindRegion *getSourceRegion() { return( region ); };
	void *getBuffer() { return( data ); };
	int getSize() { return( ( int )size ); };

	void capture();
	void get( unsigned n , neurovt *values );
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSTREAM_H
