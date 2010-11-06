
#include "knowledge_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIKnowledge::AIKnowledge() 
{ 
	thisPtr = static_cast<AIKnowledgeImpl *>( AIEngine::getInstance().getService( "Knowledge" ) ); 
}

/* static */ Service *AIKnowledge::newService()
{
	Service *svc = new AIKnowledgeImpl();
	return( svc );
}

AIKnowledgeImpl::AIKnowledgeImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIKnowledgeImpl::createService( Xml config )
{
	// create controllers
	Xml configControllers = config.getFirstChild( "controllers" );
	if( !configControllers.exists() )
		return;

	addKnowledgeController( configControllers , KnowledgeController::createImageKnowledgeBase() );
}

void AIKnowledgeImpl::addKnowledgeController( Xml configControllers , KnowledgeController *controller )
{
	String name = controller -> getName();

	// find configuration
	Xml config = configControllers.getChildNamedNode( "controller" , name );
	ASSERTMSG( config.exists() , "Configuration not found for knowledge controller=" + name );

	if( !config.getBooleanAttribute( "run" ) ) {
		// do not use this controller
		delete controller;
		logger.logInfo( "Knowledge controller ignored as not configured to run - name=" + name );
		return;
	}

	// add controller
	controllers.add( name , controller );
	controller -> createController( config );
	logger.logInfo( "Knowledge controller created - name=" + name );
}

void AIKnowledgeImpl::initService()
{
	// start controllers
	for( int k = 0; k < controllers.count(); k++ ) {
		KnowledgeController *controller = controllers.getClassByIndex( k );
		controller -> startController();
		logger.logInfo( "Knowledge controller started - name=" + controller -> getName() );
	}
}

void AIKnowledgeImpl::runService()
{
}

void AIKnowledgeImpl::exitService()
{
	// stop controllers
	for( int k = 0; k < controllers.count(); k++ ) {
		KnowledgeController *controller = controllers.getClassByIndex( k );
		controller -> stopController();
		logger.logInfo( "Knowledge controller stopped - name=" + controller -> getName() );
	}
}

void AIKnowledgeImpl::destroyService()
{
	controllers.destroy();
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
