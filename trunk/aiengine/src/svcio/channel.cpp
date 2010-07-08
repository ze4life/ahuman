
#include "io_impl.h"

const char *Channel::NAME = "Channel";

/*#########################################################################*/
/*#########################################################################*/

static 	unsigned		__stdcall threadChannelFunction( void *p_arg )
{
	Channel *channel = ( Channel * )p_arg;

	String name = channel -> getInstance();
	Logger& logger = channel -> getLogger();
	AIEngine& engine = AIEngine::getInstance();
	engine.workerStarted();
	
	int status = 0;
	try {
		channel -> processMessages();
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
		status = -12;
	}
	catch ( ... ) {
		logger.logError( String( "threadChannelFunction: unknown exception, channel=" ) + name );
		logger.printStack();
		status = -13;
	}

	engine.workerExited( status );
	return( status );
}

/*#########################################################################*/
/*#########################################################################*/

// input/output messages
// class AIIODuplexChannel
Channel::Channel( String p_msgid , String p_name , bool p_sync )
{
	Object::setInstance( p_msgid );

	name = p_name;

	opened = false;
	sync = p_sync;
	run = false;
	queueMessageId = 0;

	memset( &threadID , 0 , sizeof( RFC_THREAD ) );
	
	messages = NULL;
	logger.attach( this );
	channelLock = rfc_lock_create();
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

void Channel::open()
{
	lock();
	if( opened )
		{
			unlock();
			return;
		}

	messages = new IOQueue( Object::getInstance() );

	// create channel thread
	if( !sync )
		{
			AIEngine& engine = AIEngine::getInstance();
			engine.workerCreated();
			if( rfc_thr_process( &threadID , ( void * )this , threadChannelFunction ) )
				{
					run = false;
					logger.logError( "Channel::open - cannot start listening thread" );
					engine.workerExited( threadID , -10 );
					unlock();
					return;
				}
		}

	opened = true;
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

	opened = false;
	if( !sync )
		{
			// stop thread
			run = false;
			messages -> makeEmptyAndWakeup();

			rfc_thr_waitexit( &threadID );
			memset( &threadID , 0 , sizeof( RFC_THREAD ) );
		}
			
	if( messages != NULL )
		messages -> makeEmptyAndWakeup();

	// clear subscribers and publishers
	disconnectSubscriptions();
	disconnectPublishers();
	unlock();
}

String Channel::publish( Session *p_session , PublisherImpl *pub , const char *msg )
{
	Message *l_msg = new Message;
	l_msg -> setText( msg );
	l_msg -> setType( pub -> msgtype );
	return( publish( p_session , pub , l_msg ) );
}

String Channel::publish( Session *p_session , PublisherImpl *pub , Message *msg )
{
	ASSERT( opened );
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
	ASSERT( opened );
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
	opened = true;
	run = true;

	logger.logInfo( String( "CHANNEL ID=" ) + Object::getInstance() + ": opened" );
	while( run ) 
		{
			// get next message
			Message *message = messages -> getNextMessage();
			if( message == NULL )
				break;

			// log
			logger.logInfo( String( "CHANNEL ID=" ) + Object::getInstance() + ": extracted message ID=" + message -> getChannelMessageId() );

			// pass message
			subscribeEvent( message );
			delete message;
		}

	logger.logInfo( String( "CHANNEL: ID=" ) + Object::getInstance() + ": closed" );
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

			if( l_sub_session == NULL || l_session == l_sub_session )
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
