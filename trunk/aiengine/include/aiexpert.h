// understanding the meaning

#ifndef	INCLUDE_AIEXPERT_H
#define INCLUDE_AIEXPERT_H

#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

class AIExpert
{
public:
	virtual void processMediaMessage( AIMessage *msg , AISession *session )
		{ thisPtr -> processMediaMessage( msg , session ); };

// engine helpers
public:
	static Service *createService();
	AIExpert *thisPtr;
	AIExpert();
};

#endif	// INCLUDE_AIEXPERT_H
