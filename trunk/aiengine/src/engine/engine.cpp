
#include "engine_impl.h"
#include <windows.h>

AIEngineImpl *AIEngineImpl::instance = NULL;
DWORD tlsIndex = 0;

/*#########################################################################*/
/*#########################################################################*/

static LPTOP_LEVEL_EXCEPTION_FILTER oldAIUnhandledExceptionFilter;

void AIUnhandledExceptionTranslator( unsigned int exceptionCode , struct _EXCEPTION_POINTERS *exceptionInfo )
{
	throw RuntimeException( exceptionCode , 1 , exceptionInfo -> ExceptionRecord -> ExceptionAddress );
}

// thread data
class ThreadData
{
public:
	ThreadData() {
		memset( &threadExtId , 0 , sizeof( RFC_THREAD ) );
		threadId = ( DWORD )NULL;
		object = NULL;
		objectFunction = NULL;
		objectFunctionArg = NULL;
	}
public:
	RFC_THREAD threadExtId;
	String name;
	DWORD threadId;
	Object *object;
	void ( Object::*objectFunction )( void *p_arg );
	void *objectFunctionArg;

	MapStringToClass<ThreadObject> map;
};

/* if termination signal catched */
static void on_exit( int p_sig )
{
	AIEngine::getInstance().exit( -4 );
}

static 	unsigned		__stdcall threadMainFunction( void *p_arg )
{
	ThreadData *td = ( ThreadData * )p_arg;
	AIEngine& engine = AIEngine::getInstance();
	AIEngineImpl *impl = ( AIEngineImpl * )&engine;
	return( impl -> threadFunction( td ) );
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
	tlsIndex = TlsAlloc();
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
	Timer::startAdjustment();
	rfc_thr_sleep( 1 );
	Timer::stopAdjustment();

	logManager = new LogManager();
	logManager -> setSyncMode( true );

	logger.attachRoot();

	// register main thread
	workerCreated();

	ThreadData *td = new ThreadData;
	workerStarted( td );

	// engine configuration
	config = loadXml( "main.xml" );

	// init logging
	Xml configLogging = config.getChildNode( "logging" );
	logStart( configLogging );

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
		initServices();

		// run services
		runServices();

		logger.logInfo( "SERVER STARTED" );
		logger.logInfo( "----------------------------------------" );

		waitExitSignal();
	}
	catch ( RuntimeException& e ) {
		logger.logInfo( "UNABLE TO START SERVER" );
		e.printStack( logger );
		status = -1;
	}
	catch ( ... ) {
		fprintf( stderr , "AIEngineImpl::runInternal - unexpected unknown exception" );
		status = -2;
	}

	logger.logInfo( "----------------------------------------" );
	logger.logInfo( "SERVER STOPPING..." );
	
	// exit services
	exitServices();

	// wait till instance execution ended
	logStopAsync();
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

	ThreadData *td = new ThreadData;
	workerStarted( td );

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

	// tech services
	svc = AITestPool::newService(); svc -> isNewCompleted = true;
	svc = AIIO::newService(); svc -> isNewCompleted = true;
	svc = AIMedia::newService(); svc -> isNewCompleted = true;
	svc = AIDB::newService(); svc -> isNewCompleted = true;
	
	// mind services
	svc = AILibNN::newService(); svc -> isNewCompleted = true;
	svc = AILibBN::newService(); svc -> isNewCompleted = true;
	svc = AIKnowledge::newService(); svc -> isNewCompleted = true;
	svc = AIIntelligence::newService(); svc -> isNewCompleted = true;
	svc = AICognition::newService(); svc -> isNewCompleted = true;
	svc = AIBody::newService(); svc -> isNewCompleted = true;
	svc = AIBrain::newService(); svc -> isNewCompleted = true;

	// attach loggers
	for( int k = 0; k < services.count(); k++ )
		{
			Service *svc = services.getClassByIndex( k );
			Logger& logger = svc -> getLogger();
			logger.attach( svc );
		}

	// attach configurations and create configured data
	Xml configs = config.getChildNode( "services" );
	for( Xml item = configs.getFirstChild( "service" ); item.exists(); item = item.getNextChild( "service" ) )
		{
			String serviceName = item.getAttribute( "name" );
			String fileName = item.getProperty( "file" );
			
			svc = services.get( serviceName );
			ASSERTMSG( svc != NULL , String( "Service [" ) + serviceName + "] not found" );

			Xml configService = loadXml( fileName );
			svc -> configure( configService );
			ASSERTMSG( svc -> getConfig().exists() , String( "Service [" ) + svc -> getName() + "] is not configured" );

			svc -> isCreateStarted = true; 
			logger.logInfo( String( "create service: " ) + svc -> getName() + String( "..." ) );
			svc -> createService();
			logger.logInfo( String( "create service: " ) + svc -> getName() + String( " - done" ) );
			svc -> isCreateCompleted = true; 
		}

	logger.logInfo( "create services - done" );
}

