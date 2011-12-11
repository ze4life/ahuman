#ifndef	INCLUDE_AH_MIND_IMPL_H
#define INCLUDE_AH_MIND_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <platform/include/ah_platform.h>

class MindActiveMemoryObject;
class MindSensorSetTracker;

#define NEURON_FIRE_THRESHOLD_pQ			(( neurovt_state )70)
#define NEURON_FIRE_IMPULSE_pQ				(( neurovt_state )10)
#define NEURON_DISCHARGE_RATE_pQ_per_ms		(( neurovt_state )1)
#define NEURON_FULL_RELAX_ms				(( RFC_INT64 )1000)

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

class SpatialPooler : public Object {
public:
	SpatialPooler();
	virtual const char *getClass() { return( "SpatialPooler" ); };
	
	void create( int poolSize , int sizeX , int sizeY );
	void setMatchTolerance( int matchTolerance );
	void setProtectedUsage( int usage );

	int matchPattern( NeuroPool *pool , int *patternForgotten );
	bool getPattern( int pattern , NeuroPool *feedbackPool );

private:
	int poolSize;
	int patternSizeX;
	int patternSizeY;
};

// #############################################################################
// #############################################################################

class TemporalPooler : public Object {
public:
	TemporalPooler();
	virtual const char *getClass() { return( "TemporalPooler" ); };

	void create( int poolSize , int depth );
	void forgetSpatialPattern( int spatialPattern );
	int matchPattern( int spatialPattern ,  int *spatialPatternPredicted );
};

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MIND_IMPL_H
