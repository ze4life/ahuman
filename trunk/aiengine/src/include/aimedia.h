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

	virtual void sendTextToDirectChannel( String name , String text ) {
		thisPtr -> sendTextToDirectChannel( name , text );
	}
	virtual String receiveTextFromDirectChannel( String name , bool wait ) {
		return( thisPtr -> receiveTextFromDirectChannel( name , wait ) );
	}
	virtual String receiveFixedSizeTextFromDirectChannel( String name , int size ) {	
		return( thisPtr -> receiveFixedSizeTextFromDirectChannel( name , size ) );
	}
};

#endif	// INCLUDE_AIMEDIA_H
