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
		ThreadService *ts = ThreadService::getService();
		ts -> threadSleepMs( taskTimeSec * 1000 );
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
		ADD_METHOD( ThreadPoolTest::testResPoolWorkflow );
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
		ts -> threadSleepMs( runTimeSec * 1000 );

		logger.logInfo( "Suspend thread pool..." );
		ts -> suspendThreadPool( threadPoolName );
		ts -> threadSleepMs( suspendTimeSec * 1000 );
		logger.logInfo( "Resume thread pool..." );
		ts -> resumeThreadPool( threadPoolName );
		ts -> threadSleepMs( resumeTimeSec * 1000 );
		logger.logInfo( "Stop thread pool..." );
		ts -> stopThreadPool( threadPoolName );
		logger.logInfo( "Destroy thread pool..." );
		ts -> destroyThreadPool( threadPoolName );

		// drop tasks
		tasks.destroy();
		logger.logInfo( "Finished." );
	}

	void testResPoolWorkflow( XmlCall& call ) {
		// parameters
		String threadPoolName = call.getParam( "threadPoolName" );
		int taskTimeSec = call.getIntParam( "taskTimeSec" );

		// create and configure thread pool
		logger.logInfo( "Create thread pool..." );
		ThreadService *ts = ThreadService::getService();

		ResourcePool<ThreadPoolTest_Task> tasks;
		ts -> createThreadPool( threadPoolName , call.getXml().getChildNode( "threadpoolconfiguration" ) , ( ResourcePool<ThreadPoolTask>& ) tasks );

		// workflow
		logger.logInfo( "Start thread pool..." );
		ts -> startThreadPool( threadPoolName );

		for( int k = 0; k < 100000; k++ ) {
			logger.logInfo( String("put next task #=") + k + "..." );
			tasks.put( new ThreadPoolTest_Task( String( "task#" ) + k , taskTimeSec ) );
		}

		rfc_thr_sleep( 30 );
		logger.logInfo( "Suspend thread pool..." );
		ts -> suspendThreadPool( threadPoolName );

		for( int k = 0; k < 100000; k++ )
			tasks.put( new ThreadPoolTest_Task( String( "task#" ) + k , taskTimeSec ) );

		logger.logInfo( "Resume thread pool..." );
		ts -> resumeThreadPool( threadPoolName );

		rfc_thr_sleep( 30 );

		logger.logInfo( "Stop thread pool..." );
		ts -> stopThreadPool( threadPoolName );
		logger.logInfo( "Destroy thread pool..." );
		ts -> destroyThreadPool( threadPoolName );

		// drop tasks
		logger.logInfo( "Finished." );
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createThreadPoolTest() {
	return( new ThreadPoolTest );
}

