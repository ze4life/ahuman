
#include "aiio_impl.h"

const char *AIChannel::NAME = "AIChannel";

/*#########################################################################*/
/*#########################################################################*/

static 	unsigned		__stdcall threadChannelFunction( void *p_arg )
{
	AIChannel *channel = ( AIChannel * )p_arg;

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
AIChannel::AIChannel( String p_msgid , String p_name , bool p_sync )
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

AIChannel::~AIChannel()
{
	close();
	rfc_lock_destroy( channelLock );

	if( messages != NULL )
		delete messages;
}

/*#########################################################################*/
/*#########################################################################*/

String AIChannel::getName()
{
	return( name );
}

void AIChannel::open()
{
	lock();
	if( opened )
		{
			unlock();
			return;
		}

	messages = new AIIOQueue( Object::getInstance() );

	// create channel thread
	if( !sync )
		{
			AIEngine& engine = AIEngine::getInstance();
			engine.workerCreated();
			if( rfc_thr_process( &threadID , ( void * )this , threadChannelFunction ) )
				{
					run = false;
					logger.logError( "AIChannel::open - cannot start listening thread" );
					engine.workerExited( threadID , -10 );
					unlock();
					return;
				}
		}

	opened = true;
	unlock();
}

void AIChannel::close()
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

String AIChannel::publish( AIPublisherImpl *pub , const char *msg )
{
	ASSERT( opened );
	AIMessage *l_msg = new AIMessage;
	String id = l_msg -> id = getNewMessageId();

	l_msg -> message = msg;
	l_msg -> type = pub -> msgtype;
	l_msg -> source = pub -> name;

	if( sync )
		{
			subscribeEvent( l_msg );
			delete l_msg;
		}
	else
		messages -> addMessage( l_msg );

	return( id );
}

String AIChannel::publish( AIPublisherImpl *pub , Xml xml , const char *type )
{
	ASSERT( opened );
	AIMessage *l_msg = new AIMessage;
	String id = l_msg -> id = getNewMessageId();

	l_msg -> message = xml.serialize();
	l_msg -> type = type;
	l_msg -> source = pub -> name;

	if( sync )
		{
			subscribeEvent( l_msg );
			delete l_msg;
		}
	else
		messages -> addMessage( l_msg );

	return( id );
}

void AIChannel::addSubscription( String key , AISubscriptionImpl *sub )
{
	lock();
	ASSERT( subs.get( key ) == NULL );
	subs.add( key , sub );
	unlock();
}

void AIChannel::deleteSubscription( String key )
{
	lock();
	AISubscription *sub = subs.get( key );
	if( sub != NULL )
		subs.remove( key );
	unlock();
}

void AIChannel::addPublisher( String key , AIPublisherImpl *pub )
{
	lock();
	AIPublisher *tmp = pubs.get( key );
	if( tmp != NULL )
		{
			unlock();
			ASSERT( false );
			return;
		}

	pubs.add( key , pub );
	unlock();
}

void AIChannel::deletePublisher( String key )
{
	lock();
	AIPublisher *pub = pubs.get( key );
	if( pub != NULL )
		pubs.remove( key );
	unlock();
}

// executing in separate thread
void AIChannel::processMessages()
{
	opened = true;
	run = true;

	logger.logInfo( String( "CHANNEL ID=" ) + Object::getInstance() + ": opened" );
	while( run ) 
		{
			// get next message
			AIMessage *message = messages -> getNextMessage();
			if( message == NULL )
				break;

			// log
			logger.logInfo( String( "CHANNEL ID=" ) + Object::getInstance() + ": extracted message ID=" + message -> id );

			// pass message
			subscribeEvent( message );
			delete message;
		}

	logger.logInfo( String( "CHANNEL: ID=" ) + Object::getInstance() + ": closed" );
}

/*#########################################################################*/
/*#########################################################################*/

void AIChannel::subscribeEvent( AIMessage *p_msg )
{
	lock();
	for( int k = 0; k < subs.count(); k++ )
		{
			AISubscriptionImpl *sub = subs.getClassByIndex( k );
			sub -> sub -> onMessage( p_msg );
		}
	unlock();
}

void AIChannel::lock()
{
	rfc_lock_shared( channelLock );
}

void AIChannel::unlock()
{
	rfc_lock_release( channelLock );
}

String AIChannel::getNewMessageId()
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

void AIChannel::disconnectSubscriptions()
{
	for( int k = 0; k < subs.count(); k++ )
		{
			AISubscriptionImpl *sub = subs.getClassByIndex( k );
			sub -> disconnected();
		}
	subs.clear();
}

void AIChannel::disconnectPublishers()
{
	for( int k = 0; k < pubs.count(); k++ )
		{
			AIPublisherImpl *pub = pubs.getClassByIndex( k );
			pub -> disconnected();
		}
	pubs.clear();
}
