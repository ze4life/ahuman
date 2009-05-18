
#include "aiengine_impl.h"
#include <windows.h>
#include <eh.h>

AIEngineImpl *AIEngineImpl::instance = NULL;

/*#########################################################################*/
/*#########################################################################*/

static LPTOP_LEVEL_EXCEPTION_FILTER oldAIUnhandledExceptionFilter;
static _se_translator_function oldAIUnhandledExceptionTranslator;

void AIUnhandledExceptionTranslator( unsigned int exceptionCode , struct _EXCEPTION_POINTERS *exceptionInfo )
{
	throw RuntimeException( exceptionCode , 1 , exceptionInfo -> ExceptionRecord -> ExceptionAddress );
}

// thread data
__declspec( thread ) class ThreadData
{
public:
	MapStringToClass<ThreadObject> map;
	DWORD threadId;
} *threadData = NULL;

/* if termination signal catched */
static void on_exit( int p_sig )
{
	AIEngine::getInstance().exit( -4 );
}

/*#########################################################################*/
/*#########################################################################*/

int AIEngine::run( const char *configDir )
{
	int status = 0;

	// create & run
	AIEngineImpl::instance = new AIEngineImpl();
	status = AIEngineImpl::instance -> runInternal( configDir );

	// destroy
	delete AIEngineImpl::instance;
	AIEngineImpl::instance = NULL;

	return( status );
}

AIEngine& AIEngine::getInstance()
{
	return( *AIEngineImpl::instance );
}

/*#########################################################################*/
/*#########################################################################*/

// constructor
AIEngineImpl::AIEngineImpl()
{
	workerStatus = 0;
	lockExit = rfc_hnd_semcreate();
	eventExit = rfc_hnd_evcreate();
	countExit = 0;
	stoppedBySignal = false;

	logManager = NULL;
	mapObjectTypeIdToSerializeObject = rfc_map_strcreate();
}

AIEngineImpl::~AIEngineImpl()
{
	rfc_hnd_semdestroy( lockExit );
	rfc_hnd_evdestroy( eventExit );

	// free serialize objects
	destroySerializeObjectInstances();
	rfc_map_strdrop( mapObjectTypeIdToSerializeObject );

	delete logManager;
	configs.destroy();
}

void AIEngineImpl::init()
{
	logManager = new LogManager();
	logManager -> setSyncMode( true );

	logger.attach( "root" );
	logger.setLogLevel( Logger::LogLevelAll );

	manageCallStack();

	// register main thread
	workerCreated();
	workerStarted();

	// configuration
	mainConfigRoot = getRoot( "main" );

	// init logging
	logStart();

	// register serializable classes
	Scale::createSerializeObject();
	SerializeObject::createSerializeObject();
}

int AIEngineImpl::runInternal( const char *p_configDir )
{
	configDir = p_configDir;

	try {
		// init basics
		init();
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
		logStop();
		return( -2 );
	}
	catch ( ... ) {
		fprintf( stderr , "AIEngineImpl::runInternal - unexpected unknown exception" );
		logStop();
		return( -3 );
	}

	logger.logInfo( "SERVER STARTING..." );
	logger.logInfo( "----------------------------------------" );
	int status = 0;
	try {
		// create all service classes
		createServices();

		// initialize classes
		if( initServices() )
			status = runServices();
		else
			status = -1;

		logger.logInfo( "SERVER STARTED" );
		logger.logInfo( "----------------------------------------" );

		// wait till instance execution ended
		rfc_hnd_semlock( lockExit );
		if( countExit > 1 )
			{
				rfc_hnd_semunlock( lockExit );
				rfc_hnd_waitevent( eventExit );
			}
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
		status = -2;
	}
	catch ( ... ) {
		fprintf( stderr , "AIEngineImpl::runInternal - unexpected unknown exception" );
		status = -3;
	}

	logger.logInfo( "----------------------------------------" );
	logger.logInfo( "SERVER STOPPING..." );
	
	// exit services
	exitServices();

	// wait till instance execution ended
	while( countExit > 1 )
		rfc_thr_sleep( 1 );

	// destroy services
	destroyServices();

	logger.logInfo( "----------------------------------------" );
	logger.logInfo( "SERVER STOPPED" );
	logStop();

	return( status );
}

void AIEngineImpl::exit( int status )
{
	workerCreated();
	workerStarted();

	logger.logInfo( "Stop by signal" );

	// raise stop event
	stoppedBySignal = true;
	rfc_hnd_evsignal( eventExit );

	workerExited( 0 );
}

