#include <ah_platform.h>
#include <ah_services_impl.h>

#include <windows.h>

ServiceManager *ServiceManager::instance = NULL;

/*#########################################################################*/
/*#########################################################################*/

static void UnhandledExceptionTranslator( unsigned int exceptionCode , struct _EXCEPTION_POINTERS *exceptionInfo ) {
	throw RuntimeException( exceptionCode , 1 , exceptionInfo -> ExceptionRecord -> ExceptionAddress );
}

/*#########################################################################*/
/*#########################################################################*/

bool ServiceManager::configureDefault( String etcpath ) {
	try {
		EnvService *es = ( EnvService * )findServiceByName( "EnvService" );
		ASSERTMSG( es != NULL , "EnvService was not added to the list of services" );
		es -> configureAll( etcpath );
		return( true );
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
	}
	catch( ... ) {
		logger.logError( "createServices: unknown exception" );
	}

	return( false );
}

void ServiceManager::configureLifecycle( Xml config ) {
}

void ServiceManager::configureLogging( Xml config ) {
	logDispatcher -> configure( config );
	logDispatcher -> start();
}

void ServiceManager::setRootLogLevel( Logger::LogLevel p_logLevel ) {
	LogSettingsItem *rootSettings = LogDispatcher::getRootSettings();
	rootSettings -> setLevel( p_logLevel );
}

void ServiceManager::addService( Service *svc ) {
	serviceList.add( svc );
	svc -> attachLogger();
}

Service *ServiceManager::findServiceByName( String name ) {
	for( int k = 0; k < serviceList.count(); k++ ) {
		Service *svc = serviceList.get( k );
		if( name.equals( svc -> getServiceName() ) )
			return( svc );
	}
	return( NULL );
}

void ServiceManager::addPlatformServices() {
	addService( ThreadService::newService() );
	addService( EnvService::newService() );
	addService( ObjectService::newService() );
	addService( MessagingService::newService() );
	addService( MediaService::newService() );
	addService( PersistingService::newService() );
	addService( MathService::newService() );
	addService( SchedulerService::newService() );
	addService( StatService::newService() );
	addService( TestService::newService() );
}

Service *ServiceManager::getService( const char *serviceName ) {
	return( services.get( serviceName ) );
}

ClassList<Service>& ServiceManager::getServices() {
	return( serviceList );
}

void ServiceManager::waitRunDefault() {
	ThreadService *ts = ThreadService::getService();
	ASSERTMSG( ts != NULL , "Thread service is not created" );

	ts -> waitExitSignal();
	stopServices();
	ts -> waitAllThreads();
}

void ServiceManager::createServices() {
	logger.logInfo( "createServices: create services..." );
	state.setState( ServiceState::AH_CREATING );

	try {
		// attach loggers and run creation event
		for( int k = 0; k < serviceList.count(); k++ ) {
			Service *svc = serviceList.get( k );

			// check creation is blocked
			if( !svc -> isCreate )
				continue;

			// ensure created service is available via manager
			services.add( svc -> getServiceName() , svc );

			// setup service logging
			svc -> attachLogger();

			// internal data creation
			svc -> state.setState( ServiceState::AH_CREATING );
			logger.logInfo( String( "createServices: create service - name=" ) + svc -> getServiceName() + String( "..." ) );
			svc -> createService();
			logger.logInfo( String( "createServices: create service - name=" ) + svc -> getServiceName() + String( " - done" ) );
			svc -> state.setState( ServiceState::AH_CREATED );

			// no cross-service links are permitted on creation
			services.clear();
		}

		state.setState( ServiceState::AH_CREATED );
		logger.logInfo( "createServices: create services - done" );
		return;
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
	}
	catch( ... ) {
		logger.logError( "createServices: unknown exception" );
	}

	// in case of failure
	services.clear();
	ASSERTFAILED( "createServices: fail to create services" );
}

