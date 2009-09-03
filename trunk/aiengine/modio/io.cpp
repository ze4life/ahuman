
#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIIO::AIIO() 
{ 
	thisPtr = static_cast<AIIOImpl *>( AIEngine::getInstance().getService( "AIIO" ) ); 
}

/* static */ Service *AIIO::createService()
{
	Service *svc = new AIIOImpl();
	AIEngine::getInstance().registerService( svc , "AIIO" );
	return( svc );
}

AIIOImpl::AIIOImpl() 
:	engine( AIEngine::getInstance() )
{ 
	dataLock = rfc_lock_create();
}

void AIIOImpl::initService()
{
	// start all channels
	Xml topics = config.getChildNode( "topics" );
	for( Xml topic = topics.getFirstChild( "topic" ); topic.exists(); topic = topic.getNextChild( "topic" ) )
		createChannel( topic );
}

void AIIOImpl::runService()
{
}

void AIIOImpl::exitService()
{
	closeAllChannels();
}

void AIIOImpl::destroyService()
{
	rfc_lock_destroy( dataLock );
	mapChannels.destroy();

	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

AIPublisher *AIIOImpl::createPublisher( String channel , String pubName , String msgtype )
{
	AIChannel *ch = getChannel( channel );
	AIPublisherImpl *pub = new AIPublisherImpl( ch , pubName , msgtype );

	ch -> addPublisher( pubName , pub );

	AIIOImpl::logger.logInfo( String( "[" ) + pubName + "] publisher started on [" + channel + "] channel" );

	return( pub );
}

AISubscription *AIIOImpl::subscribe( String channel , String subName , AISubscriber *subHandler )
{
	AIChannel *ch = getChannel( channel );
	AISubscriptionImpl *sub = new AISubscriptionImpl( ch , subName , subHandler );

	ch -> addSubscription( subName , sub );
	logger.logInfo( String( "[" ) + subName + "] subscriber started on [" + channel + "] channel" );
	return( sub );
}

bool AIIOImpl::destroyPublisher( AIPublisher *publisher )
{
	AIPublisherImpl *pub = ( AIPublisherImpl * )publisher;
	AIChannel *ch = pub -> channel;

	String name = pub -> name;
	if( ch != NULL )
		{
			ch -> deletePublisher( name );
			logger.logInfo( String( "[" ) + name + "] publisher stopped on [" + ch -> getName() + "] channel" );
		}

	delete pub;
	return( true );
}

bool AIIOImpl::unsubscribe( AISubscription *subscription )
{
	AISubscriptionImpl *sub = ( AISubscriptionImpl * )subscription;
	AIChannel *ch = sub -> channel;

	if( ch != NULL )
		{
			ch -> deleteSubscription( sub -> name );
			logger.logInfo( String( "[" ) + sub -> name + "] subscriber unsubscribed from [" + ch -> getName() + "] channel" );
		}
	delete sub;
	return( true );
}

/*#########################################################################*/
/*#########################################################################*/

void AIIOImpl::createChannel( Xml config )
{
	String name = config.getAttribute( "name" );
	String msgid = config.getProperty( "msgid" );
	bool auth = config.getBooleanProperty( "auth" );
	bool sync = config.getBooleanProperty( "sync" );

	AIChannel *channel = new AIChannel( msgid , name , sync );
	
	ASSERT( auth == false );

	mapChannels.add( name , channel );
	channel -> open();
}

AIChannel *AIIOImpl::getChannel( String name )
{
	lock();
	AIChannel *channel = mapChannels.get( name );
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

void AIIOImpl::closeAllChannels()
{
	lock();

	// close all channels
	for( int k = 0; k < mapChannels.count(); k++ )
		{
			AIChannel *channel = mapChannels.getClassByIndex( k );

			// close given channel
			channel -> close();
		}

	unlock();
}
