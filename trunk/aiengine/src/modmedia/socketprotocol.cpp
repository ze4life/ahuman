#include "media_impl.h"

SocketProtocol::SocketProtocol( Logger& p_logger )
:	logger( p_logger )
{
	pin = FLOW_PROTOCOL_UNKNOWN;
	pout = FLOW_PROTOCOL_UNKNOWN;
	maxPacketSize = 0;
	maxReadSize = 0;
	waitTimeSec = 0;
	shutdownInProgress = false;
}

void SocketProtocol::initSocketLib()
{
	WSADATA l_wsa;
	memset( &l_wsa, 0 , sizeof( WSADATA ) );
	WSAStartup( MAKEWORD( 2 , 2 ) , &l_wsa );
}

void SocketProtocol::exitSocketLib()
{
	/* cleanup sockets */
	WSACleanup();
}

void SocketProtocol::create( Xml config )
{
	maxPacketSize = config.getIntProperty( "max-packet-size" , MAX_PACKET_SIZE_DEFAULT );
	maxReadSize = config.getIntProperty( "max-read-size" , MAX_READ_SIZE_DEFAULT );
	waitTimeSec = config.getIntProperty( "wait-time-sec" , WAIT_TIME_SEC_DEFAULT );

	String protocol = config.getProperty( "protocol" );
	ASSERTMSG( !protocol.isEmpty() , "protocol is not defined" );

	if( protocol.equals( "asymmetric" ) ) {
		createFlow( config , pin , delimiterIn , "protocol-inbound" );
		createFlow( config , pout , delimiterOut , "protocol-outbound" );
	}
	else {
		createFlow( config , pin , delimiterIn , "protocol" );
		pout = pin;
		delimiterOut = delimiterIn;
	}
}

void SocketProtocol::createFlow( Xml config , FLOW_PROTOCOL& proto , String& delimiter , String prototype )
{
	String protocol = config.getProperty( prototype );
	if( protocol.equals( "xml-messages" ) ) {
		proto = FLOW_PROTOCOL_XML_MESSAGES;

		String s = config.getProperty( prototype + ".delimiter" , "" );
		delimiter = String::parseStringLiteral( s );
	}
	else
	if( protocol.equals( "text-messages" ) ) {
		proto = FLOW_PROTOCOL_TEXT_MESSAGES;

		String s = config.getProperty( prototype + ".delimiter" , "" );
		delimiter = String::parseStringLiteral( s );

		ASSERTMSG( !delimiter.isEmpty() , "Delimiter is required for test messaging protocol=" + protocol );
	}
	else
	if( protocol.equals( "text-stream" ) ) {
		proto = FLOW_PROTOCOL_TEXT_STREAM;
		delimiter.clear();
	}
	else
	if( protocol.equals( "binary-stream" ) ) {
		proto = FLOW_PROTOCOL_BINARY_STREAM;
		delimiter.clear();
	}
	else {
		ASSERTFAILED( "Unknown protocol=" + protocol );
	}
}

bool SocketProtocol::waitSocketDataTimeout( SOCKET socket , int p_sec , bool& p_error )
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

	p_error = true;
	int l_res = select( 0 , 
		&l_set ,
		NULL , 
		&l_set ,
		l_pt );

	p_error = false;
	if( l_res <= 0 ) {
		if( l_res < 0 )
			p_error = true;
		return( false );
	}

	// check wakeup reason
	int l_check = 0;
	l_t.tv_sec = 0;

	// check exception
	_fd_checke( l_check , &l_set , &l_t , socket );
	if( l_check ) {
		p_error = true;
		return( false );
	}

	// check read status - should be
	p_error = false;
	_fd_checkr( l_check , &l_set , &l_t , socket );
	if( !l_check )
		return( false );

	return( true );
}

