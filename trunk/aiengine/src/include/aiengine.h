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
class Cortex;

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
	Xml getChildNamedNode( String element , String name );
	Xml getFirstChild( String name );
	Xml getNextChild( String name );
	// path items are delimited by '/' chars
	Xml findChildByPath( String path );
	Xml findChildByPathAttr( String path , String attr , String value );

	// attributes
	String getAttribute( String a );
	String getAttribute( String a , String defaultValue );
	bool getBooleanAttribute( String a );
	int getIntAttribute( String a );
	void setAttribute( String a , String value );
	void setBooleanAttribute( String a , bool value );
	void setIntAttribute( String a , int value );

	// properties
	void getProperties( MapStringToString& map );
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

	typedef enum {
		LogStart = 1 ,
		LogLine = 0 ,
		LogStop = 2 ,
		LogDefault = -1
	} LogOutputMode;

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
	void printStack( rfc_threadstack *stack , int skipTop );
	void printStackInplace( rfc_threadstack *stack , int skipTop );
	void printStackInternal( rfc_threadstack *stack , int skipTop , bool printInplace );

	// log calls
	void logInfo( const char *s , LogOutputMode logMode = LogDefault );
	void logError( const char *s , LogOutputMode logMode = LogDefault );
	void logDebug( const char *s , LogOutputMode logMode = LogDefault );
	void logObject( const char *prompt , Object *obj , Logger::LogLevel logLevel );

	// check log status
	bool isLogAll();

private:
	void log( const char *s , LogOutputMode logMode , Logger::LogLevel logLevel );
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
			isNewCompleted = false;
			isCreateStarted = false;
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
	virtual void createService( Xml config ) = 0;
	virtual void initService() = 0;
	virtual void runService() = 0;
	virtual void exitService() = 0;
	virtual void destroyService() = 0;

	// configuration
	bool isCreate;
	bool isInit;
	bool isRun;

	void setConfigMain( Xml p_config ) { configMain = p_config; };
	void setConfigService( Xml p_config ) { configService = p_config; };
	Xml getConfigMain() { return( configMain ); };
	Xml getConfigService() { return( configService ); };

	// logger
	Logger& getLogger() { return( logger ); };

	// status properties
	bool isNewCompleted;
	bool isCreateStarted;
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

private:
	// configuration
	Xml configMain;
	Xml configService;
	Xml configLogging;
};

/*#########################################################################*/
/*#########################################################################*/

typedef void (Object::*ObjectThreadFunction)( void *p_arg );

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
	virtual Service *getService( const char *serviceName ) = 0;

	// thread management
	virtual void threadDump() = 0;
	virtual RFC_HND runThread( String name , Object *object , ObjectThreadFunction function , void *p_arg ) = 0;
	virtual bool waitThreadExited( RFC_HND thread ) = 0;
	virtual RFC_HND getThreadHandle() = 0;
	virtual int getThreadId() = 0;
	virtual void addThreadObject( const char *key , ThreadObject *to ) = 0;
	virtual ThreadObject *getThreadObject( const char *key ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

#include <aiobject.h>

#endif	// INCLUDE_AIENGINE_H