void AIEngineImpl::createServices()
{
	logger.logInfo( "create services..." );
	Service *svc;

	svc = AIMedia::createService(); svc -> isCreateCompleted = true;
	svc = AIIO::createService(); svc -> isCreateCompleted = true;
	svc = AIExpert::createService(); svc -> isCreateCompleted = true;
	svc = AIHeart::createService(); svc -> isCreateCompleted = true;
	svc = AIMind::createService(); svc -> isCreateCompleted = true;
	svc = AIKnowledge::createService(); svc -> isCreateCompleted = true;
	svc = AIDB::createService(); svc -> isCreateCompleted = true;

	// attach loggers
	for( int k = 0; k < services.count(); k++ )
		{
			Service *svc = services.getClassByIndex( k );
			Logger& logger = svc -> getLogger();
			logger.attach( svc );
		}

	logger.logInfo( "create services - done" );
}

LogManager *AIEngineImpl::getLogManager()
{
	return( logManager );
}

bool AIEngineImpl::initServices() 
{
	try {
		for( int k = 0; k < services.count(); k++ )
			{
				Service *svc = services.getClassByIndex( k );
				ASSERT( svc -> isCreateCompleted );

				// call service init procedure
				logger.logInfo( String( "init service: " ) + svc -> getName() + String( "..." ) );
				svc -> isInitStarted = true; 
				svc -> initService(); 
				svc -> isInitCompleted = true;
				logger.logInfo( String( "init service: " ) + svc -> getName() + String( " - done" ) );
			}
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
		return( false );
	}

	logger.logInfo( "init services - done" );
	return( true );
}

int AIEngineImpl::runServices()
{
	logger.logInfo( "run services..." );

	// initialize event
	rfc_hnd_evreset( eventExit );

	// run all instances
	for( int k = 0; k < services.count(); k++ )
		{
			Service *svc = services.getClassByIndex( k );
			ASSERT( svc -> isInitCompleted );

			logger.logInfo( String( "run service: " ) + svc -> getName() + String( "..." ) );
			svc -> isRunStarted = true; 
			svc -> runService(); 
			svc -> isRunCompleted = true;
			logger.logInfo( String( "run service: " ) + svc -> getName() + String( " - done" ) );
		}

	logger.logInfo( "run services - done" );

	// set signal handlers
	signal( SIGABRT , on_exit );
	signal( SIGINT , on_exit );
	signal( SIGTERM , on_exit );
	signal( SIGFPE , on_exit );
	signal( SIGILL , on_exit );
	signal( SIGSEGV , on_exit );

	return( workerStatus );
}

void AIEngineImpl::exitServices()
{
	logger.logInfo( "exit services..." );
	for( int k = 0; k < services.count(); k++ )
		{
			// exit sepately from each other
			Service *svc = NULL;
			try {
				svc = services.getClassByIndex( k );
				if( svc -> isInitStarted == false || svc -> isExitStarted == true )
					continue;

				logger.logInfo( String( "exit service: " ) + svc -> getName() + String( "..." ) );
				svc -> isExitStarted = true;
				svc -> exitService();
				svc -> isExitCompleted = true;
				logger.logInfo( String( "exit service: " ) + svc -> getName() + String( " - done" ) );
			}
			catch( RuntimeException& e ) {
				e.printStack( logger );
				logger.logInfo( String( "exception while stopping service: " ) + svc -> getName() );
			}
			catch( ... ) {
				logger.logInfo( String( "unknown exception while stopping service: " ) + svc -> getName() );
			}
		}
	logger.logInfo( "exit services - done" );
}

void AIEngineImpl::destroyServices()
{
	logger.logInfo( "destroy services..." );
	for( int k = 0; k < services.count(); k++ )
		{
			// destroy sepately from each other
			Service *svc = NULL;
			try {
				svc = services.getClassByIndex( k );
				services.set( services.getKeyByIndex( k ) , NULL );

				if( svc -> isExitStarted == false || svc -> isDestroyStarted == true )
					continue;

				String name = svc -> getName();
				logger.logInfo( String( "destroy service: " ) + name + String( "..." ) );
				svc -> isDestroyStarted = true;
				svc -> destroyService();
				logger.logInfo( String( "destroy service: " ) + name + String( " - done" ) );
			}
			catch( RuntimeException& e ) {
				e.printStack( logger );
				logger.logInfo( String( "exception while destroying service: " ) + svc -> getName() );
			}
			catch( ... ) {
				logger.logInfo( String( "unknown exception while destroying service: " ) + svc -> getName() );
			}
		}
	services.clear();
	logger.logInfo( "destroy services - done" );
}

void AIEngineImpl::logStart()
{
	// open file
	logManager -> configure( "logging" );
	if( !logManager -> startWriter() )
		throw RuntimeError( "AIEngineImpl::logStart: cannot initialize logging: unknown reason" );

	logger.logInfo( "LOGGING STARTED" );
}

void AIEngineImpl::logStop()
{
	// stop async logging
	logManager -> stopWriter();
	logManager -> waitForExit();

	logger.logInfo( "LOGGING STOPPED" );
}

int AIEngineImpl::getThreadId()
{
	return( threadData -> threadId );
}

