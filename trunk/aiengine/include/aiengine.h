#ifndef	INCLUDE_AIENGINE_H
#define INCLUDE_AIENGINE_H

extern "C" 
{
#include "generic/__gen.h"
}

#include <stdexcept>
#include <iostream>

using namespace std;

#include <tinyxml.h>
#include <aibasetypes.h>

class SerializeObject;
class Object;
class ObjectField;
class Logger;
class LogManager;
class Service;

/*#########################################################################*/
/*#########################################################################*/

class ThreadObject
{
public:
	virtual ~ThreadObject() {};
};

/*#########################################################################*/
/*#########################################################################*/

class Logger
{
public:
	typedef enum {
		LogLevelNone = 0 ,
		LogLevelError = 1 ,
		LogLevelInfo = 2 ,
		LogLevelAll = 3
	} LogLevel;

public:
	// construction
	Logger();
	~Logger();
	void attach( Service *s );
	void attach( Object *o );
	void attach( const char *loggerName );
	void setLogLevel( LogLevel level );

	// stack
	void printStack();
	void printStack( rfc_threadstack *stack , int skipTop = 0 );

	// log calls
	void logInfo( const char *s , int logMode = -1 );
	void logError( const char *s , int logMode = -1 );
	void logObject( const char *prompt , Object *obj );

	// check log status
	bool isLogAll();

private:
	void log( const char *s , int logMode , bool error );
	const char *Logger::getPostfix();
	
private:
	Object *o;
	Service *s;
	int logLevel;
	const char *loggerName;
};

/*#########################################################################*/
/*#########################################################################*/

class Service
{
// interface plus engine-managed properties
public:
	Service()
		{
			isCreateCompleted = false;
			isInitStarted = false;
			isInitCompleted = false;
			isRunStarted = false;
			isRunCompleted = false;
			isExitStarted = false;
			isExitCompleted = false;
			isDestroyStarted = false;
		};

	virtual const char *getName() = 0;
	virtual void initService() = 0;
	virtual void runService() = 0;
	virtual void exitService() = 0;
	virtual void destroyService() = 0;

	// logger
	Logger& getLogger() { return( logger ); };

	// status properties
	bool isCreateCompleted;
	bool isInitStarted;
	bool isInitCompleted;
	bool isRunStarted;
	bool isRunCompleted;
	bool isExitStarted;
	bool isExitCompleted;
	bool isDestroyStarted;

protected:
	Logger logger;
};

/*#########################################################################*/
/*#########################################################################*/

class AIEngine
{
// run from main only
public:
	static int run( const char *configFile );

// external interface
public:
	static AIEngine& getInstance();

	// others
	virtual void exit( int status ) = 0;
	virtual LogManager *getLogManager() = 0;

	// object serializations
	virtual void registerSerializeObject( SerializeObject *sop ) = 0;
	virtual SerializeObject *getSerializeObject( const char *className ) = 0;
	virtual SerializeObject *getSerializeObjectInstance( const char *p_inst ) = 0;
	virtual void addSerializeObjectInstance( SerializeObject *sop , const char *p_inst ) = 0;
	virtual void replaceSerializeObjectInstance( SerializeObject *sop , const char *p_inst ) = 0;
	virtual void replaceSerializeObjectInstanceSrc( SerializeObject *sop ) = 0;

	// service operations
	virtual void registerService( Service *src , const char *serviceName ) = 0;
	virtual Service *getService( const char *serviceName ) = 0;

	// thread management
	virtual int getThreadId() = 0;
	virtual void workerCreated() = 0;
	virtual void workerStarted() = 0;
	virtual void workerExited( int status ) = 0;
	virtual void workerExited( RFC_THREAD thread , int status ) = 0;
	virtual void addWorkerObject( const char *key , ThreadObject *to ) = 0;
	virtual ThreadObject *getWorkerObject( const char *key ) = 0;

	// configuration
	virtual TiXmlElement *getRoot( const char *configName ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

#include <aiobject.h>

#endif	// INCLUDE_AIENGINE_H
