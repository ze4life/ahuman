
#include "cognition_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AICognition::AICognition() 
{ 
	thisPtr = static_cast<AICognitionImpl *>( AIEngine::getInstance().getService( "Cognition" ) ); 
}

/* static */ Service *AICognition::newService()
{
	Service *svc = new AICognitionImpl();
	AIEngine::getInstance().registerService( svc , "Cognition" );
	return( svc );
}

AICognitionImpl::AICognitionImpl()
:	engine( AIEngine::getInstance() )
{
}

void AICognitionImpl::createService()
{
}

void AICognitionImpl::initService()
{
	AIBrain brain;
	brain.addMindArea( "NeoCortex" , createNeoCortex() );
}

void AICognitionImpl::runService()
{
}

void AICognitionImpl::exitService()
{
}

void AICognitionImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
