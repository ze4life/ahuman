
#include "brain_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIBrain::AIBrain() 
{ 
	thisPtr = static_cast<AIBrainImpl *>( AIEngine::getInstance().getService( "Brain" ) ); 
}

/* static */ Service *AIBrain::createService()
{
	Service *svc = new AIBrainImpl();
	AIEngine::getInstance().registerService( svc , "Brain" );
	return( svc );
}

AIBrainImpl::AIBrainImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIBrainImpl::initService()
{
}

void AIBrainImpl::runService()
{
}

void AIBrainImpl::exitService()
{
}

void AIBrainImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
