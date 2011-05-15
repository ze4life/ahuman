#ifndef	INCLUDE_AH_MIND_IMPL_H
#define INCLUDE_AH_MIND_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <platform/include/ah_platform.h>

class MindActiveMemory;
class MindActiveMemoryObject;
class MindSensorSetTracker;
class MindSensorArea;
class MindEffectorArea;

/*#########################################################################*/
/*#########################################################################*/

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
	String threadPoolName;
	ClassList<MindActiveMemoryObject> memoryObjects;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLink;

class MindActiveMemoryObject : public ThreadPoolTask {
public:
	MindActiveMemoryObject( int id );
	~MindActiveMemoryObject();
	virtual const char *getClass() { return( "MindActiveMemoryObject" ); };

	void setTargetItem( NeuroLink *link );
	void execute();
	bool needExecution();
	bool finished();

private:
	int activeMemoryObjectId;
	String name;
	NeuroLink *targetItem;
};

/*#########################################################################*/
/*#########################################################################*/

class MindSensorSet;

class MindSensorSetTracker : public Object {
public:
	MindSensorSetTracker( MindSensorSet *set );
	virtual const char *getClass() { return( "MindSensorSetTracker" ); };

public:
	void startTracker();
	void stopTracker();

private:
	void threadSensesTrackerMain( void *p_arg );
	void pollIteration( int& sleepRemained );

private:
	MindSensorSet *set;
	RFC_HND threadSensesTracker;
	bool runSensesTracker;
};

/*#########################################################################*/
/*#########################################################################*/

class SensorArea : public MindArea {
public:
	SensorArea();
	virtual ~SensorArea();
	virtual const char *getClass() { return( "SensorArea" ); };

public:
	// mind area lifecycle
	virtual void initRegionsInArea();
	virtual void initMasterLinkToArea( MindAreaLink *link , String slaveAreaId );
	virtual void initSlaveLinkToArea( MindAreaLink *link , String masterAreaId );
	virtual void wakeupArea( MindActiveMemory *activeMemory );
	virtual void asleepArea();
};

/*#########################################################################*/
/*#########################################################################*/

class EffectorArea : public MindArea {
public:
	EffectorArea();
	virtual ~EffectorArea();
	virtual const char *getClass() { return( "EffectorArea" ); };

public:
	// mind area lifecycle
	virtual void initRegionsInArea();
	virtual void initMasterLinkToArea( MindAreaLink *link , String slaveAreaId );
	virtual void initSlaveLinkToArea( MindAreaLink *link , String masterAreaId );
	virtual void wakeupArea( MindActiveMemory *activeMemory );
	virtual void asleepArea();
};

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MIND_IMPL_H
