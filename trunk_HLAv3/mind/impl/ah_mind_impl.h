#ifndef	INCLUDE_AH_MIND_IMPL_H
#define INCLUDE_AH_MIND_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <platform/include/ah_platform.h>

class MindActiveMemoryObject;
class MindSensorSetTracker;
class CortexSpatialPoolerItem;
class CortexSpatialPooler;
class CortexTemporalPoolerItem;
class CortexTemporalPooler;

/*#########################################################################*/
/*#########################################################################*/

#define NEURON_FIRE_POTENTIAL_THRESHOLD_pQ				(( neurovt_state )70)
#define NEURON_FIRE_OUTPUT_BY_POTENTIAL_pQ				(( neurovt_state )70)
#define NEURON_FIRE_OUTPUT_THRESHOLD_pQ					(( neurovt_state )65)
#define NEURON_FIRE_OUTPUT_SILENT_ms					(( neurovt_state )10)
#define NEURON_FIRE_IMPULSE_pQ							(( neurovt_state )10)
#define NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms		(( neurovt_state )1)
#define NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms			(( neurovt_state )1)
#define NEURON_FULL_RELAX_ms							(( RFC_INT64 )1000)

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

class CortexSpatialPoolerItem : public Object {
public:
	CortexSpatialPoolerItem();
	virtual const char *getClass() { return( "CortexSpatialPoolerItem" ); };

	int getId();
	int getUsage();
	void addUsage();
	void setId( int p_id );
	int setStateFromPool( NeuroPool *pool );
	void setStateFromSignal( NeuroSignal *signal );
	void getPoolFromState( NeuroPool *pool );
	void getSignalFromState( NeuroSignal *signal );
	int getDifferencePercentage( CortexSpatialPoolerItem *item , neurovt_state toleranceNeuronState );
	void logItem();
	String getBinaryState();
	String getNumberedState();

private:
	int id;
	int usage;
	FlatList<int> indexList;
};

class CortexSpatialPooler : public Object {
public:
	CortexSpatialPooler();
	virtual ~CortexSpatialPooler();
	virtual const char *getClass() { return( "CortexSpatialPooler" ); };
	
	void create( int poolSize , int sizeX , int sizeY );
	void setMatchTolerance( int tolerancePattern , int toleranceNeuronState );
	void setProtectedUsage( int usage );

	int matchPattern( NeuroSignal *signal , int *matchProbability , int *patternForgotten );
	bool getPattern( int pattern , NeuroSignal *signal );
	CortexSpatialPoolerItem *findBestMatch( CortexSpatialPoolerItem *data , int *difference );
	CortexSpatialPoolerItem *findLeastUsed();
	void logItems();

private:
	int maxPoolSize;
	int patternSizeX;
	int patternSizeY;

	int matchTolerancePattern;
	int matchToleranceNeuronState;
	int protectedUsage;

	ClassList<CortexSpatialPoolerItem> items;
};

// #############################################################################
// #############################################################################

class CortexTemporalPoolerItem : public Object {
public:
	CortexTemporalPoolerItem( int p_maxDepth );
	virtual ~CortexTemporalPoolerItem();
	virtual const char *getClass() { return( "CortexTemporalPoolerItem" ); };

	int getId();
	void setId( int p_id );
	void deleteSpatialPatternIfAny( int spatialPattern );
	void addUsage();
	int getUsage();
	void setUsage( int p_usage );
	void setData( int *data , int dataSize );
	int getDifferencePercentage( int *data , int dataSize );
	int getPartialDifferencePercentage( int *data , int dataSize );
	int getDataSize();
	int getSpatialPattern( int index );
	String getNumberedState();
	void logItem();

private:
	int id;
	int usage;
	int maxDepth;
	int *streamData;
	int streamDataSize;
};

class CortexTemporalPooler : public Object {
public:
	CortexTemporalPooler();
	virtual ~CortexTemporalPooler();
	virtual const char *getClass() { return( "CortexTemporalPooler" ); };

	void create( int poolSize , int depth );
	void setMatchTolerance( int tolerancePattern );
	void setProtectedUsage( int usage );
	void setPredictionProbabilityTolerance( int tolerance );
	void setPredictionMatchTolerance( int tolerance );
	void forgetSpatialPattern( int spatialPattern );
	int matchPattern( int spatialPattern ,  int *spatialPatternPredicted , int *predictionProbability , int *temporalPatternForgotten );
	CortexTemporalPoolerItem *matchFillPattern( int *data , int datasize , int spatialPattern , int *temporalPatternForgotten );
	int predictPattern( int *data , int datasize , int *spatialPatternPredicted , int *predictionProbability );
	CortexTemporalPoolerItem *findBestMatch( int minSize , int *data , int dataSize , int *difference , int *matchedCount );
	CortexTemporalPoolerItem *findPartialBestMatch( int minSize , int *data , int dataSize , int *difference , int *matchedCount );
	CortexTemporalPoolerItem *findLeastUsed();
	void logItems();

private:
	int maxPoolSize;
	int maxDepth;
	int protectedUsage;
	ClassList<CortexTemporalPoolerItem> items;
	int *streamData;
	int streamDataSize;
	int matchTolerancePattern;
	int predictionProbabilityTolerance;
	int predictionMatchTolerance;
};

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MIND_IMPL_H
