
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

void AIMediaImpl::createService( Xml config )
{
	Xml configListeners = config.getChildNode( "listeners" );
	createListeners( configListeners );

	Xml configActiveSockets = config.getChildNode( "directchannels" );
	createActiveSockets( configActiveSockets );
}

void AIMediaImpl::initService()
{
	SocketProtocol::initSocketLib();
}

void AIMediaImpl::runService()
{
	startListeners();
	startActiveSockets();
}

void AIMediaImpl::exitService()
{
	stopListeners();
	stopActiveSockets();
}

void AIMediaImpl::destroyService()
{
	listeners.destroy();
	activeSockets.destroy();

	SocketProtocol::exitSocketLib();
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

Listener *AIMediaImpl::runListenerFactory( String name , Xml config )
{
	ASSERT( listeners.get( name ) == NULL );

	Listener *listener = new SocketServer( name );
	listener -> configure( config );

	listeners.add( name , listener );

	return( listener );
}

void AIMediaImpl::createListeners( Xml config )
{
	if( !config.exists() )
		return;

	// scan configuration
	for( Xml item = config.getFirstChild( "listener" ); item.exists(); item = item.getNextChild( "listener" ) ) {
		String name = item.getAttribute( "name" );
		if( !item.getBooleanAttribute( "run" ) ) {
			logger.logInfo( "AIMediaImpl::createListeners: listener is not configured to run - name=" + name );
			continue;
		}

		// create and configure
		Listener *listener = runListenerFactory( name , item );
		logger.logInfo( "AIMediaImpl::createListeners: listener created - name=" + name );
	}
}

void AIMediaImpl::startListeners()
{
	// for all listeners
	for( int k = 0; k < listeners.count(); k++ ) {
		Listener *listener = listeners.getClassByIndex( k );

		// start
		String name = listener -> getName();
		ASSERTMSG( listener -> startListener() , 
			"AIMediaImpl::startListeners: cannot start listener=" + name );
		logger.logInfo( "AIMediaImpl::startListeners: listener started at " + listener -> getAddress() + " - name=" + name );
	}
}

ActiveSocket *AIMediaImpl::runActiveSocketFactory( String p_name , Xml config )
{
	ASSERT( activeSockets.get( p_name ) == NULL );

	ActiveSocket *as = new ActiveSocket( p_name );
	as -> configure( config );

	activeSockets.add( p_name , as );

	return( as );
}

void AIMediaImpl::createActiveSockets( Xml config )
{
	if( !config.exists() )
		return;

	// scan configuration
	for( Xml item = config.getFirstChild( "channel" ); item.exists(); item = item.getNextChild( "channel" ) ) {
		String name = item.getAttribute( "name" );
		if( !item.getBooleanAttribute( "run" ) ) {
			logger.logInfo( "AIMediaImpl::createActiveSockets: direct channel is not configured to run - name=" + name );
			continue;
		}

		// create and configure
		ActiveSocket *ac = runActiveSocketFactory( name , item );
		logger.logInfo( "AIMediaImpl::createActiveSockets: direct channel created - name=" + name );
	}
}

void AIMediaImpl::startActiveSockets()
{
	// for all active sockets
	for( int k = 0; k < activeSockets.count(); k++ ) {
		ActiveSocket *ac = activeSockets.getClassByIndex( k );

		// start
		String name = ac -> getName();
		ASSERTMSG( ac -> startActiveSocket() , 
			"AIMediaImpl::startActiveSockets: cannot start channel=" + name );
		logger.logInfo( "AIMediaImpl::startActiveSockets: direct channel started name=" + name );
	}
}

void AIMediaImpl::stopActiveSockets()
{
	for( int k = 0; k < activeSockets.count(); k++ ) {
		ActiveSocket *ac = activeSockets.getClassByIndex( k );
		ac -> stopActiveSocket();
	}
}

void AIMediaImpl::stopListeners()
{
	for( int k = 0; k < listeners.count(); k++ ) {
		Listener *listener = listeners.getClassByIndex( k );
		listener -> stopListener();
		listener -> stopListenerConnections();
	}
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
	return( s -> receiveFixedText( size , false ) );
}
