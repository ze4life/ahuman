
#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIMedia::AIMedia() 
{ 
	thisPtr = AIMediaImpl::getServiceImpl(); 
}

/* static */ Service *AIMedia::newService()
{
	Service *svc = new AIMediaImpl();
	return( svc );
}

AIMediaImpl::AIMediaImpl()
:	engine( AIEngine::getInstance() )
{
}

AIMediaImpl *AIMediaImpl::getServiceImpl()
{
	return( static_cast<AIMediaImpl *>( AIEngine::getInstance().getService( "Media" ) ) );
}

void AIMediaImpl::createService()
{
}

void AIMediaImpl::initService()
{
	initSocketLib();
}

void AIMediaImpl::runService()
{
	startListeners();
}

void AIMediaImpl::exitService()
{
	stopListeners();
}

void AIMediaImpl::destroyService()
{
	listeners.destroy();
	exitSocketLib();
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

void AIMediaImpl::startListeners()
{
	// scan configuration
	Xml configListeners = configService.getChildNode( "listeners" );
	for( Xml item = configListeners.getFirstChild( "listener" ); item.exists(); item = item.getNextChild( "listener" ) ) {
		String name = item.getAttribute( "name" );

		// create and configure
		Listener *listener = runListenerFactory( name );
		listener -> configure( item );

		// start
		ASSERTMSG( listener -> startListener() , 
			"AIMediaImpl::startListeners: cannot start listener=" + name );
		logger.logInfo( name + " listener started at " + listener -> getAddress() );
	}
}

void AIMediaImpl::startActiveSockets()
{
	// scan configuration
	Xml configListeners = configService.getChildNode( "directchannels" );
	for( Xml item = configListeners.getFirstChild( "channel" ); item.exists(); item = item.getNextChild( "channel" ) ) {
		String name = item.getAttribute( "name" );

		// create and configure
		ActiveSocket *ac = new ActiveSocket( name );
		ac -> configure( item );

		// start
		ASSERTMSG( ac -> startActiveSocket() , 
			"AIMediaImpl::startActiveSockets: cannot start channel=" + name );
		logger.logInfo( name + " successfully connected " + ac -> getAddress() );
	}
}

Listener *AIMediaImpl::runListenerFactory( String name )
{
	ASSERT( listeners.get( name ) == NULL );

	Listener *listener = new SocketServer( name );
	listeners.add( name , listener );

	return( listener );
}

void AIMediaImpl::stopListeners()
{
	for( int k = 0; k < listeners.count(); k++ ) {
		Listener *listener = listeners.getClassByIndex( k );
		listener -> stopListener();
		listener -> stopListenerConnections();
	}
}

void AIMediaImpl::initSocketLib()
{
	WSADATA l_wsa;
	memset( &l_wsa, 0 , sizeof( WSADATA ) );
	WSAStartup( MAKEWORD( 2 , 2 ) , &l_wsa );
}

void AIMediaImpl::exitSocketLib()
{
	/* cleanup sockets */
	WSACleanup();
}

ActiveSocket *AIMediaImpl::getActiveSocket( String name )
{
	ActiveSocket *socket = activeSockets.get( name );
	ASSERTMSG( socket != NULL , "Unable to find channel by name=" + name );
	return( socket );
}

void AIMediaImpl::sendTextToDirectChannel( String name , String text )
{
	ActiveSocket *s = getActiveSocket( name );
	s -> sendText( text );
}

String AIMediaImpl::receiveTextFromDirectChannel( String name , bool wait )
{
	ActiveSocket *s = getActiveSocket( name );
	return( s -> receiveText( wait ) );
}

String AIMediaImpl::receiveFixedSizeTextFromDirectChannel( String name , int size )
{
	ActiveSocket *s = getActiveSocket( name );
	return( s -> receiveFixedText( size ) );
}
