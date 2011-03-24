#ifndef	INCLUDE_AH_SERVICES_IMPL_H
#define INCLUDE_AH_SERVICES_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <ah_services.h>

#include <stdio.h>
#include <signal.h>

#define TIXML_USE_STL
#include "ah_tinyxml.h"

class LogSettingsItem;
class LogSettings;
class LogManager;

/*#########################################################################*/
/*#########################################################################*/

class LogSettingsItem
{
public:
	LogSettingsItem();
	~LogSettingsItem();

public:
	void configure( Xml config , String defaultLevel );

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

class LogManager
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
	LogSettingsItem *getObjectLogSettings( const char *className , const char *classInstance );
	LogSettingsItem *getServiceLogSettings( const char *serviceName );
	LogSettingsItem *getCustomLogSettings( const char *loggerName );

private:
	void set( LogRecord *p , bool copy , const char **chunkLines , int count , Logger::LogLevel logLevel , const char *postfix );
	void clear( LogRecord *p );
	void output( LogRecord *p );
	void showAsyncMessages();

private:
	ServiceManager *engine;
	Logger logger;
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
	RFC_THREAD asyncThread;

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

#endif	// INCLUDE_AH_SERVICES_IMPL_H
