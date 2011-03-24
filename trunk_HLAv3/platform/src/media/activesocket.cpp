#include <ah_platform.h>
#include <ah_media_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ActiveSocket::ActiveSocket( String p_name )
:	protocol( logger ) {
	name = p_name;

	setInstance( name );
	attachLogger();

	redirectInbound = false;
	redirectOutbound = false;
	connected = false;
	shutdownInProgress = false;

	sub = NULL;
	pub = NULL;
	socketThread = NULL;

	lock = rfc_hnd_semcreate();
}

ActiveSocket::~ActiveSocket() {
	_closesocket( socketHandle );
	rfc_hnd_semdestroy( lock );
}

void ActiveSocket::configure( Xml config ) {
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
	Object::setInstance( name );
	attachLogger();
}

bool ActiveSocket::startActiveSocket() {
	// init messaging
	MessagingService *io = MessagingService::getService();
	if( redirectOutbound )
		sub = io -> subscribe( NULL , outboundChannelName , name + "active-socket" , this );
	if( redirectInbound ) {
		pub = io -> createPublisher( NULL , inboundChannelName , name + "active-socket" , "text" );

		// start reading thread
		ThreadService *ts = ThreadService::getService();
		socketThread = ts -> runThread( Object::getLoggerName() , this , ( ObjectThreadFunction )&ActiveSocket::readSocketThread , NULL );
	}

	return( true );
}

void ActiveSocket::stopActiveSocket() {
	// stop thread reading from socket if any
	shutdownInProgress = true;
	disconnectSocket();

	if( socketThread != NULL ) {
		ThreadService *ts = ThreadService::getService();
		ts -> waitThreadExited( socketThread );
		socketThread = NULL;
	}
}

String ActiveSocket::getAddress() {
	return( host + ":" + port );
}

String ActiveSocket::getName() {
	return( name );
}

bool ActiveSocket::connectSocket() {
	rfc_hnd_semlock( lock );
	bool res = false;

	try {
		res = connectSocketProtected();
	}
	catch( ... ) {
		logger.printStack();
		logger.logDebug( "connectSocket: unexpected exception caught for name=" + name );
	}

	rfc_hnd_semunlock( lock );
	return( res );
}

bool ActiveSocket::connectSocketProtected() {
	if( connected )
		return( true );

	// open connection and start thread related to connection - to read from socket - if expected
	struct sockaddr_in addr;
	memset( &addr , 0 , sizeof( SOCKADDR_IN ) );
	struct hostent *hostEntry = gethostbyname( host );

	if( hostEntry == NULL ) {
		logger.logDebug( "connectSocketProtected: unable to find address of host=" + host + " for name=" + name );
		return( false );
	}

	addr.sin_addr.S_un.S_addr = *( unsigned long * )hostEntry -> h_addr_list[ 0 ];
	addr.sin_family = AF_INET;
	addr.sin_port = htons( ( short )atoi( port ) );

	// create handle
	socketHandle = socket( AF_INET , SOCK_STREAM , 0 );
	ASSERTMSG( socketHandle != SOCKET_ERROR , "connectSocketProtected - unable to create socket for name=" + name );

	// connect to exteranl host/port
	if( connect( socketHandle , ( struct sockaddr * )&addr , sizeof( sockaddr_in ) ) == SOCKET_ERROR ) {
		logger.logDebug( "connectSocketProtected: unable to connect to host=" + host + ", port=" + port + " for name=" + name );
		return( false );
	}

	unsigned long flag = 1;
	ioctlsocket( socketHandle , FIONBIO , &flag );

	logger.logDebug( "connectSocketProtected: successfully connected to host=" + host + ", port=" + port + ", name=" + name );
	connected = true;
	return( true );
}

void ActiveSocket::disconnectSocket() {
	rfc_hnd_semlock( lock );
	if( connected ) {
		connected = false;

		_closesocket( socketHandle );
		socketHandle = INVALID_SOCKET;

		logger.logInfo( "disconnectSocket: disconnected name=" + name );
	}
	rfc_hnd_semunlock( lock );
}

void ActiveSocket::handleBrokenConnection() {
	if( !shutdownInProgress )
		disconnectSocket();
}

void ActiveSocket::sendText( String text ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "sendText - unable to connect ActiveSocket=" + name );

	bool connectionClosed;
	protocol.writeMessage( socketHandle , text , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
		logger.logInfo( "sendText: sent message to socket: text=" + text );
}

String ActiveSocket::receiveText( bool wait ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "receiveText - unable to connect ActiveSocket=" + name );

	bool connectionClosed;
	String final;
	bool res = protocol.readMessage( socketHandle , final , wait , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
	if( res )
		logger.logInfo( "receiveText: received message from socket: text=" + final );

	if( !res )
		return( "" );

	return( final );
}

String ActiveSocket::receiveFixedText( int size , bool wait ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "receiveFixedText - unable to connect ActiveSocket=" + name );

	bool connectionClosed;
	String final;
	bool res = protocol.readFixedSizeMessage( socketHandle , size , final , wait , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
	if( res )
		logger.logInfo( "receiveFixedText: received message from socket: text=" + final );

	if( !res )
		return( "" );

	return( final );
}

bool ActiveSocket::waitReadSocket( bool wait ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "waitReadSocket - unable to connect ActiveSocket=" + name );

	return( protocol.waitSocketData( socketHandle , wait ) );
}

void ActiveSocket::onTextMessage( TextMessage *msg ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "onTextMessage - unable to connect ActiveSocket=" + name );

	// forward from channel to socket
	bool connectionClosed;
	protocol.writeMessage( socketHandle , msg -> getText() , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
		logger.logInfo( "onTextMessage: forwarded message from channel=" + outboundChannelName + " to socket msgid=" + msg -> getChannelMessageId() );
}

void ActiveSocket::readSocketThread( void *p_arg ) {
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
		logger.logInfo( "readSocketThread: forwarded message from socket msgid=" + msgid + " to channel=" + inboundChannelName );
	}
}
