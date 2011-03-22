#include "libbn_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AILibBN::AILibBN() 
{ 
	thisPtr = AILibBNImpl::getServiceImpl(); 
}

AILibBNImpl *AILibBNImpl::getServiceImpl()
{
	return( static_cast<AILibBNImpl *>( AIEngine::getInstance().getService( "LibBN" ) ) );
}

/* static */ Service *AILibBN::newService()
{
	Service *svc = new AILibBNImpl();
	return( svc );
}

AILibBNImpl::AILibBNImpl()
:	engine( AIEngine::getInstance() )
{
}

void AILibBNImpl::createService( Xml config )
{
	addLibVariant( AILibBNImpl::createViewCustomLib() );
	addLibVariant( AILibBNImpl::createNeoCortexCustomLib() );
}

void AILibBNImpl::initService()
{
	// log available commands
	logger.logInfo( "initService: AVAILABLE LIBRARIES:" );
	for( int k = 0; k < variants.count(); k++ ) {
		AILibBNVariant *var = variants.getClassByIndex( k );
		logger.logInfo( "initService: library=" + var -> getName() );
	}
}

void AILibBNImpl::runService()
{
}

void AILibBNImpl::exitService()
{
}

void AILibBNImpl::destroyService()
{
	variants.destroy();
	delete this;
}

void AILibBNImpl::addLibVariant( AILibBNVariant *lib )
{
	variants.add( lib -> getName() , lib );
}

AILibBNVariant *AILibBNImpl::getLibVariant( String name )
{
	return( variants.get( name ) );
}

/*#########################################################################*/
/*#########################################################################*/

