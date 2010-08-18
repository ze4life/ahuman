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

	operationsPerSecond = 0;
	msPerOperation = 0;
	secondsPerCycle = 0;
	maxLoad = 0;

	ticksPerSecond = Timer::timeMsToTicks( 1000 );
	ticksPerOperation = 0;
	ticksExecTimeTotal = 0;
	ticksSleepTimeTotal = 0;
	ticksWaitTimeRemained = 0;
	ratioExecutionByOperation = 0;
	nLastOperations = 0;

	idle = 0; user = 0; kernel = 0;
	rfc_sys_getcpuload( &idle , &user , &kernel , &didle , &duser , &dkernel );

	ticksPerOperationLastFactor = 0;
	ticksPerOperationLastIncrease = false;
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
	thread = engine.runThread( name , this , ( ObjectThreadFunction )&ActiveMemoryThread::run , NULL );
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
	reportGroup = secondsPerCycle * operationsPerSecond;

	logger.attach( name );
	logger.logInfo( String( "Thread started: msPerOperation=" ) + msPerOperation +
		", operationsPerSecond=" + operationsPerSecond +
		", reportGroup=" + reportGroup +
		", secondsPerCycle=" + secondsPerCycle +
		", maxLoad=" + maxLoad +
		", ticksPerSecond=" + ticksPerSecond );

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
	Timer t( true );
	object -> execute();
	int executeTimeTicks = t.timePassedTicks();

	// to calculate current execute/sleep ratio
	ticksExecTimeTotal += executeTimeTicks;

	// calculate sleep time for this opeation (can be negative!)
	int opSleepTimeTicks = ticksPerOperation - executeTimeTicks;

	// add to pending sleep time
	ticksWaitTimeRemained += opSleepTimeTicks;
	nLastOperations++;

	// if sleep time is less than second - do nothing
	if( ticksWaitTimeRemained < ticksPerSecond ) {
		logger.logInfo( "non-sleep execute operation=" + object -> getName() + 
			", nLastOperations=" + nLastOperations +
			", executeTimeTicks=" + executeTimeTicks +
			", opSleepTimeTicks=" + opSleepTimeTicks + 
			", ticksWaitTimeRemained=" + ticksWaitTimeRemained );
	}
	else {
		// get whole number of seconds to sleep (probably always will be 1) and sleep
		int sleepSeconds = ticksWaitTimeRemained / ticksPerSecond;
		rfc_thr_sleep( sleepSeconds );
		int sleepTimeTicks = t.timePassedTicks() - executeTimeTicks;
		ticksSleepTimeTotal += sleepTimeTicks;
		ticksWaitTimeRemained -= sleepTimeTicks;

		logger.logInfo( "sleep execute operation=" + object -> getName() + 
			", nLastOperations=" + nLastOperations +
			", executeTimeTicks=" + executeTimeTicks +
			", opSleepTimeTicks=" + opSleepTimeTicks +
			", sleepSeconds=" + sleepSeconds +
			", sleepTimeTicks=" + sleepTimeTicks +
			", ticksWaitTimeRemained=" + ticksWaitTimeRemained );
	}

	// measure new execute/operation ratio in percents - once per 100 executions
	if( nLastOperations < reportGroup )
		return;

	// calculate ratio
	ratioExecutionByOperation = ( ticksExecTimeTotal * 100.0f ) / ( ticksExecTimeTotal + ticksSleepTimeTotal );
	float currentOperationsPerSecond = nLastOperations / ( ( float )( ticksExecTimeTotal + ticksSleepTimeTotal ) / ticksPerSecond );

	// log stat
	float currentCPULoad = 	rfc_sys_getcpuload( &idle , &user , &kernel , &didle , &duser , &dkernel );
	logger.logInfo( String( "Execution/Duration Ratio is " ) + ratioExecutionByOperation + "%" +
		", currentCPULoad=" + currentCPULoad +
		", didle=" + ( int )didle +
		", dkernel=" + ( int )dkernel +
		", duser=" + ( int )duser +
		", ticksExecTimeTotal=" + ticksExecTimeTotal + 
		", currentOperationsPerSecond=" + currentOperationsPerSecond +
		", ticksSleepTimeTotal=" + ticksSleepTimeTotal +
		", ticksWaitTimeRemained=" + ticksWaitTimeRemained );

	// recalculate operation time if dynamic
	if( currentCPULoad > maxLoad ) {
		decreaseSpeed( 1 );
	}
	else
	if( currentCPULoad < 0.9 * maxLoad && 
		currentOperationsPerSecond < ( float )operationsPerSecond ) {
		increaseSpeed( 1 );
	}

	// clean statistics
	nLastOperations = 0;
	ticksExecTimeTotal = 0;
	ticksSleepTimeTotal = 0;
}

// factor is shows ratio whole/part, where whole is current speed and part is its change to be done
// always positive, maximum change is current value
void ActiveMemoryThread::increaseSpeed( int factor )
{
	int factorApply;

	if( ticksPerOperationLastFactor != 0 ) {
		factorApply = ticksPerOperationLastFactor / factor;
		if( ticksPerOperationLastIncrease )
			factorApply /= 2;
		else
			factorApply *= 2;
	}
	else
		factorApply = 2 * factor;

	if( factorApply < 1 )
		factorApply = 1;

	ticksPerOperation -= ticksPerOperation / factorApply;
	if( ticksPerOperation < 1 )
		ticksPerOperation = 1;

	ticksPerOperationLastFactor = factorApply;
	ticksPerOperationLastIncrease = true;

	msPerOperation = Timer::timeTicksToMs( ticksPerOperation );
	if( msPerOperation < 1 )
		msPerOperation = 1;
	logger.logInfo( String( "speed increased, msPerOperation=" ) + msPerOperation );
}

void ActiveMemoryThread::decreaseSpeed( int factor )
{
	int factorApply;

	if( ticksPerOperationLastFactor != 0 ) {
		factorApply = ticksPerOperationLastFactor / factor;
		if( ticksPerOperationLastIncrease )
			factorApply *= 2;
		else
			factorApply /= 2;
	}
	else
		factorApply = 2 * factor;

	if( factorApply < 1 )
		factorApply = 1;

	ticksPerOperation += ticksPerOperation / factorApply;
	if( ticksPerOperation < 1 )
		ticksPerOperation = 1;

	ticksPerOperationLastFactor = factorApply;
	ticksPerOperationLastIncrease = false;

	msPerOperation = Timer::timeTicksToMs( ticksPerOperation );
	if( msPerOperation < 1 )
		msPerOperation = 1;
	logger.logInfo( String( "speed decreased, msPerOperation=" ) + msPerOperation );
}
