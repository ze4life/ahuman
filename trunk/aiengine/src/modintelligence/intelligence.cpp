
#include "intelligence_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIIntelligence::AIIntelligence() 
{ 
	thisPtr = static_cast<AIIntelligenceImpl *>( AIEngine::getInstance().getService( "Intelligence" ) ); 
}

/* static */ Service *AIIntelligence::createService()
{
	Service *svc = new AIIntelligenceImpl();
	AIEngine::getInstance().registerService( svc , "Intelligence" );
	return( svc );
}

AIIntelligenceImpl::AIIntelligenceImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIIntelligenceImpl::initService()
{
}

void AIIntelligenceImpl::runService()
{
}

void AIIntelligenceImpl::exitService()
{
}

void AIIntelligenceImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