void ServiceManager::initServices() {
	state.setState( ServiceState::AH_INITIALIZING );

	// allow cross-links
	for( int k = 0; k < serviceList.count(); k++ ) {
		Service *svc = serviceList.get( k );

		// add created service to cross-link map
		if( svc -> state.getState() != ServiceState::AH_CREATED )
			continue;

		services.add( svc -> getServiceName() , svc );
	}

	// init services
	for( int k = 0; k < serviceList.count(); k++ ) {
		Service *svc = serviceList.get( k );

		// check initialization is blocked
		if( !svc -> isInit )
			continue;

		// call service init procedure
		logger.logInfo( String( "initServices: init service name=" ) + svc -> getServiceName() + String( "..." ) );
		svc -> state.setState( ServiceState::AH_INITIALIZING );
		svc -> initService(); 
		svc -> state.setState( ServiceState::AH_INITIALIZED );
		logger.logInfo( String( "initServices: init service name=" ) + svc -> getServiceName() + String( " - done" ) );
	}

	state.setState( ServiceState::AH_INITIALIZED );
	logger.logInfo( "initServices: init services - done" );
}

void ServiceManager::runServices() {
	logDispatcher -> enableAsyncMode();

	logger.logInfo( "runServices: run services..." );
	state.setState( ServiceState::AH_RUNNING );

	// run all instances
	for( int k = 0; k < serviceList.count(); k++ ) {
		Service *svc = serviceList.get( k );

		// check run is blocked
		if( !svc -> isRun )
			continue;

		logger.logInfo( String( "runServices: run service name=" ) + svc -> getServiceName() + String( "..." ) );
		svc -> state.setState( ServiceState::AH_RUNNING );
		svc -> runService();
		logger.logInfo( String( "runServices: run service name=" ) + svc -> getServiceName() + String( " - done" ) );
	}

	logger.logInfo( "runServices: run services - done" );
}

void ServiceManager::stopServices() {
	if( !isRunning() )
		return;

	logger.logInfo( "stopServices: stop services..." );

	// in back order
	for( int k = serviceList.count() - 1; k >= 0 ; k-- ) {
		// exit sepately from each other
		Service *svc = NULL;
		try {
			svc = serviceList.get( k );
			if( svc -> state.getState() != ServiceState::AH_RUNNING )
				continue;

			logger.logInfo( String( "stopServices: stop service name=" ) + svc -> getServiceName() + String( "..." ) );
			svc -> stopService();
			svc -> state.setState( ServiceState::AH_STOPPED );
			logger.logInfo( String( "stopServices: stop service name=" ) + svc -> getServiceName() + String( " - done" ) );
		}
		catch( RuntimeException& e ) {
			logger.printStack( e );
			logger.logInfo( String( "stopServices: exception while stopping service name=" ) + svc -> getServiceName() );
		}
		catch( ... ) {
			logger.logInfo( String( "stopServices: unknown exception while stopping service name=" ) + svc -> getServiceName() );
		}
	}
	
	state.setState( ServiceState::AH_STOPPED );
	logger.logInfo( "stopServices: stop services - done" );
}

void ServiceManager::exitServices() {
	logDispatcher -> disableAsyncMode();

	if( !state.readyForExit() )
		return;

	logger.logInfo( "exitServices: exit services..." );
	state.setState( ServiceState::AH_EXITING );

	// in back order
	bool everyExited = true;
	for( int k = serviceList.count() - 1; k >= 0 ; k-- ) {
		// exit sepately from each other
		Service *svc = NULL;
		try {
			svc = serviceList.get( k );
			if( !svc -> state.readyForExit() ) {
				if( svc -> state.exitRequired() )
					everyExited = false;
				continue;
			}

			logger.logInfo( String( "exitServices: exit service name=" ) + svc -> getServiceName() + String( "..." ) );
			svc -> state.setState( ServiceState::AH_EXITING );
			svc -> exitService();
			svc -> state.setState( ServiceState::AH_CREATED );
			logger.logInfo( String( "exitServices: exit service name=" ) + svc -> getServiceName() + String( " - done" ) );
		}
		catch( RuntimeException& e ) {
			everyExited = false;
			logger.printStack( e );
			logger.logInfo( String( "exitServices: exception while exiting service name=" ) + svc -> getServiceName() );
		}
		catch( ... ) {
			everyExited = false;
			logger.logInfo( String( "exitServices: unknown exception while exiting service name=" ) + svc -> getServiceName() );
		}
	}

	if( everyExited ) {
		state.setState( ServiceState::AH_CREATED );
		logger.logInfo( "exitServices: exit services - done" );
	}
	else {
		logger.logInfo( "exitServices: exit services - not fully completed" );
	}
}

