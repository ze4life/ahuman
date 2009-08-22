#ifndef	INCLUDE_AIMEDIA_IMPL_H
#define INCLUDE_AIMEDIA_IMPL_H

#include <winsock.h>

#include <aiengine.h>
#include <aimedia.h>
#include <aiio.h>

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

class AISockServer;
class AISocketConnection;
class AIListener;

/*#########################################################################*/
/*#########################################################################*/

class AIListener
{
public:
	AIListener() {};
	virtual ~AIListener() {};

public:
	virtual void configure( Configuration config ) = 0;
	virtual bool startListener() = 0;
	virtual void stopListener() = 0;

	void setName( String p_name ) { name = p_name; };
	String getName() { return( name ); };

private:
	String name;
};

/*#########################################################################*/
/*#########################################################################*/

// handles different media AI will use to communicate
class AIMediaImpl : public AIMedia , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Media" ); };

// external interface
public:
	AIMediaImpl();
	virtual void sendMessageToUser( AIMessage *msg , AISession *session );
	virtual void closeMediaReflect( AISession *session );

public:
	AISockServer *getSockServer( String name );

// internals
private:
	void startListeners();
	void stopListeners();
	AIListener *runListenerFactory( String name , String type );

private:
	AIEngine& engine;
	MapStringToClass<AIListener> listeners;
};

/*#########################################################################*/
/*#########################################################################*/

class AISockServer : public AIListener
{
public:
	AISockServer();
	~AISockServer();

public:
	virtual void configure( Configuration config );
	virtual bool startListener();
	virtual void stopListener();

public:
	void acceptConnectionLoop();
	bool openListeningPort();
	void closeListeningPort();

	bool waitReadSocket( SOCKET socket , int p_sec );
	void performConnect();
	bool startConnectionThread( SOCKET clientSocket , struct sockaddr_in *clientAddress );

	static String getAddress( struct sockaddr_in *clientAddress );

private:
	AIEngine& engine;
	Logger logger;
	String loggerName;

	bool continueConnecting;
	bool shutdownInProgress;
	int port;

	RFC_THREAD listenThread;
	SOCKET listenSocket;
};

/*#########################################################################*/
/*#########################################################################*/

class AISocketConnection
{
public:
	AISocketConnection( AISockServer *server , SOCKET clientSocket , struct sockaddr_in *clientAddress );
	~AISocketConnection();

	bool startConnectionThread();
	void readMessages();
	String getID();
	void closeReflect();

	void performRead();
	void processMessage( const char *p_msg );
	void tryConnect( const char *p_msg );
	void writeMessage( AIMessage *p_msg );
	void sendString( const char *p_msg );

private:
	AIEngine& engine;
	AIIO io;
	Logger logger;

	AISockServer *server;
	AISession *session;

	SOCKET socket;
	struct sockaddr_in addr;
	RFC_THREAD thread;

	bool threadStarted;
	bool continueRead;
	bool connected;
	bool logout;
};

#endif	// INCLUDE_AIMEDIA_IMPL_H
