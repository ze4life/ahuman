#include "aimedia_impl.h"

/*#########################################################################*/
/*#########################################################################*/

static 	unsigned		__stdcall threadConnectFunction( void *p_arg )
{
	AISockServer *server = ( AISockServer * )p_arg;

	// register thread
	AIEngine& engine = AIEngine::getInstance();
	engine.workerStarted();

	// startup sockets
	AISockServer::initSocketLib();

	// accept connections
	server -> acceptConnectionLoop();

	// cleanup sockets
	AISockServer::exitSocketLib();

	engine.workerExited( 0 );
	return( 0 );
}

/*#########################################################################*/
/*#########################################################################*/

AISockServer::AISockServer()
:	engine( AIEngine::getInstance() )
{
	continueConnecting = true;
	shutdownInProgress = false;
}

AISockServer::~AISockServer()
{
}

String AISockServer::getTopicIn()
{
	return( topicIn );
}

String AISockServer::getTopicOut()
{
	return( topicOut );
}

bool AISockServer::getAuth()
{
	return( auth );
}

bool AISockServer::getWayIn()
{
	return( wayIn );
}

bool AISockServer::getWayOut()
{
	return( wayOut );
}

void AISockServer::initSocketLib()
{
	WSADATA l_wsa;
	memset( &l_wsa, 0 , sizeof( WSADATA ) );
	WSAStartup( MAKEWORD( 2 , 2 ) , &l_wsa );
}

void AISockServer::exitSocketLib()
{
	/* cleanup sockets */
	WSACleanup();
}

void AISockServer::configure( Xml config )
{
	auth = config.getBooleanAttribute( "direction" );
	String direction = config.getAttribute( "direction" );
	wayIn = direction.equals( "in" ) || direction.equals( "duplex" );
	wayOut = direction.equals( "out" ) || direction.equals( "duplex" );

	if( wayIn )
		topicIn = config.getProperty( "topic.in" );
	if( wayOut )
		topicOut = config.getProperty( "topic.out" );

	port = atoi( config.getProperty( "port" ) );
	loggerName = String( "AISockServer::" ) + AIListener::getName();
	logger.attach( loggerName );
}

bool AISockServer::startListener()
{
	return( openListeningPort() );
}

void AISockServer::stopListener()
{
	closeListeningPort();
}

bool AISockServer::openListeningPort()
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
	engine.workerCreated();
	if( rfc_thr_process( &listenThread , this , threadConnectFunction ) ) {
		logger.logError( "openListeningPort: cannot start listening thread" );
		engine.workerExited( listenThread , -20 );
		return( false );
	}

	String msg = "openListeningPort: started listener on " + getAddress( &listen_inet );

	logger.logInfo( msg );
	return( true );
}

String AISockServer::getAddress( struct sockaddr_in *a )
{
	char l_buf[ 20 ];
	sprintf( l_buf , "%d.%d.%d.%d" , 
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b1 ,
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b2 ,
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b3 ,
		( unsigned int )a -> sin_addr.S_un.S_un_b.s_b4 );
	
	String s = l_buf;
	s += ":";

	sprintf( l_buf , "%d" , ( unsigned int )ntohs( a -> sin_port ) );
	s += l_buf;

	return( s );
}

void AISockServer::closeListeningPort()
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
}

void AISockServer::acceptConnectionLoop()
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

bool AISockServer::waitReadSocket( SOCKET socket , int p_sec )
{
	struct fd_set l_set;
	struct timeval l_t;

	_fd_init( &l_set );
	_fd_sethnd( &l_set , socket );
	memset( &l_t , 0 , sizeof( struct timeval ) );

	struct timeval *l_pt = NULL;
	if( p_sec > 0 )
		{
			l_pt = &l_t;
			l_t.tv_sec = p_sec;
		}

	int l_res = select( 0 , 
		&l_set ,
		NULL , 
		&l_set ,
		l_pt );

	if( l_res <= 0 )
		{
			if( !shutdownInProgress )
				logger.logError( "select returned value <= 0" );
			return( false );
		}

	// check wakeup reason
	int l_check = 0;
	l_t.tv_sec = 0;

	// check exception
	_fd_checke( l_check , &l_set , &l_t , socket );
	if( l_check )
		{
			if( !shutdownInProgress )
				logger.logError( "select returned exception status" );
			return( false );
		}

	// check read status - should be
	_fd_checkr( l_check , &l_set , &l_t , socket );
	if( !l_check )
		{
			if( !shutdownInProgress )
				logger.logError( "select returned invalid state" );
			return( false );
		}

	return( true );
}

void AISockServer::performConnect()
{
	if( !waitReadSocket( listenSocket , 0 ) )
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

bool AISockServer::startConnection( SOCKET clientSocket , struct sockaddr_in *clientAddress )
{
	AISocketConnection *client = new AISocketConnection( this , clientSocket , clientAddress );
	if( !client -> startConnection() )
		{
			client -> stopConnection();
			delete client;
			return( false );
		}

	AIListener::addListenerConnection( client -> getID() , client );
	return( true );
}

/*#########################################################################*/
/*#########################################################################*/

