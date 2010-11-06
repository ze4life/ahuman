/*#########################################################################
 * This class is the implementation of the queue data structure so that all
 * the messages from various sources can be added and processed later.
/*#########################################################################*/

#include "io_impl.h"

/* Define the name of the queue */
const char *IOQueue::NAME = "IOQueue";

/*#########################################################################
/*#########################################################################*/

/*
 * Constructer to create the instance of queue so that we can 
 * create a queue to append messages to.
 * @param queue ID
 */
IOQueue::IOQueue( String p_queueId )
:	engine( AIEngine::getInstance() )
{
	Object::setInstance( p_queueId );

	queueId = p_queueId;
	queueLock = rfc_lock_create();
	queueWakeupEvent = rfc_hnd_evcreate();
	/* Create a list to add messages of type pointer */
	queueMessages = rfc_lst_create( RFC_EXT_TYPEPTR );

	logger.attach( this );
}

/*
 * Destructor that clears all the messages from queue.
 */
IOQueue::~IOQueue()
{
	// delete all pending messages
	rfc_lock_exclusive( queueLock );
	clearMessages();
	rfc_lst_destroy( queueMessages );
	rfc_hnd_evdestroy( queueWakeupEvent );
	rfc_lock_destroy( queueLock );
}

/*
 * This function adds the message passed, to the queue.
 * @param Message Pointer
 */
void IOQueue::addMessage( Message *p_str )
{
	rfc_lock_exclusive( queueLock );

	// log
	logger.logInfo( String( "i/o addMessage: id=" ) + p_str -> getChannelMessageId() );

	// add to list
	RFC_TYPE val;
	val.u_p = p_str;
	rfc_lst_add( queueMessages , &val );

	// signal for waiter and release lock
	rfc_hnd_evsignal( queueWakeupEvent );
	logger.logDebug( "i/o addMessage: signal on" );
	rfc_lock_release( queueLock );
}	

/*
 * Gets the message from top of the queue.
 */
Message *IOQueue::getNextMessage()
{
	rfc_lock_exclusive( queueLock );
	
	// check if no message
	if( rfc_lst_count( queueMessages ) == 0 ) {
		// wait for signal
		logger.logDebug( "i/o getNextMessage: found zero records " );
		rfc_lock_release( queueLock );
		logger.logDebug( "i/o getNextMessage: start wait event..." );
		rfc_hnd_waitevent( queueWakeupEvent );
		logger.logDebug( "i/o getNextMessage: event found" );

		// lock again and reset event
		rfc_lock_exclusive( queueLock );

		// check if no messages
		if( rfc_lst_count( queueMessages ) == 0 ) {
			// return empty message
			logger.logInfo( "i/o getNextMessage: empty message queue detected, exiting..." );
			rfc_lock_release( queueLock );
			return( NULL );
		}
	}

	// get first item
	RFC_TYPE *val = rfc_lst_get( queueMessages , 0 );
	/* Get u_p type as the list that we created was of type pointer */
	Message *x = ( Message * )val -> u_p;

	// remove from queue
	rfc_lst_remove( queueMessages , 0 );
	logger.logDebug( String( "i/o getNextMessage: extracted message from queue: " ) + x -> getChannelMessageId() );

	// signal off if no records remained
	if( rfc_lst_count( queueMessages ) == 0 ) {
		logger.logDebug( "i/o getNextMessage: set signal off" );
		rfc_hnd_evreset( queueWakeupEvent );
	}

	// unlock and return
	rfc_lock_release( queueLock );
	return( x );
}

Message *IOQueue::getNextMessageNoLock()
{
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

/*
 * This API will clear all the messages and will send the wake up event
 */
void IOQueue::makeEmptyAndWakeup()
{
	rfc_lock_exclusive( queueLock );
	// remove all messages
	clearMessages();
	logger.logInfo( "i/o makeEmptyAndWakeup: clear messages" );
	// signal for waiter and release lock
	rfc_hnd_evsignal( queueWakeupEvent );
	logger.logDebug( "i/o makeEmptyAndWakeup: signal on" );

	rfc_lock_release( queueLock );
}

/*
 * Check to ses if the list has some messages or not.
 */
bool IOQueue::isEmpty()
{
	rfc_lock_shared( queueLock );
	// signal for waiter and release lock
	bool retval = ( rfc_lst_count( queueMessages ) > 0 )? true : false;
	rfc_lock_release( queueLock );

	return( retval );
}

/*
 * Delete all the messages from queue.
 */
void IOQueue::clearMessages()
{
	for( int k = rfc_lst_count( queueMessages ) - 1; k >= 0; k-- ) 
		{
			Message *x = ( Message * )rfc_lst_get( queueMessages , k );
			delete x;
		}
	rfc_lst_clear( queueMessages );
}
