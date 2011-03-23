#ifndef	INCLUDE_AH_ENVIRONMENT_H
#define INCLUDE_AH_ENVIRONMENT_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_services.h"

/*#########################################################################*/
/*#########################################################################*/

class EnvService : public Service {
public:
	String getConfigurationPath( String etcpath );

	virtual const char *getServiceName() { return( "EnvService" ); };
	virtual void configureService( Xml config ) {};
	virtual void createService() {};
	virtual void initService() {};
	virtual void runService() {};
	virtual void stopService() {};
	virtual void exitService() {};
	virtual void destroyService();

// internals
protected:
	EnvService() {};
public:
	static Service *newService();
	static EnvService *getService() { return( ( EnvService * )ServiceManager::getInstance().getService( "EnvService" ) ); };

private:
	Xml loadXml( String fileName );

private:
	String configDir;
	Xml config;

	// configurations loaded
	MapStringToClass<Xml> configs;
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_ENVIRONMENT_H
