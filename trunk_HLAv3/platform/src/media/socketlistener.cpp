#include <ah_platform.h>
#include <ah_media_impl.h>

/*#########################################################################*/
/*#########################################################################*/

SocketListener::SocketListener( String p_name )
:	protocol( logger ) {
	name = p_name;
	lastConnectionId = 0;

	setInstance( p_name );
	attachLogger();
}

SocketListener::~SocketListener() {
	connections.destroy();
}

void SocketListener::setMsgType( Message::MsgType p_msgType ) {
	msgType = p_msgType;
}

Message::MsgType SocketListener::getMsgType() {
	return( msgType );
}

String SocketListener::getName() { 
	return( name ); 
}

void SocketListener::addListenerConnection( SocketConnection *connection ) {
	String key = getName() + "." + (++lastConnectionId);

	connections.add( key , connection );
	connection -> setListener( this );
	connection -> setName( key );
}

void SocketListener::stopListenerConnections() {
	for( int k = 0; k < connections.count(); k++ ) {
		SocketConnection *connection = connections.getClassByIndex( k );
		connection -> stopConnection();
	}
}

void SocketListener::removeListenerConnection( SocketConnection *connection ) {
	String key = connection -> getName();
	connections.remove( key );
}

void SocketListener::exitListenerConnections() {
	for( int k = 0; k < connections.count(); k++ ) {
		SocketConnection *connection = connections.getClassByIndex( k );
		connection -> exitConnection();
	}
}

