#ifndef	INCLUDE_AIMEDIA_IMPL_H
#define INCLUDE_AIMEDIA_IMPL_H

#include <winsock2.h>

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

class AIListener;
class AIConnection;

class AISockServer;
class AISocketConnection;

/*#########################################################################*/
/*#########################################################################*/

class AIConnection
{
public:
	AIConnection() { listener = NULL; };
	virtual ~AIConnection() {};

	void setListener( AIListener *p_listener ) { listener = p_listener; };
	AIListener *getListener() { return( listener ); };

	void setID( String id ) { key = id; };
	String getID() { return( key ); };

public:
	virtual bool startConnection() = 0;
	virtual void stopConnection() = 0;

private:
	AIListener *listener;
	String key;
};

/*#########################################################################*/
/*#########################################################################*/

class AIListener
{
public:
	// interface
	virtual void configure( Xml config ) = 0;
	virtual bool startListener() = 0;
	virtual void stopListener() = 0;

public:
	AIListener();
	virtual ~AIListener();

public:
	void setName( String p_name );
	String getName();

	void addListenerConnection( String key , AIConnection *connection );
	void stopListenerConnections();

private:
	String name;
	MapStringToClass<AIConnection> connections;
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

	static void initSocketLib();
	static void exitSocketLib();

public:
	virtual void configure( Xml config );
	virtual bool startListener();
	virtual void stopListener();

public:
	String getTopicIn();
	String getTopicOut();
	bool getAuth();
	bool getWayIn();
	bool getWayOut();

	void acceptConnectionLoop();
	bool openListeningPort();
	void closeListeningPort();

	bool waitReadSocket( SOCKET socket , int p_sec );
	void performConnect();
	bool startConnection( SOCKET clientSocket , struct sockaddr_in *clientAddress );

	static String getAddress( struct sockaddr_in *clientAddress );

private:
	AIEngine& engine;

	Logger logger;
	String loggerName;

	bool continueConnecting;
	bool shutdownInProgress;
	int port;

	bool auth;
	bool wayIn;
	bool wayOut;
	String topicIn;
	String topicOut;

	RFC_THREAD listenThread;
	SOCKET listenSocket;
	struct sockaddr_in listen_inet;
};

/*#########################################################################*/
/*#########################################################################*/

class AISocketConnection : public AIConnection , public AISubscriber
{
public:
	AISocketConnection( AISockServer *server , SOCKET clientSocket , struct sockaddr_in *clientAddress );
	~AISocketConnection();

	virtual bool startConnection();
	virtual void stopConnection();

	String getID();

	void readMessages();
	void sendString( const char *p_msg );
	void writeMessage( AIMessage *p_msg );

	virtual void onMessage( AIMessage *msg );

private:
	void tryLogin( const char *p_msg );
	void performRead();
	void processData( const char *p_msg );
	void processMessage( const char *p_msg );

private:
	AIEngine& engine;
	AIIO io;
	Logger logger;

	AISockServer *server;
	AIPublisher *pub;
	AISubscription *sub;

	String name;
	SOCKET socket;
	struct sockaddr_in addr;
	RFC_THREAD thread;
	String message;

	bool threadStarted;
	bool continueRead;
	bool connected;
	bool logout;
};

#endif	// INCLUDE_AIMEDIA_IMPL_H
