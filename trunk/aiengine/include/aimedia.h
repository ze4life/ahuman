#ifndef	INCLUDE_AIMEDIA_H
#define INCLUDE_AIMEDIA_H

#include <aiengine.h>
#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

// handles different media AI will use to communicate
class AIMedia
{
public:

// engine helpers
public:
	static Service *createService();
	AIMedia *thisPtr;
	AIMedia();
};

#endif	// INCLUDE_AIMEDIA_H
