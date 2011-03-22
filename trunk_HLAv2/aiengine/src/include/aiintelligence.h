#ifndef	INCLUDE_AIINTELLIGENCE_H
#define INCLUDE_AIINTELLIGENCE_H

#include <aiengine.h>
#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// handle inquires to AI accumulated experience and information
class AIIntelligence
{
public:

// engine helpers
public:
	static Service *newService();
	AIIntelligence *thisPtr;
	AIIntelligence();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIINTELLIGENCE_H
