
#include "aiengine_impl.h"

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

void LogSettingsItem::setLevelSymbol( char p_level )
{
	switch( p_level )
		{
			case 'N' :	level = Logger::LogLevelNone; break;
			case 'E' :	level = Logger::LogLevelError; break;
			case 'I' :	level = Logger::LogLevelInfo; break;
			case 'A' :	level = Logger::LogLevelDebug; break;
			default :
				ASSERT( false );
		}
}

Xml LogSettingsItem::getXml()
{
	return( settings );
}

void LogSettingsItem::configure( Xml xml )
{
	settings = xml;

	String level = xml.getAttribute( "level" );
	setLevelSymbol( *( const char * )level );

	// read exclude settings if any
	for( Xml item = xml.getFirstChild( "exclude" ); item.exists(); item = item.getNextChild( "exclude" ) )
		{
			String name = item.getAttribute( "string" );
			excludeList.add( name , this );
		}

	// read instances if any
	for( Xml instance = xml.getFirstChild( "instance" ); instance.exists(); instance = instance.getNextChild( "instance" ) )
		{
			String name = instance.getAttribute( "name" );

			LogSettingsItem *lsi = new LogSettingsItem;
			lsi -> configure( instance );
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

