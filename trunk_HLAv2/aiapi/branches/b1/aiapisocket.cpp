
#include "aiapi_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIApiSocket::AIApiSocket()
{
	socketHandle = INVALID_SOCKET;
	memset( &addr , 0 , sizeof( sockaddr_in ) );
}

AIApiSocket::~AIApiSocket()
{
}

void AIApiSocket::initSocketLib()
{
	WSADATA l_wsa;
	memset( &l_wsa, 0 , sizeof( WSADATA ) );
	WSAStartup( MAKEWORD( 2 , 2 ) , &l_wsa );
}

void AIApiSocket::exitSocketLib()
{
	/* cleanup sockets */
	WSACleanup();
}

void AIApiSocket::open( String host , unsigned short port )
{
	initSocketLib();

	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );

	char c = *( const char * )host;
	if( isdigit( c ) )
		{
			// get IP address
			unsigned long l_addr = inet_addr( host );
			addr.sin_addr.S_un.S_addr = l_addr;
		}
	else
		{
			// get IP by hostname
			struct hostent *he = gethostbyname( host );
			ASSERTMSG( he != NULL , "Cannot resolve host address" );

			addr.sin_addr.S_un.S_addr = *( unsigned long * )he -> h_addr_list[ 0 ];
		}
			
	socketHandle = socket( AF_INET , SOCK_STREAM , 0 );
	int res = connect( socketHandle , ( struct sockaddr * )&addr , sizeof( sockaddr_in ) );
	int errorCode = WSAGetLastError();
	ASSERTMSG( res == 0 , String( "Error code found: " ) + errorCode );
}

void AIApiSocket::close()
{
	shutdown( socketHandle , SD_BOTH );
	_closesocket( socketHandle );
	socketHandle = INVALID_SOCKET;

	exitSocketLib();
}

bool AIApiSocket::sendMessage( const char *msg )
{
	ASSERT( socketHandle != INVALID_SOCKET );

	int msgLen = strlen( msg );
	int sentLen = send( socketHandle , msg , msgLen , 0 );
	if( sentLen != msgLen )
		return( false );

	char c = 0x01;
	sentLen = send( socketHandle , &c , 1 , 0 );
	if( sentLen != 1 )
		return( false );

	return( true );
}

String AIApiSocket::recvMessage( int waitTime )
{
	ASSERT( socketHandle != INVALID_SOCKET );

	Timer timer( waitTime );
	while( timer.go() )
		{
			// find end of message
			const char *p = NULL;
			if( !buffer.isEmpty() )
				p = strchr( buffer , 0x01 );
			if( p != NULL )
				{
					// read
					String retValue = buffer.getMid( 0 , p - ( const char * )buffer );
					p++;
					buffer = buffer.getMid( p - ( const char * )buffer , buffer.length() - ( p - ( const char * )buffer ) );
					return( retValue );
				}

			// wait for next message
			if( !waitSocketRead( waitTime ) )
				return( "" );

			// read from socket
			const int SIZE = 1024;
			char l_buf[ SIZE ];
			int recvLen = recv( socketHandle , l_buf , SIZE , 0 );
			ASSERT( recvLen != SOCKET_ERROR );

			// server disconnected
			if( recvLen == 0 )
				return( "" );

			buffer.append( l_buf , recvLen );
		}

	ASSERTMSG( false , "No message received within defined wait interval" );
}

bool AIApiSocket::waitSocketRead( int timeMillis )
{
	fd_set set;
	FD_ZERO( &set );
	FD_SET( socketHandle , &set );
	
	struct timeval tv;
	tv.tv_sec = timeMillis / 1000;
	tv.tv_usec = ( timeMillis % 1000 ) * 1000;
	int res = select( 0 , &set , NULL , NULL , &tv );

	if( res == SOCKET_ERROR )
		return( false );

	// timeout expired
	ASSERTMSG( res == 1 , String( "No response received within " ) + timeMillis + "ms" );

	return( true );
}

