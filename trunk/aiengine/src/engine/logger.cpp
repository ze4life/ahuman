
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
	loggerName = p_loggerName;

	LogManager *logManager = AIEngine::getInstance().getLogManager();
	settings = logManager -> getCustomLogSettings( loggerName );
}

// stack
void Logger::printStack()
{
	rfc_threadstack *stack = rfc_thr_stackget( 1 );
	printStack( stack , 0 );
	rfc_thr_stackfree( stack );
}

void Logger::printStack( rfc_threadstack *stack , int skipTop )
{
	int startItem = rfc_thr_stackfulldepth( stack ) - 1;

	log( String( "CALL STACK:" ) , 1 , Logger::LogLevelInfo );

	if( skipTop == 0 )
		skipTop = stack -> extraLevels;
	if( skipTop > 0 )
		{
			log( String( "\t...skipped..." ) , 0 , Logger::LogLevelInfo );
			startItem -= skipTop;
		}

	for( int k = startItem; k >= 0; k-- )
		{
			rfc_threadstacklevel *sl = rfc_thr_stacklevel( stack , k );

			int mode = 0;
			if( k == 0 )
				mode = 2;

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
					strcmp( functionName , "threadMainFunction" ) == 0 ) {
					mode = 2;
					log( "\t...skipped..." , mode , Logger::LogLevelInfo );
					break;
				}
		}
}

// log calls
void Logger::logInfo( const char *s , int mode )
{
	if( settings == NULL )
		attachRoot(); 
	if( settings -> logDisabled( Logger::LogLevelInfo ) )
		return;

	log( s , mode , Logger::LogLevelInfo );
}

void Logger::logError( const char *s , int mode )
{
	if( settings == NULL )
		attachRoot(); 
	if( settings -> logDisabled( Logger::LogLevelError ) )
		return;

	log( s , mode , Logger::LogLevelError );
}

void Logger::logDebug( const char *s , int mode )
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

void Logger::log( const char *s , int mode , Logger::LogLevel p_logLevel )
{
	// check needs to be excluded
	if( settings == NULL )
		attachRoot(); 
	if( settings -> isExcluded( s ) )
		return;

	AIEngine& engine = AIEngine::getInstance();
	EngineThreadHelper *logTail = EngineThreadHelper::getThreadObject();

	LogManager *logManager = engine.getLogManager();
	if( logTail == NULL )
		{
			logManager -> add( &s , 1 , p_logLevel , getPostfix() );
			return;
		}
	
	// release old
	String& w = logTail -> lastMsg;
	if( logTail -> remains )
		{
			if( mode == 1 || mode < 0 )
				{
					const char *p = logTail -> lastMsg;
					logManager -> add( &p , 1 , p_logLevel , getPostfix() );

					logTail -> remains = false;
					w.clear();
				}
		}

	w += s;
	if( mode ==	0 || mode == 1 )
		w += "\n";

	if( mode == 2 || mode < 0 )
		{
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
