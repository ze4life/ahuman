#include "aimedia_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIListener::AIListener()
{
}

AIListener::~AIListener()
{
	connections.destroy();
}

void AIListener::setName( String p_name )
{ 
	name = p_name; 
}

String AIListener::getName() 
{ 
	return( name ); 
}

void AIListener::addListenerConnection( String key , AIConnection *connection )
{
	connections.add( key , connection );
	connection -> setListener( this );
	connection -> setID( key );
}

void AIListener::stopListenerConnections()
{
	for( int k = 0; k < connections.count(); k++ )
		{
			AIConnection *connection = connections.getClassByIndex( k );
			connection -> stopConnection();
		}
}
