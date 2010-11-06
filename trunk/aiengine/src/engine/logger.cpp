
#include "engine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class Logger
// construction
Logger::Logger()
{
	o = NULL;
	s = NULL;
	loggerName = NULL;
	settings = NULL;
}

Logger::~Logger()
{
}

void Logger::attachRoot()
{
	loggerName = ".";

	LogManager *logManager = AIEngine::getInstance().getLogManager();
	settings = logManager -> getDefaultSettings();
}

void Logger::attach( Service *p_s )
{
	loggerName = p_s -> getName();
	s = p_s;

	LogManager *logManager = AIEngine::getInstance().getLogManager();
	settings = logManager -> getServiceLogSettings( p_s );
}

void Logger::attach( Object *p_o )
{
	loggerName = p_o -> getClass();
	o = p_o;

	LogManager *logManager = AIEngine::getInstance().getLogManager();
	settings = logManager -> getObjectLogSettings( p_o );
}

void Logger::attach( const char *p_loggerName )
{
	LogManager *logManager = AIEngine::getInstance().getLogManager();

	// attach custom only if set
	LogSettingsItem *settingsNew = logManager -> getCustomLogSettings( p_loggerName );
	if( settingsNew == NULL ) {
		// set to default if none currently
		if( settings == NULL ) {
			settingsNew = logManager -> getCustomDefaultLogSettings();
		}
	}

	loggerName = p_loggerName;
	if( settingsNew != NULL )
		settings = settingsNew;
}

// stack
void Logger::printStack()
{
	rfc_threadstack *stack = rfc_thr_stackget( 1 );
	printStackInternal( stack , 0 , true );
	rfc_thr_stackfree( stack );
}

void Logger::printStack( rfc_threadstack *stack , int skipTop )
{
	printStackInternal( stack , skipTop , false );
}

void Logger::printStackInplace( rfc_threadstack *stack , int skipTop )
{
	printStackInternal( stack , skipTop , true );
}

void Logger::printStackInternal( rfc_threadstack *stack , int skipTop , bool printInplace )
{
	int startItem = rfc_thr_stackfulldepth( stack ) - 1;

	log( String( "CALL STACK:" ) , ( ( printInplace )? Logger::LogLine : Logger::LogStart ) , Logger::LogLevelInfo );

	if( skipTop == 0 )
		skipTop = stack -> extraLevels;
	if( skipTop > 0 ) {
		log( String( "\t...skipped..." ) , Logger::LogLine , Logger::LogLevelInfo );
		startItem -= skipTop;
	}

	for( int k = startItem; k >= 0; k-- ) {
		rfc_threadstacklevel *sl = rfc_thr_stacklevel( stack , k );

		LogOutputMode mode = Logger::LogLine;
		if( k == 0 )
			mode = ( ( printInplace )? Logger::LogLine : Logger::LogStop );

		// extract short name
		String moduleName = sl -> moduleName;
		int from = moduleName.findLastAny( "/\\" );
		int to = moduleName.findLast( '.' );

		String moduleNameShort = moduleName;
		if( from >= 0 && to >= 0 )
			moduleNameShort = moduleNameShort.getMid( from + 1 , to - from - 1 );

		log( String( "\t" ) + sl -> className + 
			"::" + sl -> functionName + 
			" (" + moduleNameShort + 
			", " + sl -> message + ")" , mode , Logger::LogLevelInfo );

		// stop after main function
		String functionName = sl -> functionName;
		if( k > 0 )
			if( strcmp( functionName , "_main" ) == 0 ||
				strcmp( functionName , "threadMainFunction" ) == 0 ||
				strcmp( functionName , "runThread" ) == 0 ) {
				mode = Logger::LogStop;
				log( "\t...skipped..." , mode , Logger::LogLevelInfo );
				break;
			}
	}
}

// log calls
void Logger::logInfo( const char *s , LogOutputMode mode )
{
	if( settings == NULL )
		attachRoot(); 
	if( settings -> logDisabled( Logger::LogLevelInfo ) )
		return;

	log( s , mode , Logger::LogLevelInfo );
}

void Logger::logError( const char *s , LogOutputMode mode )
{
	if( settings == NULL )
		attachRoot(); 
	if( settings -> logDisabled( Logger::LogLevelError ) )
		return;

	log( s , mode , Logger::LogLevelError );
}

void Logger::logDebug( const char *s , LogOutputMode mode )
{
	if( settings == NULL )
		attachRoot(); 
	if( settings -> logDisabled( Logger::LogLevelDebug ) )
		return;

	log( s , mode , Logger::LogLevelDebug );
}

void Logger::logObject( const char *prompt , Object *obj , Logger::LogLevel p_logLevel )
{
	if( settings == NULL )
		attachRoot(); 
	if( settings -> logDisabled( p_logLevel ) )
		return;

	const char *lines[2];
	String p = "%s: ";
	p += prompt;
	lines[ 0 ] = p;
	
	SerializeObject *so = obj -> getSerializeObject();
	Object::serialize( obj , *so );

	String data = so -> getDataStringNameToValue();
	lines[ 1 ] = data;

	LogManager *logManager = AIEngine::getInstance().getLogManager();
	logManager -> add( lines , 2 , p_logLevel , getPostfix() );
}

void Logger::log( const char *s , LogOutputMode mode , Logger::LogLevel p_logLevel )
{
	// check needs to be excluded
	if( settings == NULL )
		attachRoot(); 
	if( settings -> isExcluded( s ) )
		return;

	AIEngine& engine = AIEngine::getInstance();
	EngineThreadHelper *logTail = EngineThreadHelper::getThreadObject();

	LogManager *logManager = engine.getLogManager();
	if( logTail == NULL ) {
		logManager -> add( &s , 1 , p_logLevel , getPostfix() );
		return;
	}
	
	// release old
	String& w = logTail -> lastMsg;
	if( logTail -> remains )
		if( mode == Logger::LogStart || mode == Logger::LogDefault ) {
			const char *p = w;
			logManager -> add( &p , 1 , p_logLevel , getPostfix() );

			logTail -> remains = false;
			w.clear();
		}

	w += s;
	if( mode ==	Logger::LogLine || mode == Logger::LogStart )
		w += "\n";

	if( mode == Logger::LogStop || mode == Logger::LogDefault ) {
		const char *p = w;
		logManager -> add( &p , 1 , p_logLevel , getPostfix() );
		logTail -> remains = false;
		w.clear();
	}
	else
		logTail -> remains = true;
}

const char *Logger::getPostfix()
{
	if( loggerName != NULL )
		return( loggerName );
	return( NULL );
}

bool Logger::isLogAll()
{
	if( settings == NULL )
		attachRoot(); 
	return( settings -> getLevel() == LogLevelDebug );
}

Xml Logger::getLogSettings()
{
	if( settings == NULL )
		attachRoot(); 
	return( settings -> getXml() );
}
