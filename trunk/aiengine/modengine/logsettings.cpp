
#include "aiengine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class LogSettings : public Object
LogSettings::LogSettings()
{
	defaultObjectLevel = Logger::LogLevelAll;
	defaultObjectInstanceLevel = Logger::LogLevelAll;
	defaultServiceLevel = Logger::LogLevelAll;
	defaultCustomLevel = Logger::LogLevelAll;
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

	readLevels( config , "objectLogLevel" , objectData , defaultObjectLevel );
	readLevels( config , "objectInstanceLogLevel" , objectInstanceData , defaultObjectInstanceLevel );
	readLevels( config , "serviceLogLevel" , serviceData , defaultServiceLevel );
	readLevels( config , "customLogLevel" , customData , defaultCustomLevel );
}

void LogSettings::readLevels( Xml config , const char *listName , MapStringToClass<LogSettingsItem>& map , int& dv )
{
	map.destroy();

	Xml list = config.getChildNode( listName );
	if( !list.exists() )
		return;

	// read default value
	String defval = list.getAttribute( "default" );
	if( defval.equals( "E" ) )
		dv = Logger::LogLevelError;
	else
	if( defval.equals( "I" ) )
		dv = Logger::LogLevelInfo;
	else
	if( defval.equals( "A" ) )
		dv = Logger::LogLevelAll;
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

			if( !instance.isEmpty() )
				{
					String s = name + "." + instance;
					map.add( s , lsi );
				}
			else
				map.add( name , lsi );
		}
}

int LogSettings::getObjectLogLevel( const char *className , const char *instance )
{
	// get instance-based logger
	if( instance != NULL && *instance != 0 )
		{
			String s = className;
			s += ".";
			s += instance;
			LogSettingsItem *item = objectInstanceData.get( s );
			if( item != NULL )
				return( item -> getLevel() );
		}

	// get class-based logger
	LogSettingsItem *item = objectData.get( className );
	if( item == NULL )
		return( defaultObjectLevel );

	return( item -> getLevel() );
}

int LogSettings::getServiceLogLevel( const char *className )
{
	LogSettingsItem *item = serviceData.get( className );
	if( item == NULL )
		return( defaultServiceLevel );

	return( item -> getLevel() );
}

int LogSettings::getCustomLogLevel( const char *loggerName )
{
	LogSettingsItem *item = customData.get( loggerName );
	if( item == NULL )
		return( defaultCustomLevel );

	return( item -> getLevel() );
}

String LogSettings::getFileName()
{
	return( logFile );
}

String LogSettings::getFormat()
{
	return( logFormat );
}
