
#include "aimedia_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIMedia::AIMedia() 
{ 
	thisPtr = static_cast<AIMediaImpl *>( AIEngine::getInstance().getService( "AIMedia" ) ); 
}

/* static */ Service *AIMedia::createService()
{
	Service *svc = new AIMediaImpl();
	AIEngine::getInstance().registerService( svc , "AIMedia" );
	return( svc );
}

AIMediaImpl::AIMediaImpl()
:	engine( AIEngine::getInstance() )
{
	sockServer = NULL;
}

void AIMediaImpl::initService()
{
}

void AIMediaImpl::runService()
{
	startSocketServer();
}

void AIMediaImpl::exitService()
{
	stopSocketServer();
}

void AIMediaImpl::destroyService()
{
	if( sockServer != NULL )
		delete sockServer;

	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

void AIMediaImpl::startSocketServer()
{
	sockServer = new AISockServer();
	if( !sockServer -> openListeningPort() )
		throw RuntimeError( "AIMediaImpl::startSocketServer: cannot start socket server" );
}

void AIMediaImpl::stopSocketServer()
{
	if( sockServer != NULL )
		sockServer -> closeListeningPort();
}

void AIMediaImpl::sendMessageToUser( AIMessage *msg , AISession *session )
{
	if( !session -> isMediaOpen() )
		return;

	AISocketConnection *client = ( AISocketConnection * )session -> getMedia();
	if( client == NULL )
		return;

	client -> writeMessage( msg );
}

void AIMediaImpl::closeMediaReflect( AISession *session )
{
	AISocketConnection *client = ( AISocketConnection * )session -> getMedia();
	if( client == NULL )
		return;

	client -> closeReflect();
}

