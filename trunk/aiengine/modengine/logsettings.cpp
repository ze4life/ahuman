
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

void LogSettings::load( const char *configName )
{
	// read
	AIEngine& engine = AIEngine::getInstance();
	TiXmlElement *xml = engine.getRoot( configName );
	ASSERT( xml != NULL );
	TiXmlElement *xmlFileName = xml -> FirstChildElement( "filename" );
	ASSERT( xmlFileName != NULL );
	logFile = xmlFileName -> GetText();

	TiXmlElement *xmlFormat = xml -> FirstChildElement( "format" );
	ASSERT( xmlFormat != NULL );
	logFormat = xmlFormat -> GetText();

	readLevels( xml , "objectLogLevel" , objectData , defaultObjectLevel );
	readLevels( xml , "objectInstanceLogLevel" , objectInstanceData , defaultObjectInstanceLevel );
	readLevels( xml , "serviceLogLevel" , serviceData , defaultServiceLevel );
	readLevels( xml , "customLogLevel" , customData , defaultCustomLevel );
}

void LogSettings::readLevels( TiXmlElement *root , const char *listName , MapStringToClass<LogSettingsItem>& map , int& dv )
{
	map.destroy();

	TiXmlElement *listRoot = root -> FirstChildElement( listName );
	if( listRoot == NULL )
		return;

	// read default value
	String defval = listRoot -> Attribute( "default" );
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
	TiXmlElement *item = listRoot -> FirstChildElement( "class" );
	if( item == NULL )
		return;

	do
		{
			String name = item -> Attribute( "name" );
			String level = item -> Attribute( "level" );
			const char *instance = item -> Attribute( "instance" );

			LogSettingsItem *lsi = new LogSettingsItem;
			lsi -> setLevelSymbol( *( const char * )level );

			if( instance != NULL )
				{
					String s = name + "." + instance;
					map.add( s , lsi );
				}
			else
				map.add( name , lsi );

			item = item -> NextSiblingElement( "class" );
		}
	while( item != NULL );
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
