#ifndef	INCLUDE_AIMEDIA_H
#define INCLUDE_AIMEDIA_H

#include <aiengine.h>
#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// handles different media AI will use to communicate
class AIMedia
{
public:

// engine helpers
public:
	static Service *newService();
	AIMedia *thisPtr;
	AIMedia();
};

#endif	// INCLUDE_AIMEDIA_H
