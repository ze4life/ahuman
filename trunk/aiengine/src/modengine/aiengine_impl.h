#ifndef	INCLUDE_AIENGINE_IMPL_H
#define INCLUDE_AIENGINE_IMPL_H

#include <aiengine.h>
#include <aimedia.h>
#include <aiio.h>
#include <ainnlib.h>
#include <aihtmlib.h>
#include <aiheart.h>
#include <aimind.h>
#include <aiknowledge.h>
#include <aidb.h>

#include <stdio.h>
#include <signal.h>

#include "tinyxml.h"

/*#########################################################################*/
/*#########################################################################*/

class LogManager;

/*#########################################################################*/
/*#########################################################################*/

class AIEngineImpl : public AIEngine 
{
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
	virtual void registerService( Service *src ,  const char *serviceName );
	virtual Service *getService( const char *serviceName );

	// threads
	virtual int getThreadId();
	virtual void workerCreated();
	virtual void workerStarted();
	virtual void workerExited( int status );
	virtual void workerExited( RFC_THREAD thread , int status );
	virtual void addWorkerObject( const char *key , ThreadObject *to );
	virtual ThreadObject *getWorkerObject( const char *key );

// base class interface
private:
	friend class AIEngine;

	static AIEngineImpl *instance;
	int runInternal( const char *configDir );
	void workerDestroyed();

	// constructor
	AIEngineImpl();
	~AIEngineImpl();

// internals
private:
	void init();
	void destroySerializeObjectInstances();
	void manageCallStack();

	// services
	void createServices();
	bool initServices();
	int runServices();
	void exitServices();
	void destroyServices();

	// log manager
	void logStart( Xml configLogging );
	void logStop();

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
	int getLevel();
	Xml getSettings();
	void setLevel( int level );
	void setLevelSymbol( char level );
	void setSettings( Xml xml );

private:
	Xml settings;
	int level;
};

/*#########################################################################*/
/*#########################################################################*/

class LogSettings
{
public:
	LogSettings();
	~LogSettings();

	void load( Xml config );

	String getFileName();
	String getFormat();
	Xml getObjectLogSettings( const char *className , const char *instance , int *level );
	Xml getServiceLogSettings( const char *className , int *level );
	Xml getCustomLogSettings( const char *loggerName , int *level );

private:
	void readLevels( Xml config , const char *listName , MapStringToClass<LogSettingsItem>& map , int& dv , Xml& settings );

private:
	String logFile;
	String logFormat;

	MapStringToClass<LogSettingsItem> objectData;
	MapStringToClass<LogSettingsItem> objectInstanceData;
	MapStringToClass<LogSettingsItem> serviceData;
	MapStringToClass<LogSettingsItem> customData;

	Xml objectSettings;
	Xml instanceSettings;
	Xml serviceSettings;
	Xml customSettings;
	int defaultObjectLevel;
	int defaultObjectInstanceLevel;
	int defaultServiceLevel;
	int defaultCustomLevel;
};

/*#########################################################################*/
/*#########################################################################*/

class LogManager
{
	typedef struct {
		union {
			char *one;
			char **many;
		} strings;
		int count;
		long time;
		long time_ms;
		Logger::LogLevel logLevel;
		long threadId;
		char *postfix;
	} LogRecord;
public:
	LogManager();
	~LogManager();

	// main run function
	void configure( Xml config );
	int run();

	// sync/async mode
	void setSyncMode( bool syncMode );
	bool getSyncMode();

	// start/stop async thread
	bool startWriter();
	void stopWriter();
	void waitForExit();

	// add/get log records
	void add( const char **chunkLines , int count , Logger::LogLevel logLevel , const char *postfix );
	bool get();
	int getLogRecordsPending();

	// log level
	Xml getObjectLogSettings( Object *o , Logger::LogLevel *level );
	Xml getServiceLogSettings( Service *s , Logger::LogLevel *level );
	Xml getCustomLogSettings( const char *loggerName , Logger::LogLevel *level );

private:
	void set( LogRecord *p , bool copy , const char **chunkLines , int count , Logger::LogLevel logLevel , const char *postfix );
	void clear( LogRecord *p );
	void output( LogRecord *p );

private:
	AIEngine *engine;
	FILE *logFileStream;
	LogSettings logSettings;
	bool isFileLoggingEnabled;
	bool stop;
	RFC_THREAD independentThreadID;

	// rolling read/write buffer
	LogRecord *v;
	RFC_HND lock;

	// total buffer allocated
	int va;
	bool extraMode;
	bool syncMode;

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
