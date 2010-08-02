#include "brain_impl.h"

ActiveMemoryThread::ActiveMemoryThread( int id , ClassList<ActiveMemoryObject>& objects )
:	engine( AIEngine::getInstance() )
{
	thread = ( RFC_HND )NULL;
	threadId = id;

	runEvent = rfc_hnd_evcreate();
	suspendEvent = rfc_hnd_evcreate();
	suspendSignal = true;
	stopSignal = false;
	rfc_hnd_evreset( runEvent );
	rfc_hnd_evsignal( suspendEvent );

	executeObjects.create( objects );

	msPerOperation = 0;
	reportGroup = 0;
	dynamicOperationTime = false;

	msExecTimeTotal = 0;
	msSleepTimeTotal = 0;
	msWaitTimeRemained = 0;
	ratioExecutionByOperation = 0;
	nRatioOperations = 0;
}

ActiveMemoryThread::~ActiveMemoryThread()
{
	rfc_hnd_evdestroy( runEvent );
	rfc_hnd_evdestroy( suspendEvent );
}

String ActiveMemoryThread::getName()
{
	return( name );
}

void ActiveMemoryThread::create()
{
	// start thread
	name = String( "AMT" ) + threadId;
	thread = engine.runThread( name , this , ( ObjectFunction )&ActiveMemoryThread::run , NULL );
}

void ActiveMemoryThread::suspend()
{
	rfc_hnd_evreset( runEvent );
	suspendSignal = true;
	rfc_hnd_waitevent( suspendEvent );
}

void ActiveMemoryThread::resume()
{
	suspendSignal = false;
	rfc_hnd_evsignal( runEvent );
}

void ActiveMemoryThread::stop()
{
	stopSignal = true;
	rfc_hnd_evsignal( runEvent );
	if( thread != ( RFC_HND )NULL ) {
		engine.waitThreadExited( thread );
		thread = NULL;
	}
}

void ActiveMemoryThread::run( void *p_arg )
{
	// cycled queue
	int currentObject = 0;

	logger.attach( name );
	logger.logInfo( String( "Thread started: msPerOperation=" ) + msPerOperation +
		", reportGroup=" + reportGroup );

	while( !stopSignal ) {
		// ensure run enabled
		rfc_hnd_waitevent( runEvent );

		// get execution object
		ActiveMemoryObject *object = executeObjects.get( currentObject );

		// execute one operation
		execute( object );

		// switch to next object
		currentObject++;
		if( currentObject == executeObjects.count() )
			currentObject = 0;

		if( suspendSignal ) {
			// notify stopped
			rfc_hnd_evsignal( suspendEvent );
			logger.logInfo( String( "Thread suspended" ) );

			// wait till resumed
			rfc_hnd_waitevent( runEvent );
			if( !stopSignal )
				logger.logInfo( String( "Thread resumed" ) );

			// next cycle
			rfc_hnd_evreset( suspendEvent );
		}
	}

	logger.logInfo( String( "Thread stopped" ) );
}

void ActiveMemoryThread::execute( ActiveMemoryObject *object )
{
	// execute and measure execution time (in milliseconds)
	Timer t;
	object -> execute();
	int executeTime = t.timePassed();

	// to calculate current execute/sleep ratio
	msExecTimeTotal += executeTime;

	// calculate sleep time for this opeation (can be negative!)
	int opSleepTime = msPerOperation - executeTime;

	// add to pending sleep time
	msWaitTimeRemained += opSleepTime;
	nRatioOperations++;

	// if sleep time is less than second - do nothing
	if( msWaitTimeRemained < 1000 ) {
		logger.logInfo( "non-sleep execute operation=" + object -> getName() + 
			", nRatioOperations=" + nRatioOperations +
			", executeTime=" + executeTime +
			", opSleepTime=" + opSleepTime + 
			", msWaitTimeRemained=" + msWaitTimeRemained );

		// if negative and synamic mode - decrease speed
		if( dynamicOperationTime && msWaitTimeRemained < 0 )
			decreaseSpeed( 2 );

		return;
	}
	
	// get whole number of seconds to sleep (probably always will be 1) and sleep
	int sleepSeconds = msWaitTimeRemained / 1000;
	rfc_thr_sleep( sleepSeconds );
	int sleepTime = t.timePassed() - executeTime;
	msSleepTimeTotal += sleepTime;
	msWaitTimeRemained -= sleepTime;

	logger.logInfo( "sleep execute operation=" + object -> getName() + 
		", nRatioOperations=" + nRatioOperations +
		", executeTime=" + executeTime +
		", opSleepTime=" + opSleepTime +
		", sleepSeconds=" + sleepSeconds +
		", sleepTime=" + sleepTime +
		", msWaitTimeRemained=" + msWaitTimeRemained );

	// measure new execute/operation ratio in percents - once per 100 executions
	if( nRatioOperations < reportGroup )
		return;

	// calculate ratio
	ratioExecutionByOperation = ( msExecTimeTotal * 100.0f ) / ( msExecTimeTotal + msSleepTimeTotal );

	// log stat
	logger.logInfo( String( "Execution/Duration Ratio is " ) + ratioExecutionByOperation + 
		"%, msExecTimeTotal=" + msExecTimeTotal + 
		", msSleepTimeTotal=" + msSleepTimeTotal +
		", msWaitTimeRemained=" + msWaitTimeRemained );

	// clean statistics
	nRatioOperations = 0;
	msExecTimeTotal = 0;
	msSleepTimeTotal = 0;

	// recalculate operation time if dynamic
	if( !dynamicOperationTime )
		return;

	if( ratioExecutionByOperation < minLoad )
		increaseSpeed( 1 );
	else
	if( ratioExecutionByOperation > maxLoad )
		decreaseSpeed( 1 );
}

void ActiveMemoryThread::increaseSpeed( int factor )
{
	msPerOperation /= 2 * factor;
	logger.logInfo( String( "speed increased, msPerOperation=" ) + msPerOperation );
}

void ActiveMemoryThread::decreaseSpeed( int factor )
{
	msPerOperation *= 2 * factor;
	logger.logInfo( String( "speed decreased, msPerOperation=" ) + msPerOperation );
}
