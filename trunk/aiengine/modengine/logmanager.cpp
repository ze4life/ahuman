
#include "aiengine_impl.h"
#include <sys/types.h>
#include <sys/timeb.h>

// #############################################################################
// #############################################################################

static 	unsigned		__stdcall threadMainFunction( void *p_arg )
{
	LogManager *log = ( LogManager * )( p_arg );
	return( log -> run() );
}

RFC_HND LogManager::stopEvent = NULL;

// #############################################################################
// #############################################################################

LogManager::LogManager()
{
	engine = NULL;
	logFileStream = NULL;
	lock = rfc_hnd_semcreate();
	stopEvent = rfc_hnd_evcreate();
	rfc_hnd_evsignal( stopEvent );

	isFileLoggingEnabled = false;
	stop = true;

	va = 1000;
	v = ( LogRecord * )calloc( va , sizeof( LogRecord ) );
	extraMode = false;
	syncMode = false;

	n1e = 0; n3e = va;
	n2f = n4f = n5f = n6e = 0;

	startAdd = startGet = 0;
}

LogManager::~LogManager()
{
	stop = true;

	// check no filled data
	ASSERT( n2f == 0 && n4f == 0 && n5f == 0 );

	if( logFileStream != NULL )
		fclose( logFileStream );

	rfc_hnd_semdestroy( lock );
	rfc_hnd_evdestroy( stopEvent );
}

void LogManager::configure( Xml config )
{
	logSettings.load( config );
}

Logger::LogLevel LogManager::getObjectLogLevel( Object *o )
{
	return( ( Logger::LogLevel )logSettings.getObjectLogLevel( o -> getClass() , o -> getInstance() ) );
}

Logger::LogLevel LogManager::getServiceLogLevel( Service *s )
{
	return( ( Logger::LogLevel )logSettings.getServiceLogLevel( s -> getName() ) );
}

Logger::LogLevel LogManager::getCustomLogLevel( const char *loggerName )
{
	return( ( Logger::LogLevel )logSettings.getCustomLogLevel( loggerName ) );
}

// sync/async mode
void LogManager::setSyncMode( bool p_syncMode )
{
	syncMode = p_syncMode;
	if( syncMode == false )
		return;

	// wait till all async are written
	while( getLogRecordsPending() > 0 )
		rfc_thr_sleep( 1 );
}

bool LogManager::getSyncMode()
{
	return( syncMode );
}

void LogManager::waitForExit()
{
	rfc_hnd_waitevent( stopEvent );
}

bool LogManager::startWriter()
{
	String fileName = logSettings.getFileName();

	logFileStream = fopen( fileName , "at" );
	if( logFileStream == NULL ) {
		String error = "AIEngineImpl::logStart: cannot initialize logging: cannot open file - ";
		error += fileName;
		fprintf( stderr , error );
		return( false );
	}

	AIEngine& engine = AIEngine::getInstance();
	if( rfc_thr_process( &independentThreadID , ( void * )this , threadMainFunction ) ) {
		fprintf( stderr , "LogManager::start: cannot start listening thread" );
		return( false );
	}

	isFileLoggingEnabled = true;
	stop = false;

	return( true );
}

void LogManager::stopWriter()
{
	stop = true;
	setSyncMode( true );
}

int LogManager::run()
{
	engine = &AIEngine::getInstance();
	rfc_hnd_evreset( stopEvent );

	int status = 0;
	try {
		// do get in cycle
		while( get() );
	}
	catch ( RuntimeException& e ) {
		fprintf( stderr , "exception in logging: " , e.getMsg() );
		status = -41;
	}
	catch ( ... ) {
		fprintf( stderr , "unknown exception in logging" );
		status = -42;
	}

	rfc_hnd_evsignal( stopEvent );
	return( status );
}

