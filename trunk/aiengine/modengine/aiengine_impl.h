#ifndef	INCLUDE_AIENGINE_IMPL_H
#define INCLUDE_AIENGINE_IMPL_H

#include <aiengine.h>
#include <aimedia.h>
#include <aiio.h>
#include <aiexpert.h>
#include <aiheart.h>
#include <aimind.h>
#include <aiknowledge.h>
#include <aidb.h>

#include <stdio.h>
#include <signal.h>

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

	// configuration
	virtual TiXmlElement *getRoot( const char *configName );

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
	void logStart();
	void logStop();

// data
private:
	String configDir;
	String logLineFormat;
	LogManager *logManager;
	bool stoppedBySignal;
	Logger logger;

	// threads
	int workerStatus;
	RFC_HND lockExit;
	RFC_HND eventExit;
	int countExit;

	// configuration
	MapStringToClass<TiXmlDocument> configs;
	TiXmlElement *mainConfigRoot;

	// services
	MapStringToClass<Service> services;

	// serializable objects
	rfc_strmap *mapObjectTypeIdToSerializeObject;
};

/*#########################################################################*/
/*#########################################################################*/

class ThreadLogTail : public ThreadObject
{
public:
	ThreadLogTail() { remains = false; };
	virtual ~ThreadLogTail() {};

public:
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
	void setLevel( int level );
	void setLevelSymbol( char level );

private:
	int level;
};

/*#########################################################################*/
/*#########################################################################*/

class LogSettings
{
public:
	LogSettings();
	~LogSettings();

	void load( const char *configName );

	String getFileName();
	String getFormat();
	int getObjectLogLevel( const char *className , const char *instance = NULL );
	int getServiceLogLevel( const char *className );
	int getCustomLogLevel( const char *loggerName );

private:
	void readLevels( TiXmlElement *root , const char *listName , MapStringToClass<LogSettingsItem>& map , int& dv );

private:
	String logFile;
	String logFormat;

	MapStringToClass<LogSettingsItem> objectData;
	MapStringToClass<LogSettingsItem> objectInstanceData;
	MapStringToClass<LogSettingsItem> serviceData;
	MapStringToClass<LogSettingsItem> customData;

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
		bool error;
		long threadId;
		char *postfix;
	} LogRecord;
public:
	LogManager();
	~LogManager();

	// main run function
	void configure( const char *configName );
	int run();

	// sync/async mode
	void setSyncMode( bool syncMode );
	bool getSyncMode();

	// start/stop async thread
	bool startWriter();
	void stopWriter();
	void waitForExit();

	// add/get log records
	void add( const char **chunkLines , int count , bool error , const char *postfix );
	bool get();
	int getLogRecordsPending();

	// log level
	Logger::LogLevel getObjectLogLevel( Object *o );
	Logger::LogLevel getServiceLogLevel( Service *s );
	Logger::LogLevel getCustomLogLevel( const char *loggerName );

private:
	void set( LogRecord *p , bool copy , const char **chunkLines , int count , bool error , const char *postfix );
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
