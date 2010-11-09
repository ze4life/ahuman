
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
	Xml configInterfaces = config.getFirstChild( "interfaces" );
	if( !configInterfaces.exists() )
		return;
	// find configuration
	Xml conf = configInterfaces.getChildNamedNode( "interface" , "chat");
	if(conf.getBooleanAttribute( "run" ) ) {
		chatInterface = new ChatInterface();
		chatInterface->createService(conf);
	}
}

void AIBodyImpl::initService()
{
	AIBrain brain;
	brain.addMindArea( "Sensors" , createSensors() );
	if(chatInterface != NULL){
		chatInterface->initService();
	}
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
