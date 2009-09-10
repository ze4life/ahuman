
#include "aiengine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class LogSettingsItem
LogSettingsItem::LogSettingsItem()
{
}

LogSettingsItem::~LogSettingsItem()
{
}

int LogSettingsItem::getLevel()
{
	return( level );
}

void LogSettingsItem::setLevel( int p_level )
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
			case 'A' :	level = Logger::LogLevelAll; break;
			default :
				ASSERT( false );
		}
}

