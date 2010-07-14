#ifndef	INCLUDE_AIBRAIN_H
#define INCLUDE_AIBRAIN_H

#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// handle 3D-set of neurexes
class AIBrain
{
public:

// engine helpers
public:
	static Service *createService();
	AIBrain *thisPtr;
	AIBrain();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIBRAIN_H