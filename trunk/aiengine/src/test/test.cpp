#include "test_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AITestPool::AITestPool() { 
	thisPtr = AITestPoolImpl::getServiceImpl(); 
}

AITestPoolImpl *AITestPoolImpl::getServiceImpl() {
	return( static_cast<AITestPoolImpl *>( AIEngine::getInstance().getService( "TestPool" ) ) );
}

/* static */ Service *AITestPool::createService() {
	Service *svc = new AITestPoolImpl();
	AIEngine::getInstance().registerService( svc , "TestPool" );
	return( svc );
}

AITestPoolImpl::AITestPoolImpl()
:	engine( AIEngine::getInstance() ) {
	callPub = NULL;
	callSub = NULL;
}

void AITestPoolImpl::initService() {
	// create units
	addTestUnit( TestUnit::createFannCustom() );
	addTestUnit( TestUnit::createHtmViewCustom() );
	
	// log available commands
	logger.logInfo( "AVAILABLE TEST METHODS:" );
	for( int k = 0; k < units.count(); k++ ) {
		TestUnit *tu = units.getClassByIndex( k );
		
		MapStringToClass<TestMethod>& methods = tu -> methods;
		for( int m = 0; m < methods.count(); m++ ) {
			logger.logInfo( String( "method=" ) + methods.getKeyByIndex( m ) );
		}
	}
}

void AITestPoolImpl::runService() {
	// subscribe
	Xml xml = Service::config.getFirstChild( "channels" );
	String channelIn = xml.getProperty( "request" );
	String channelOut = xml.getProperty( "response" );

	AIIO io;
	callSub = io.subscribe( NULL , channelIn , "testpool" , this );
	callPub = io.createPublisher( NULL , channelOut , "testpool" , "test" );
}

void AITestPoolImpl::exitService() {
	AIIO io;
	if( callPub != NULL )
		io.destroyPublisher( callPub );
	if( callSub != NULL )
		io.unsubscribe( callSub );
		
	units.destroy();
}

void AITestPoolImpl::destroyService() {
	delete this;
}

void AITestPoolImpl::addTestUnit( TestUnit *p_unit ) {
	units.add( p_unit -> getName() , p_unit );
	p_unit -> init();
}

/*#########################################################################*/
/*#########################################################################*/

void AITestPoolImpl::onXmlCall( XmlCall *msg ) {
	XmlCall& call = *msg;
	String cn = call.getClassName();
	String fn = call.getFunctionName();
	String fnfull = cn + "::" + fn;
	logger.logInfo( fnfull + " called in session " + call.getSession() -> getSessionId() );

	// find unit
	TestUnit *unit = units.get( cn );
	if( unit == NULL )
		return;
		
	// find method
	TestMethod *method = unit -> getMethod( fnfull );
	if( method == NULL )
		return;

	try {
		logger.logInfo( fnfull + " method found in test classes" );
		unit -> logger.attach( fnfull );
		unit -> callMethod( method , call );
		call.sendStatusResponse( "OK" );
	}
	catch ( RuntimeException& e ) {
		call.sendResponseException( callPub , e );
		e.printStack( logger );
	}
	catch( ... ) {
		call.sendResponseUnknownException( callPub );
		logger.logError( "Unknown exception:" );
		logger.printStack();
	}
}

