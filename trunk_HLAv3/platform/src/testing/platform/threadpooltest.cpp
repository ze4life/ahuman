#include <ah_platform.h>
#include <ah_testing_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class ThreadPoolTest_Task : public ThreadPoolTask {
private:
	String name;
	int taskTimeSec;

public:
	ThreadPoolTest_Task( String p_name , int p_taskTimeSec ) : ThreadPoolTask() {
		name = p_name;
		taskTimeSec = p_taskTimeSec;
		setInstance( name );
	};
	virtual const char *getClass() { return( "ThreadPoolTest_Task" ); };

public:
	virtual void execute() {
		logger.logInfo( String( "Task started for delay=" ) + taskTimeSec );
		rfc_thr_sleep( taskTimeSec );
	};
};

/*#########################################################################*/
/*#########################################################################*/

class ThreadPoolTest : public TestUnit {
// construction
public:
	ThreadPoolTest() : TestUnit( "ThreadPoolTest" ) {
		attachLogger();
	};
	~ThreadPoolTest() {
	};

	virtual void onCreate() {
		ADD_METHOD( ThreadPoolTest::testWorkflow );
	}
	
// tests
public:

	void testWorkflow( XmlCall& call ) {
		// parameters
		String threadPoolName = call.getParam( "threadPoolName" );
		int nTasks = call.getIntParam( "nTasks" );
		int taskTimeSec = call.getIntParam( "taskTimeSec" );
		int runTimeSec = call.getIntParam( "runTimeSec" );
		int suspendTimeSec = call.getIntParam( "suspendTimeSec" );
		int resumeTimeSec = call.getIntParam( "resumeTimeSec" );

		// create task list
		ClassList<ThreadPoolTask> tasks;
		for( int k = 0; k < nTasks; k++ ) {
			ThreadPoolTest_Task *task = new ThreadPoolTest_Task( String( "T" ) + k , taskTimeSec );
			tasks.add( task );
		}

		// create and configure thread pool
		logger.logInfo( "Create thread pool..." );
		ThreadService *ts = ThreadService::getService();
		ts -> createThreadPool( threadPoolName , call.getXml().getChildNode( "threadpoolconfiguration" ) , tasks );

		// workflow
		logger.logInfo( "Start thread pool..." );
		ts -> startThreadPool( threadPoolName );
		rfc_thr_sleep( runTimeSec );
		logger.logInfo( "Suspend thread pool..." );
		ts -> suspendThreadPool( threadPoolName );
		rfc_thr_sleep( suspendTimeSec );
		logger.logInfo( "Resume thread pool..." );
		ts -> resumeThreadPool( threadPoolName );
		rfc_thr_sleep( resumeTimeSec );
		logger.logInfo( "Stop thread pool..." );
		ts -> stopThreadPool( threadPoolName );
		logger.logInfo( "Destroy thread pool..." );
		ts -> destroyThreadPool( threadPoolName );

		// drop tasks
		tasks.destroy();
		logger.logInfo( "Finished." );
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createThreadPoolTest() {
	return( new ThreadPoolTest );
}

