
#include <time.h>
#include "aiapi_impl.h"

// #############################################################################
// #############################################################################

Timer::Timer()
{
	timeStarted = clock();
}

Timer::Timer( int p_waitTime )
{
	timeStarted = clock();
	waitTime = p_waitTime;
}

int Timer::timePassed()
{
	long timeNow = clock();
	return( ( int )( ( timeNow - timeStarted ) * 1000 ) / CLOCKS_PER_SEC );
}

bool Timer::go()
{
	return( timePassed() < waitTime );
}

