#ifndef	INCLUDE_AIBODY_H
#define INCLUDE_AIBODY_H

#include <aiengine.h>
#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// handle inquires to AI accumulated experience and information
class AIBody
{
public:

// engine helpers
public:
	static Service *newService();
	AIBody *thisPtr;
	AIBody();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIBODY_H