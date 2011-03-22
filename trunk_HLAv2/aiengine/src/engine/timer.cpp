
#include "engine_impl.h"

// #############################################################################
// #############################################################################

Timer::Timer( bool setInitialTime )
{
	if( setInitialTime ) {
		timeStarted = clock();
		rfc_hpt_setpoint( &timeStartedTicks );
	}

	waitTime = 0;
	waitCount = 0;
}

Timer::Timer( int p_waitTime )
{
	timeStarted = clock();
	rfc_hpt_setpoint( &timeStartedTicks );

	waitTime = p_waitTime;
}

// time passed from process start - in ms
int Timer::timeNow()
{
	long timeNow = clock();
	return( ( int )( timeNow * 1000 / CLOCKS_PER_SEC ) );
}

int Timer::timeCreated()
{
	return( ( int )( timeStarted * 1000 / CLOCKS_PER_SEC ) );
}

void Timer::startAdjustment()
{
	rfc_hpt_startadjustment();
}

void Timer::stopAdjustment()
{
	rfc_hpt_stopadjustment();
}

int Timer::timePassed()
{
	long timeNow = clock();
	return( ( int )( ( timeNow - timeStarted ) * 1000 ) / CLOCKS_PER_SEC );
}

// time passed - in clocks
int Timer::timePassedClocks()
{
	return( ( int )( clock() - timeStarted ) );
}

// time passed - in ticks
int Timer::timePassedTicks()
{
	return( rfc_hpt_timepassed( &timeStartedTicks ) );
}

// convert clocks to ms
int Timer::timeClocksToMs( int clocks )
{
	return( ( int )( ( clocks * 1000 ) / CLOCKS_PER_SEC ) );
}

// convert ms to clocks
int Timer::timeMsToClocks( int ms )
{
	return( ( int )( ( ms * CLOCKS_PER_SEC ) / 1000 ) );
}

bool Timer::go()
{
	return( timePassed() < waitTime );
}

// convert ticks to ms
int Timer::timeTicksToMs( int ticks )
{
	return( rfc_hpt_ticks2ms( ticks ) );
}

// convert ms to ticks
int Timer::timeMsToTicks( int ms )
{
	return( rfc_hpt_ms2ticks( ms ) );
}

int Timer::waitNext()
{
	int secs = waitTime / 1000;
	if( secs == 0 )
		secs = 1;
	rfc_thr_sleep( secs );
	return( ++waitCount );
}
