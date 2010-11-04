#ifndef	INCLUDE_AIMEDIA_IMPL_H
#define INCLUDE_AIMEDIA_IMPL_H

#include <winsock2.h>

#include <aiengine.h>
#include <aimedia.h>
#include <aisvcio.h>

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

class Listener;
class Connection;

class SocketServer;
class ActiveSocket;
class SocketConnection;

/*#########################################################################*/
/*#########################################################################*/

class Connection
{
public:
	Connection() { listener = NULL; session = NULL; };
	virtual ~Connection() {};

	void setListener( Listener *p_listener ) { listener = p_listener; };
	Listener *getListener() { return( listener ); };

	void setName( String name ) { key = name; };
	String getName() { return( key ); };

	void setSession( Session *p_session ) { session = p_session; };
	Session *getSession() { return( session ); };

public:
	virtual bool startConnection() = 0;
	virtual void stopConnection() = 0;

private:
	Listener *listener;
	String key;
	Session *session;
};

/*#########################################################################*/
/*#########################################################################*/

class Listener
{
public:
	// interface
	virtual void configure( Xml config ) = 0;
	virtual bool startListener() = 0;
	virtual void stopListener() = 0;
	virtual String getAddress() = 0;

public:
	Listener();
	virtual ~Listener();

public:
	void setMsgType( Message::MsgType msgType );
	Message::MsgType getMsgType();
	String getName();

	void addListenerConnection( Connection *connection );
	void removeListenerConnection( Connection *connection );
	void stopListenerConnections();

private:
	int lastConnectionId;
	Message::MsgType msgType;
	String name;
	MapStringToClass<Connection> connections;
};

/*#########################################################################*/
/*#########################################################################*/

// handles different media AI will use to communicate
class AIMediaImpl : public AIMedia , public Service
{
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Media" ); };

// external interface
public:
	AIMediaImpl();
	static AIMediaImpl *getServiceImpl();

public:
	Listener *getListener( String name );

	void initSocketLib();
	void exitSocketLib();

	virtual void sendTextToDirectChannel( String name , String text );
	virtual String receiveTextFromDirectChannel( String name , bool wait );
	virtual String receiveFixedSizeTextFromDirectChannel( String name , int size );

// internals
private:
	// implement set of listeners
	void startListeners();
	void stopListeners();
	Listener *runListenerFactory( String name );

	// implement active connections
	void startActiveSockets();
	void stopActiveSockets();
	ActiveSocket *runActivatorFactory( String name );

	ActiveSocket *getActiveSocket( String name );

private:
	AIEngine& engine;
	MapStringToClass<Listener> listeners;
	MapStringToClass<ActiveSocket> activeSockets;
};

/*#########################################################################*/
/*#########################################################################*/

class ActiveSocket : public Object , public Subscriber
{
private:
	SOCKET socketHandle;
	struct sockaddr_in addr;
	bool typetext;

	RFC_HND thread;
	bool threadStarted;
	bool continueRead;
	bool connected;
	bool shutdownInProgress;

	Message::MsgType msgType;
	String name;
	String loggerName;
	
	String host;
	String port;
	bool permanentConnection;
	int maxPacketSize;
	static const int MAX_PACKET_SIZE_DEFAULT = 1000000;
	int maxReadSize;
	static const int MAX_READ_SIZE_DEFAULT = 4096;
	int waitTimeSec;
	static const int WAIT_TIME_SEC_DEFAULT = 30;

	bool redirectInbound;
	bool redirectOutbound;

	String inboundChannelName;
	String outboundChannelName;
	Publisher *inboundChannel;

public:
	// interface
	void configure( Xml config );
	bool startActiveSocket();
	void stopActiveSocket();

public:
	ActiveSocket( String name );
	virtual ~ActiveSocket();
	virtual const char *getClass() { return( "ActiveSocket" ); };

public:
	Message::MsgType getMsgType();
	String getName();
	String getAddress();

	void sendText( String text );
	String receiveText( bool wait );
	String receiveFixedText( int size );

private:
	bool connectSocket();
	void disconnectSocket();
	bool waitReadSocket( bool wait );
};

/*#########################################################################*/
/*#########################################################################*/

class SocketConnection : public Object , public Connection , public Subscriber
{
public:
	SocketConnection( SocketServer *server , SOCKET clientSocket , struct sockaddr_in *clientAddress , Message::MsgType msgType );
	~SocketConnection();

	virtual const char *getClass() { return( "SocketConnection" ); };
	virtual bool startConnection();
	virtual void stopConnection();

	String getClientSocketName();

	void readMessages();
	void sendString( const char *p_msg , int len );
	void writeMessage( TextMessage *p_msg );

	// subscriber
	virtual void onTextMessage( TextMessage *msg );
	virtual void onXmlMessage( XmlMessage *msg );
	virtual void onXmlCall( XmlCall *msg );

public:
	void threadClientFunction( void *p_arg );

private:
	void tryLogin( const char *p_msg );
	void performRead();
	void processData( const char *p_msg );
	void processMessage( const char *p_msg );

private:
	AIEngine& engine;
	AIIO io;
	Logger logger;

	SocketServer *server;
	Publisher *pub;
	Subscription *sub;
	Message::MsgType msgType;

	SOCKET socket;
	struct sockaddr_in addr;
	String message;

	RFC_HND thread;
	bool threadStarted;
	bool continueRead;
	bool connected;
	bool logout;
};

/*#########################################################################*/
/*#########################################################################*/

class SocketServer : public Object , public Listener
{
public:
	SocketServer( String name );
	~SocketServer();

public:
	virtual const char *getClass() { return( "SocketServer" ); };
	virtual void configure( Xml config );
	virtual bool startListener();
	virtual void stopListener();
	virtual String getAddress();

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
	void threadConnectFunction( void *p_arg );

	static String getAddress( struct sockaddr_in *clientAddress );

private:
	AIEngine& engine;

	Logger logger;
	String name;
	String loggerName;

	bool continueConnecting;
	bool shutdownInProgress;
	int port;

	bool auth;
	bool wayIn;
	bool wayOut;
	String topicIn;
	String topicOut;

	RFC_HND listenThread;
	SOCKET listenSocket;
	struct sockaddr_in listen_inet;
};

#endif	// INCLUDE_AIMEDIA_IMPL_H
