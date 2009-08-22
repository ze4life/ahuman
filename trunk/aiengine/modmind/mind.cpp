
#include "aimind_impl.h"

/*#########################################################################*/
/*#########################################################################*/

static 	unsigned		__stdcall threadMainFunction( void *p_arg )
{
	AIEngine& engine = AIEngine::getInstance();
	engine.workerStarted();

	AIMind mind;
	AIMindImpl *impl = static_cast<AIMindImpl *>( mind.thisPtr );
	Logger& logger = impl -> getLogger();

	int status = 0;
	try {
		impl -> performIndependentThinking();
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
		status = -41;
	}
	catch ( ... ) {
		logger.logError( "ai_connect: unknown exception" );
		logger.printStack();
		status = -42;
	}

	engine.workerExited( status );
	return( status );
}

/*#########################################################################*/
/*#########################################################################*/

AIMind::AIMind() 
{ 
	thisPtr = static_cast<AIMindImpl *>( AIEngine::getInstance().getService( "AIMind" ) ); 
}

/* static */ Service *AIMind::createService()
{
	Service *svc = new AIMindImpl();
	AIEngine::getInstance().registerService( svc , "AIMind" );
	return( svc );
}

AIMindImpl::AIMindImpl()
:	engine( AIEngine::getInstance() )
{
	enabled = false;
}

void AIMindImpl::initService()
{
}

void AIMindImpl::runService()
{
	startIndependentThinking();
}

void AIMindImpl::exitService()
{
	stopIndependentThinking();
}

void AIMindImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

void AIMindImpl::startIndependentThinking()
{
	// create channel thread
	enabled = true;
	engine.workerCreated();

	if( rfc_thr_process( &independentThreadID , ( void * )this , threadMainFunction ) ) {
		logger.logError( "AIMind::start: cannot start listening thread" );
		engine.workerExited( independentThreadID , -40 );
		throw RuntimeError( "AIMind::startIndependentThinking: cannot start listening thread" );
	}
}

void AIMindImpl::performIndependentThinking()
{
	while( canContinue() )
		rfc_thr_sleep( 1 );
}

void AIMindImpl::stopIndependentThinking()
{
	enabled = false;
}
