#ifndef	INCLUDE_AH_MEDIA_IMPL_H
#define INCLUDE_AH_MEDIA_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <winsock2.h>

#include <ah_platform.h>

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

class SocketListener;
class SocketServer;
class ActiveSocket;
class SocketConnection;

/*#########################################################################*/
/*#########################################################################*/

class SocketProtocol {
// protocol configuration
public:
	typedef enum {
		FLOW_PROTOCOL_UNKNOWN = 0 , 
		FLOW_PROTOCOL_TEXT_MESSAGES = 1 ,
		FLOW_PROTOCOL_XML_MESSAGES = 2 ,
		FLOW_PROTOCOL_HTTP_MESSAGES = 3 ,
		FLOW_PROTOCOL_TEXT_STREAM = 4 ,
		FLOW_PROTOCOL_BINARY_STREAM = 5
	} FLOW_PROTOCOL;

	FLOW_PROTOCOL pin;
	FLOW_PROTOCOL pout;
	String delimiterIn;
	String delimiterOut;
	bool showMessagesIn;
	bool showMessagesOut;
	bool showPacketsIn;
	bool showPacketsOut;

	int maxPacketSize;
	static const int MAX_PACKET_SIZE_DEFAULT = 1000000;
	int maxReadSize;
	static const int MAX_READ_SIZE_DEFAULT = 4096;
	int waitTimeSec;
	static const int WAIT_TIME_SEC_DEFAULT = 30;

private:
	String inPending;
	bool shutdownInProgress;
	Logger& logger;

	// message data
	String startLine;
	MapStringToString headerLines;
	String chunks;
	char state;
	char substate;
	int chunkSize;

public:
	SocketProtocol( Logger& logger );
	void create( Xml config );
	void copy( SocketProtocol& src );
	void init();

public:
	static void initSocketLib();
	static void exitSocketLib();
	static bool waitSocketDataTimeout( SOCKET socket , int p_sec , bool& p_error );
	static SOCKET open( String host , unsigned short port , struct sockaddr_in *addr );
	static void close( SOCKET socket );

public:
	bool readMessage( SOCKET socketHandle , String& msg , bool wait , bool& connectionClosed );
	bool readFixedSizeMessage( SOCKET socketHandle , int size , String& msg , bool wait , bool& connectionClosed );

	bool readXmlMessage( SOCKET socketHandle , Xml& xml , String& msg , bool wait , bool& connectionClosed );
	void writeMessage( SOCKET socketHandle , const String& msg , bool& connectionClosed );
	bool waitSocketData( SOCKET socket , bool p_wait );

private:
	void createFlow( Xml config , FLOW_PROTOCOL& proto , String& delimiter , String prototype , bool& showPackets , bool& showMessages );

	bool readMessageInternal( SOCKET socketHandle , String& msg , int fixedSize , bool wait , bool& connectionClosed );
	bool readXmlMessageInternal( SOCKET socketHandle , Xml& xml , String& msg , bool wait , bool& connectionClosed );
	bool readTextMessageInternal( SOCKET socketHandle , String& msg , int fixedSize , bool wait , bool& connectionClosed );
	bool readTextStreamInternal( SOCKET socketHandle , String& msg , int fixedSize , bool wait , bool& connectionClosed );
	bool readHttpMessageInternal( SOCKET socketHandle , String& msg , bool wait , bool& connectionClosed );
	bool readHttpMessageStartLine( SOCKET socketHandle , bool wait , bool& connectionClosed );
	bool readHttpMessageHeader( SOCKET socketHandle , bool wait , bool& connectionClosed );
	bool readHttpMessageBody( SOCKET socketHandle , String& msg , bool wait , bool& connectionClosed );
	bool readHttpMessageBodyChunk( SOCKET socketHandle , String& msg , int size , bool wait , bool& connectionClosed );
	void writeHttpMessageInternal( SOCKET socketHandle , const String& msg , bool& connectionClosed );
	void writeSocketInternal( SOCKET socketHandle , const char *s , bool& connectionClosed );
	bool readSocketInternal( SOCKET socketHandle , bool wait , bool& connectionClosed );
};

