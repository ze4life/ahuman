// understanding the meaning

#ifndef	INCLUDE_AIHTMLIB_H
#define INCLUDE_AIHTMLIB_H

#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLib
{
public:

// engine helpers
public:
	static Service *createService();
	AIHtmLib *thisPtr;
	AIHtmLib();
};

#endif	// INCLUDE_AIHTMLIB_H