void LogManager::output( LogRecord *p )
{
	struct tm *lt = localtime( &p -> time );

	if( p -> count <= 0 )
		return;

	char l_buf[ 100 ];
	sprintf( l_buf , "[%s, 0x%4.4x] %2.2d:%2.2d:%2.2d,%3.3d - " , 
		( ( p -> error )? "WARN" : "INFO" ) ,
		p -> threadId ,
		lt -> tm_hour , lt -> tm_min , lt -> tm_sec , 
		p -> time_ms );

	// output
	FILE *cs = ( p -> error )? stderr : stdout;
	if( p -> count == 1 )
		{
			fprintf( cs , "%s%s" , l_buf , p -> strings.one );
			if( p -> postfix != NULL )
				fprintf( cs , " [%s]\n" , p -> postfix );
			else
				fprintf( cs , "\n" );
			if( isFileLoggingEnabled )
				{
					fprintf( logFileStream , "%s%s" , l_buf , p -> strings.one );
					if( p -> postfix != NULL )
						fprintf( logFileStream , " [%s]\n" , p -> postfix );
					else
						fprintf( logFileStream , "\n" );
				}
		}
	else
		{
			if( p -> postfix != NULL )
				fprintf( cs , "%s [%s]\n" , l_buf , p -> postfix );
			else
				fprintf( cs , "%s\n" , l_buf );
			if( isFileLoggingEnabled )
				{
					if( p -> postfix != NULL )
						fprintf( logFileStream , "%s [%s]\n" , l_buf , p -> postfix );
					else
						fprintf( logFileStream , "%s\n" , l_buf );
				}

			for( int k = 0; k < p -> count; k++ )
				{
					fprintf( cs , "%s\n" , p -> strings.many[ k ] );
					if( isFileLoggingEnabled )
						fprintf( logFileStream , "%s\n" , p -> strings.many[ k ] );
				}
		}

	if( isFileLoggingEnabled )
		fflush( logFileStream );
}

void LogManager::add( const char **chunkLines , int count , bool error , const char *postfix )
{
	if( syncMode )
		{
			// print in sync
			LogRecord lr;
			set( &lr , false , chunkLines , count , error , postfix );
			output( &lr );
			return;
		}

	// only exclusive
	rfc_hnd_semlock( lock );

	// simple mode
	if( !extraMode )
		{
			// space available
			if( n1e || n3e )
				{
					// has space for adding
					set( &v[ startAdd ] , true , chunkLines , count , error , postfix );
					if( n4f )
						{
							n3e--;
							n2f++;
							startAdd++;
						}
					else
						{
							n3e--;
							n2f++;
							startAdd++;

							// roll to top
							if( startAdd == va )
								{
									startAdd = 0;
									n4f = n2f;
									n2f = 0;
									n3e = n1e;
									n1e = 0;
								}
						}

					// fprintf( logFileStream , "+n[%d, %d, %d, %d, %d, %d], s[%d, %d]\n" ,
					//	n1e , n2f , n3e , n4f , n5f , n6e , startAdd , startGet );
					// fflush( logFileStream );
					rfc_hnd_semunlock( lock );
					return;
				}

			// no space - start extended mode
			extraMode = true;
			startAdd = va;
		}

	// add in extra mode
	if( !n6e )
		{
			// no empty slots - reallocation required
			n6e = 100;
			va += n6e;
			v = ( LogRecord * )realloc( v , va * sizeof( LogRecord ) );
			memset( &v[ va - n6e ] , 0 , sizeof( LogRecord ) * n6e );
		}

	// write log record
	set( &v[ startAdd ] , true , chunkLines , count , error , postfix );
	startAdd++;
	n6e--;
	n5f++;

	// fprintf( logFileStream , "+n[%d, %d, %d, %d, %d, %d], s[%d, %d]\n" ,
	//	n1e , n2f , n3e , n4f , n5f , n6e , startAdd , startGet );
	// fflush( logFileStream );
	rfc_hnd_semunlock( lock );
}

