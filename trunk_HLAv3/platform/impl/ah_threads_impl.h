#ifndef	INCLUDE_AH_THREADS_IMPL_H
#define INCLUDE_AH_THREADS_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <ah_threads.h>

class ThreadData;
class ThreadPool;
class ThreadPoolItem;
class ThreadPoolTask;

/*#########################################################################*/
/*#########################################################################*/

// thread data
class ThreadData {
public:
	RFC_THREAD threadExtId;
	String name;
	unsigned long threadId;
	Object *object;
	void ( Object::*objectFunction )( void *p_arg );
	void *objectFunctionArg;

	RFC_HND sleepEvent;
	MapStringToClass<ThreadObject> map;

public:
	ThreadData() {
		memset( &threadExtId , 0 , sizeof( RFC_THREAD ) );
		threadId = ( unsigned long )NULL;
		object = NULL;
		objectFunction = NULL;
		objectFunctionArg = NULL;
		sleepEvent = rfc_hnd_evcreate();
	};

	~ThreadData() {
		rfc_hnd_evdestroy( sleepEvent );
	};
};

/*#########################################################################*/
/*#########################################################################*/

class ThreadState {
public:
	typedef enum {
		THREAD_STATE_CREATED = 1 ,	// start -> running
		THREAD_STATE_RUNNING = 2 ,	// suspend -> suspended, stop -> created
		THREAD_STATE_SUSPENDED = 3	// resume -> running, stop -> created
	} ThreadStateType;

private:
	ThreadStateType state;

public:
	ThreadState() { state = THREAD_STATE_CREATED; };
	ThreadStateType getState() { return( state ); };

	void setState( ThreadStateType value ) {
		bool checkTransition = false;
		if( state == THREAD_STATE_CREATED )
			checkTransition = ( value == THREAD_STATE_RUNNING );
		else
		if( state == THREAD_STATE_RUNNING )
			checkTransition = ( value == THREAD_STATE_CREATED || value == THREAD_STATE_SUSPENDED );
		else
		if( state == THREAD_STATE_SUSPENDED )
			checkTransition = ( value == THREAD_STATE_CREATED || value == THREAD_STATE_RUNNING );

		ASSERTMSG( checkTransition , String( "Invalid state transition: stateFrom=" )  + state + ", stateTo=" + value );
		state = value;
	};
};

/*#########################################################################*/
/*#########################################################################*/

class ThreadPool : public Object {
private:
	String name;
	bool runEnabled;
	int nThreads;
	int secondsPerMonitoringCycle;
	int maxLoadPercents;

	ClassList<ThreadPoolItem> threads;
	RFC_HND monitorThread;
	CPULOADINFO cpuload;
	float lastCPULoad;
	ThreadState state;
	bool stopSignal;

public:
	void configure( Xml config );
	void create( ClassList<ThreadPoolTask>& tasks );
	void ensureStopped();

	void start();
	void stop();
	void suspend();
	void resume();

// internals
protected:
	void runMonitorThread( void *arg );
	void runMonitorTask();

public:
	ThreadPool( String name );
	~ThreadPool();
	virtual const char *getClass() { return( "ThreadPool" ); };
};

/*#########################################################################*/
/*#########################################################################*/

class ThreadPoolItem : public Object {
public:
	String getThreadName();
	void setExecutionTimeWindowTicks( int ticks );
	void clearStatistics();

	void start();
	void stop();
	void suspend();
	void resume();

	void run( void *p_arg );
	void execute( ThreadPoolTask *task );

public:
	ThreadPoolItem( String name , int threadPoolItem , ClassList<ThreadPoolTask>& threadTasks );
	~ThreadPoolItem();
	virtual const char *getClass() { return( "ThreadPoolItem" ); };

private:
	String name;
	ThreadState state;
	RFC_HND thread;
	int threadPoolId;

	RFC_HND runEvent;
	RFC_HND suspendEvent;
	bool suspendSignal;
	bool stopSignal;
	ClassList<ThreadPoolTask> tasks;

	int ticksPerSecond;

public:
	int executionCount;
	int ticksExecTimeTotal;
	int ticksSleepTimeTotal;
	int ticksWaitTimeRemained;
	int executionTimeWindowTicks;
};

/*#########################################################################*/
/*#########################################################################*/

class ThreadPoolPerformance {
public:
	ThreadPoolPerformance( Logger& logger , ClassList<ThreadPoolItem>& threads );

public:
	void gather();
	void updateSpeedIfRequired( float prevLoadPercents , float lastLoadPercents , float maxLoadPercents , CPULOADINFO& loadinfo );

public:
	Logger& logger;
	ClassList<ThreadPoolItem>& threads;

	int lastAverageTimeWindowTicks;
	int lastAverageRunTicks;
	int lastAverageSleepTicks;
	int lastAverageExecutionCount;
	int lastActiveThreads;

	int ticksPerSecond;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_THREADS_IMPL_H
