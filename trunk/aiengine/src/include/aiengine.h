#ifndef	INCLUDE_AIENGINE_H
#define INCLUDE_AIENGINE_H

extern "C" 
{
#include "generic/__gen.h"
}

#include <stdexcept>
#include <iostream>

using namespace std;

#include <aibasetypes.h>

class SerializeObject;
class Object;
class ObjectField;
class Logger;
class LogManager;
class LogSettingsItem;
class Service;
class Xml;

/*#########################################################################*/
/*#########################################################################*/

class ThreadObject
{
public:
	virtual ~ThreadObject() {};
};

/*#########################################################################*/
/*#########################################################################*/

class Xml
{
	friend class AIEngineImpl;

public:
	Xml();
	void attach( void *doc , void *node );
	bool exists();

	// direct data
	String getName();
	String getValue();
	String serialize();
	String getHeading();

	// navigation
	Xml getChildNode( String s );
	Xml getFirstChild( String name );
	Xml getNextChild( String name );

	// attributes
	String getAttribute( String a );
	String getAttribute( String a , String defaultValue );
	bool getBooleanAttribute( String a );
	void setAttribute( String a , String value );
	void setBooleanAttribute( String a , bool value );

	// properties
	String getProperty( String name );
	String getProperty( String name , String defaultValue );
	bool getBooleanProperty( String name );
	int getIntProperty( String name );
	int getIntProperty( String name , int defaultValue );
	float getFloatProperty( String name );
	float getFloatProperty( String name , float defaultValue );
	void setProperty( String name , String value );
	void setBooleanProperty( String name , bool value );
	void setIntProperty( String name , int value );
	void setFloatProperty( String name , float value );

	// elements
	Xml addTextElement( String name , String value );
	Xml addElement( String name );

private:
	void *doc;
	void *node;
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
		LogLevelDebug = 3
	} LogLevel;

public:
	// construction
	Logger();
	~Logger();

	Xml getLogSettings();
	void attachRoot();
	void attach( Service *s );
	void attach( Object *o );
	void attach( const char *loggerName );

	// stack
	void printStack();
	void printStack( rfc_threadstack *stack , int skipTop = 0 );

	// log calls
	void logInfo( const char *s , int logMode = -1 );
	void logError( const char *s , int logMode = -1 );
	void logDebug( const char *s , int logMode = -1 );
	void logObject( const char *prompt , Object *obj , Logger::LogLevel logLevel );

	// check log status
	bool isLogAll();

private:
	void log( const char *s , int logMode , Logger::LogLevel logLevel );
	const char *getPostfix();
	
private:
	Object *o;
	Service *s;
	const char *loggerName;
	LogSettingsItem *settings;
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

	// configuration
	virtual void configure( Xml p_config ) { config = p_config; };
	Xml getConfig() { return( config ); };

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

	// configuration
	Xml config;
	Xml configLogging;
};

/*#########################################################################*/
/*#########################################################################*/

typedef void (Object::*ObjectFunction)( void *p_arg );

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
	virtual Xml loadXml( String fileName ) = 0;
	virtual Xml readXml( const char *data , const char *contentName ) = 0;
	virtual Xml createXml( const char *contentName ) = 0;
	virtual void destroyXmlDoc( Xml& xml ) = 0;

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
	virtual int runThread( String name , Object *object , ObjectFunction function , void *p_arg ) = 0;
	virtual int getThreadId() = 0;
	virtual void addWorkerObject( const char *key , ThreadObject *to ) = 0;
	virtual ThreadObject *getWorkerObject( const char *key ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

#include <aiobject.h>

#endif	// INCLUDE_AIENGINE_H