void LogManager::set( LogRecord *p , bool copy , const char **chunkLines , int count , bool error , const char *postfix )
{
	p -> count = count;

	struct _timeb timebuffer;
	_ftime( &timebuffer );
	p -> time = timebuffer.time;
	p -> time_ms = timebuffer.millitm;
	p -> error = error;
	p -> threadId = ( engine == NULL )? 0 : engine -> getThreadId();

	if( count == 0 )
		p -> strings.one = NULL;
	else
	if( count == 1 )
		{
			if( copy )
				{
					p -> strings.one = strdup( *chunkLines );
					p -> postfix = ( postfix == NULL || *postfix == 0 )? NULL : strdup( postfix );
				}
			else
				{
					p -> strings.one = ( char * )*chunkLines;
					p -> postfix = ( postfix == NULL || *postfix == 0 )? NULL : ( char * )postfix;
				}
		}
	else
		{
			if( copy )
				{
					p -> strings.many = ( char ** )calloc( count , sizeof( char * ) );
					for( int k = 0; k < count; k++ )
						p -> strings.many[ k ] = strdup( chunkLines[ k ] );
					p -> postfix = ( postfix == NULL || *postfix == 0 )? NULL : strdup( postfix );
				}
			else
				{
					p -> strings.many = ( char ** )chunkLines;
					p -> postfix = ( postfix == NULL || *postfix == 0 )? NULL : ( char * )postfix;
				}
		}
}

void LogManager::clear( LogRecord *p )
{
	if( p -> count == 1 )
		{
			free( p -> strings.one );
			p -> strings.one = NULL;
		}
	else
		{
			for( int k = 0; k < p -> count; k++ )
				free( p -> strings.many[ k ] );
			free( p -> strings.many );
			p -> strings.many = NULL;
		}
	p -> count = 0;
}

bool LogManager::get()
{
	// await data
	while( 1 )
		{
			// only exclusive
			rfc_hnd_semlock( lock );

			if( n2f || n4f )
				break;

			// exit event
			if( stop )
				{
					rfc_hnd_semunlock( lock );
					return( false );
				}

			// no data - wait
			rfc_hnd_semunlock( lock );
			rfc_thr_sleep( 1 );
		}

	// get pending count
	int readFrom = startGet;
	int n = 0;
	const int maxRead = 100;
	LogRecord localRecords[ maxRead ];

	// read n2/n4 first
	if( n4f > 0 )
		{
			// read n4
			if( n4f > maxRead )
				{
					// partial read
					n4f -= maxRead;
					n3e += maxRead;
					n = maxRead;
					startGet += n;
				}
			else
				{
					// full read
					n = n4f;
					n3e += n4f;
					n4f = 0;

					// roll read to top
					startGet = n1e;
				}
		}
	else
		{
			// read n2
			if( n2f > maxRead )
				{
					// partial read
					n2f -= maxRead;
					n1e += maxRead;
					n = maxRead;
					startGet += n;
				}
			else
				{
					// full read
					n = n2f;
					n1e += n2f;
					n2f = 0;
					startGet += n;

					// extra mode
					if( extraMode )
						{
							startGet += n3e;
							n1e += n3e;
							n3e = n6e;
							n6e = 0;
							n2f = n5f;
							n5f = 0;

							extraMode = false;
						}
					else
						{
							// roll
							if( startGet == va )
								startGet = n1e;
						}
				}
		}

	// read
	memcpy( localRecords , &v[ readFrom ] , sizeof( LogRecord ) * n );
	memset( &v[ readFrom ] , 0 , sizeof( LogRecord ) * n );
	// fprintf( logFileStream , "-n[%d, %d, %d, %d, %d, %d], s[%d, %d]\n" ,
	//	n1e , n2f , n3e , n4f , n5f , n6e , startAdd , startGet );
	rfc_hnd_semunlock( lock );

	// write w/o lock
	for( int k = 0; k < n; k++ )
		{
			output( &localRecords[ k ] );
			clear( &localRecords[ k ] );
		}

	return( true );
}

int LogManager::getLogRecordsPending()
{
	rfc_hnd_semlock( lock );
	int n = n2f + n4f + n5f;
	rfc_hnd_semunlock( lock );

	return( n );
}
