#include "libnn_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AILibNN::AILibNN() 
{ 
	thisPtr = AILibNNImpl::getServiceImpl(); 
}

AILibNNImpl *AILibNNImpl::getServiceImpl()
{
	return( static_cast<AILibNNImpl *>( AIEngine::getInstance().getService( "LibNN" ) ) );
}

/* static */ Service *AILibNN::createService()
{
	Service *svc = new AILibNNImpl();
	AIEngine::getInstance().registerService( svc , "LibNN" );
	return( svc );
}

AILibNNImpl::AILibNNImpl()
:	engine( AIEngine::getInstance() )
{
}

void AILibNNImpl::initService()
{
	addLibVariant( AILibNNVariant::createFannCustom() );
}

void AILibNNImpl::runService()
{
	// log available commands
	logger.logInfo( "AVAILABLE LIBRARIES:" );
	for( int k = 0; k < variants.count(); k++ ) {
		AILibNNVariant *var = variants.getClassByIndex( k );
		logger.logInfo( "library=" + var -> getName() );
	}
}

void AILibNNImpl::exitService()
{
	variants.destroy();
}

void AILibNNImpl::destroyService()
{
	delete this;
}

void AILibNNImpl::addLibVariant( AILibNNVariant *lib )
{
	variants.add( lib -> getName() , lib );
}

AILibNNVariant *AILibNNImpl::getLibVariant( String name )
{
	return( variants.get( name ) );
}

/*#########################################################################*/
/*#########################################################################*/

