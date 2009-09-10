// understanding the meaning

#ifndef	INCLUDE_AIEXPERT_H
#define INCLUDE_AIEXPERT_H

#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

class AIExpert
{
public:

// engine helpers
public:
	static Service *createService();
	AIExpert *thisPtr;
	AIExpert();
};

#endif	// INCLUDE_AIEXPERT_H
