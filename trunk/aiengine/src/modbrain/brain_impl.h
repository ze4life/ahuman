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

	// mind areas
	virtual void addMindArea( String areaId , MindArea *area );
	virtual MindArea *getMindArea( String areaId );

	void allocateArea( MindArea *area , int size );
	  
	// cortex
	virtual Cortex *getCortex( String cortexId );
	virtual Cortex *createCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler );

	Cortex *createHardcodedCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler );
	Cortex *createHardcodedInputsCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler );
	Cortex *createHardcodedOutputsCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler );

	// mind map
	MindMap *getMindMap() {
		return( mindMap );
	}

	// structure lock
	void lock() {
		rfc_hnd_semlock( lockStructure );
	}
	void unlock() {
		rfc_hnd_semunlock( lockStructure );
	}

// internals
private:
	AIEngine& engine;

	MindMap *mindMap;
	MapStringToClass<MindArea> mindAreas;
	MapStringToInt mapCortexFactoryIndex;

typedef Cortex *( AIBrainImpl::*CortexFactory )( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler );

	FlatList<CortexFactory> cortexFactories;
	RFC_HND lockStructure;
	int sessionId;
	int cortexId;
	MapStringToClass<Cortex> mapCortex;
};

/*#########################################################################*/
/*#########################################################################*/

class MindAreaInfo : public Object
{
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
	const ClassList<MindLinkInfo>& getLinks() {
		return( links );
	};
	void resolveLinks( MindMap *map );
	void allocate( int size );

	// structure lock
	void lock() {
		rfc_hnd_semlock( lockStructure );
	}
	void unlock() {
		rfc_hnd_semunlock( lockStructure );
	}

private:
	String areaId;
	ClassList<MindLinkInfo> links;
	RFC_HND lockStructure;
	int size;
	int sizeNotAllocated;
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
		return( info );
	}

private:
	ClassList<MindAreaInfo> mindAreas;
	MapStringToClass<MindAreaInfo> mindAreaMap;
};

// #############################################################################
// #############################################################################

class CortexHardcoded : public Cortex
{
public:
	CortexHardcoded( MindArea *area , int inputs , int outputs , CortexEventHandler *handler );
	~CortexHardcoded();

	void updateInputs();
	void updateOutputs();

private:
	MindArea *area;
	int inputs;
	int outputs;
	CortexEventHandler *handler;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIBRAIN_IMPL_H
