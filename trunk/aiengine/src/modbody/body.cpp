
#include "body_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIBody::AIBody() 
{ 
	thisPtr = AIBodyImpl::getInstance(); 
}

AIBodyImpl *AIBodyImpl::getInstance()
{
	return( ( AIBodyImpl * )AIEngine::getInstance().getService( "Body" ) );
}

/* static */ Service *AIBody::newService()
{
	Service *svc = new AIBodyImpl();
	return( svc );
}

AIBodyImpl::AIBodyImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIBodyImpl::createService( Xml config )
{
}

void AIBodyImpl::initService()
{
	AIBrain brain;
	brain.addMindArea( "Sensors" , createSensors() );
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
