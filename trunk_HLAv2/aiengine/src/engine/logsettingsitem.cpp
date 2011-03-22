
#include "engine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class LogSettingsItem
LogSettingsItem::LogSettingsItem()
{
	level = Logger::LogLevelDebug;
}

LogSettingsItem::~LogSettingsItem()
{
}

Logger::LogLevel LogSettingsItem::getLevel()
{
	return( level );
}

void LogSettingsItem::setLevel( Logger::LogLevel p_level )
{
	level = p_level;
}

void LogSettingsItem::setLevelByName( String p_level )
{
	p_level = p_level.toUpper();
	
	if( p_level.equals( "ERROR" ) )
		level = Logger::LogLevelError;
	else if( p_level.equals( "INFO" ) )
		level = Logger::LogLevelInfo;
	else if( p_level.equals( "DEBUG" ) )
		level = Logger::LogLevelDebug;
	else
		ASSERTFAILED( "Unknown log level=" + p_level );
}

Xml LogSettingsItem::getXml()
{
	return( settings );
}

void LogSettingsItem::configure( Xml xml , String defaultLevel )
{
	settings = xml;
	setLevelByName( defaultLevel );

	// read exclude settings if any
	for( Xml item = xml.getFirstChild( "exclude" ); item.exists(); item = item.getNextChild( "exclude" ) ) {
		String name = item.getAttribute( "string" );
		excludeList.add( name , this );
	}

	// read instances if any
	for( Xml instance = xml.getFirstChild( "instance" ); instance.exists(); instance = instance.getNextChild( "instance" ) ) {
		String name = instance.getAttribute( "name" );

		LogSettingsItem *lsi = new LogSettingsItem;
		String level = instance.getAttribute( "level" );
		lsi -> configure( instance , level );
		instanceSettings.add( name , lsi );
	}
}

bool LogSettingsItem::logDisabled( Logger::LogLevel p_level )
{
	return( p_level > level );
}

bool LogSettingsItem::isExcluded( const char *s )
{
	return( excludeList.getPartial( s ) != NULL );
}

LogSettingsItem *LogSettingsItem::getSettings( const char *instance )
{
	if( instance == NULL || *instance == 0 )
		return( this );

	LogSettingsItem *is = instanceSettings.get( instance );
	if( is == NULL )
		return( this );

	return( is );
}

