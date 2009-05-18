
#include <aiio_impl.h>

/*#########################################################################*/
/*#########################################################################*/

// sync queue
// class AIIOQueue 
AIIOQueue::AIIOQueue( const char *p_queueId )
:	engine( AIEngine::getInstance() )
{
	queueId = p_queueId;
	queueMessageId = 0;
	queueLock = rfc_lock_create();
	queueWakeupEvent = rfc_hnd_evcreate();
	queueMessages = rfc_lst_create( RFC_EXT_TYPEPTR );

	logger.attach( this );
}

AIIOQueue::~AIIOQueue()
{
	// delete all pending messages
	rfc_lock_exclusive( queueLock );
	clearMessages();
	rfc_lst_destroy( queueMessages );
	rfc_hnd_evdestroy( queueWakeupEvent );
	rfc_lock_destroy( queueLock );
}

void AIIOQueue::addMessage( AIMessage *p_str )
{
	rfc_lock_exclusive( queueLock );

	// assign message number
	String msgId = queueId;
	msgId += ":";
	char l_buf[ 10 ];
	sprintf( l_buf , "%d" , ++queueMessageId );
	msgId += l_buf;
	p_str -> setId( msgId );

	// log
	logger.logInfo( String( "QUEUE: add message=" ) + p_str -> getId() );

	// add to list
	RFC_TYPE val;
	val.u_p = p_str;
	rfc_lst_add( queueMessages , &val );

	// signal for waiter and release lock
	rfc_hnd_evsignal( queueWakeupEvent );
	logger.logInfo( "signal on" );
	rfc_lock_release( queueLock );
}	

AIMessage *AIIOQueue::getNextMessage()
{
	rfc_lock_exclusive( queueLock );
	
	// check if no message
	if( rfc_lst_count( queueMessages ) == 0 ) {
		// wait for signal
		logger.logInfo( "found zero records " );
		rfc_lock_release( queueLock );
		logger.logInfo( "start wait event..." );
		rfc_hnd_waitevent( queueWakeupEvent );
		logger.logInfo( "event found" );

		// lock again and reset event
		rfc_lock_exclusive( queueLock );

		// check if no messages
		if( rfc_lst_count( queueMessages ) == 0 ) {
			// return empty message
			logger.logInfo( "empty message queue detected, exiting..." );
			rfc_lock_release( queueLock );
			return( NULL );
		}
	}

	// get first item
	RFC_TYPE *val = rfc_lst_get( queueMessages , 0 );
	AIMessage *x = ( AIMessage * )val -> u_p;

	// remove from queue
	rfc_lst_remove( queueMessages , 0 );
	logger.logInfo( String( "removed message from queue: " ) + x -> getId() );

	// signal off if no records remained
	if( rfc_lst_count( queueMessages ) == 0 ) {
		logger.logInfo( "set signal off" );
		rfc_hnd_evreset( queueWakeupEvent );
	}

	// unlock and return
	rfc_lock_release( queueLock );
	return( x );
}

AIMessage *AIIOQueue::getNextMessageNoLock()
{
	logger.logInfo( "unexpected shared lock" );

	rfc_lock_shared( queueLock );
	
	// check if no message
	if( rfc_lst_count( queueMessages ) == 0 ) {
		rfc_lock_release( queueLock );
		return( NULL );
	}

	// make exclusive lock
	rfc_lock_escalate( queueLock );

	// get first item
	RFC_TYPE *val = rfc_lst_get( queueMessages , 0 );
	AIMessage *x = ( AIMessage * )val -> u_p;

	// remove from queue
	rfc_lst_remove( queueMessages , 0 );

	// unlock and return
	rfc_lock_release( queueLock );
	return( x );
}

void AIIOQueue::makeEmptyAndWakeup()
{
	rfc_lock_exclusive( queueLock );
	// remove all messages
	clearMessages();
	logger.logInfo( "clear messages" );
	// signal for waiter and release lock
	rfc_hnd_evsignal( queueWakeupEvent );
	logger.logInfo( "signal on" );

	rfc_lock_release( queueLock );
}

bool AIIOQueue::isEmpty()
{
	rfc_lock_shared( queueLock );
	// signal for waiter and release lock
	bool retval = ( rfc_lst_count( queueMessages ) > 0 )? true : false;
	rfc_lock_release( queueLock );

	return( retval );
}

void AIIOQueue::clearMessages()
{
	for( int k = rfc_lst_count( queueMessages ) - 1; k >= 0; k-- ) 
		{
			AIMessage *x = ( AIMessage * )rfc_lst_get( queueMessages , k );
			io.destroyMessage( x );
		}
	rfc_lst_clear( queueMessages );
}

