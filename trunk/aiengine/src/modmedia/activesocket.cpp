
#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

ActiveSocket::ActiveSocket( String p_name )
:	protocol( logger )
{
	name = p_name;
	msgType = Message::MsgType_Unknown;
	redirectInbound = false;
	redirectOutbound = false;
	connected = false;
	shutdownInProgress = false;
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

	typetext = config.getProperty( "msgtype" , "text" ).equals( "text" );

	host = config.getProperty( "host" );
	port = config.getProperty( "port" );

	loggerName = String( "ActiveSocket::" ) + name;
	logger.attach( loggerName );

	permanentConnection = config.getBooleanProperty( "permanent" );
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

	return( connectSocket() );
}

void ActiveSocket::stopActiveSocket()
{
	// stop thread reading from socket if any
	disconnectSocket();
}

String ActiveSocket::getAddress()
{
	return( host + ":" + port );
}

Message::MsgType ActiveSocket::getMsgType()
{
	return( msgType );
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
		_closesocket( socketHandle );
		socketHandle = INVALID_SOCKET;

		String msg = "ActiveSocket::disconnectSocket: stopped socket on " + getAddress();
		logger.logInfo( msg );

		connected = false;
	}
}

void ActiveSocket::handleBrokenConnection()
{
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

