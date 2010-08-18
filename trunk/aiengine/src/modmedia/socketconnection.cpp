
#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

SocketConnection::SocketConnection( SocketServer *p_server , SOCKET p_clientSocket , struct sockaddr_in *p_clientAddress , Message::MsgType p_msgType )
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
	msgType = p_msgType;

	logger.attach( "SocketConnection" );
}

SocketConnection::~SocketConnection()
{
	// delete session
	Session *session = Connection::getSession();
	if( session != NULL )
		{
			AIIO io;
			io.closeSession( session );
		}
}

void SocketConnection::threadClientFunction( void *p_arg )
{
	// startup sockets
	WSADATA l_wsa;
	WSAStartup( MAKEWORD( 1 , 1 ) , &l_wsa );

	// read messages
	readMessages();

	Listener *listener = getListener();
	listener -> destroyListenerConnection( this );

	// cleanup sockets
	WSACleanup();
}

bool SocketConnection::startConnection()
{
	// complete connection
	logger.logInfo( String( "client [" ) + getName() + 
		"] connected on listener [" + server -> getName() + 
		"] from network address " + getClientSocketName() );

	// connect to topics
	AIIO io;
	Session *session = io.createSession();
	Connection::setSession( session );
	if( server -> getWayIn() )
		{
			String topicIn = server -> getTopicIn();
			AIIO io;
			pub = io.createPublisher( session , topicIn , getName() , "generic" );
		}

	if( server -> getWayOut() )
		{
			String topicOut = server -> getTopicOut();
			AIIO io;
			sub = io.subscribe( session , topicOut , getName() , this );
		}

	// start reading thread
	if( server -> getWayIn() || server -> getAuth() )
		{
			engine.runThread( Connection::getName() , this , ( ObjectThreadFunction )&SocketConnection::threadClientFunction , NULL );
			threadStarted = true;
		}

	// log success
	connected = true;

	return( true );
}

void SocketConnection::readMessages()
{
	try {
		continueRead = true;
		while( continueRead )
			performRead();
	}
	catch ( RuntimeException& e ) {
		logger.logError( getName() + ": SocketConnection::readMessages - exception catched:" );
		e.printStack( logger );
	}
	catch ( ... ) {
		logger.logError( getName() + ": SocketConnection::readMessages - unknown exception in read" );
		logger.printStack();
	}

	try {
		stopConnection();
	}
	catch ( ... ) {
		logger.logError( getName() + ": SocketConnection::readMessages - unknown exception in stop" );
		logger.printStack();
	}
}

void SocketConnection::performRead()
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
	if( l_recv == 0 || l_recv == SOCKET_ERROR )
		{
			continueRead = false;
			logout = true;
			logger.logDebug( "SocketConnection::performRead - empty message, disconnecting" );
			return;
		}

	// process data
	buf[ l_recv ] = 0;
	processData( buf );
}

void SocketConnection::stopConnection()
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
			logger.logInfo( getName() + ": disconnected" );
			connected = false;
		}
}

void SocketConnection::processData( const char *p_msg )
{
	// format is "message0x01", where message contains only printable characters
	do
		{
			const char *l_end = strchr( p_msg , 0x01 );
			if( l_end == NULL )
				{
					message += p_msg;
					return;
				}

			// full message found - process it
			message.append( p_msg , l_end - p_msg );
			processMessage( message );
			message.clear();

			p_msg += l_end - p_msg + 1;
		}
	while( *p_msg );
}

void SocketConnection::processMessage( const char *p_msg )
{
	if( server -> getAuth() && connected == false )
		{
			// the only message acceptable is connect
			tryLogin( p_msg );
			return;
		}

	// pass to channel
	logger.logDebug( getName() + ": socket received message (" + p_msg + ")" );
							    
	if( msgType == Message::MsgType_Text )
		{
			pub -> publish( Connection::getSession() , p_msg );
		}
	else
	if( msgType == Message::MsgType_Xml )
		{
			XmlMessage *l_msg = new XmlMessage( p_msg );
			l_msg -> setXmlFromMessage( pub -> getMsgType() );
			pub -> publish( Connection::getSession() , p_msg );
		}
	else
	if( msgType == Message::MsgType_XmlCall )
		{
			XmlCall *call = new XmlCall( pub -> getChannel() , sub -> getChannel() , p_msg );
			call -> setXmlFromMessage();
			pub -> publish( Connection::getSession() , call );
		}
}

void SocketConnection::tryLogin( const char *p_msg )
{
}

void SocketConnection::writeMessage( Message *p_msg )
{
	const String& s = p_msg -> getText();
	sendString( ( const char * )s , s.length() );
}

void SocketConnection::sendString( const char *p_msg , int p_len )
{
	ASSERTMSG( p_len > 0 , "SocketConnection::sendString - empty message" );

	// send message
	logger.logDebug( getName() + ": send message to socket - (" + String( p_msg , p_len ) + ")" );
 	send( socket , p_msg , p_len , 0 );

	// send message terminator
	char c = 0x01;
	send( socket , &c , 1 , 0 );
}

String SocketConnection::getClientSocketName()
{
	String msg = SocketServer::getAddress( &addr );
	return( msg );
}

void SocketConnection::onMessage( Message *msg )
{
	writeMessage( msg );
}

void SocketConnection::onXmlMessage( XmlMessage *msg )
{
	msg -> setMessageFromXml();
	writeMessage( msg );
}

void SocketConnection::onXmlCall( XmlCall *msg )
{
	ASSERTMSG( false , "not implemented yet" );
}
