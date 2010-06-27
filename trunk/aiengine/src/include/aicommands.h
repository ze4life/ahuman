#ifndef	INCLUDE_AICOMMANDS_H
#define INCLUDE_AICOMMANDS_H

#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

// handle inquires to AI accumulated experience and information
class AICommands
{
public:

// engine helpers
public:
	static Service *createService();
	AICommands *thisPtr;
	AICommands();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AICOMMANDS_H
