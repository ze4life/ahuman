#ifndef	INCLUDE_AIKNOWLEDGE_H
#define INCLUDE_AIKNOWLEDGE_H

#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// handle inquires to AI accumulated experience and information
class AIKnowledge
{
public:

// engine helpers
public:
	static Service *newService();
	AIKnowledge *thisPtr;
	AIKnowledge();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIKNOWLEDGE_H
