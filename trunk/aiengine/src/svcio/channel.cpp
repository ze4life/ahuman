
#include "io_impl.h"

const char *Channel::NAME = "IOChannel";

/*#########################################################################*/
/*#########################################################################*/

// input/output messages
// class AIIODuplexChannel
Channel::Channel( String p_msgid , String p_name , bool p_sync )
{
	name = p_name;

	opened = false;
	sync = p_sync;
	run = false;
	queueMessageId = 0;

	messages = NULL;
	channelLock = rfc_lock_create();

	Object::setInstance( name );
}

Channel::~Channel()
{
	close();
	rfc_lock_destroy( channelLock );

	if( messages != NULL )
		delete messages;
}

/*#########################################################################*/
/*#########################################################################*/

String Channel::getName()
{
	return( name );
}

void Channel::threadChannelFunction( void *p_arg )
{
	processMessages();
}

void Channel::open()
{
	logger.attach( this );

	lock();
	if( opened )
		{
			unlock();
			return;
		}

	messages = new IOQueue( Object::getInstance() );
	opened = true;
}

void Channel::start()
{
	// create channel thread
	lock();
	if( !sync )
		{
			AIEngine& engine = AIEngine::getInstance();
			channelThread = engine.runThread( name ,  this , ( ObjectThreadFunction )&Channel::threadChannelFunction , NULL );
		}

	run = true;
	unlock();
}

void Channel::close()
{
	lock();
	if( !opened )
		{
			unlock();
			return;
		}

	// close queue and cleanup
	opened = false;
	run = false;
	if( messages != NULL )
		messages -> makeEmptyAndWakeup();

	if( !sync )
		{
			// stop thread
			AIEngine& engine = AIEngine::getInstance();
			engine.waitThreadExited( channelThread );
			channelThread = NULL;
		}

	// clear subscribers and publishers
	disconnectSubscriptions();
	disconnectPublishers();
	unlock();
}

String Channel::publish( Session *p_session , PublisherImpl *pub , const char *msg )
{
	TextMessage *l_msg = new TextMessage( pub -> msgtype );
	l_msg -> setText( msg );
	return( publish( p_session , pub , l_msg ) );
}

String Channel::publish( Session *p_session , PublisherImpl *pub , Message *msg )
{
	ASSERTMSG( opened , "cannot publish to i/o channel name=" + name + " - not open" );
	if( sync )
		ASSERTMSG( run , "cannot publish to sync i/o channel name=" + name + " - not started" );

	String id = getNewMessageId();
	msg -> setChannelMessageId( id ); 
	msg -> setSourceId( pub -> name );
	msg -> setSession( p_session );

	if( sync )
		{
			subscribeEvent( msg );
			delete msg;
		}
	else
		messages -> addMessage( msg );

	return( id );
}

String Channel::publish( Session *p_session , Message *msg )
{
	ASSERTMSG( opened , "cannot publish to i/o channel name=" + name + " - not open" );
	if( sync )
		ASSERTMSG( run , "cannot publish to sync i/o channel name=" + name + " - not started" );

	String id = getNewMessageId();
	msg -> setChannelMessageId( id ); 
	msg -> setSession( p_session );

	if( sync )
		{
			subscribeEvent( msg );
			delete msg;
		}
	else
		messages -> addMessage( msg );

	return( id );
}

void Channel::addSubscription( String key , SubscriptionImpl *sub )
{
	lock();
	ASSERT( subs.get( key ) == NULL );
	subs.add( key , sub );
	unlock();
}

void Channel::deleteSubscription( String key )
{
	lock();
	Subscription *sub = subs.get( key );
	if( sub != NULL )
		subs.remove( key );
	unlock();
}

void Channel::addPublisher( String key , PublisherImpl *pub )
{
	lock();
	Publisher *tmp = pubs.get( key );
	if( tmp != NULL )
		{
			unlock();
			ASSERT( false );
			return;
		}

	pubs.add( key , pub );
	unlock();
}

void Channel::deletePublisher( String key )
{
	lock();
	Publisher *pub = pubs.get( key );
	if( pub != NULL )
		pubs.remove( key );
	unlock();
}

// executing in separate thread
void Channel::processMessages()
{
	logger.logInfo( String( "processMessages: i/o channel opened id=" ) + Object::getInstance() );
	while( run ) 
		{
			// get next message
			Message *message = messages -> getNextMessage();
			if( message == NULL )
				break;

			// log
			logger.logInfo( String( "processMessages: message extracted from i/o channel id=" ) + Object::getInstance() + ", channelMessageId=" + message -> getChannelMessageId() );

			// pass message
			subscribeEvent( message );
			delete message;
		}

	logger.logInfo( String( "processMessages: i/o channel closed id=" ) + Object::getInstance() );
}

/*#########################################################################*/
/*#########################################################################*/

void Channel::subscribeEvent( Message *p_msg )
{
	lock();
	Session *l_session = p_msg -> getSession();
	for( int k = 0; k < subs.count(); k++ )
		{
			SubscriptionImpl *sub = subs.getClassByIndex( k );
			Session *l_sub_session = sub -> session;
			//TODO: Sarbjit: Not sure how to get over this
			//if( l_sub_session == NULL || l_session == l_sub_session )
				sub -> processMessage( p_msg );
		}
	unlock();

	// after all executions
	p_msg -> postExecute();
}

void Channel::lock()
{
	rfc_lock_shared( channelLock );
}

void Channel::unlock()
{
	rfc_lock_release( channelLock );
}

String Channel::getNewMessageId()
{
	// assign message number
	String msgId = Object::getInstance();
	msgId += "-";
	char l_buf[ 10 ];

	int id = rfc_thr_increment( &queueMessageId );
	sprintf( l_buf , "%d" , id );
	msgId += l_buf;
	
	return( msgId );
}

void Channel::disconnectSubscriptions()
{
	for( int k = 0; k < subs.count(); k++ )
		{
			SubscriptionImpl *sub = subs.getClassByIndex( k );
			sub -> disconnected();
		}
	subs.clear();
}

void Channel::disconnectPublishers()
{
	for( int k = 0; k < pubs.count(); k++ )
		{
			PublisherImpl *pub = pubs.getClassByIndex( k );
			pub -> disconnected();
		}
	pubs.clear();
}

