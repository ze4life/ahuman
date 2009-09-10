
#include "aiio_impl.h"

const char *IOQueue::NAME = "IOQueue";

/*#########################################################################*/
/*#########################################################################*/

// sync queue
// class IOQueue 
IOQueue::IOQueue( String p_queueId )
:	engine( AIEngine::getInstance() )
{
	queueId = p_queueId;
	queueLock = rfc_lock_create();
	queueWakeupEvent = rfc_hnd_evcreate();
	queueMessages = rfc_lst_create( RFC_EXT_TYPEPTR );

	logger.attach( this );
}

IOQueue::~IOQueue()
{
	// delete all pending messages
	rfc_lock_exclusive( queueLock );
	clearMessages();
	rfc_lst_destroy( queueMessages );
	rfc_hnd_evdestroy( queueWakeupEvent );
	rfc_lock_destroy( queueLock );
}

void IOQueue::addMessage( Message *p_str )
{
	rfc_lock_exclusive( queueLock );

	// log
	logger.logInfo( String( "QUEUE: add message=" ) + p_str -> getChannelMessageId() );

	// add to list
	RFC_TYPE val;
	val.u_p = p_str;
	rfc_lst_add( queueMessages , &val );

	// signal for waiter and release lock
	rfc_hnd_evsignal( queueWakeupEvent );
	logger.logInfo( "signal on" );
	rfc_lock_release( queueLock );
}	

Message *IOQueue::getNextMessage()
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
	Message *x = ( Message * )val -> u_p;

	// remove from queue
	rfc_lst_remove( queueMessages , 0 );
	logger.logInfo( String( "removed message from queue: " ) + x -> getChannelMessageId() );

	// signal off if no records remained
	if( rfc_lst_count( queueMessages ) == 0 ) {
		logger.logInfo( "set signal off" );
		rfc_hnd_evreset( queueWakeupEvent );
	}

	// unlock and return
	rfc_lock_release( queueLock );
	return( x );
}

Message *IOQueue::getNextMessageNoLock()
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
	Message *x = ( Message * )val -> u_p;

	// remove from queue
	rfc_lst_remove( queueMessages , 0 );

	// unlock and return
	rfc_lock_release( queueLock );
	return( x );
}

void IOQueue::makeEmptyAndWakeup()
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

bool IOQueue::isEmpty()
{
	rfc_lock_shared( queueLock );
	// signal for waiter and release lock
	bool retval = ( rfc_lst_count( queueMessages ) > 0 )? true : false;
	rfc_lock_release( queueLock );

	return( retval );
}

void IOQueue::clearMessages()
{
	for( int k = rfc_lst_count( queueMessages ) - 1; k >= 0; k-- ) 
		{
			Message *x = ( Message * )rfc_lst_get( queueMessages , k );
			delete x;
		}
	rfc_lst_clear( queueMessages );
}

