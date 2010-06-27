#ifndef	INCLUDE_AIKNOWLEDGE_H
#define INCLUDE_AIKNOWLEDGE_H

#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

// handle inquires to AI accumulated experience and information
class AIKnowledge
{
public:

// engine helpers
public:
	static Service *createService();
	AIKnowledge *thisPtr;
	AIKnowledge();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIKNOWLEDGE_H
