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
	runEnabled = config.getBooleanProperty( "run" );
	nThreads = config.getIntProperty( "threadCount" );
	executionTimeWindowMs = config.getIntProperty( "executionTimeWindowMs" );
	secondsPerMonitoringCycle = config.getIntProperty( "secondsPerMonitoringCycle" );
	maxLoadPercents = config.getIntProperty( "maxLoadPercents" );
	ticksPerSecond = Timer::timeMsToTicks( 1000 );
	stopSignal = false;
}

void ThreadPool::create( ClassList<ThreadPoolTask>& tasks ) {
	if( !runEnabled )
		return;

	int nTasks = tasks.count();
	if( nThreads > nTasks )
		nThreads = nTasks;

	ASSERTMSG( nThreads >= 1 , "nThreads is invalid" );

	int nWhole = nTasks / nThreads;
	int nPart = nTasks % nThreads;

	int executionTimeWindowTicks = ( int )( executionTimeWindowMs * 1000. / ticksPerSecond );

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
		ThreadPoolItem *thread = new ThreadPoolItem( name , k , threadTasks );
		threads.add( thread );

		// configure thread
		thread -> setExecutionTimeWindowTicks( executionTimeWindowTicks );
		nFrom += n;
	}
}

void ThreadPool::ensureStopped() {
	if( state.getState() != ThreadState::THREAD_STATE_CREATED )
		stop();
}

void ThreadPool::start() {
	state.setState( ThreadState::THREAD_STATE_RUNNING );

	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> start();
	}

	// start monitoring thread
	ThreadService *ts = ThreadService::getService();
	monitorThread = ts -> runThread( "monitor." + name , this , ( ObjectThreadFunction )&ThreadPool::runMonitorThread , NULL );
}

void ThreadPool::suspend() {
	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> suspend();
	}

	state.setState( ThreadState::THREAD_STATE_SUSPENDED );
}

void ThreadPool::resume() {
	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ThreadPoolItem *thread = threads.get( k );
		thread -> resume();
	}

	state.setState( ThreadState::THREAD_STATE_RUNNING );
}

void ThreadPool::stop() {
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

	while( !stopSignal ) {
		rfc_thr_sleep( secondsPerMonitoringCycle );
		runMonitorTask();
	}
}

void ThreadPool::runMonitorTask() {
	// log stat
	lastCPULoad = rfc_sys_getcpuload( &cpuload );
	logger.logInfo( String( "execute: currentCPULoad=" ) + lastCPULoad +
		", didle=" + ( int )( cpuload.idle - cpuload.pidle ) +
		", dkernel=" + ( int )( cpuload.kernel - cpuload.pkernel ) +
		", duser=" + ( int )( cpuload.user - cpuload.puser ) +
		", dclocks=" + ( int )( cpuload.clocks - cpuload.pclocks ) );

	// recalculate operation time if dynamic
	if( lastCPULoad > maxLoadPercents ) {
		decreaseSpeed( 1 );
	}
	else
	if( lastCPULoad < 0.9 * maxLoadPercents ) {
		increaseSpeed( 1 );
	}
}
	
// factor is shows ratio whole/part, where whole is current speed and part is its change to be done
// always positive, maximum change is current value
void ThreadPool::increaseSpeed( int factor ) {
	logger.logInfo( String( "increaseSpeed: speed increased" ) );
}

void ThreadPool::decreaseSpeed( int factor ) { 	
	logger.logInfo( String( "decreaseSpeed: speed decreased" ) );
}
