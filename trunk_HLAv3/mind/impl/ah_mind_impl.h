#ifndef	INCLUDE_AH_MIND_IMPL_H
#define INCLUDE_AH_MIND_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include "platform/include/ah_platform.h"

class MindMap;
class MindAreaInfo;
class MindLinkInfo;
class MindActiveMemory;
class MindActiveMemoryObject;

/*#########################################################################*/
/*#########################################################################*/

// set of mind areas is a mind map
// topology of mind map is pre-defined , including size and inter-area connections
// mind map is defined statically (at least until invention of artificial genetics), in configuration files
class MindMap {
public:
	MindMap() {};
	~MindMap();

// operations
public:
	void createFromXml( Xml xml );

	ClassList<MindAreaInfo>& getMindAreas() { return( mindAreas ); };
	ClassList<MindLinkInfo>& getLinks() { return( mindLinks ); }
	MindAreaInfo *getAreaById( String areaId );

private:
	ClassList<MindAreaInfo> mindAreas;
	ClassList<MindLinkInfo> mindLinks;
	MapStringToClass<MindAreaInfo> mindAreaMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaInfo : public Object {
public:
	MindAreaInfo();
	~MindAreaInfo();

	virtual const char *getClass() { return( "MindAreaInfo" ); };

// operations
public:
	void createFromXml( Xml xml );
	String getAreaId() {
		return( areaId );
	};
	const MindLocation& getLocation() { return( location ); };
	const ClassList<MindLinkInfo>& getLinks() { return( links ); };
	void addLink( MindLinkInfo *link ) {
		links.add( link );
	}

	// structure lock
	void lock() {
		rfc_hnd_semlock( lockStructure );
	}
	void unlock() {
		rfc_hnd_semunlock( lockStructure );
	}

private:
	String areaId;
	MindLocation location;

	ClassList<MindLinkInfo> links;
	RFC_HND lockStructure;
	int size;
};

/*#########################################################################*/
/*#########################################################################*/

class MindLinkInfo {
public:
	MindLinkInfo();
	~MindLinkInfo() {};

// operations
public:

	void createFromXml( Xml xml );
	String getMasterAreaId() { return( masterAreaId ); };
	String getSlaveAreaId() { return( slaveAreaId ); };
	String getChannelId() { return( channelId ); };

// data
public:
	String masterAreaId;
	String slaveAreaId;
	String channelId;
};

/*#########################################################################*/
/*#########################################################################*/

class MindActiveMemory : public Object {
public:
	MindActiveMemory();
	~MindActiveMemory();
	const char *getClass() { return( "MindActiveMemory" ); };

public:
	void create( Xml config );

// operations
public:
	void start();
	void stop();

private:
	void createMemoryObjects();

private:
	String threadPool;
	ClassList<MindActiveMemoryObject> memoryObjects;

	int focusSize;
};

/*#########################################################################*/
/*#########################################################################*/

class MindActiveMemoryObject : public ThreadPoolTask {
public:
	MindActiveMemoryObject( int id );
	~MindActiveMemoryObject();

	virtual const char *getClass() { return( "MindActiveMemoryObject" ); };

// ThreadPoolTask
protected:
	virtual bool needExecution();
	virtual bool finished();
	virtual void execute();

// operations
public:
	void setCortex( Cortex *cortex );
	String getName() { return( name ); };

private:
	Cortex *cortex;
	int activeMemoryObjectId;
	String name;
};

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MIND_IMPL_H
