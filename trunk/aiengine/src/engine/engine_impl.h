#ifndef	INCLUDE_AIENGINE_IMPL_H
#define INCLUDE_AIENGINE_IMPL_H

#include <aiengine.h>
#include <aisvcio.h>
#include <aisvcdb.h>
#include <ailibnn.h>
#include <ailibbn.h>
#include <aimedia.h>
#include <aiknowledge.h>
#include <aiintelligence.h>
#include <aicognition.h>
#include <aibody.h>
#include <aibrain.h>
#include <test.h>

#include <stdio.h>
#include <signal.h>

#define TIXML_USE_STL
#include "tinyxml.h"

/*#########################################################################*/
/*#########################################################################*/

class LogManager;
class ThreadData;

typedef Service * ( *ServiceFactoryFunction )();

/*#########################################################################*/
/*#########################################################################*/

class AIEngineImpl : public AIEngine 
{
	enum {
		AI_COLD = 1 ,
		AI_CREATED = 2 ,
		AI_INITIALIZED = 3 ,
		AI_RUNNING = 4 ,
		AI_EXITED = 5 ,
		AI_STOPPED = 6
	} state;

// external interface
public:
	// others
	virtual void exit( int status );
	virtual LogManager *getLogManager();
	virtual Xml loadXml( String fileName );
	virtual Xml readXml( const char *data , const char *contentName );
	virtual Xml createXml( const char *contentName );
	virtual void destroyXmlDoc( Xml& xml );

	// serializable objects
	virtual void registerSerializeObject( SerializeObject *sop );
	virtual SerializeObject *getSerializeObject( const char *className );
	virtual SerializeObject *getSerializeObjectInstance( const char *p_inst );
	virtual void addSerializeObjectInstance( SerializeObject *o , const char *p_inst );
	virtual void replaceSerializeObjectInstance( SerializeObject *o , const char *p_inst );
	virtual void replaceSerializeObjectInstanceSrc( SerializeObject *o );

	// services
	virtual Service *getService( const char *serviceName );

	// threads
	virtual RFC_HND runThread( String name , Object *object , void (Object::*)( void *p_arg ) , void *p_arg );
	virtual bool waitThreadExited( RFC_HND thread );
	virtual RFC_HND getThreadHandle();
	virtual int getThreadId();
	virtual void addThreadObject( const char *key , ThreadObject *to );
	virtual ThreadObject *getThreadObject( const char *key );

public:
	unsigned threadFunction( ThreadData *td );

// base class interface
private:
	friend class AIEngine;

	static AIEngineImpl *instance;
	int runInternal( const char *configDir );
	void workerDestroyed();
	void workerCreated();
	void workerStarted( ThreadData *threadData );
	void workerExited( int status );
	void workerExited( RFC_THREAD thread , int status );

	// constructor
	AIEngineImpl();
	~AIEngineImpl();

// internals
private:
	void init();
	void destroySerializeObjectInstances();
	void manageCallStack();

	// services
	void registerService( Service *src ,  const char *serviceName );
	void createServices();
	void constructServices();
	Service *constructService( String name , ServiceFactoryFunction factoryFunction );
	void initServices();
	void runServices();
	void exitServices();
	void destroyServices();
	void waitExitSignal();

	// log manager
	void logStart( Xml configLogging );
	void logStop();
	void logStopAsync();

// data
private:
	String configDir;
	Xml config;

	String logLineFormat;
	LogManager *logManager;
	bool stoppedBySignal;
	Logger logger;

	// threads
	int workerStatus;
	RFC_HND lockExit;
	RFC_HND eventExit;
	int countExit;

	// configurations loaded
	MapStringToClass<TiXmlDocument> configs;

	// services
	MapStringToClass<Service> services;

	// serializable objects
	rfc_strmap *mapObjectTypeIdToSerializeObject;
};

/*#########################################################################*/
/*#########################################################################*/

class EngineThreadHelper : public ThreadObject
{
public:
	EngineThreadHelper();
	virtual ~EngineThreadHelper();

