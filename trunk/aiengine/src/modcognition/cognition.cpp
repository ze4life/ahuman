
#include "cognition_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AICognition::AICognition() 
{ 
	thisPtr = static_cast<AICognitionImpl *>( AIEngine::getInstance().getService( "Cognition" ) ); 
}

/* static */ Service *AICognition::createService()
{
	Service *svc = new AICognitionImpl();
	AIEngine::getInstance().registerService( svc , "Cognition" );
	return( svc );
}

AICognitionImpl::AICognitionImpl()
:	engine( AIEngine::getInstance() )
{
}

void AICognitionImpl::initService()
{
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
