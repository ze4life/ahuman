
#include "aimedia_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIMedia::AIMedia() 
{ 
	thisPtr = static_cast<AIMediaImpl *>( AIEngine::getInstance().getService( "AIMedia" ) ); 
}

/* static */ Service *AIMedia::createService()
{
	Service *svc = new AIMediaImpl();
	AIEngine::getInstance().registerService( svc , "AIMedia" );
	return( svc );
}

AIMediaImpl::AIMediaImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIMediaImpl::initService()
{
	AISockServer::initSocketLib();
}

void AIMediaImpl::runService()
{
	startListeners();
}

void AIMediaImpl::exitService()
{
	stopListeners();
}

void AIMediaImpl::destroyService()
{
	AISockServer::exitSocketLib();

	listeners.destroy();
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

void AIMediaImpl::startListeners()
{
	// scan configuration
	Xml configListeners = config.getChildNode( "listeners" );
	for( Xml item = configListeners.getFirstChild( "listener" ); item.exists(); item = item.getNextChild( "listener" ) )
		{
			String name = item.getAttribute( "name" );
			String type = item.getAttribute( "type" );

			// create and configure
			AIListener *listener = runListenerFactory( name , type );
			listener -> configure( item );

			// start
			ASSERTMSG( listener -> startListener() , 
				"AIMediaImpl::startListeners: cannot start listener " + name );
		}
}

AIListener *AIMediaImpl::runListenerFactory( String name , String type )
{
	ASSERT( listeners.get( name ) == NULL );
	ASSERT( type.equals( "tcp" ) );

	AIListener *listener = new AISockServer();
	listener -> setName( name );
	listeners.add( name , listener );

	return( listener );
}

void AIMediaImpl::stopListeners()
{
	for( int k = 0; k < listeners.count(); k++ )
		{
			AIListener *listener = listeners.getClassByIndex( k );
			listener -> stopListener();
			listener -> stopListenerConnections();
		}
}

