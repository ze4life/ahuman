#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIHtmLib::AIHtmLib() 
{ 
	thisPtr = AIHtmLibImpl::getServiceImpl(); 
}

AIHtmLibImpl *AIHtmLibImpl::getServiceImpl()
{
	return( static_cast<AIHtmLibImpl *>( AIEngine::getInstance().getService( "HtmLib" ) ) );
}

/* static */ Service *AIHtmLib::createService()
{
	Service *svc = new AIHtmLibImpl();
	AIEngine::getInstance().registerService( svc , "HtmLib" );
	return( svc );
}

AIHtmLibImpl::AIHtmLibImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIHtmLibImpl::initService()
{
	addLibVariant( AIHtmLibVariant::createHtmCustom() );
}

void AIHtmLibImpl::runService()
{
	// log available commands
	logger.logInfo( "AVAILABLE LIBRARIES:" );
	for( int k = 0; k < variants.count(); k++ ) {
		AIHtmLibVariant *var = variants.getClassByIndex( k );
		logger.logInfo( "library=" + var -> getName() );
	}
}

void AIHtmLibImpl::exitService()
{
}

void AIHtmLibImpl::destroyService()
{
	variants.destroy();
	delete this;
}

void AIHtmLibImpl::addLibVariant( AIHtmLibVariant *lib )
{
	variants.add( lib -> getName() , lib );
}

AIHtmLibVariant *AIHtmLibImpl::getLibVariant( String name )
{
	return( variants.get( name ) );
}

/*#########################################################################*/
/*#########################################################################*/