void ServiceManager::destroyServices() {
	logger.logInfo( "destroyServices: destroy services..." );

	// in back order
	for( int k = serviceList.count() - 1; k >= 0; k-- ) {
		// destroy sepately from each other
		Service *svc = NULL;
		try {
			svc = serviceList.get( k );

			// clear in service map
			services.set( svc -> getServiceName() , NULL );
			if( svc -> state.getState() == ServiceState::AH_COLD )
				continue;

			String name = svc -> getServiceName();
			logger.logInfo( String( "destroyServices: destroy service name= " ) + name + String( "..." ) );
			svc -> destroyService();
			svc -> state.setState( ServiceState::AH_COLD );
			logger.logInfo( String( "destroyServices: destroy service name=" ) + name + String( " - done" ) );
		}
		catch( RuntimeException& e ) {
			logger.printStack( e );
			logger.logInfo( String( "destroyServices: exception while destroying service name=" ) + svc -> getServiceName() );
		}
		catch( ... ) {
			logger.printStack();
			logger.logInfo( String( "destroyServices: unknown exception while destroying service name=" ) + svc -> getServiceName() );
		}
	}

	services.clear();
	serviceList.clear();
	state.setState( ServiceState::AH_COLD );
	logger.logInfo( "destroyServices: destroy services - done" );
}

LogDispatcher *ServiceManager::getLogDispatcher() {
	return( logDispatcher );
}

bool ServiceManager::canStartThread() {
	return( state.getState() == ServiceState::AH_INITIALIZED || state.getState() == ServiceState::AH_RUNNING );
}

bool ServiceManager::isRunning() {
	return( state.getState() == ServiceState::AH_RUNNING );
}

bool ServiceManager::isCreated() {
	return( state.getState() != ServiceState::AH_COLD );
}

/*#########################################################################*/
/*#########################################################################*/

// constructor
ServiceManager::ServiceManager() {
	ServiceManager::instance = this;

	logDispatcher = new LogDispatcher();
	logger.attachRoot();

	// enable exception handling
	rfc_thr_initstackhandle();
	::_set_se_translator( UnhandledExceptionTranslator );
}

ServiceManager::~ServiceManager() {
	delete logDispatcher;

	rfc_thr_exitstackhandle();
}

ServiceManager& ServiceManager::getInstance() {
	return( *ServiceManager::instance );
}

void ServiceManager::logStart( Xml configLogging ) {
	// read configuration file
	ASSERTMSG( configLogging.exists() , "logStart: logging is not configured, empty configuration" );

	// open file
	logDispatcher -> configure( configLogging );
	if( !logDispatcher -> start() )
		throw RuntimeError( "logStart: cannot initialize logging - unknown reason" );

	logger.logInfo( "logStart: LOGGING STARTED" );
}

void ServiceManager::logStop() {
	// stop logging
	logger.logInfo( "logStop: LOGGING STOPPED" );
	logDispatcher -> stop();
}

void ServiceManager::execute() {
	try {
		logger.logInfo( "--------------------" );
		logger.logInfo( "execute: STARTING..." );
		logger.logInfo( "--------------------" );

		// create and initialize services
		createServices();
		initServices();

		// wait for completion
		logger.logInfo( "--------------------" );
		logger.logInfo( "execute: RUNNING..." );
		logger.logInfo( "--------------------" );
		runServices();

		logger.logInfo( "--------------------" );
		logger.logInfo( "execute: STARTED, WAITING FOR COMPLETION..." );
		logger.logInfo( "-------------------------------------------" );
		waitRunDefault();
	}
	catch( RuntimeException& e ) {
		logger.logInfo( "----------------------------------" );
		logger.logInfo( "execute: STARTUP/RUNTIME EXCEPTION" );
		logger.logInfo( "----------------------------------" );

		logger.printStack( e );
	}

	// cleanup
	try {
		logger.logInfo( "--------------------" );
		logger.logInfo( "execute: EXITING..." );
		logger.logInfo( "-------------------" );

		stopServices();
		exitServices();
		destroyServices();

		logger.logInfo( "----------------" );
		logger.logInfo( "execute: STOPPED" );
		logger.logInfo( "----------------" );
	}
	catch( RuntimeException& e ) {
		logger.logInfo( "------------------------------" );
		logger.logInfo( "execute: EXCEPTION ON SHUTDOWN" );
		logger.logInfo( "------------------------------" );
		logger.printStack( e );
	}
}