LogManager *AIEngineImpl::getLogManager()
{
	return( logManager );
}

void AIEngineImpl::initServices() 
{
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

	logger.logInfo( "init services - done" );
}

void AIEngineImpl::runServices()
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
}

void AIEngineImpl::waitExitSignal()
{
	rfc_hnd_semlock( lockExit );
	if( countExit > 1 )
		{
			rfc_hnd_semunlock( lockExit );
			rfc_hnd_waitevent( eventExit );
		}
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

void AIEngineImpl::logStart( Xml configLogging )
{
	// open file
	logManager -> configure( configLogging );
	if( !logManager -> start() )
		throw RuntimeError( "AIEngineImpl::logStart: cannot initialize logging: unknown reason" );

	logger.logInfo( "LOGGING STARTED" );

	// start configured mode
	bool mode = logManager -> getConfiguredSyncMode();
	logManager -> setSyncMode( mode );
}

void AIEngineImpl::logStop()
{
	// stop logging
	logger.logInfo( "LOGGING STOPPED" );
	logManager -> stop();
}

void AIEngineImpl::logStopAsync()
{
	// stop async logging
	logManager -> stopAsync();
}

int AIEngineImpl::getThreadId()
{
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	return( threadData -> threadId );
}

RFC_HND AIEngineImpl::getThreadHandle() {
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	return( threadData -> threadExtId.s_ih );
}

unsigned AIEngineImpl::threadFunction( ThreadData *td )
{
	workerStarted( td );
	
	int status = 0;
	Object *o = td -> object;
	Logger& tlogger = o -> getLogger();
	tlogger.attach( o );

	try {
		tlogger.logInfo( "Thread " + td -> name + ": started with threadId=0x" + String::toHex( ( int )td -> threadId ) );
		tlogger.attach( td -> name );
		void ( Object::*of )( void *p_arg ) = td -> objectFunction;
		void *oa = td -> objectFunctionArg;
		( o ->* of )( oa );
	}
	catch ( RuntimeException& e ) {
		e.printStack( tlogger );
		status = -12;
	}
	catch ( ... ) {
		tlogger.logError( "Thread " + td -> name + ": unknown exception" );
		tlogger.printStack();
		status = -13;
	}

	workerExited( status );
	return( status );
}

RFC_HND AIEngineImpl::runThread( String p_name , Object *object , void (Object::*p_function)( void *p_arg ) , void *p_arg )
{
	workerCreated();

	ThreadData *td = new ThreadData;
	td -> object = object;
	td -> objectFunction = p_function;
	td -> objectFunctionArg = p_arg;
	td -> name = p_name;

	if( rfc_thr_process( &td -> threadExtId , ( void * )td , threadMainFunction ) )
		{
			logger.logError( "AIEngineImpl::runThread - cannot start thread: " + td -> name );
			workerExited( td -> threadExtId , -10 );
			return( NULL );
		}

	return( td -> threadExtId.s_ih );
}

void AIEngineImpl::workerCreated()
{
	rfc_hnd_semlock( lockExit );
	countExit++;
	rfc_hnd_semunlock( lockExit );
}

void AIEngineImpl::workerStarted( ThreadData *threadData )
{
	// thread-allocated data
	TlsSetValue( tlsIndex , threadData );

	threadData -> threadId = ::GetCurrentThreadId();

	// init logging
	EngineThreadHelper *to = new EngineThreadHelper;
	to -> addThreadObject();
	manageCallStack();
}

void AIEngineImpl::workerExited( RFC_THREAD threadId , int status )
{
	workerDestroyed();
}

void AIEngineImpl::workerExited( int status )
{
	workerDestroyed();

	// thread-allocated data
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	ASSERT( threadData != NULL );
	threadData -> map.destroy();
	delete threadData;
}

bool AIEngineImpl::waitThreadExited( RFC_HND threadId )
{
	RFC_THREAD th;
	th.s_ih = threadId;
	th.s_ip = NULL;
	if( rfc_thr_waitexit( &th ) < 0 )
		return( false );

	return( true );
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
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	ASSERT( threadData != NULL );
	ASSERT( threadData -> map.get( key ) == NULL );

	threadData -> map.add( key , to );
}

ThreadObject *AIEngineImpl::getWorkerObject( const char *key )
{
	ThreadData *threadData = ( ThreadData * )TlsGetValue( tlsIndex );
	ASSERT( threadData != NULL );
	return( threadData -> map.get( key ) );
}

Xml AIEngineImpl::loadXml( String fileName )
{
	// check whether already loaded
	TiXmlDocument *doc = configs.get( fileName );
	if( doc == NULL )
		{
			// init instance
			String path = configDir + "/" + fileName;
			doc = new TiXmlDocument( path );
			if( !doc -> LoadFile() )
				{
					String err = String( "AIEngineImpl::getRoot: cannot load root configuration from: " ) + path;
					delete doc;
					throw RuntimeError( err );
				}

			configs.add( fileName , doc );
		}

	Xml config;
	config.attach( doc , doc -> FirstChildElement() );
	return( config );
}

Xml AIEngineImpl::readXml( const char *data , const char *contentName )
{
	TiXmlDocument *doc = new TiXmlDocument();

	const char *p = doc -> Parse( data );
	if( doc -> Error() )
		{
			delete doc;
			String err = "XML message cannot be read";
			throw RuntimeError( err );
		}

	// verify trailing data are only spaces
	if( p != NULL )
		{
			char c;
			while( c = *p++ )
				if( !( c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\r' ) )
					break;

			if( c )
				{
					delete doc;
					String err = "XML message is malformed - data found behind message";
					throw RuntimeError( err );
				}
		}

	// verify message has given child element
	try {
		TiXmlElement *item = doc -> FirstChildElement( contentName );
		if( item != NULL )
			{
				Xml xml;
				xml.attach( doc , item );
				return( xml );
			}
	}
	catch( ... ) {
	}

	delete doc;
	String err = String( "XML message is malformed - cannot find required top item: " ) + contentName;
	throw RuntimeError( err );
}

Xml AIEngineImpl::createXml( const char *contentName )
{
	TiXmlDocument *doc = new TiXmlDocument();
	TiXmlElement *top = new TiXmlElement( contentName );
	doc -> LinkEndChild( top );
	
	Xml xml;
	xml.attach( doc , top );

	return( xml );
}

void AIEngineImpl::destroyXmlDoc( Xml& xml )
{
	TiXmlDocument *doc = ( TiXmlDocument * )xml.doc;
	delete doc;

	xml.doc = NULL;
	xml.node = NULL;
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
	EngineThreadHelper *to = EngineThreadHelper::getThreadObject();
	to -> oldAIUnhandledExceptionTranslator = ( void (*)() )::_set_se_translator( AIUnhandledExceptionTranslator );
}
