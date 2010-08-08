
#include "io_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIIO::AIIO() 
{ 
	thisPtr = static_cast<AIIOImpl *>( AIEngine::getInstance().getService( "IO" ) );
}

/* static */ Service *AIIO::newService()
{
	Service *svc = new AIIOImpl();
	AIEngine::getInstance().registerService( svc , "IO" );
	return( svc );
}

AIIOImpl::AIIOImpl() 
:	engine( AIEngine::getInstance() )
{ 
	dataLock = rfc_lock_create();
	lastSessionId = 0;
}

void AIIOImpl::createService()
{
	// create all channels
	Xml topics = config.getChildNode( "topics" );
	for( Xml topic = topics.getFirstChild( "topic" ); topic.exists(); topic = topic.getNextChild( "topic" ) )
		createChannel( topic );
}

void AIIOImpl::initService()
{
}

void AIIOImpl::runService()
{
	openAllChannels();
}

void AIIOImpl::exitService()
{
	closeAllChannels();
}

void AIIOImpl::destroyService()
{
	rfc_lock_destroy( dataLock );
	mapChannels.destroy();
	sessions.destroy();

	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

Session *AIIOImpl::createSession()
{
	lock();
	SessionImpl *session = new SessionImpl( ++lastSessionId );
	sessions.add( session -> getSessionId() , session );
	unlock();

	return( session );
}

void AIIOImpl::closeSession( Session *session )
{
	lock();
	int id = session -> getSessionId();
	sessions.removeByKey( id );
	unlock();

	delete session;
}

Publisher *AIIOImpl::createPublisher( Session *session , String channel , String pubName , String msgtype )
{
	Channel *ch = getChannel( channel );
	PublisherImpl *pub = new PublisherImpl( session , ch , pubName , msgtype );

	ch -> addPublisher( pubName , pub );
	logger.logInfo( pubName + " publisher started on " + channel + " channel" );

	return( pub );
}

Subscription *AIIOImpl::subscribe( Session *session , String channel , String subName , Subscriber *subHandler )
{
	Channel *ch = getChannel( channel );
	SubscriptionImpl *sub = new SubscriptionImpl( session , ch , subName , subHandler );

	ch -> addSubscription( subName , sub );
	logger.logInfo( subName + " subscriber started on " + channel + " channel" );
	
	return( sub );
}

bool AIIOImpl::destroyPublisher( Publisher *publisher )
{
	PublisherImpl *pub = ( PublisherImpl * )publisher;
	Channel *ch = pub -> channel;

	String name = pub -> name;
	if( ch != NULL )
		{
			ch -> deletePublisher( name );
			logger.logInfo( name + " publisher stopped on " + ch -> getName() + " channel" );
		}

	delete pub;
	return( true );
}

bool AIIOImpl::unsubscribe( Subscription *subscription )
{
	SubscriptionImpl *sub = ( SubscriptionImpl * )subscription;
	Channel *ch = sub -> channel;

	if( ch != NULL )
		{
			ch -> deleteSubscription( sub -> name );
			logger.logInfo( sub -> name + " subscriber unsubscribed from " + ch -> getName() + " channel" );
		}
	delete sub;
	return( true );
}

/*#########################################################################*/
/*#########################################################################*/

Channel *AIIOImpl::createChannel( Xml config )
{
	String name = config.getAttribute( "name" );
	String msgid = config.getProperty( "msgid" );
	bool auth = config.getBooleanProperty( "auth" );
	bool sync = config.getBooleanProperty( "sync" );

	Channel *channel = new Channel( msgid , name , sync );
	
	ASSERT( auth == false );

	mapChannels.add( name , channel );
	return( channel );
}

Channel *AIIOImpl::getChannel( String name )
{
	lock();
	Channel *channel = mapChannels.get( name );
	unlock();
	ASSERTMSG( channel != NULL , String( "Channel does not exist: [" ) + name + "]" );

	return( channel );
}

void AIIOImpl::lock()
{
	rfc_lock_shared( dataLock );
}

void AIIOImpl::unlock()
{
	rfc_lock_release( dataLock );
}

void AIIOImpl::openAllChannels()
{
	lock();

	// close all channels
	for( int k = 0; k < mapChannels.count(); k++ )
		{
			Channel *channel = mapChannels.getClassByIndex( k );

			// close given channel
			channel -> open();
		}

	unlock();
}

void AIIOImpl::closeAllChannels()
{
	lock();

	// close all channels
	for( int k = 0; k < mapChannels.count(); k++ )
		{
			Channel *channel = mapChannels.getClassByIndex( k );

			// close given channel
			channel -> close();
		}

	unlock();
}
