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
	virtual void sendMessageToUser( AIMessage *msg , AISession *session )
		{ thisPtr -> sendMessageToUser( msg , session ); };

	virtual void closeMediaReflect( AISession *session )
		{ thisPtr -> closeMediaReflect( session ); };

// engine helpers
public:
	static Service *createService();
	AIMedia *thisPtr;
	AIMedia();
};

#endif	// INCLUDE_AIMEDIA_H
