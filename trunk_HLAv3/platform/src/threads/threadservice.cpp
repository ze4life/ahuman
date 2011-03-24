#include <ah_platform.h>
#include <ah_threads_impl.h>

#include <windows.h>
#include <signal.h>

unsigned long tlsIndex = 0;

/*#########################################################################*/
/*#########################################################################*/

/* if termination signal catched */
static void on_exit( int p_sig ) {
	ThreadService *ts = ThreadService::getService();
	if( ts != NULL )
		ts -> stopServicesBySignal( p_sig );
}

static unsigned __stdcall threadMainFunction( void *p_arg ) {
	ThreadData *td = ( ThreadData * )p_arg;
	ThreadService *ts = ThreadService::getService();
	return( ts -> threadFunction( td ) );
}

static void UnhandledExceptionTranslator( unsigned int exceptionCode , struct _EXCEPTION_POINTERS *exceptionInfo ) {
	throw RuntimeException( exceptionCode , 1 , exceptionInfo -> ExceptionRecord -> ExceptionAddress );
}

/*#########################################################################*/
/*#########################################################################*/

Service *ThreadService::newService() {
	return( new ThreadService() );
}

void ThreadService::createService() {
	workerStatus = 0;
	lockExit = rfc_hnd_semcreate();
	eventExit = rfc_hnd_evcreate();
	countExit = 0;

	tlsIndex = TlsAlloc();

	Timer::startAdjustment();
	rfc_thr_sleep( 1 );
	Timer::stopAdjustment();

	// initialize event
	rfc_hnd_evreset( eventExit );

	// cover main thread
	addMainThread();
}

void ThreadService::destroyService() {
	rfc_hnd_semdestroy( lockExit );
	rfc_hnd_evdestroy( eventExit );
}

void ThreadService::addMainThread() {
	// register main thread
	workerCreated();

	ThreadData *td = new ThreadData;
	td -> name = "main";
	td -> threadExtId.s_ih = ::OpenThread( THREAD_ALL_ACCESS , FALSE , ::GetCurrentThreadId() );
	td -> threadExtId.s_ip = NULL;
	workerStarted( td );
}

int ThreadService::getThreadId() {
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	if( threadData == NULL )
		return( 0 );
	return( threadData -> threadId );
}

RFC_HND ThreadService::getThreadHandle() {
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	if( threadData == NULL )
		return( ( RFC_HND )NULL );
	return( threadData -> threadExtId.s_ih );
}

unsigned ThreadService::threadFunction( ThreadData *td ) {
	workerStarted( td );
	
	int status = 0;
	Object *o = td -> object;
	Logger& tlogger = o -> getLogger();

	String name = td -> name;
	try {
		void ( Object::*of )( void *p_arg ) = td -> objectFunction;
		void *oa = td -> objectFunctionArg;
		( o ->* of )( oa );
	}
	catch ( RuntimeException& e ) {
		tlogger.printStack( e );
		status = -12;
	}
	catch ( ... ) {
		logger.printStack();
		tlogger.logError( "threadFunction: thread name=" + name + " - unknown exception" );
		tlogger.printStack();
		status = -13;
	}

	workerExited( status );
	return( status );
}

RFC_HND ThreadService::runThread( String p_name , Object *object , void (Object::*p_function)( void *p_arg ) , void *p_arg ) {
	ServiceManager& sm = ServiceManager::getInstance();
	ASSERTMSG( sm.canStartThread() , String( "Cannot start any thread in current state" ) );
	workerCreated();

	ThreadData *td = new ThreadData;
	td -> object = object;
	td -> objectFunction = p_function;
	td -> objectFunctionArg = p_arg;
	td -> name = p_name;

	if( rfc_thr_process( &td -> threadExtId , ( void * )td , threadMainFunction ) ) {
		logger.logError( "runThread: cannot start thread name=" + td -> name );
		workerExited( td , -10 );
		return( NULL );
	}

	return( td -> threadExtId.s_ih );
}

void ThreadService::workerCreated() {
	rfc_hnd_semlock( lockExit );
	countExit++;
	rfc_hnd_semunlock( lockExit );
}

void ThreadService::workerStarted( ThreadData *threadData ) {
	String name = threadData -> name;

	// add worker to managed list
	rfc_hnd_semlock( lockExit );
	if( threads.get( name ) != NULL ) {
		rfc_hnd_semunlock( lockExit );
		ASSERTFAILED( "Thread already started with name=" + name );
	}

	threads.add( name , threadData );

	// thread-allocated data
	TlsSetValue( tlsIndex , threadData );

	threadData -> threadId = ::GetCurrentThreadId();

	// init logging
	ThreadHelper *to = new ThreadHelper;
	to -> addThreadObject();
	manageThreadCallStack();

	logger.logInfo( "workerStarted: thread started name=" + name + ", threadId=0x" + String::toHex( ( int )threadData -> threadId ) );
	rfc_hnd_semunlock( lockExit );
}

void ThreadService::workerExited( ThreadData *threadData , int status ) {
	ASSERT( threadData != NULL );

	rfc_hnd_semlock( lockExit );

	// drop from thread list
	String name = threadData -> name;
	int threadId = ( int )threadData -> threadId;
	threads.remove( name );

	threadData -> map.destroy();

	// decrease counter
	countExit--;

	// if no more workers (except main) - notify
	if( countExit == 1 )
		rfc_hnd_evsignal( eventExit );

	logger.logInfo( "workerExited: thread stopped name=" + name + ", threadId=0x" + String::toHex( ( int )threadData -> threadId ) );
	delete threadData;

	rfc_hnd_semunlock( lockExit );
}

