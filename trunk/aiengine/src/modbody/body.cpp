
#include "body_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIBody::AIBody() 
{ 
	thisPtr = static_cast<AIBodyImpl *>( AIEngine::getInstance().getService( "Body" ) ); 
}

/* static */ Service *AIBody::newService()
{
	Service *svc = new AIBodyImpl();
	AIEngine::getInstance().registerService( svc , "Body" );
	return( svc );
}

AIBodyImpl::AIBodyImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIBodyImpl::createService()
{
	AIBrain brain;
	brain.addMindArea( "Sensors" , createSensors() );
}

void AIBodyImpl::initService()
{
}

void AIBodyImpl::runService()
{
}

void AIBodyImpl::exitService()
{
}

void AIBodyImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
