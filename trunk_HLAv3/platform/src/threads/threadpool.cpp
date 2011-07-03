#include <ah_platform.h>
#include <ah_threads_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ThreadPool::ThreadPool( String p_name ) {
	name = p_name;
	runEnabled = false;
	setInstance( name );
}

ThreadPool::~ThreadPool() {
	threads.destroy();
}

void ThreadPool::configure( Xml config ) {
	runEnabled = config.getBooleanProperty( "run" , true );
	nThreads = config.getIntProperty( "threadCount" , 10 );
	secondsPerMonitoringCycle = config.getIntProperty( "secondsPerMonitoringCycle" , 10 );
	maxLoadPercents = config.getIntProperty( "maxLoadPercents" , 10 );
	stopSignal = false;
}

void ThreadPool::create( ClassList<ThreadPoolTask>& tasks ) {
	if( !runEnabled ) {
		logger.logInfo( "Ignore threadPool=" + name + ", runEnabled=false" );
		return;
	}

	int nTasks = tasks.count();
	if( nThreads > nTasks )
		nThreads = nTasks;

	ASSERTMSG( nThreads >= 1 , "nThreads is invalid" );

	int nWhole = nTasks / nThreads;
	int nPart = nTasks % nThreads;

	// split objects by threads
	int nFrom = 0;
	for( int k = 0; k < nThreads; k++ ) {
		// calculate number of objects for thread
		int n = nWhole;
		if( nPart ) {
			n++;
			nPart--;
		}

		// create list of thread tasks
		ClassList<ThreadPoolTask> threadTasks;
		threadTasks.allocate( n );
		for( int j = 0; j < n; j++ ) {
			ThreadPoolTask *task = tasks.get( nFrom + j );
			task -> pool = this;
			threadTasks.add( task );
		}

		// create thread (suspended) and add to the pool
		String threadName = name + "#" + k;
		ThreadPoolItem *thread = new ThreadPoolFixedTaskListItem( threadName , k , threadTasks );
		threads.add( thread );

		// configure thread
		nFrom += n;
	}
}

void ThreadPool::create( ResourcePool<ThreadPoolTask>& tasks ) {
	if( !runEnabled ) {
		logger.logInfo( "Ignore threadPool=" + name + ", runEnabled=false" );
		return;
	}

	ASSERTMSG( nThreads >= 1 , "nThreads is invalid" );

	for( int k = 0; k < nThreads; k++ ) {
		// create thread (suspended) and add to the pool
		String threadName = name + "#" + k;
		ThreadPoolItem *thread = new ThreadPoolTaskQueueItem( threadName , k , tasks );
		threads.add( thread );
	}
}

void ThreadPool::ensureStopped() {
	if( state.getState() != ThreadState::THREAD_STATE_CREATED )
		stop();
}

void ThreadPool::start() {
	if( !runEnabled )
		return;

	state.setState( ThreadState::THREAD_STATE_RUNNING );

	// iterate by threads - start threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> start();
	}

	// iterate by threads - resune
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> resume();
	}

	// start monitoring thread
	ThreadService *ts = ThreadService::getService();
	monitorThread = ts -> runThread( "monitor." + name , this , ( ObjectThreadFunction )&ThreadPool::runMonitorThread , NULL );
}

void ThreadPool::suspend() {
	if( !runEnabled )
		return;

	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> suspend();
	}

	state.setState( ThreadState::THREAD_STATE_SUSPENDED );
}

void ThreadPool::resume() {
	if( !runEnabled )
		return;

	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> resume();
	}

	state.setState( ThreadState::THREAD_STATE_RUNNING );
}

void ThreadPool::stop() {
	if( !runEnabled )
		return;

	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> stop();
	}

	stopSignal = true;
	if( monitorThread != ( RFC_HND )NULL ) {
		ThreadService *ts = ThreadService::getService();
		ts -> waitThreadExited( monitorThread );
		monitorThread = NULL;
	}

	state.setState( ThreadState::THREAD_STATE_CREATED );
}

void ThreadPool::runMonitorThread( void *arg ) {
	cpuload.initialized = 0;
	lastCPULoad = rfc_sys_getcpuload( &cpuload );

	ThreadService *ts = ThreadService::getService();
	while( !stopSignal ) {
		ts -> threadSleepMs( secondsPerMonitoringCycle * 1000 );
		runMonitorTask();
	}
}

void ThreadPool::runMonitorTask() {
	// log stat
	float cpuLoad = rfc_sys_getcpuload( &cpuload );
	logger.logInfo( String( "execute: currentCPULoad=" ) + lastCPULoad +
		", didle=" + ( int )( cpuload.idle - cpuload.pidle ) +
		", dkernel=" + ( int )( cpuload.kernel - cpuload.pkernel ) +
		", duser=" + ( int )( cpuload.user - cpuload.puser ) +
		", dclocks=" + ( int )( cpuload.clocks - cpuload.pclocks ) );

	// calculate current metrics
	ThreadPoolPerformance tpp( logger , threads );
	tpp.gather();

	// recalculate operation time if dynamic
	tpp.updateSpeedIfRequired( cpuLoad , lastCPULoad , ( float )maxLoadPercents , cpuload );
	lastCPULoad = cpuLoad;
}
