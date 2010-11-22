// libespeak.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "libespeak.h"


// This is an example of an exported variable
LIBESPEAK_API int nlibespeak=0;

// This is an example of an exported function.
LIBESPEAK_API int fnlibespeak(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see libespeak.h for the class definition
Clibespeak::Clibespeak()
{
	return;
}
