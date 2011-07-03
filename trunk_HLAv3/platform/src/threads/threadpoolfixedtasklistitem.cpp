#include <ah_platform.h>
#include <ah_threads_impl.h>

/*#########################################################################*/
/*#########################################################################*/

ThreadPoolFixedTaskListItem::ThreadPoolFixedTaskListItem( String p_name , int p_threadPoolItem , ClassList<ThreadPoolTask>& p_tasks )
:	ThreadPoolItem( p_name , p_threadPoolItem ) {

	// assign task list
	for( int k = 0; k < p_tasks.count(); k++ ) {
		ThreadPoolTask *task = p_tasks.get( k );
		task -> thread = this;
		tasks.add( task );
	}
}

void ThreadPoolFixedTaskListItem::run( void *p_arg ) {
	// cycled queue
	int currentTask = 0;

	int executionTimeWindowMs = ( int )( ( 1000. * executionTimeWindowTicks ) / ticksPerSecond );
	logger.logInfo( String( "run: thread started - executionTimeWindowMs=" ) + executionTimeWindowMs );

	while( !stopSignal ) {
		// ensure run enabled
		rfc_hnd_waitevent( runEvent , -1 );

		if( tasks.count() == 0 )
			break;

		// get execution object
		ThreadPoolTask *task = tasks.get( currentTask );
		if( !task -> needExecution() ) {
			if( task -> finished() )
				tasks.remove( currentTask );
		}
		else {
			// execute one operation
			execute( task );

			// switch to next object
			currentTask++;
		}

		// ensure current task is valid
		if( currentTask == tasks.count() )
			currentTask = 0;

		if( suspendSignal ) {
			// notify stopped
			rfc_hnd_evsignal( suspendEvent );
			logger.logInfo( String( "run: thread suspended" ) );

			// wait till resumed
			rfc_hnd_waitevent( runEvent , -1 );
			if( !stopSignal )
				logger.logInfo( String( "run: thread resumed" ) );

			// next cycle
			rfc_hnd_evreset( suspendEvent );
		}
	}

	thread = NULL;
	state.setState( ThreadState::THREAD_STATE_CREATED );
	logger.logInfo( String( "run: thread stopped" ) );
}

