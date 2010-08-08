#ifndef	INCLUDE_AICOGNITION_H
#define INCLUDE_AICOGNITION_H

#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// convert sensor information into flow of internal patterns
class AICognition
{
public:

// engine helpers
public:
	static Service *newService();
	AICognition *thisPtr;
	AICognition();
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AICOGNITION_H