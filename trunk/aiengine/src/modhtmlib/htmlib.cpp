#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIHtmLib::AIHtmLib() 
{ 
	thisPtr = AIHtmLibImpl::getServiceImpl(); 
}

AIHtmLibImpl *AIHtmLibImpl::getServiceImpl()
{
	return( static_cast<AIHtmLibImpl *>( AIEngine::getInstance().getService( "AIHtmLib" ) ) );
}

/* static */ Service *AIHtmLib::createService()
{
	Service *svc = new AIHtmLibImpl();
	AIEngine::getInstance().registerService( svc , "AIHtmLib" );
	return( svc );
}

AIHtmLibImpl::AIHtmLibImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIHtmLibImpl::initService()
{
	// register serialisable classes
}

void AIHtmLibImpl::runService()
{
	// register debug call subscriber
	debug.init( config );
}

void AIHtmLibImpl::exitService()
{
	debug.exit();
}

void AIHtmLibImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

