#ifndef	INCLUDE_AIMIND_H
#define INCLUDE_AIMIND_H

#include <aiengine.h>
#include <aiio.h>
#include <aiknowledge.h>

/*#########################################################################*/
/*#########################################################################*/

class AIMind
{
// intenface
public:

// engine helpers
public:
	static Service *createService();
	AIMind *thisPtr;
	AIMind();
};

#endif	// INCLUDE_AIMIND_H
