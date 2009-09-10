
#include "aiengine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class Logger
// construction
Logger::Logger()
{
	o = NULL;
	s = NULL;
	logLevel = Logger::LogLevelNone;
	loggerName = NULL;
}

Logger::~Logger()
{
}

void Logger::setLogLevel( LogLevel level )
{
	logLevel = level;
}

void Logger::attach( Service *p_s )
{
	LogManager *logManager = AIEngine::getInstance().getLogManager();
	logLevel = logManager -> getServiceLogLevel( p_s );
	loggerName = p_s -> getName();
	s = p_s;
}

void Logger::attach( Object *p_o )
{
	LogManager *logManager = AIEngine::getInstance().getLogManager();
	logLevel = logManager -> getObjectLogLevel( p_o );
	loggerName = p_o -> getClass();
	o = p_o;
}

void Logger::attach( const char *p_loggerName )
{
	o = NULL;
	s = NULL;
	loggerName = p_loggerName;
	LogManager *logManager = AIEngine::getInstance().getLogManager();
	logLevel = logManager -> getCustomLogLevel( loggerName );
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

	log( String( "CALL STACK:" ) , 1 , true );

	if( skipTop > 0 )
		{
			log( String( "\t...skipped..." ) , 0 , true );
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
				", " + sl -> message + ")" , mode , true );
		}
}

// log calls
void Logger::logInfo( const char *s , int mode )
{
	if( logLevel < Logger::LogLevelInfo )
		return;

	log( s , mode , false );
}

void Logger::logError( const char *s , int mode )
{
	if( logLevel < Logger::LogLevelError )
		return;

	log( s , mode , true );
}

void Logger::logDebug( const char *s , int mode )
{
	log( s , mode , false );
}

void Logger::logObject( const char *prompt , Object *obj )
{
	if( logLevel < Logger::LogLevelInfo )
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
	logManager -> add( lines , 2 , false , getPostfix() );
}

void Logger::log( const char *s , int mode , bool error )
{
	AIEngine& engine = AIEngine::getInstance();
	ThreadLogTail *logTail = ( ThreadLogTail * )engine.getWorkerObject( "LogTail" );

	LogManager *logManager = engine.getLogManager();
	if( logTail == NULL )
		{
			logManager -> add( &s , 1 , error , getPostfix() );
			return;
		}
	
	// release old
	String& w = logTail -> lastMsg;
	if( logTail -> remains )
		{
			if( mode == 1 || mode < 0 )
				{
					const char *p = logTail -> lastMsg;
					logManager -> add( &p , 1 , error , getPostfix() );

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
			logManager -> add( &p , 1 , error , getPostfix() );
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
	return( logLevel == LogLevelAll );
}

