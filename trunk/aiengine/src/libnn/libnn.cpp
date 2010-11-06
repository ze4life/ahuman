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

/* static */ Service *AILibNN::newService()
{
	Service *svc = new AILibNNImpl();
	return( svc );
}

AILibNNImpl::AILibNNImpl()
:	engine( AIEngine::getInstance() )
{
}

void AILibNNImpl::createService( Xml config )
{
	addLibVariant( AILibNNVariant::createFannCustom() );
}

void AILibNNImpl::initService()
{
	// log available commands
	logger.logInfo( "AVAILABLE LIBRARIES:" );
	for( int k = 0; k < variants.count(); k++ ) {
		AILibNNVariant *var = variants.getClassByIndex( k );
		logger.logInfo( "library=" + var -> getName() );
	}
}

void AILibNNImpl::runService()
{
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

