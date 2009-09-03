
#include "aiheart_impl.h"

/*#########################################################################*/
/*#########################################################################*/

static 	unsigned		__stdcall threadMainFunction( void *p_arg )
{
	AIEngine& engine = AIEngine::getInstance();
	engine.workerStarted();

	AIHeartImpl *ptr = static_cast<AIHeartImpl *>( engine.getService( "AIHeart" ) );
	Logger& logger = ptr -> getLogger();
	int status = 0;
		{
			try {
				status = ptr -> performIndependentThinking();
			}
			catch ( RuntimeException& e ) {
				e.printStack( logger );
				status = -41;
			}
			catch ( ... ) {
				logger.logInfo( "unknown exception" );
				logger.printStack();
				status = -42;
			}
		}

	engine.workerExited( status );
	return( status );
}

/*#########################################################################*/
/*#########################################################################*/

AIHeart::AIHeart() 
{ 
	thisPtr = static_cast<AIHeartImpl *>( AIEngine::getInstance().getService( "AIHeart" ) ); 
}

/* static */ Service *AIHeart::createService()
{
	Service *svc = new AIHeartImpl();
	AIEngine::getInstance().registerService( svc , "AIHeart" );
	return( svc );
}

void AIHeartImpl::initService()
{
	emotion = new AIEmotionImpl( AIEMOTION_MIXED , 0 );
}

void AIHeartImpl::runService()
{
	startIndependentThinking();
}

void AIHeartImpl::exitService()
{
	stopIndependentThinking();
}

void AIHeartImpl::destroyService()
{
	delete emotion;
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

AIHeartImpl::AIHeartImpl()
:	engine( AIEngine::getInstance() )
{
	enabled = false;
	emotion = NULL;
}

bool AIHeartImpl::isApprovedEmotion( const AIEmotion& e )
{
	return( emotion -> isApproved( ( AIEmotionImpl& )e ) );
}

void AIHeartImpl::startIndependentThinking()
{
	// create channel thread
	enabled = true;
	engine.workerCreated();

	if( rfc_thr_process( &independentThreadID , ( void * )this , threadMainFunction ) ) {
		engine.workerExited( independentThreadID , -40 );
		throw RuntimeError( "startIndependentThinking: cannot start listening thread" );
	}
}

int AIHeartImpl::performIndependentThinking()
{
	while( canContinue() )
		doLive();

	return( 0 );
}

void AIHeartImpl::stopIndependentThinking()
{
	enabled = false;
}

void AIHeartImpl::doLive()
{
}