/*#########################################################################*/
/*#########################################################################*/

class SocketListener : public Object {
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
	virtual void exitListener() = 0;
	virtual String getAddress() = 0;

public:
	SocketListener( String name );
	virtual ~SocketListener();

	virtual const char *getClass() { return( "SocketListener" ); };

public:
	void setMsgType( Message::MsgType msgType );
	Message::MsgType getMsgType();
	String getName();
	SocketProtocol& getProtocol() { return( protocol ); };

	void addListenerConnection( SocketConnection *connection );
	void removeListenerConnection( SocketConnection *connection );
	void stopListenerConnections();
	void exitListenerConnections();
};

/*#########################################################################*/
/*#########################################################################*/

class ActiveSocket : public Object , public MessageSubscriber {
private:
	SOCKET socketHandle;
	SocketProtocol protocol;
	RFC_HND lock;

	RFC_HND socketThread;
	bool threadStarted;
	bool continueRead;
	bool connected;
	bool shutdownInProgress;
	int reconnectionTimeout;

	String name;
	String host;
	String port;
	bool permanentConnection;

	bool redirectInbound;
	bool redirectOutbound;

	String inboundChannelName;
	String outboundChannelName;
	MessageSubscription *sub;
	MessagePublisher *pub;

public:
	// interface
	void configure( Xml config );
	bool startActiveSocket();
	void stopActiveSocket();
	void exitActiveSocket();

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
	bool connectSocketProtected();
	void disconnectSocket();
	bool waitReadSocket( bool wait );
	void handleBrokenConnection();
	void readSocketThread( void *p_arg );
};

/*#########################################################################*/
/*#########################################################################*/

class SocketConnection : public Object , public MessageSubscriber {
private:
	Logger logger;
	SocketProtocol protocol;

	SocketServer *server;
	MessagePublisher *pub;
	MessageSubscription *sub;
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
	SocketListener *listener;
	MessageSession *session;

public:
	SocketConnection( SocketServer *server , SOCKET clientSocket , struct sockaddr_in *clientAddress , Message::MsgType msgType );
	~SocketConnection();

	virtual const char *getClass() { return( "SocketConnection" ); };

public:
	bool startConnection();
	void stopConnection();
	void exitConnection();

	String getClientSocketName();

	void readMessages();
	void sendString( const char *p_msg , int len );
	void writeMessage( TextMessage *p_msg );

	// subscriber
	virtual void onTextMessage( TextMessage *msg );
	virtual void onXmlMessage( XmlMessage *msg );
	virtual void onXmlCall( XmlCall *msg );

	// connection
	void setListener( SocketListener *p_listener ) { listener = p_listener; };
	SocketListener *getListener() { return( listener ); };

	void setName( String name );
	String getName() { return( getInstance() ); };

	void setSession( MessageSession *p_session ) { session = p_session; };
	MessageSession *getSession() { return( session ); };

public:
	void threadClientFunction( void *p_arg );

private:
	void tryLogin( const char *p_msg );
	void performRead();
	void processMessage( const char *p_msg );
};

/*#########################################################################*/
/*#########################################################################*/

class SocketServer : public SocketListener
{
public:
	SocketServer( String name );
	~SocketServer();

public:
	virtual const char *getClass() { return( "SocketServer" ); };
	virtual void configure( Xml config );
	virtual bool startListener();
	virtual void stopListener();
	virtual void exitListener();
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
	void exitListeningPort();

	void performConnect();
	bool startConnection( SOCKET clientSocket , struct sockaddr_in *clientAddress );
	void threadConnectFunction( void *p_arg );

	static String getAddress( struct sockaddr_in *clientAddress );

private:
	String name;

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

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIMEDIA_IMPL_H
