
#include "aimedia_impl.h"

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
	sub = NULL;

	socket = p_clientSocket;
	memcpy( &addr , p_clientAddress , sizeof( struct sockaddr_in ) );

	threadStarted = false;
	connected = false;
	logout = false;
	continueRead = false;

	logger.attach( "AISocketConnection" );
}

AISocketConnection::~AISocketConnection()
{
}

bool AISocketConnection::startConnection()
{
	// configure
	name = server -> getName() + ":" + ( int )ntohs( addr.sin_port );

	// connect to topics
	if( server -> getWayIn() )
		{
			String topicIn = server -> getTopicIn();
			AIIO io;
			pub = io.createPublisher( topicIn , name , "generic" );
		}

	if( server -> getWayOut() )
		{
			String topicOut = server -> getTopicOut();
			AIIO io;
			sub = io.subscribe( topicOut , name , this );
		}

	// start reading thread
	if( server -> getWayIn() || server -> getAuth() )
		{
			engine.workerCreated();
			if( rfc_thr_process( &thread , this , threadClientFunction ) ) {
				logger.logError( "startConnectionThread: cannot start client thread" );
				engine.workerExited( thread , -21 );
				return( false );
			}
			threadStarted = true;
		}

	// log success
	String msg = getID();
	msg += ": connected";
	logger.logInfo( msg );
	connected = true;

	return( true );
}

void AISocketConnection::readMessages()
{
	try {
		continueRead = true;
		while( continueRead )
			performRead();
	}
	catch ( RuntimeException& e ) {
		logger.logError( getID() + ": AISocketConnection::readMessages - exception catched:" );
		e.printStack( logger );
	}
	catch ( ... ) {
		logger.logError( getID() + ": AISocketConnection::readMessages - unknown exception in read" );
		logger.printStack();
	}

	try {
		stopConnection();
	}
	catch ( ... ) {
		logger.logError( getID() + ": AISocketConnection::readMessages - unknown exception in stop" );
		logger.printStack();
	}
}

void AISocketConnection::performRead()
{
	// wait for input
	if( server -> getWayIn() == false && server -> getAuth() == false )
		return;

	if( !server -> waitReadSocket( socket , 0 ) )
		{
			continueRead = false;
			return;
		}

	// read message size
	const int SIZE = 1024;
	char buf[ SIZE + 1 ];
	int l_recv = recv( socket , buf , SIZE , 0 );
	if( l_recv == 0 )
		{
			continueRead = false;
			logout = true;
			logger.logDebug( "no content" );
			return;
		}

	// process data
	buf[ l_recv ] = 0;
	processData( buf );
}

void AISocketConnection::stopConnection()
{
	// do not read more
	continueRead = false;

	// stop receiving messages
	AIIO io;
	if( pub != NULL )
		{
			io.destroyPublisher( pub );
			pub = NULL;
		}
	if( sub != NULL )
		{
			io.unsubscribe( sub );
			sub = NULL;
		}

	// close socket part
	if( socket != INVALID_SOCKET )
		{
			shutdown( socket , SD_BOTH );

			logout = true;
			_closesocket( socket );
			socket = INVALID_SOCKET;
		}

	if( connected )
		{
			logger.logInfo( getID() + ": disconnected" );
			connected = false;
		}
}

void AISocketConnection::processData( const char *p_msg )
{
	// format is "message0x01", where message contains only printable characters
	do
		{
			char *l_end = strchr( p_msg , 0x01 );
			if( l_end == NULL )
				{
					message += p_msg;
					return;
				}

			// full message found - process it
			message.append( p_msg , l_end - p_msg );
			processMessage( message );
			message.clear();

			p_msg = ++l_end;
		}
	while( *p_msg );
}

void AISocketConnection::processMessage( const char *p_msg )
{
	if( server -> getAuth() && connected == false )
		{
			// the only message acceptable is connect
			tryLogin( p_msg );
			return;
		}

	// pass to channel
	logger.logInfo( name + ": socket received message (" + p_msg + ")" );
	pub -> publish( p_msg );
}

void AISocketConnection::tryLogin( const char *p_msg )
{
}

void AISocketConnection::writeMessage( AIMessage *p_msg )
{
	sendString( p_msg -> message );
}

void AISocketConnection::sendString( const char *p_msg )
{
	// send message
	send( socket , p_msg , strlen( p_msg ) , 0 );

	// send message terminator
	char c = 0x01;
	send( socket , &c , 1 , 0 );
}

String AISocketConnection::getID()
{
	String msg = inet_ntoa( addr.sin_addr );
	char l_buf[ 10 ];
	sprintf( l_buf , "[%d]" , ( int )ntohs( ( unsigned short )addr.sin_port ) );
	msg += l_buf;

	return( msg );
}

void AISocketConnection::onMessage( AIMessage *msg )
{
	writeMessage( msg );
}

