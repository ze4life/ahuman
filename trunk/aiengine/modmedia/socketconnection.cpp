
#include <aimedia_impl.h>

/*#########################################################################*/
/*#########################################################################*/

static 	unsigned		__stdcall threadClientFunction( void *p_arg )
{
	AIEngine& engine = AIEngine::getInstance();
	engine.workerStarted();

	// startup sockets
	WSADATA l_wsa;
	WSAStartup( MAKEWORD( 1 , 1 ) , &l_wsa );

	// read messages
	AISocketConnection *client = ( AISocketConnection * )p_arg;
	client -> readMessages();

	// cleanup sockets
	WSACleanup();

	engine.workerExited( 0 );
	return( 0 );
}

/*#########################################################################*/
/*#########################################################################*/

AISocketConnection::AISocketConnection( AISockServer *p_server , SOCKET p_clientSocket , struct sockaddr_in *p_clientAddress )
:	engine( AIEngine::getInstance() )
{
	server = p_server;
	session = NULL;

	socket = p_clientSocket;
	memcpy( &addr , p_clientAddress , sizeof( struct sockaddr_in ) );

	threadStarted = false;
	connected = false;
	logout = false;
	continueRead = false;

	logger.attach( "" );
}

AISocketConnection::~AISocketConnection()
{
}

bool AISocketConnection::startConnectionThread()
{
	// start reading thread - still without session
	engine.workerCreated();
	if( rfc_thr_process( &thread , this , threadClientFunction ) ) {
		logger.logError( "startConnectionThread: cannot start client thread" );
		engine.workerExited( thread , -21 );
		return( false );
	}

	String msg = getID();
	msg += ": connected";
	logger.logInfo( msg );

	threadStarted = true;
	return( true );
}

void AISocketConnection::readMessages()
{
	String msg = getID();
	msg += ": ";
	try {
		continueRead = true;
		while( continueRead )
			performRead();

		msg += "disconnected";
		logger.logInfo( msg );
	}
	catch ( RuntimeException& e ) {
		logger.logError( msg );
		e.printStack( logger );
	}
	catch ( ... ) {
		msg += "ai_listen: unknown exception";
		logger.printStack();
		logger.logError( msg );
	}
}

void AISocketConnection::performRead()
{
	// wait for input
	if( !server -> waitReadSocket( socket , 0 ) )
		{
			continueRead = false;
			return;
		}

	// read message size
	char l_buf[ 10 ];
	int l_recv;
	if( ( l_recv = recv( socket , l_buf , 8 , 0 ) ) != 8 )
		{
			continueRead = false;
			if( l_recv <= 0 )
				logout = true;
			else
				logger.logError( "no message header" );
			return;
		}
	l_buf[ 8 ] = 0;

	int l_len = 0;
	sscanf( l_buf , "%x" , &l_len );
	
	// wait for input
	if( !server -> waitReadSocket( socket , 30 ) )
		{
			continueRead = false;
			return;
		}

	// read message
	char *l_msg = ( char * )malloc( l_len + 1 );
	if( ( l_recv = recv( socket , l_msg , l_len , 0 ) ) != l_len )
		{
			continueRead = false;
			logger.logError( "no message content" );
			return;
		}
	l_msg[ l_len ] = 0;

	// process message
	processMessage( l_msg );

	free( l_msg );
}

void AISocketConnection::closeReflect()
{
	// do not read more
	connected = false;
	continueRead = false;

	// close socket part
	if( socket != INVALID_SOCKET )
		{
			logout = true;
			_closesocket( socket );
			socket = INVALID_SOCKET;
		}
}

void AISocketConnection::processMessage( const char *p_msg )
{
	if( !connected )
		{
			// the only message acceptable is connect
			tryConnect( p_msg );
			return;
		}

	// pass to channel
	AIMessage *msg = io.createMessage( p_msg , "socket" );

	logger.logInfo( String( "SOCKET RECEIVED MESSAGE:" ) + p_msg );
	session -> sendMessageToExpert( msg );
}

void AISocketConnection::tryConnect( const char *p_msg )
{
	char l_user[ 256 ];
	bool l_ok = true;
	if( sscanf( p_msg , "connect:%s" , l_user ) != 1 )
		l_ok = false;

	// create session
	if( l_ok )
		{
			session = io.connect( l_user , "socket" , this );
			connected = true;
		}

	// write ack
	if( l_ok )
		sendString( "S" );
	else
		sendString( "F" );
}

void AISocketConnection::writeMessage( AIMessage *p_msg )
{
	sendString( p_msg -> getMessage() );
}

void AISocketConnection::sendString( const char *p_msg )
{
	char l_buf[ 10 ];

	// send message size
	int l_len = strlen( p_msg );
	sprintf( l_buf , "%8.8x" , l_len );
	send( socket , l_buf , 8 , 0 );

	// send message content
	send( socket , p_msg , l_len , 0 );
}

String AISocketConnection::getID()
{
	String msg = inet_ntoa( addr.sin_addr );
	char l_buf[ 10 ];
	sprintf( l_buf , "[%d]" , ( int )ntohs( ( unsigned short )addr.sin_port ) );
	msg += l_buf;

	return( msg );
}
