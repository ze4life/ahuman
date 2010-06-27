
#include "aicommands_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AICommands::AICommands() 
{ 
	thisPtr = static_cast<AICommandsImpl *>( AIEngine::getInstance().getService( "Commands" ) ); 
}

/* static */ Service *AICommands::createService()
{
	Service *svc = new AICommandsImpl();
	AIEngine::getInstance().registerService( svc , "Commands" );
	return( svc );
}

AICommandsImpl::AICommandsImpl()
:	engine( AIEngine::getInstance() )
{
}

void AICommandsImpl::initService()
{
}

void AICommandsImpl::runService()
{
}

void AICommandsImpl::exitService()
{
}

void AICommandsImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
