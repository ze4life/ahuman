
#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

ActiveSocket::ActiveSocket( String p_name )
:	protocol( logger )
{
	name = p_name;
	redirectInbound = false;
	redirectOutbound = false;
	connected = false;
	shutdownInProgress = false;

	sub = NULL;
	pub = NULL;
	socketThread = NULL;
}

ActiveSocket::~ActiveSocket()
{
	_closesocket( socketHandle );
}

void ActiveSocket::configure( Xml config )
{
	redirectInbound = config.getBooleanProperty( "redirect-in" );
	redirectOutbound = config.getBooleanProperty( "redirect-out" );

	if( redirectInbound )
		inboundChannelName = config.getProperty( "topic-in" );
	if( redirectOutbound )
		outboundChannelName = config.getProperty( "topic-out" );

	host = config.getProperty( "host" );
	port = config.getProperty( "port" );
	permanentConnection = config.getBooleanProperty( "permanent" );
	reconnectionTimeout = config.getIntProperty( "reconnectionTimeoutSec" , 10 );

	// start protocol
	protocol.create( config );

	// start logging
	loggerName = String( "ActiveSocket::" ) + name;
	logger.attach( this , loggerName );
}

bool ActiveSocket::startActiveSocket()
{
	// open connection and start thread related to connection - to read from socket - if expected
	memset( &addr , 0 , sizeof( SOCKADDR_IN ) );
	struct hostent *hostEntry = gethostbyname( host );
	addr.sin_addr = *( ( LPIN_ADDR ) *hostEntry -> h_addr_list );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( atoi( port ) );

	// init messaging
	AIIO io;
	if( redirectOutbound )
		sub = io.subscribe( NULL , outboundChannelName , name + "active-socket" , this );
	if( redirectInbound ) {
		pub = io.createPublisher( NULL , inboundChannelName , name + "active-socket" , "text" );

		// start reading thread
		AIEngine& engine = AIEngine::getInstance();
		socketThread = engine.runThread( name + ".reader" , this , ( ObjectThreadFunction )&ActiveSocket::readSocketThread , NULL );
	}

	return( true );
}

void ActiveSocket::stopActiveSocket()
{
	// stop thread reading from socket if any
	shutdownInProgress = true;
	disconnectSocket();

	if( socketThread != NULL ) {
		AIEngine& engine = AIEngine::getInstance();
		engine.waitThreadExited( socketThread );
		socketThread = NULL;
	}
}

String ActiveSocket::getAddress()
{
	return( host + ":" + port );
}

String ActiveSocket::getName()
{
	return( name );
}

bool ActiveSocket::connectSocket()
{
	if( connected )
		return( true );

	// create handle
	socketHandle = socket( AF_INET , SOCK_STREAM , 0 );
	ASSERTMSG( socketHandle != SOCKET_ERROR , "ActiveSocket::startActiveSocket - unable to create socket for name=" + name );

	// connect to exteranl host/port
	if( connect( socketHandle , ( LPSOCKADDR )&addr , sizeof( SOCKADDR_IN ) ) == SOCKET_ERROR ) {
		logger.logDebug( "ActiveSocket::connectSocket - unable to connect to host=" + host + ", port=" + port + " for name=" + name );
		return( false );
	}

	logger.logDebug( "ActiveSocket::connectSocket - successfully connected to host=" + host + ", port=" + port + ", name=" + name );
	connected = true;
	return( true );
}

void ActiveSocket::disconnectSocket()
{
	if( connected ) {
		connected = false;

		_closesocket( socketHandle );
		socketHandle = INVALID_SOCKET;

		logger.logInfo( "ActiveSocket::disconnectSocket: disconnected name=" + name );
	}
}

void ActiveSocket::handleBrokenConnection()
{
	if( !shutdownInProgress )
		disconnectSocket();
}

void ActiveSocket::sendText( String text )
{
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "ActiveSocket::sendText - unable to connect ActiveSocket=" + name );

	bool connectionClosed;
	protocol.writeMessage( socketHandle , text , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
}

String ActiveSocket::receiveText( bool wait )
{
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "ActiveSocket::receiveText - unable to connect ActiveSocket=" + name );

	bool connectionClosed;
	String final;
	bool res = protocol.readMessage( socketHandle , final , wait , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();

	if( !res )
		return( "" );

	return( final );
}

String ActiveSocket::receiveFixedText( int size , bool wait )
{
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "ActiveSocket::receiveFixedText - unable to connect ActiveSocket=" + name );

	bool connectionClosed;
	String final;
	bool res = protocol.readFixedSizeMessage( socketHandle , size , final , wait , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();

	if( !res )
		return( "" );

	return( final );
}

bool ActiveSocket::waitReadSocket( bool wait )
{
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "ActiveSocket::waitReadSocket - unable to connect ActiveSocket=" + name );

	return( protocol.waitSocketData( socketHandle , wait ) );
}

void ActiveSocket::onTextMessage( TextMessage *msg )
{
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "ActiveSocket::onTextMessage - unable to connect ActiveSocket=" + name );

	// forward from channel to socket
	bool connectionClosed;
	protocol.writeMessage( socketHandle , msg -> getText() , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
		logger.logDebug( "sent message to socket msgid=" + msg -> getChannelMessageId() );
}

void ActiveSocket::readSocketThread( void *p_arg )
{
	while( !shutdownInProgress ) {
		if( !connected ) {
			// try to connect
			if( !connectSocket() ) {
				rfc_thr_sleep( reconnectionTimeout );
				continue;
			}
		}

		// try reading
		bool connectionClosed;
		String final;
		bool res = protocol.readMessage( socketHandle , final , true , connectionClosed );
		if( connectionClosed ) {
			handleBrokenConnection();
			continue;
		}

		if( !res )
			continue;

		// write message to channel
		String msgid = pub -> publish( NULL , final );
		logger.logDebug( "read message from socket msgid=" + msgid );
	}
}
