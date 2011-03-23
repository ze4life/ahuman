#ifndef	INCLUDE_AH_MEDIA_H
#define INCLUDE_AH_MEDIA_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_services.h"
#include "ah_messaging.h"

class MediaService;

/*#########################################################################*/
/*#########################################################################*/

// handles different media AI will use to communicate
class MediaService : public Service
{
public:
	void sendTextToDirectChannel( String name , String text );
	String receiveTextFromDirectChannel( String name , bool wait );
	String receiveFixedSizeTextFromDirectChannel( String name , int size );

	virtual const char *getServiceName() { return( "MediaService" ); };
	virtual void configureService( Xml config ) {};
	virtual void createService() {};
	virtual void initService() {};
	virtual void runService() {};
	virtual void stopService() {};
	virtual void exitService() {};
	virtual void destroyService() {};

// engine helpers
protected:
	MediaService() {};
public:
	static Service *newService();
	static MediaService *getService() { return( ( MediaService * )ServiceManager::getInstance().getService( "MediaService" ) ); };
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AH_MEDIA_H
