#ifndef	INCLUDE_AH_SERVICES_H
#define INCLUDE_AH_SERVICES_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_basetypes.h"
#include "ah_templates.h"
#include "ah_logging.h"

class ServiceManager;
class Service;
class PropertyContainer;

/*#########################################################################*/
/*#########################################################################*/

class LogManager;

class ServiceState {
public:
	typedef enum {
		AH_COLD = 1 ,			// enabled: create->CREATING->CREATED
		AH_CREATING = 2 ,		// enabled: create->CREATED, exit->EXITING->COLD
		AH_CREATED = 3 ,		// enabled: init->INITIALIZING->INITIALIZED, exit->EXITING->COLD
		AH_INITIALIZING = 4 ,	// enabled: init->INITIALIZED, exit->EXITING->COLD
		AH_INITIALIZED = 5 ,	// enabled: run->RUNNING,exit->EXITING->COLD
		AH_RUNNING = 6 ,		// enabled: stop->STOPPED
		AH_STOPPED = 7 ,		// enabled: exit->EXITING->COLD
		AH_EXITING = 8			// enabled: exit->COLD
	} ServiceStateType;

private:
	ServiceStateType state;

public:
	ServiceState() { state = AH_COLD; };
	ServiceStateType getState() { return( state ); };

	void setState( ServiceStateType value ) {
		bool ok = false;
		if( state == AH_COLD )
			ok = ( value == AH_CREATING );
		else
		if( state == AH_CREATING )
			ok = ( value == AH_CREATED || value == AH_EXITING );
		else
		if( state == AH_CREATED )
			ok = ( value == AH_INITIALIZING || value == AH_EXITING );
		else
		if( state == AH_INITIALIZING )
			ok = ( value == AH_INITIALIZED || value == AH_EXITING );
		else
		if( state == AH_INITIALIZED )
			ok = ( value == AH_RUNNING || value == AH_EXITING );
		else
		if( state == AH_RUNNING )
			ok = ( value == AH_STOPPED );
		else
		if( state == AH_STOPPED )
			ok = ( value == AH_EXITING );
		else
		if( state == AH_EXITING )
			ok = ( value == AH_COLD );

		ASSERTMSG( ok , String( "Invalid state transition: stateFrom=" )  + state + ", stateTo=" + value );
		state = value;
	};

	bool readyForExit() {
		if( state == AH_CREATING || state == AH_CREATED || state == AH_INITIALIZING || state == AH_INITIALIZED || state == AH_STOPPED )
			return( true );
		return( false );
	};
};

class ServiceManager {
public:
	void addService( Service *src );
	void addPlatformServices();
	Service *getService( const char *serviceName );
	ClassList<Service> getServices();

	// operations for all added and optionally configured services
	void createServices();		// create/set internal items according to configuration if any
	void initServices();		// create contextual links among services, can start threads here
	void runServices();			// enable to generate events inside service, can start threads here
	void stopServices();		// stop generating events, wait for completion of all threads created
	void exitServices();		// wait for completion of all threads created, cleanup without dropping interfaces, last chance to use links between services
	void destroyServices();		// drop internal data

	LogManager *getLogManager();
	bool canStartThread();

public:
	ServiceManager();
	~ServiceManager();
	static ServiceManager& getInstance();

// class internals
private:
	void init();

	// log manager
	void logStart( Xml configLogging );
	void logStop();
	void logStopAsync();

// data
private:
	static ServiceManager *instance;

	ServiceState state;
	String logLineFormat;
	LogManager *logManager;
	bool stoppedBySignal;
	Logger logger;

	// services
	ClassList<Service> serviceList;
	MapStringToClass<Service> services;
};

/*#########################################################################*/
/*#########################################################################*/

class Service {
// interface plus engine-managed properties
public:
	Service() {
		isCreate = true;
		isInit = true;
		isRun = true;
	};

	virtual const char *getServiceName() = 0;
	virtual void configureService( Xml config ) = 0;
	virtual void createService() = 0;
	virtual void initService() = 0;
	virtual void runService() = 0;
	virtual void stopService() = 0;
	virtual void exitService() = 0;
	virtual void destroyService() = 0;

	// configuration
	ServiceState state;
	bool isCreate;
	bool isInit;
	bool isRun;

	void setConfigMain( Xml p_config ) { configMain = p_config; };
	void setConfigService( Xml p_config ) { configService = p_config; };
	Xml getConfigMain() { return( configMain ); };
	Xml getConfigService() { return( configService ); };

	// logger
	void attachLogger() { logger.attachService( getServiceName() ); };
	Logger& getLogger() { return( logger ); };

protected:
	Logger logger;

private:
	// configuration
	Xml configMain;
	Xml configService;
	Xml configLogging;
};

/*#########################################################################*/
/*#########################################################################*/

class PropertyContainer {
private:
	MapStringToClass<Value> params;

public:
	PropertyContainer() {};
	~PropertyContainer() { params.destroy(); };

	void setInt( const char *key , int value ) { 
		ASSERTMSG( params.get( key ) == NULL , "Already used key=" + String( key ) );
		params.set( key , new Value( ( long )value ) ); 
	};
	int getInt( const char *key ) { 
		Value *pv = params.get( key ); 
		ASSERTMSG( pv != NULL , "Not found key=" + String( key ) );
		return( pv -> getLong() );
	}

	void setString( const char *key , const char *value ) { 
		ASSERTMSG( params.get( key ) == NULL , "Already used key=" + String( key ) );
		params.set( key , new Value( value ) ); 
	};
	const char *getString( const char *key ) { 
		Value *pv = params.get( key ); 
		ASSERTMSG( pv != NULL , "Not found key=" + String( key ) );
		return( pv -> getString() );
	}
};

/*#########################################################################*/
/*#########################################################################*/

#endif // INCLUDE_AH_SERVICES_H
