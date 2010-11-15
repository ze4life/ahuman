
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

	// start protocol
	protocol.create( config );

	// start logging
	loggerName = String( "ActiveSocket::" ) + name;
	logger.attach( loggerName );
}

bool ActiveSocket::startActiveSocket()
{
	// open connection and start thread related to connection - to read from socket - if expected
	socketHandle = socket( AF_INET , SOCK_STREAM , 0 );

	ASSERTMSG( socketHandle != SOCKET_ERROR , "ActiveSocket::startActiveSocket - could not create socket for name=" + name );

	memset( &addr , 0 , sizeof( SOCKADDR_IN ) );
	struct hostent *hostEntry = gethostbyname( host );
	addr.sin_addr = *( ( LPIN_ADDR ) *hostEntry -> h_addr_list );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( atoi( port ) );

	if( !permanentConnection )
		return( true );

	// init messaging
	AIIO io;
	if( redirectOutbound )
		sub = io.subscribe( NULL , outboundChannelName , name + "active-socket" , this );
	if( redirectInbound ) {
		pub = io.createPublisher( NULL , inboundChannelName , name + "active-socket" , "text" );

		// start reading thread
		AIEngine& engine = AIEngine::getInstance();
		socketThread = engine.runThread( name + "active-socket" , this , ( ObjectThreadFunction )&ActiveSocket::readSocketThread , NULL );
	}

	// connect to external address
	return( connectSocket() );
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

	if( connect( socketHandle , ( LPSOCKADDR )&addr , sizeof( SOCKADDR_IN ) ) == SOCKET_ERROR ) {
		logger.logDebug( "ActiveSocket::connectSocket - Could not connect to data source for name=" + name );
		return( false );
	}

	connected = true;
	return( true );
}

void ActiveSocket::disconnectSocket()
{
	if( connected ) {
		connected = false;

		_closesocket( socketHandle );
		socketHandle = INVALID_SOCKET;

		String msg = "ActiveSocket::disconnectSocket: stopped socket on " + getAddress();
		logger.logInfo( msg );
	}
}

void ActiveSocket::handleBrokenConnection()
{
	if( !shutdownInProgress )
		disconnectSocket();
}

void ActiveSocket::sendText( String text )
{
	ASSERTMSG( connected , "Not connected" );

	bool connectionClosed;
	protocol.writeMessage( socketHandle , text , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
}

String ActiveSocket::receiveText( bool wait )
{
	ASSERTMSG( connected , "Not connected" );

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
	ASSERTMSG( connected , "Not connected" );

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
	return( protocol.waitSocketData( socketHandle , wait ) );
}

void ActiveSocket::onTextMessage( TextMessage *msg )
{
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
				rfc_thr_sleep( 1 );
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