bool SocketProtocol::waitSocketData( SOCKET socket , bool p_wait )
{
	int waitTime = ( p_wait )? waitTimeSec : 0;
	bool error = false;
	if( waitSocketDataTimeout( socket , waitTime , error ) )
		return( true );

	if( !shutdownInProgress )
		ASSERTFAILED( "SocketProtocol::waitSocketData: error while reading socket" );

	return( false );
}

bool SocketProtocol::readMessage( SOCKET socketHandle , String& msg , bool wait , bool& connectionClosed )
{
	return( readMessageInternal( socketHandle , msg , 0 , wait , connectionClosed ) );
}

bool SocketProtocol::readXmlMessage( SOCKET socketHandle , Xml& xml , String& msg , bool wait , bool& connectionClosed )
{
	connectionClosed = false;

	char buf[ 1024 ];
	switch( pin ) {
		default :
		case FLOW_PROTOCOL_UNKNOWN :
			ASSERTFAILED( "SocketProtocol::readMessage: protocol is not defined to read from socket" );
			break;

		case FLOW_PROTOCOL_XML_MESSAGES :
			while( true ) {
				// try to extract next doc
				if( inPending.length() > 0 ) {
					int len = 0;
					bool errflag = false;

					// parse string
					xml = Xml::parse( inPending , len , errflag );
					if( errflag ) {
						if( xml.exists() )
							xml.destroy();
						continue;
					}
				
					if( xml.exists() ) {
						msg = inPending;
						inPending.remove( 0 , len );
						return( true );
					}
				}

				// wait next chunk from socket
				int waitTime = ( wait )? waitTimeSec : 0;
				while( !waitSocketDataTimeout( socketHandle , waitTime , connectionClosed ) ) {
					if( connectionClosed || wait == false )
						return( false );
				}

				// read into buffer
				int l_recv = recv( socketHandle , buf , sizeof( buf ) - 1 , 0 );
				if( l_recv == 0 || l_recv == SOCKET_ERROR ) {
					connectionClosed = true;
					inPending.clear();
					return( false );
				}

				buf[ l_recv ] = 0;
				inPending += buf;
			}
			break;
	}

	return( false );
}

void SocketProtocol::writeMessage( SOCKET socketHandle , const String& msg , bool& connectionClosed )
{
	int lenRemained = msg.length();
	const char *p = msg;
	while( lenRemained > 0 ) {
		int len = send( socketHandle , p , lenRemained , 0 );
		if( len == SOCKET_ERROR || len == 0 ) {
			connectionClosed = true;
			return;
		};

		logger.logDebug( String( "Packet sent, size=" ) + len );
		lenRemained -= len;
		p += len;
	}

	// add delimiter if specified
	if( delimiterOut.isEmpty() )
		return;

	lenRemained = delimiterOut.length();
	p = delimiterOut;
	while( lenRemained > 0 ) {
		int len = send( socketHandle , p , lenRemained , 0 );
		if( len == SOCKET_ERROR || len == 0 ) {
			connectionClosed = true;
			return;
		};

		logger.logDebug( String( "Delimiter sent, size=" ) + len );
		lenRemained -= len;
		p += len;
	}
}

bool SocketProtocol::readFixedSizeMessage( SOCKET socketHandle , int size , String& msg , bool wait , bool& connectionClosed )
{
	return( readMessageInternal( socketHandle , msg , size , wait , connectionClosed ) );
}

