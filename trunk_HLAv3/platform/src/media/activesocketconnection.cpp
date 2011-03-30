#include <ah_platform.h>
#include <ah_media_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ActiveSocketConnection::ActiveSocketConnection( String p_urlkey , SocketProtocol& p_protocol , MessagePublisher *p_pub )
:	protocol( p_protocol ) {
	urlKey = p_urlkey;
	pub = p_pub;

	socketHandle = INVALID_SOCKET;
	continueRead = false;
	connected = false;
	socketThread = ( RFC_HND )NULL;
	threadStarted = false;
	shutdownInProgress = false;
	reconnectionTimeoutSec = 0;

	lock = rfc_hnd_semcreate();
}

ActiveSocketConnection::~ActiveSocketConnection() {
	rfc_hnd_semdestroy( lock );
}

String ActiveSocketConnection::getUrlKey() {
	return( urlKey );
}

void ActiveSocketConnection::setUrlKey( String p_urlkey ) {
	if( connected ) {
		disconnectSocket();
		waitThreadFinished();
	}

	urlKey = p_urlkey;
	connectSocket();
}

void ActiveSocketConnection::setReconnectionTimeoutSec( int p_reconnectionTimeoutSec ) {
	reconnectionTimeoutSec = p_reconnectionTimeoutSec;
}

bool ActiveSocketConnection::connectSocket() {
	rfc_hnd_semlock( lock );
	bool res = false;

	try {
		res = connectSocketProtected();
	}
	catch( ... ) {
		logger.printStack();
		logger.logDebug( "connectSocket: unexpected exception caught key=" + urlKey );
	}

	rfc_hnd_semunlock( lock );
	return( res );
}

void ActiveSocketConnection::exitSocket() {
	waitThreadFinished();
}

/*#########################################################################*/
/*#########################################################################*/

void ActiveSocketConnection::waitThreadFinished() {
	if( socketThread != NULL ) {
		ThreadService *ts = ThreadService::getService();
		ts -> waitThreadExited( socketThread );

		socketThread = NULL;
	}
}

String ActiveSocketConnection::getAddress() {
	SocketUrl url( urlKey );
	String host = url.getHost();
	int port = url.getPort();
	return( host + ":" + port );
}

bool ActiveSocketConnection::connectSocketProtected() {
	if( connected )
		return( true );

	rfc_hnd_semlock( lock );
	try {
		SocketUrl su( urlKey );
		socketHandle = protocol.open( su , &addr );

		// start reading thread
		ThreadService *ts = ThreadService::getService();
		socketThread = ts -> runThread( Object::getLoggerName() , this , ( ObjectThreadFunction )&ActiveSocketConnection::readSocketThread , NULL );

		logger.logDebug( "connectSocketProtected: successfully connected to urlKey=" + urlKey );
		connected = true;
	}
	catch( RuntimeException& e ) {
		rfc_hnd_semunlock( lock );
		logger.printStack( e );
		ASSERTFAILED( "connectSocketProtected: runtime exception, urlkey=" +  urlKey );
	}

	return( true );
}

void ActiveSocketConnection::disconnectSocket() {
	rfc_hnd_semlock( lock );
	if( connected ) {
		connected = false;

		_closesocket( socketHandle );
		socketHandle = INVALID_SOCKET;

		logger.logInfo( "disconnectSocket: disconnected key=" + urlKey );
	}
	rfc_hnd_semunlock( lock );
}

void ActiveSocketConnection::handleBrokenConnection() {
	if( !shutdownInProgress )
		disconnectSocket();
}

void ActiveSocketConnection::closeSocket() {
	// signal to thread
	shutdownInProgress = true;
	disconnectSocket();
}

void ActiveSocketConnection::sendText( SocketUrl& url , String text ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "receiveText: unable to connect urlkey=" + urlKey );

	bool connectionClosed;
	protocol.writeMessage( socketHandle , text , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
		logger.logInfo( "sendText: sent message to socket: text=" + text );
}

String ActiveSocketConnection::receiveText( SocketUrl& url , bool wait ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "receiveText: unable to connect urlkey=" + urlKey );

	bool connectionClosed;
	String final;
	bool res = protocol.readMessage( socketHandle , final , wait , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
	if( res )
		logger.logInfo( "receiveText: received message from socket: text=" + final );

	if( !res )
		return( "" );

	return( final );
}

String ActiveSocketConnection::receiveFixedText( SocketUrl& url , int size , bool wait ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "receiveFixedText: unable to connect key=" + urlKey );

	bool connectionClosed;
	String final;
	bool res = protocol.readFixedSizeMessage( socketHandle , size , final , wait , connectionClosed );
	if( connectionClosed )
		handleBrokenConnection();
	else
	if( res )
		logger.logInfo( "receiveFixedText: received message from socket: text=" + final );

	if( !res )
		return( "" );

	return( final );
}

bool ActiveSocketConnection::waitReadSocket( SocketUrl& url , bool wait ) {
	// connect to external address
	if( !connected )
		ASSERTMSG( connectSocket() , "waitReadSocket: unable to connect key=" + urlKey );

	return( protocol.waitSocketData( socketHandle , wait ) );
}

void ActiveSocketConnection::readSocketThread( void *p_arg ) {
	while( !shutdownInProgress ) {
		if( !connected ) {
			// try to connect
			if( !connectSocket() ) {
				rfc_thr_sleep( reconnectionTimeoutSec );
				continue;
			}
		}

		// try reading
		bool connectionClosed;
		String final;
		bool res = protocol.readMessage( socketHandle , final , true , connectionClosed );
		if( connectionClosed ) {
			handleBrokenConnection();
			continue;
		}

		if( !res )
			continue;

		// write message to channel
		String msgid = pub -> publish( NULL , final );
		logger.logInfo( "readSocketThread: forwarded message from socket=" + urlKey + ", msgid=" + msgid + " to channel=" + pub -> name );
	}
}

