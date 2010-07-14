#ifndef	INCLUDE_AIBODY_H
#define INCLUDE_AIBODY_H

#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// handle inquires to AI accumulated experience and information
class AIBody
{
public:

// engine helpers
public:
	static Service *createService();
	AIBody *thisPtr;
	AIBody();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIBODY_H