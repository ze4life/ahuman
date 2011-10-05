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

private:
// utility
	MessageSession *session;
	MessageSubscription *iosub;

// own data
	MindRegionLinkSet *links;

// references
	MindAreaLinkInfo *info;
	MindArea *sourceArea;
	MindArea *destinationArea;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaLinkSet : public Object {
public:
	const char *getClass() { return( "MindAreaLinkSet" ); };

	void addSetItem( MindAreaLink *link );

public:
// own data
	ClassList<MindAreaLink> list;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLinkSet;
class MindRegion;

class MindRegionLink : public Object {
public:
	MindRegionLink( MindAreaLink *areaLink );
	const char *getClass() { return( "MindRegionLink" ); };

	MindRegion *getSrcRegion();
	MindRegion *getDstRegion();

	void createRegionLink( MindNet *net , MindRegion *srcRegion , MindRegion *dstRegion );
	void exitRegionLink();
	void destroyRegionLink();

private:
	NeuroLink *createNeuroLink( MindNet *net , NeuroLinkInfo *linkInfo );

public:
// references
	MindAreaLink *areaLink;
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
	void exitRegionLinkSet();
	void destroyRegionLinkSet();

public:
// own data
	ClassList<MindRegionLink> list;
};

/*#########################################################################*/
/*#########################################################################*/

class MindActiveMemoryObject;

class MindActiveMemory : public Object {
public:
	MindActiveMemory();
	~MindActiveMemory();
	const char *getClass() { return( "MindActiveMemory" ); };

	// lifecycle
	void create( Xml config );
	void start();
	void stop();
	void destroy();

public:
// utility
	String threadPoolName;

// own data
	ClassList<MindActiveMemoryObject> memoryObjects;
};

/*#########################################################################*/
/*#########################################################################*/

// class to snapshot outputs from cortex and transfer to other cortexes
class MindMessage : public Message {
public:
	MindMessage( NeuroLink *p_link );
	MindMessage( NeuroLink *p_link , NeuroVector *p_data );
	virtual ~MindMessage();
	virtual const char *getClass() { return( "MindMessage" ); };

public:
	NeuroLink *getNeuroLink() { return( link ); };
	NeuroVector *getMsgData();

private:
// own data
	NeuroVector *data;

// references
	NeuroLink *link;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_MINDSTREAM_H
