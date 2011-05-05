#ifndef	INCLUDE_AH_MINDSTREAM_H
#define INCLUDE_AH_MINDSTREAM_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_mindbase.h"

class MindAreaLink;
class MindAreaLinkSet;
class MindRegionLink;
class MindRegionLinkSet;
class MindActiveMemory;
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
	MindAreaLink( MindLinkInfo *p_info );
	~MindAreaLink();
	const char *getClass() { return( "MindAreaLink" ); };

// operations
public:
	virtual void onMessage( Message *msg );

	void open( MessageSession *session );
	void transferOutputs( MindRegion *region );
	MessageSubscription *subscribe( MessageSubscriber *handler , String name );
	MessageSubscription *subscribeSelector( MessageSubscriber *handler , String name , String selector );

	MindArea *getSourceArea() { return( srcArea ); };
	MindArea *getDestinationArea() { return( dstArea ); };

private:
	MindLinkInfo *info;

	MindArea *srcArea;
	MindArea *dstArea;
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

public:
	ClassList<MindAreaLink> links;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkSet;

class MindRegionLink : public Object {
public:
	const char *getClass() { return( "MindRegionLink" ); };

public:
	MindRegion *src;
	MindRegion *dst;
	NeuroLinkSet *links;
};

/*#########################################################################*/
/*#########################################################################*/

class MindRegionLinkSet : public Object {
public:
	const char *getClass() { return( "MindRegionLinkSet" ); };

public:
	ClassList<MindRegionLink> links;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLink;

class MindActiveMemory : public Object {
public:
	const char *getClass() { return( "MindActiveMemory" ); };

public:
	ClassList<NeuroLink> links;
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
