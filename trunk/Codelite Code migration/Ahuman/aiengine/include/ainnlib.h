// understanding the meaning

#ifndef	INCLUDE_AINNLIB_H
#define INCLUDE_AINNLIB_H

#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

class AINNLib
{
public:

// engine helpers
public:
	static Service *createService();
	AINNLib *thisPtr;
	AINNLib();
};

#endif	// INCLUDE_AINNLIB_H
