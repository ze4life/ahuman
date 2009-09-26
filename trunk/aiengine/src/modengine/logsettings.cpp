
#include "aiengine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class LogSettings : public Object
LogSettings::LogSettings()
{
	defaultObjectLevel = Logger::LogLevelDebug;
	defaultObjectInstanceLevel = Logger::LogLevelDebug;
	defaultServiceLevel = Logger::LogLevelDebug;
	defaultCustomLevel = Logger::LogLevelDebug;
}

LogSettings::~LogSettings()
{
	objectData.destroy();
	objectInstanceData.destroy();
	serviceData.destroy();
	customData.destroy();
}

void LogSettings::load( Xml config )
{
	// read
	logFile = config.getProperty( "filename" );
	logFormat = config.getProperty( "format" );

	readLevels( config , "objectLogLevel" , objectData , defaultObjectLevel , objectSettings );
	readLevels( config , "objectInstanceLogLevel" , objectInstanceData , defaultObjectInstanceLevel , instanceSettings );
	readLevels( config , "serviceLogLevel" , serviceData , defaultServiceLevel , serviceSettings );
	readLevels( config , "customLogLevel" , customData , defaultCustomLevel , customSettings );
}

void LogSettings::readLevels( Xml config , const char *listName , MapStringToClass<LogSettingsItem>& map , int& dv , Xml& settings )
{
	map.destroy();

	Xml list = config.getChildNode( listName );
	if( !list.exists() )
		return;

	settings = list;

	// read default value
	String defval = list.getAttribute( "default" );
	if( defval.equals( "E" ) )
		dv = Logger::LogLevelError;
	else
	if( defval.equals( "I" ) )
		dv = Logger::LogLevelInfo;
	else
	if( defval.equals( "A" ) )
		dv = Logger::LogLevelDebug;
	else
		dv = Logger::LogLevelNone;

	// read list
	for( Xml item = list.getFirstChild( "class" ); item.exists(); item = item.getNextChild( "class" ) )
		{
			String name = item.getAttribute( "name" );
			String level = item.getAttribute( "level" );
			String instance = item.getAttribute( "instance" , "" );

			LogSettingsItem *lsi = new LogSettingsItem;
			lsi -> setLevelSymbol( *( const char * )level );
			lsi -> setSettings( item );

			if( !instance.isEmpty() )
				{
					String s = name + "." + instance;
					map.add( s , lsi );
				}
			else
				map.add( name , lsi );
		}
}

Xml LogSettings::getObjectLogSettings( const char *className , const char *instance , int *level )
{
	// get instance-based logger
	if( instance != NULL && *instance != 0 )
		{
			String s = className;
			s += ".";
			s += instance;
			LogSettingsItem *item = objectInstanceData.get( s );
			if( item != NULL )
				{
					*level = item -> getLevel();
					return( item -> getSettings() );
				}
		}

	// get class-based logger
	LogSettingsItem *item = objectData.get( className );
	if( item == NULL )
		{
			*level = defaultObjectLevel;
			return( objectSettings );
		}

	*level = item -> getLevel();
	return( item -> getSettings() );
}

Xml LogSettings::getServiceLogSettings( const char *className , int *level )
{
	LogSettingsItem *item = serviceData.get( className );
	if( item == NULL )
		{
			*level = defaultServiceLevel;
			return( serviceSettings );
		}

	*level = item -> getLevel();
	return( item -> getSettings() );
}

Xml LogSettings::getCustomLogSettings( const char *loggerName , int *level )
{
	LogSettingsItem *item = customData.get( loggerName );
	if( item == NULL )
		{
			*level = defaultCustomLevel;
			return( customSettings );
		}

	*level = item -> getLevel();
	return( item -> getSettings() );
}

String LogSettings::getFileName()
{
	return( logFile );
}

String LogSettings::getFormat()
{
	return( logFormat );
}
