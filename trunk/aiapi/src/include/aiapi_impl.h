
/*#########################################################################*/
/*#########################################################################*/

#include <winsock2.h>

#define _closesocket	closesocket
#define _ioctlsocket	ioctlsocket

#define _fd_init( _fd_set ) \
	(_fd_set) -> fd_count = 0

#define _fd_sethnd( _fd_set , _fd_hnd ) \
	(_fd_set) -> fd_array[ (_fd_set) -> fd_count++ ] = _fd_hnd

#define _fd_checkr( _res , _fd_set , _fd_time , _fd_hnd ) \
	(_fd_set) -> fd_count = 1; \
	(_fd_set) -> fd_array[ 0 ] = _fd_hnd; \
	_res = select( 0 , _fd_set , NULL , NULL , _fd_time )
	
#define _fd_checkw( _res , _fd_set , _fd_time , _fd_hnd ) \
	(_fd_set) -> fd_count = 1; \
	(_fd_set) -> fd_array[ 0 ] = _fd_hnd; \
	_res = select( 0 , NULL , _fd_set , NULL , _fd_time )

#define _fd_checke( _res , _fd_set , _fd_time , _fd_hnd ) \
	(_fd_set) -> fd_count = 1; \
	(_fd_set) -> fd_array[ 0 ] = _fd_hnd; \
	_res = select( 0 , NULL , NULL , _fd_set , _fd_time )

#include "aiapi.h"
#include "tinyxml.h"

#define ASSERT( x ) if( !(x) ) throw String( #x )
#define ASSERTMSG( x , msg ) if( !(x) ) throw String( #x ) + " - " + (msg)

/*#########################################################################*/
/*#########################################################################*/

class AIApiSocket
{
public:
	AIApiSocket();
	~AIApiSocket();

	static void initSocketLib();
	static void exitSocketLib();

	void open( String host , unsigned short port );
	void close();

	bool sendMessage( const char *msg );
	String recvMessage( int waitTime );
	bool waitSocketRead( int timeMillis );

private:
	SOCKET socketHandle;
	struct sockaddr_in addr;
	String buffer;
};

/*#########################################################################*/
/*#########################################################################*/

class Timer
{
public:
	Timer();
	Timer( int waitTime );

public:
	// time passed - in ms
	int timePassed();
	bool go();

private:
	long timeStarted;
	int waitTime;
};

// #############################################################################
// #############################################################################

class AIApiImpl
{
public:
	AIApiImpl();
	~AIApiImpl();

	void connect( String url );
	void disconnect();
	bool isConnected();
	Xml execute( Xml req );

	Xml createXmlRequest( const char *contentName );
	void destroyXml( Xml xml );
	Xml loadXmlRequest( String fileName , const char *contentName );
	Xml readXmlRequest( const char *data , const char *contentName );

private:
	Xml readXml( const char *data , const char *contentName );
	void setXmlRequestId( Xml req );

private:
	AIApiSocket socket;
	bool connected;
	int lastRequestNumber;
	int requestWaitTime;
};
