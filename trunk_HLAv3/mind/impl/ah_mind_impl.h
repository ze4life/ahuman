#ifndef	INCLUDE_AH_MIND_IMPL_H
#define INCLUDE_AH_MIND_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <platform/include/ah_platform.h>

class MindActiveMemoryObject;
class MindSensorSetTracker;

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

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MIND_IMPL_H