void ThreadService::workerExited( int status ) {
	// get thread-allocated data - clean it in thread memory
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );

	// run common
	workerExited( threadData , status );

	// to be no more used
	TlsSetValue( tlsIndex , NULL );
}

bool ThreadService::waitThreadExited( RFC_HND threadId ) {
	RFC_THREAD th;
	th.s_ih = threadId;
	th.s_ip = NULL;
	if( rfc_thr_waitexit( &th ) < 0 )
		return( false );

	return( true );
}

String ThreadService::getActiveThreads() {
	String rs = "";
	rfc_hnd_semlock( lockExit );
	for( int k = 0; k < threads.count(); k++ ) {
		ThreadData *td = threads.getClassByIndex( k );
		if( td -> name.equals( "main" ) )
			continue;

		if( !rs.isEmpty() )
			rs += ", ";
		rs += td -> name;
	}
	rfc_hnd_semunlock( lockExit );
	return( rs );
}

void ThreadService::addThreadObject( const char *key , ThreadObject *to ) {
	ASSERT( key != NULL );
	ASSERT( to != NULL );
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	ASSERT( threadData != NULL );
	ASSERT( threadData -> map.get( key ) == NULL );

	threadData -> map.add( key , to );
}

ThreadObject *ThreadService::getThreadObject( const char *key ) {
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	if( threadData == NULL )
		return( NULL );
	return( threadData -> map.get( key ) );
}

void ThreadService::manageThreadCallStack() {
	ThreadHelper *to = ThreadHelper::getThreadObject();
	to -> oldAIUnhandledExceptionTranslator = ( void (*)() )::_set_se_translator( UnhandledExceptionTranslator );
}

void ThreadService::threadDumpAll( bool showStackTrace ) {
	rfc_hnd_semlock( lockExit );
	logger.logInfo( String( "threadDumpAll: THREAD DUMP (" ) + "THREAD COUNT=" + threads.count() + "):" , Logger::LogStart );
	logger.logInfo( "threadDumpAll: ------------" , Logger::LogLine );

	for( int k = 0; k < threads.count(); k++ ) {
		ThreadData *td = threads.getClassByIndex( k );

		String threadInfo = String( "threadDumpAll: THREAD DUMP: thread index=" ) + k + ", name=" + td -> name + ", threadId=0x" + String::toHex( ( int )td -> threadId );
		if( showStackTrace )
			 threadInfo += ":";
		logger.logInfo( threadInfo , Logger::LogLine );

		if( showStackTrace )
			printThreadStackTrace( td );
	}

	logger.logInfo( "threadDumpAll: ------------" , Logger::LogStop );
	rfc_hnd_semunlock( lockExit );
}

void ThreadService::threadDumpByName( String name , bool showStackTrace ) {
	rfc_hnd_semlock( lockExit );
	ThreadData *td = threads.get( name );
	if( td != NULL ) {
		String threadInfo = String( "threadDumpByName: THREAD DUMP: thread name=" ) + td -> name + ", threadId=0x" + String::toHex( ( int )td -> threadId );
		if( showStackTrace )
			 threadInfo += ":";
		logger.logInfo( threadInfo );

		if( showStackTrace )
			printThreadStackTrace( td );
	}
	rfc_hnd_semunlock( lockExit );

	ASSERTMSG( td != NULL , "Unknown thread name=" + name );
}

void ThreadService::printThreadStackTrace( ThreadData *td ) {
	// suspend if not the same thread
	DWORD currentThread = ::GetCurrentThreadId();
	bool sameThread = ( currentThread == td -> threadId )? true : false;
	rfc_threadstack *stack;

	if( sameThread )
		stack = rfc_thr_stackget( 0 );
	else {
		// suspend thread
		HANDLE handle = td -> threadExtId.s_ih;
		::SuspendThread( handle );

		// get stack
		stack = rfc_thr_stackgetforthread( ( RFC_HND )handle , 0 );

		// resume thread
		::ResumeThread( handle );
	}

	// print stack
	logger.printStackInplace( stack , 0 );
}

// services
void ThreadService::setSignalHandlers() {
	signal( SIGABRT , on_exit );
	signal( SIGINT , on_exit );
	signal( SIGTERM , on_exit );
	signal( SIGFPE , on_exit );
	signal( SIGILL , on_exit );
	signal( SIGSEGV , on_exit );
}

void ThreadService::stopServicesBySignal( int status ) {
	logger.logInfo( "stopServices: Stop by signal" );

	// reset signal handlers
	setSignalHandlers();

	// process again
	workerCreated();

	ThreadData *td = new ThreadData;
	td -> name = "exit";
	workerStarted( td );

	ServiceManager::getInstance().stopServices();
	rfc_hnd_evsignal( eventExit );
	workerExited( 0 );
}

void ThreadService::waitExitSignal() {
	rfc_hnd_semlock( lockExit );
	if( countExit > 1 ) {
		rfc_hnd_semunlock( lockExit );
		rfc_hnd_waitevent( eventExit , -1 );
	}
}

void ThreadService::waitAllThreads() {
	// wait till instance execution ended
	while( true ) {
		int count = countExit - 1;
		if( count <= 0 )
			break;

		String activeThreadList = getActiveThreads();
		logger.logInfo( String( "runInternal: Waiting for stopping " ) + count + " thread(s): " + activeThreadList );
		rfc_thr_sleep( 1 );
	}
}
