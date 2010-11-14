#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

Listener::Listener( String p_name )
:	protocol( logger )
{
	name = p_name;
	lastConnectionId = 0;
}

Listener::~Listener()
{
	connections.destroy();
}

void Listener::setMsgType( Message::MsgType p_msgType )
{
	msgType = p_msgType;
}

Message::MsgType Listener::getMsgType()
{
	return( msgType );
}

String Listener::getName() 
{ 
	return( name ); 
}

void Listener::addListenerConnection( SocketConnection *connection )
{
	String key = getName() + "." + (++lastConnectionId);

	connections.add( key , connection );
	connection -> setListener( this );
	connection -> setName( key );
}

void Listener::stopListenerConnections()
{
	for( int k = 0; k < connections.count(); k++ ) {
		SocketConnection *connection = connections.getClassByIndex( k );
		connection -> stopConnection();
	}
}

void Listener::removeListenerConnection( SocketConnection *connection )
{
	String key = connection -> getName();
	connections.remove( key );
}
