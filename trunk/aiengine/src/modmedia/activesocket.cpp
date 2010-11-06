
#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

ActiveSocket::ActiveSocket( String p_name )
{
	name = p_name;
	msgType = Message::MsgType_Unknown;
	redirectInbound = false;
	redirectOutbound = false;
	connected = false;
	maxPacketSize = 0;
	shutdownInProgress = false;
	maxPacketSize = 0;
	maxReadSize = 0;
}

ActiveSocket::~ActiveSocket()
{
	_closesocket( socketHandle );
}

void ActiveSocket::configure( Xml config )
{
	redirectInbound = config.getBooleanProperty( "redirect-inbound" );
	redirectOutbound = config.getBooleanProperty( "redirect-outbound" );

	if( redirectInbound )
		inboundChannelName = config.getProperty( "topic-in" );
	if( redirectOutbound )
		outboundChannelName = config.getProperty( "topic-out" );

	typetext = config.getProperty( "msgtype" , "text" ).equals( "text" );

	host = config.getProperty( "host" );
	port = config.getProperty( "port" );
	maxPacketSize = config.getIntProperty( "max-packet-size" , MAX_PACKET_SIZE_DEFAULT );
	maxReadSize = config.getIntProperty( "max-read-size" , MAX_READ_SIZE_DEFAULT );
	waitTimeSec = config.getIntProperty( "wait-time-sec" , WAIT_TIME_SEC_DEFAULT );

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

void ActiveSocket::sendText( String text )
{
	ASSERTMSG( connected , "Not connected" );

	int lenRemained = text.length();
	const char *p = text;
	while( lenRemained > 0 ) {
		int len = send( socketHandle , p , lenRemained , 0 );
		ASSERTMSG( len != SOCKET_ERROR && len > 0 , String( "Unable send data to socket size=" ) + lenRemained );

		logger.logDebug( String( "Packet sent, size=" ) + len );
		lenRemained -= len;
		p += len;
	}
}

String ActiveSocket::receiveText( bool wait )
{
	ASSERTMSG( connected , "Not connected" );

	String final;
	int packetSize = 0;

	while( packetSize < maxPacketSize ) {
		int readSize = maxPacketSize - packetSize;
		if( readSize > maxReadSize )
			readSize = maxReadSize;

		// allocate space
		final.resize( readSize + packetSize );

		// only first run can be blocking
		bool haveData = waitReadSocket( ( packetSize == 0 )? wait : false );
		if( !haveData )
			break;

		char *p = final.getBuffer();
		int len = recv( socketHandle , p + packetSize , readSize , 0 );
		ASSERTMSG( len != SOCKET_ERROR && len > 0 , String( "Unable receive data from socket size=" ) + readSize );

		packetSize += len;
		p[ packetSize ] = 0;
		logger.logDebug( String( "Packet received, size=" ) + len );
	}

	return( final );
}

String ActiveSocket::receiveFixedText( int size )
{
	ASSERTMSG( connected , "Not connected" );

	String final;
	int packetSize = 0;

	while( packetSize < size ) {
		int readSize = size - packetSize;
		if( readSize > maxReadSize )
			readSize = maxReadSize;

		// allocate space
		final.resize( readSize + packetSize );

		// only first run can be blocking
		bool haveData = waitReadSocket( true );
		if( !haveData )
			continue;

		char *p = final.getBuffer();
		int len = recv( socketHandle , p + packetSize , readSize , 0 );
		ASSERTMSG( len != SOCKET_ERROR && len > 0 , String( "Unable receive data from socket size=" ) + readSize );

		packetSize += len;
		p[ packetSize ] = 0;
		logger.logDebug( String( "Packet received, size=" ) + len );
	}

	return( final );
}

bool ActiveSocket::waitReadSocket( bool wait )
{
	struct fd_set l_set;
	struct timeval l_t;

	_fd_init( &l_set );
	_fd_sethnd( &l_set , socketHandle );
	memset( &l_t , 0 , sizeof( struct timeval ) );

	struct timeval *l_pt = NULL;

	if( waitTimeSec > 0 ) {
		l_pt = &l_t;
		l_t.tv_sec = waitTimeSec;
	}

	int l_res = select( 0 , 
		&l_set ,
		NULL , 
		&l_set ,
		l_pt );

	if( l_res <= 0 ) {
		if( !shutdownInProgress )
			logger.logError( "select returned value <= 0" );
		return( false );
	}

	// check wakeup reason
	int l_check = 0;
	l_t.tv_sec = 0;

	// check exception
	_fd_checke( l_check , &l_set , &l_t , socketHandle );
	if( l_check ) {
		if( !shutdownInProgress )
			logger.logError( "select returned exception status" );
		return( false );
	}

	// check read status - should be
	_fd_checkr( l_check , &l_set , &l_t , socketHandle );
	if( !l_check ) {
		if( !shutdownInProgress )
			logger.logError( "select returned invalid state" );
		return( false );
	}

	return( true );
}

