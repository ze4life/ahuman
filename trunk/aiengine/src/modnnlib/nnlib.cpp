#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AINNLib::AINNLib() 
{ 
	thisPtr = AINNLibImpl::getServiceImpl(); 
}

AINNLibImpl *AINNLibImpl::getServiceImpl()
{
	return( static_cast<AINNLibImpl *>( AIEngine::getInstance().getService( "NNLib" ) ) );
}

/* static */ Service *AINNLib::createService()
{
	Service *svc = new AINNLibImpl();
	AIEngine::getInstance().registerService( svc , "NNLib" );
	return( svc );
}

AINNLibImpl::AINNLibImpl()
:	engine( AIEngine::getInstance() )
{
}

void AINNLibImpl::initService()
{
	addLibVariant( AINNLibVariant::createFannCustom() );
}

void AINNLibImpl::runService()
{
	// log available commands
	logger.logInfo( "AVAILABLE LIBRARIES:" );
	for( int k = 0; k < variants.count(); k++ ) {
		AINNLibVariant *var = variants.getClassByIndex( k );
		logger.logInfo( "library=" + var -> getName() );
	}
}

void AINNLibImpl::exitService()
{
	variants.destroy();
}

void AINNLibImpl::destroyService()
{
	delete this;
}

void AINNLibImpl::addLibVariant( AINNLibVariant *lib )
{
	variants.add( lib -> getName() , lib );
}

AINNLibVariant *AINNLibImpl::getLibVariant( String name )
{
	return( variants.get( name ) );
}

/*#########################################################################*/
/*#########################################################################*/

