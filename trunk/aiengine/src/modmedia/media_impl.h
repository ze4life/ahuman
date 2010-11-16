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
class SocketServer;
class ActiveSocket;
class SocketConnection;

/*#########################################################################*/
/*#########################################################################*/

class SocketProtocol
{
private:
	typedef enum {
		FLOW_PROTOCOL_UNKNOWN = 0 , 
		FLOW_PROTOCOL_TEXT_MESSAGES = 1 ,
		FLOW_PROTOCOL_XML_MESSAGES = 2 ,
		FLOW_PROTOCOL_TEXT_STREAM = 3 ,
		FLOW_PROTOCOL_BINARY_STREAM = 4
	} FLOW_PROTOCOL;

	FLOW_PROTOCOL pin;
	FLOW_PROTOCOL pout;
	String delimiterIn;
	String delimiterOut;
	bool showMessagesIn;
	bool showMessagesOut;

	int maxPacketSize;
	static const int MAX_PACKET_SIZE_DEFAULT = 1000000;
	int maxReadSize;
	static const int MAX_READ_SIZE_DEFAULT = 4096;
	int waitTimeSec;
	static const int WAIT_TIME_SEC_DEFAULT = 30;

	String inPending;
	bool shutdownInProgress;
	Logger& logger;

public:
	SocketProtocol( Logger& logger );
	void create( Xml config );
	void copy( SocketProtocol& src );

public:
	static void initSocketLib();
	static void exitSocketLib();
	static bool waitSocketDataTimeout( SOCKET socket , int p_sec , bool& p_error );

public:
	bool readMessage( SOCKET socketHandle , String& msg , bool wait , bool& connectionClosed );
	bool readFixedSizeMessage( SOCKET socketHandle , int size , String& msg , bool wait , bool& connectionClosed );

	bool readXmlMessage( SOCKET socketHandle , Xml& xml , String& msg , bool wait , bool& connectionClosed );
	void writeMessage( SOCKET socketHandle , const String& msg , bool& connectionClosed );

	bool waitSocketData( SOCKET socket , bool p_wait );

private:
	void createFlow( Xml config , FLOW_PROTOCOL& proto , String& delimiter , String prototype , bool& showMessages );
	bool readMessageInternal( SOCKET socketHandle , String& msg , int fixedSize , bool wait , bool& connectionClosed );
};

/*#########################################################################*/
/*#########################################################################*/

class Listener : public Object
{
private:
	SocketProtocol protocol;
	int lastConnectionId;
	Message::MsgType msgType;
	String name;
	MapStringToClass<SocketConnection> connections;

public:
	// interface
	virtual void configure( Xml config ) = 0;
	virtual bool startListener() = 0;
	virtual void stopListener() = 0;
	virtual String getAddress() = 0;

public:
	Listener( String name );
	virtual ~Listener();

	virtual const char *getClass() { return( "Listener" ); };

public:
	void setMsgType( Message::MsgType msgType );
	Message::MsgType getMsgType();
	String getName();
	SocketProtocol& getProtocol() { return( protocol ); };

	void addListenerConnection( SocketConnection *connection );
	void removeListenerConnection( SocketConnection *connection );
	void stopListenerConnections();
};

/*#########################################################################*/
/*#########################################################################*/

// handles different media AI will use to communicate
class AIMediaImpl : public AIMedia , public Service
{
private:
	AIEngine& engine;
	MapStringToClass<Listener> listeners;
	MapStringToClass<ActiveSocket> activeSockets;

public:
	// service
	virtual void createService( Xml config );
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Media" ); };

public:
	AIMediaImpl();
	static AIMediaImpl *getServiceImpl();

// external interface
public:
	Listener *getListener( String name );

	virtual void sendTextToDirectChannel( String name , String text );
	virtual String receiveTextFromDirectChannel( String name , bool wait );
	virtual String receiveFixedSizeTextFromDirectChannel( String name , int size );

// internals
private:
	// implement set of listeners
	void createListeners( Xml config );
	void startListeners();
	void stopListeners();
	Listener *runListenerFactory( String name , Xml config );

	// implement active connections
	void createActiveSockets( Xml config );
	void startActiveSockets();
	void stopActiveSockets();
	ActiveSocket *runActiveSocketFactory( String name , Xml config );

	ActiveSocket *getActiveSocket( String name );
};

/*#########################################################################*/
/*#########################################################################*/

class ActiveSocket : public Object , public Subscriber
{
private:
	SOCKET socketHandle;
	struct sockaddr_in addr;
	SocketProtocol protocol;

	RFC_HND socketThread;
	bool threadStarted;
	bool continueRead;
	bool connected;
	bool shutdownInProgress;
	int reconnectionTimeout;

	String name;
	String loggerName;
	
	String host;
	String port;
	bool permanentConnection;

	bool redirectInbound;
	bool redirectOutbound;

	String inboundChannelName;
	String outboundChannelName;
	Subscription *sub;
	Publisher *pub;

public:
	// interface
	void configure( Xml config );
	bool startActiveSocket();
	void stopActiveSocket();

	virtual void onTextMessage( TextMessage *msg );

public:
	ActiveSocket( String name );
	virtual ~ActiveSocket();
	virtual const char *getClass() { return( "ActiveSocket" ); };

public:
	String getName();
	String getAddress();

	void sendText( String text );
	String receiveText( bool wait );
	String receiveFixedText( int size , bool wait);

private:
	bool connectSocket();
	void disconnectSocket();
	bool waitReadSocket( bool wait );
	void handleBrokenConnection();
	void readSocketThread( void *p_arg );
};

/*#########################################################################*/
/*#########################################################################*/

class SocketConnection : public Object , public Subscriber
{
private:
	AIEngine& engine;
	AIIO io;
	Logger logger;
	SocketProtocol protocol;

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

	// connection
	Listener *listener;
	String key;
	Session *session;

public:
	SocketConnection( SocketServer *server , SOCKET clientSocket , struct sockaddr_in *clientAddress , Message::MsgType msgType );
	~SocketConnection();

	virtual const char *getClass() { return( "SocketConnection" ); };

public:
	bool startConnection();
	void stopConnection();

	String getClientSocketName();

	void readMessages();
	void sendString( const char *p_msg , int len );
	void writeMessage( TextMessage *p_msg );

	// subscriber
	virtual void onTextMessage( TextMessage *msg );
	virtual void onXmlMessage( XmlMessage *msg );
	virtual void onXmlCall( XmlCall *msg );

	// connection
	void setListener( Listener *p_listener ) { listener = p_listener; };
	Listener *getListener() { return( listener ); };

	void setName( String name );
	String getName() { return( key ); };

	void setSession( Session *p_session ) { session = p_session; };
	Session *getSession() { return( session ); };

public:
	void threadClientFunction( void *p_arg );

private:
	void tryLogin( const char *p_msg );
	void performRead();
	void processMessage( const char *p_msg );
};

/*#########################################################################*/
/*#########################################################################*/

class SocketServer : public Listener
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