void AIEngineImpl::workerCreated()
{
	rfc_hnd_semlock( lockExit );
	countExit++;
	rfc_hnd_semunlock( lockExit );
}

void AIEngineImpl::workerStarted()
{
	// thread-allocated data
	ASSERT( threadData == NULL );
	threadData = new ThreadData;
	threadData -> threadId = ::GetCurrentThreadId();

	// init logging
	ThreadLogTail *logTail = new ThreadLogTail;
	addWorkerObject( "LogTail" , logTail );
}

void AIEngineImpl::workerExited( RFC_THREAD threadId , int status )
{
	workerDestroyed();
}

void AIEngineImpl::workerExited( int status )
{
	workerDestroyed();

	// thread-allocated data
	ASSERT( threadData != NULL );
	threadData -> map.destroy();
	delete threadData;
}

void AIEngineImpl::workerDestroyed()
{
	rfc_hnd_semlock( lockExit );
	countExit--;

	// if no more workers (except main) - notify
	if( countExit == 1 )
		rfc_hnd_evsignal( eventExit );

	rfc_hnd_semunlock( lockExit );
}

void AIEngineImpl::addWorkerObject( const char *key , ThreadObject *to )
{
	ASSERT( key != NULL );
	ASSERT( to != NULL );
	ASSERT( threadData != NULL );
	ASSERT( threadData -> map.get( key ) == NULL );

	threadData -> map.add( key , to );
}

ThreadObject *AIEngineImpl::getWorkerObject( const char *key )
{
	ASSERT( threadData != NULL );
	return( threadData -> map.get( key ) );
}

TiXmlElement *AIEngineImpl::getRoot( const char *configName )
{
	// check whether already loaded
	TiXmlDocument *doc = configs.get( configName );
	if( doc == NULL )
		{
			// init instance
			String path = configDir + "/" + configName + ".xml";
			doc = new TiXmlDocument( path );
			if( !doc -> LoadFile() )
				{
					String err = String( "AIEngineImpl::getRoot: cannot load root configuration from: " ) + path;
					delete doc;
					throw RuntimeError( err );
				}

			configs.add( configName , doc );
		}

	return( doc -> FirstChildElement() );
}

// services
void AIEngineImpl::registerService( Service *svc ,  const char *serviceName )
{
	services.add( serviceName , svc );
}

Service *AIEngineImpl::getService( const char *serviceName )
{
	return( services.get( serviceName ) );
}

// serialized objects
void AIEngineImpl::registerSerializeObject( SerializeObject *so )
{
	addSerializeObjectInstance( so , so -> getObjectClass() );
}

SerializeObject *AIEngineImpl::getSerializeObject( const char *className )
{
	// try to find existent
	SerializeObject *so = getSerializeObjectInstance( className );
	if( so == NULL )
		throw RuntimeError( String( "AIEngineImpl::getSerializeObject: object " ) + 
			className + " not found" );

	return( so );
}

void AIEngineImpl::addSerializeObjectInstance( SerializeObject *so , const char *p_inst )
{
	// old cannot exist
	SerializeObject *soOld = getSerializeObjectInstance( p_inst );
	if( soOld != NULL )
		throw RuntimeError( String( "AIDBImpl::addSerializeObjectInstance: old object exists: " ) + p_inst );

	rfc_map_stradd( mapObjectTypeIdToSerializeObject , p_inst , so );
	so -> ref();
}

void AIEngineImpl::replaceSerializeObjectInstance( SerializeObject *so , const char *p_inst )
{
	SerializeObject *soOld = getSerializeObjectInstance( p_inst );

	// check the same
	if( soOld == so )
		return;

	// replace
	rfc_map_stradd( mapObjectTypeIdToSerializeObject , p_inst , so );
	so -> ref();

	// delete old if any
	if( soOld == NULL )
		return;

	// deref old
	soOld -> deref();
}

void AIEngineImpl::replaceSerializeObjectInstanceSrc( SerializeObject *so )
{
	String className = so -> getObjectClass();
	className += "#src";
	replaceSerializeObjectInstance( so , className );
}

SerializeObject *AIEngineImpl::getSerializeObjectInstance( const char *p_inst )
{
	// try to find existent
	SerializeObject *so;
	if( rfc_map_strcheck( mapObjectTypeIdToSerializeObject , p_inst , ( void ** )&so ) >= 0 )
		return( so );

	return( NULL );
}

void AIEngineImpl::destroySerializeObjectInstances()
{
	for( int k = 0; k < rfc_map_strcount( mapObjectTypeIdToSerializeObject ); k++ )
		{
			SerializeObject *so = ( SerializeObject * )rfc_map_strget( mapObjectTypeIdToSerializeObject , k );
			so -> deref();
		}
	rfc_map_strclear( mapObjectTypeIdToSerializeObject );
}

void AIEngineImpl::manageCallStack()
{
	oldAIUnhandledExceptionTranslator = ::_set_se_translator( AIUnhandledExceptionTranslator );
}
