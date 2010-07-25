#ifndef	INCLUDE_AIBRAIN_IMPL_H
#define INCLUDE_AIBRAIN_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aisvcdb.h>
#include <aisvcio.h>

class MindMap;
class MindAreaInfo;
class MindLinkInfo;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIBrainImpl : public AIBrain , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Brain" ); };

// external interface
public:
	AIBrainImpl();

	// mind map
	MindMap *getMindMap() {
		return( mindMap );
	}

// internals
private:
	AIEngine& engine;

	MindMap *mindMap;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaInfo
{
public:
	MindAreaInfo() {};
	~MindAreaInfo() {
		links.destroy();
	};

// operations
public:
	void createFromXml( Xml xml );
	String getAreaId() {
		return( areaId );
	};
	const ClassList<MindLinkInfo>& getLinks() {
		return( links );
	};
	void resolveLinks( MindMap *map );

private:
	String areaId;
	ClassList<MindLinkInfo> links;
};

class MindLinkInfo
{
public:
	MindLinkInfo();
	~MindLinkInfo() {};

// operations
public:
	void createFromXml( Xml xml );
	String getMasterAreaId() {
		return( masterAreaId );
	};
	String getSlaveAreaId() {
		return( slaveAreaId );
	};
	void resolveLinks( MindMap *map );

// data
public:
	String masterAreaId;
	String slaveAreaId;

	MindAreaInfo *masterArea;
	MindAreaInfo *slaveArea;
};

// set of mind areas is a mind map
// topology of mind map is pre-defined , including size and inter-area connections
// mind map is defined statically (at least until invention of artificial genetics), in configuration files
class MindMap
{
public:
	MindMap() {};
	~MindMap() {
		mindAreas.destroy();
	};

// operations
public:
	void createFromXml( Xml xml );
	const ClassList<MindAreaInfo>& getMindAreas() {
		return( mindAreas );
	}
	MindAreaInfo *getAreaById( String areaId ) {
		MindAreaInfo *info = mindAreaMap.get( areaId );
		ASSERTMSG( info != NULL , "Wrong area id=" + areaId );
	}

private:
	ClassList<MindAreaInfo> mindAreas;
	MapStringToClass<MindAreaInfo> mindAreaMap;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIBRAIN_IMPL_H