bool SocketProtocol::readMessageInternal( SOCKET socketHandle , String& msg , int fixedSize , bool wait , bool& connectionClosed )
{
	char buf[ 1024 ];

	connectionClosed = false;
	Xml xml;
	switch( pin ) {
		default :
		case FLOW_PROTOCOL_UNKNOWN :
			ASSERTFAILED( "SocketProtocol::readMessageInternal: protocol is not defined to read from socket" );
			break;

		case FLOW_PROTOCOL_XML_MESSAGES :
			if( !readXmlMessage( socketHandle , xml , msg , wait , connectionClosed ) )
				return( false );

			// xml is actualy not required
			xml.destroy();
			if( fixedSize > 0 && fixedSize != msg.length() )
				ASSERTFAILED( "SocketProtocol::readMessageInternal: returned xml message has length, different from fixed size=" + fixedSize );

			return( true );

		case FLOW_PROTOCOL_TEXT_MESSAGES :
			while( true ) {
				// message with delimiters
				int index = inPending.find( delimiterIn );
				if( index > 0 ) {
					msg = inPending.getMid( 0 , index );
					inPending.remove( 0 , index + delimiterIn.length() );
					if( fixedSize > 0 )
						ASSERTMSG( msg.length() == fixedSize , String( "SocketProtocol::readMessageInternal: received message has size=" ) + msg.length() + ", expected size=" + fixedSize );
					return( true );
				}

				// wait next chunk from socket
				while( true ) {
					int waitTime = ( wait )? waitTimeSec : 0;
					if( waitSocketDataTimeout( socketHandle , waitTime , connectionClosed ) )
						break;

					if( connectionClosed )
						return( false );

					if( !wait )
						return( false );
				}

				// read into buffer
				int l_recv = recv( socketHandle , buf , sizeof( buf ) - 1 , 0 );
				if( l_recv == 0 || l_recv == SOCKET_ERROR ) {
					connectionClosed = true;
					inPending.clear();
					return( false );
				}

				buf[ l_recv ] = 0;
				inPending += buf;
			}
			break;

		case FLOW_PROTOCOL_TEXT_STREAM :
			int packetSize = 0;
			inPending.clear();

			while( true ) {
				if( fixedSize > 0 ) {
					// if waiting for fixed size data
					int waitTime = ( wait )? waitTimeSec : 0;
					if( !waitSocketDataTimeout( socketHandle , waitTime , connectionClosed ) ) {
						if( connectionClosed )
							return( false );

						// in wait mode try again
						if( wait )
							continue;

						// return no message
						return( false );
					}
				}
				else {
					// just any part of text stream - wait can be only for first time
					bool waitCall = ( packetSize == 0 )? wait : false;
					int waitTime = ( waitCall )? waitTimeSec : 0;
					if( !waitSocketDataTimeout( socketHandle , waitTime , connectionClosed ) ) {
						if( connectionClosed )
							return( false );

						if( packetSize > 0 ) {
							msg = inPending;
							inPending.clear();
							return( true );
						}

						// in wait mode need at least one packet
						if( wait )
							continue;

						// return no message
						return( false );
					}
				}

				int readOneSize = ( fixedSize > 0 )? fixedSize - packetSize : maxPacketSize - packetSize;
				if( readOneSize > maxReadSize )
					readOneSize = maxReadSize;

				// allocate space
				inPending.resize( readOneSize + packetSize );

				// read packet
				char *p = inPending.getBuffer();
				int len = recv( socketHandle , p + packetSize , readOneSize , 0 );
				if( len == SOCKET_ERROR || len == 0 ) {
					connectionClosed = true;
					inPending.clear();
					return( false );
				}

				packetSize += len;
				p[ packetSize ] = 0;
				logger.logDebug( String( "SocketProtocol::readMessageInternal: packet received, size=" ) + len );

				// check fixed size is received
				if( fixedSize > 0 && packetSize == fixedSize ) {
					msg = inPending;
					inPending.clear();
					return( true );
				}

				// check max size is received
				if( fixedSize <= 0 && packetSize == maxPacketSize ) {
					msg = inPending;
					inPending.clear();
					return( true );
				}
			}
		
			break;
	}

	return( false );
}

void SocketProtocol::copy( SocketProtocol& src )
{
	pin = src.pin;;
	pout = src.pout;
	delimiterIn = src.delimiterIn;
	delimiterOut = src.delimiterOut;

	maxPacketSize = src.maxPacketSize;
	maxReadSize = src.maxReadSize;
	waitTimeSec = src.waitTimeSec;
}