	void addThreadObject();
	static EngineThreadHelper *getThreadObject();

public:
	void ( *oldAIUnhandledExceptionTranslator )(); // _se_translator_function
	String lastMsg;
	bool remains;
};

/*#########################################################################*/
/*#########################################################################*/

class LogSettingsItem
{
public:
	LogSettingsItem();
	~LogSettingsItem();

public:
	void configure( Xml config );

	bool logDisabled( Logger::LogLevel level );
	bool isExcluded( const char *s );
	LogSettingsItem *getSettings( const char *instance );

	Logger::LogLevel getLevel();
	Xml getXml();
	void setLevel( Logger::LogLevel level );
	void setLevelByName( String level );

private:
	Xml settings;
	Logger::LogLevel level;
	MapStringToClass<LogSettingsItem> instanceSettings;
	MapStringToClass<LogSettingsItem> excludeList;
};

/*#########################################################################*/
/*#########################################################################*/

class LogSettings
{
public:
	LogSettings();
	~LogSettings();

	void load( Xml config );

	bool getSyncMode();

	String getFileName();
	String getFormat();

	LogSettingsItem *getDefaultSettings();
	LogSettingsItem *getCustomDefaultSettings();
	LogSettingsItem *getObjectSettings( const char *className , const char *instance );
	LogSettingsItem *getServiceSettings( const char *className );
	LogSettingsItem *getCustomSettings( const char *loggerName );

	static void readLevels( Xml config , const char *listName , MapStringToClass<LogSettingsItem>& map , LogSettingsItem& settings );

private:
	bool syncMode;
	String logFile;
	String logFormat;

	LogSettingsItem defaultSettings;
	LogSettingsItem defaultObjectSettings;
	LogSettingsItem defaultServiceSettings;
	LogSettingsItem defaultCustomSettings;
	MapStringToClass<LogSettingsItem> objectData;
	MapStringToClass<LogSettingsItem> serviceData;
	MapStringToClass<LogSettingsItem> customData;
};

/*#########################################################################*/
/*#########################################################################*/

class LogManager : public Object
{
	typedef struct {
		union {
			char *one;
			char **many;
		} strings;
		int count;
		__time64_t time;
		long time_ms;
		Logger::LogLevel logLevel;
		long threadId;
		char *postfix;
	} LogRecord;
public:
	LogManager();
	~LogManager();

	virtual const char *getClass() { return( "LogManager" ); };

	// main run function
	void configure( Xml config );
	void run( void * );

	// sync/async mode
	void setSyncMode( bool syncMode );
	bool getSyncMode();
	bool getConfiguredSyncMode();

	// start/stop async thread
	bool start();
	void stopAsync();
	void stop();

	// add/get log records
	void add( const char **chunkLines , int count , Logger::LogLevel logLevel , const char *postfix );
	bool get( bool p_autolock );
	int getLogRecordsPending();

	// log level
	LogSettingsItem *getDefaultSettings();
	LogSettingsItem *getCustomDefaultLogSettings();
	LogSettingsItem *getObjectLogSettings( Object *o );
	LogSettingsItem *getServiceLogSettings( Service *s );
	LogSettingsItem *getCustomLogSettings( const char *loggerName );

private:
	void set( LogRecord *p , bool copy , const char **chunkLines , int count , Logger::LogLevel logLevel , const char *postfix );
	void clear( LogRecord *p );
	void output( LogRecord *p );
	void showAsyncMessages();

private:
	AIEngine *engine;
	FILE *logFileStream;
	LogSettings logSettings;
	bool isFileLoggingEnabled;
	bool stopAll;

	// rolling read/write buffer
	LogRecord *v;
	RFC_HND lock;

	// total buffer allocated
	int va;
	bool extraMode;
	bool syncMode;
	bool syncModeConfigured;

	int n1e;	// empty
	int n2f;	// filled
	int n3e;	// empty
	int n4f;	// filled
	int n5f;	// filled in extra mode
	int n6e;	// empty in extra mode

	int startAdd;	// next add pos
	int startGet;	// next get pos

	static RFC_HND stopEvent;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIENGINE_IMPL_H
