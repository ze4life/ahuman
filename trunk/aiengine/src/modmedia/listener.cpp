#include "media_impl.h"

/*#########################################################################*/
/*#########################################################################*/

Listener::Listener()
{
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

void Listener::setName( String p_name )
{ 
	name = p_name; 
}

String Listener::getName() 
{ 
	return( name ); 
}

void Listener::addListenerConnection( Connection *connection )
{
	String key = getName() + "." + (++lastConnectionId);

	connections.add( key , connection );
	connection -> setListener( this );
	connection -> setName( key );
}

void Listener::stopListenerConnections()
{
	for( int k = 0; k < connections.count(); k++ )
		{
			Connection *connection = connections.getClassByIndex( k );
			connection -> stopConnection();
		}
}

void Listener::destroyListenerConnection( Connection *connection )
{
	String key = connection -> getName();
	connections.remove( key );
	delete connection;
}

