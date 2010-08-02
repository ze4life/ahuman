#ifndef	INCLUDE_AIBRAIN_IMPL_H
#define INCLUDE_AIBRAIN_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aisvcdb.h>
#include <aisvcio.h>

class AIBrainImpl;
class MindMap;
class MindAreaInfo;
class MindLinkInfo;
class TopCortexEventHandler;
class ActiveMemory;
class ActiveMemoryThread;
class ActiveMemoryThreadPool;
class ActiveMemoryObject;

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
	static AIBrainImpl *getInstance();

	// mind areas
	virtual void addMindArea( String areaId , MindArea *area );
	virtual MindArea *getMindArea( String areaId );

	void allocateArea( MindArea *area , int size );
	  
	// cortex
	virtual Cortex *getCortex( String cortexId );
	virtual Cortex *createCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler );

	Cortex *createHardcodedCortex( MindArea *area , String netType , int size , int inputs , int outputs );
	Cortex *createHardcodedInputsCortex( MindArea *area , String netType , int size , int inputs , int outputs );
	Cortex *createHardcodedOutputsCortex( MindArea *area , String netType , int size , int inputs , int outputs );

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

typedef Cortex *( AIBrainImpl::*CortexFactory )( MindArea *area , String netType , int size , int inputs , int outputs );

	FlatList<CortexFactory> cortexFactories;
	RFC_HND lockStructure;
	int sessionId;
	int cortexId;
	MapStringToClass<Cortex> mapCortex;
	ActiveMemory *activeMemory;
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

/*#########################################################################*/
/*#########################################################################*/

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

/*#########################################################################*/
/*#########################################################################*/

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

class TopCortexEventHandler : public CortexEventHandler
{
public:
	virtual void onCreate( Cortex *cortex );
	virtual void onInputsUpdated( Cortex *cortex );
	virtual void onOutputsUpdated( Cortex *cortex );

	AIBrainImpl *svc;
};

// #############################################################################
// #############################################################################

class ActiveMemory
{
public:
	ActiveMemory();
	~ActiveMemory();

	void create( Xml config );

// operations
public:
	void start();
	void stop();

private:
	void configure( Xml config );
	void createMemoryObjects();
	void createThreadPool();

private:
	ActiveMemoryThreadPool *threadPool;
	ClassList<ActiveMemoryObject> memoryObjects;

	int focusSize;
};

// #############################################################################
// #############################################################################

class ActiveMemoryThread : public Object
{
public:
	ActiveMemoryThread( int id , ClassList<ActiveMemoryObject>& objects );
	~ActiveMemoryThread();

	const char *getClass() { return( "ActiveMemoryThread" ); };

	// configuring
	void setMsPerOperation( int p_msPerOperation ) { msPerOperation = p_msPerOperation; };
	void setReportGroup( int p_reportGroup ) { reportGroup = p_reportGroup; };
	void setDynamicOperationTime( bool p_dynamicOperationTime ) { dynamicOperationTime = p_dynamicOperationTime; };
	void setMinLoad( float p_minLoad ) { minLoad = p_minLoad; };
	void setMaxLoad( float p_maxLoad ) { maxLoad = p_maxLoad; };

// operations
public:
	String getName();

	void create();
	void suspend();
	void resume();
	void stop();

	void run( void *p_arg );
	void execute( ActiveMemoryObject *object );

private:
	void increaseSpeed( int factor );
	void decreaseSpeed( int factor );

private:
	AIEngine& engine;

	// identity
	int threadId;
	ClassList<ActiveMemoryObject> executeObjects; 
	String name;

	// configuration
	int msPerOperation;
	bool dynamicOperationTime;
	int reportGroup;
	float minLoad;
	float maxLoad;

	// control
	bool suspendSignal;
	bool stopSignal;
	RFC_HND thread;
	RFC_HND runEvent;
	RFC_HND suspendEvent;

	// statistics
	int msExecTimeTotal;
	int msSleepTimeTotal;
	int msWaitTimeRemained;
	int nRatioOperations;
	float ratioExecutionByOperation;
};

// #############################################################################
// #############################################################################

class ActiveMemoryThreadPool
{
public:
	ActiveMemoryThreadPool();
	~ActiveMemoryThreadPool();

	void configure( Xml config );

// operations
public:
	void create( ClassList<ActiveMemoryObject>& objects );

	void start();
	void suspend();
	void resume();
	void stop();

private:
	ClassList<ActiveMemoryThread> threads;

	int nThreads;
	bool dynamicOperationTime;
	int nReportGroup;
	int minLoad;
	int maxLoad;
};

// #############################################################################
// #############################################################################

class ActiveMemoryObject : public Object
{
public:
	ActiveMemoryObject( int id );
	~ActiveMemoryObject();

	const char *getClass() { return( "ActiveMemoryObject" ); };

// operations
public:
	void setCortex( Cortex *cortex );
	String getName() { return( name ); };

	void execute();

private:
	int activeMemoryObjectId;
	String name;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIBRAIN_IMPL_H
