#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

SocketServer::SocketServer( String p_name )
:	engine( AIEngine::getInstance() ) ,
	Listener( p_name )
{
	name = p_name;
	continueConnecting = true;
	shutdownInProgress = false;
	listenThread = ( RFC_HND )NULL;
	Listener::setMsgType( Message::MsgType_Unknown );
}

SocketServer::~SocketServer()
{
}

String SocketServer::getTopicIn()
{
	return( topicIn );
}

String SocketServer::getTopicOut()
{
	return( topicOut );
}

bool SocketServer::getAuth()
{
	return( auth );
}

bool SocketServer::getWayIn()
{
	return( wayIn );
}

bool SocketServer::getWayOut()
{
	return( wayOut );
}

void SocketServer::configure( Xml config )
{
	Listener::getProtocol().create( config );

	auth = config.getBooleanProperty( "auth" );
	String direction = config.getProperty( "direction" );
	wayIn = direction.equals( "in" ) || direction.equals( "duplex" );
	wayOut = direction.equals( "out" ) || direction.equals( "duplex" );

	if( wayIn )
		topicIn = config.getProperty( "topic-in" );
	if( wayOut )
		topicOut = config.getProperty( "topic-out" );

	String smsgType = config.getProperty( "msgtype" , "text" );
	if( smsgType.equals( "text" ) )
		Listener::setMsgType( Message::MsgType_Text );
	else
	if( smsgType.equals( "xml" ) )
		Listener::setMsgType( Message::MsgType_Xml );
	else
	if( smsgType.equals( "xmlcall" ) )
		Listener::setMsgType( Message::MsgType_XmlCall );

	port = atoi( config.getProperty( "port" ) );
	loggerName = String( "SocketServer::" ) + Listener::getName();
	logger.attach( loggerName );
}

bool SocketServer::startListener()
{
	return( openListeningPort() );
}

void SocketServer::stopListener()
{
	closeListeningPort();
}

String SocketServer::getAddress()
{
	return( getAddress( &listen_inet ) );
}

void SocketServer::threadConnectFunction( void *p_arg )
{
	AIMediaImpl *media = AIMediaImpl::getServiceImpl();

	// startup sockets
	SocketProtocol::initSocketLib();

	// accept connections
	acceptConnectionLoop();

	// cleanup sockets
	SocketProtocol::exitSocketLib();
}

bool SocketServer::openListeningPort()
{
	// read parameters
	short socket_port = port;

	// prepare socket
	char l_hostname[ 256 ];
	struct hostent *l_hostent;
	int l_len;

	l_len = sizeof( struct sockaddr_in );
	memset( &listen_inet , 0 , l_len );
	listen_inet.sin_port = htons( ( unsigned short )socket_port );

	/* calculate itself address */
	gethostname( l_hostname , 255 );
	l_hostent = gethostbyname( l_hostname );
	listen_inet.sin_family = AF_INET;
	memcpy( &listen_inet.sin_addr , l_hostent -> h_addr_list[ 0 ] , sizeof( listen_inet.sin_addr ) );

	unsigned long l_ok = 1;
	listenSocket = socket( AF_INET , SOCK_STREAM , 0 );
	if( listenSocket == INVALID_SOCKET )
		l_ok = 0;

	if( l_ok )
		if( bind( listenSocket , ( struct sockaddr * )&listen_inet , l_len ) )
			l_ok = 0;

	// options
	BOOL option = FALSE;
	if( l_ok )
		if( setsockopt( listenSocket , SOL_SOCKET , SO_KEEPALIVE , ( const char * )&option , sizeof( BOOL ) ) )
			l_ok = 0;

	/* set socket to non-blocking mode */
	if( l_ok )
		if( _ioctlsocket( listenSocket , FIONBIO , &l_ok ) )
			l_ok = 0;

	// set listening mode
	if( l_ok )
		if( listen( listenSocket , SOMAXCONN ) )
			l_ok = 0;

	if( !l_ok )
		return( false );

	// start listening thread
	listenThread = engine.runThread( Listener::getName() , this , ( ObjectThreadFunction )&SocketServer::threadConnectFunction , NULL );
	
	String msg = "openListeningPort: started listener [" + Listener::getName() + "] on " + getAddress( &listen_inet );
	logger.logInfo( msg );

	return( true );
}

String SocketServer::getAddress( struct sockaddr_in *a )
{
	char l_buf[ 20 ];
	sprintf( l_buf , "[%d.%d.%d.%d" , 
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b1 ,
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b2 ,
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b3 ,
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b4 );
	
	String s = l_buf;
	s += ":";

	sprintf( l_buf , "%d]" , ( unsigned int )ntohs( a -> sin_port ) );
	s += l_buf;

	return( s );
}

void SocketServer::closeListeningPort()
{
	shutdownInProgress = true;

	// close listening socket
	if( listenSocket != INVALID_SOCKET )
		{
			_closesocket( listenSocket );
			listenSocket = INVALID_SOCKET;

			String msg = "closeListeningPort: stopped listener on " + getAddress( &listen_inet );
			logger.logInfo( msg );
		}

	if( listenThread != ( RFC_HND )NULL ) {
		engine.waitThreadExited( listenThread );
		listenThread = ( RFC_HND )NULL;
	}
}

void SocketServer::acceptConnectionLoop()
{
	try {
		continueConnecting = true;
		shutdownInProgress = false;
		while( continueConnecting )
			performConnect();
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
	}
	catch ( ... ) {
		logger.logError( "acceptConnectionLoop: unknown exception" );
		logger.printStack();
	}
}

void SocketServer::performConnect()
{
	bool l_error;
	if( !SocketProtocol::waitSocketData( listenSocket , 0 , l_error ) )
		{
			continueConnecting = false;
			return;
		}

	// connect request received
	struct sockaddr_in clientAddress;
	memset( &clientAddress , 0 , sizeof( struct sockaddr_in ) );
	clientAddress.sin_family = AF_INET;

	int l_len = sizeof( struct sockaddr_in );
	SOCKET clientSocket = accept( listenSocket , ( struct sockaddr * )&clientAddress , &l_len );

	if( clientSocket == INVALID_SOCKET )
		{
			continueConnecting = false;
			logger.logError( "accept returned INVALID_SOCKET" );
			return;
		}

	/* set non-blocking */
	unsigned long l_ok = 1;
	_ioctlsocket( clientSocket , FIONBIO , &l_ok );
	/* set linger */
	struct linger l_linger;
	l_linger.l_onoff = 1;
	l_linger.l_linger = 0;

	setsockopt( clientSocket , SOL_SOCKET , SO_LINGER , ( char * )&l_linger , sizeof( struct linger ) );

	// start connection thread
	if( !startConnection( clientSocket , &clientAddress ) )
		{
			continueConnecting = false;
			logger.logError( "cannot start client thread" );
			return;
		}
}

bool SocketServer::startConnection( SOCKET clientSocket , struct sockaddr_in *clientAddress )
{
	SocketConnection *client = new SocketConnection( this , clientSocket , clientAddress , Listener::getMsgType() );
	Listener::addListenerConnection( client );

	if( !client -> startConnection() )
		{
			client -> stopConnection();
			delete client;
			return( false );
		}

	return( true );
}

/*#########################################################################*/
/*#########################################################################*/

