
#include "aimedia_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIMedia::AIMedia() 
{ 
	thisPtr = static_cast<AIMediaImpl *>( AIEngine::getInstance().getService( "Media" ) ); 
}

/* static */ Service *AIMedia::createService()
{
	Service *svc = new AIMediaImpl();
	AIEngine::getInstance().registerService( svc , "Media" );
	return( svc );
}

AIMediaImpl::AIMediaImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIMediaImpl::initService()
{
	SocketServer::initSocketLib();
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
	SocketServer::exitSocketLib();

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
			Listener *listener = runListenerFactory( name , type );
			listener -> configure( item );

			// start
			ASSERTMSG( listener -> startListener() , 
				"AIMediaImpl::startListeners: cannot start listener " + name );
			logger.logInfo( name + " listener started at " + listener -> getAddress() );
		}
}

Listener *AIMediaImpl::runListenerFactory( String name , String type )
{
	ASSERT( listeners.get( name ) == NULL );
	ASSERT( type.equals( "tcp" ) );

	Listener *listener = new SocketServer();
	listener -> setName( name );
	listeners.add( name , listener );

	return( listener );
}

void AIMediaImpl::stopListeners()
{
	for( int k = 0; k < listeners.count(); k++ )
		{
			Listener *listener = listeners.getClassByIndex( k );
			listener -> stopListener();
			listener -> stopListenerConnections();
		}
}

