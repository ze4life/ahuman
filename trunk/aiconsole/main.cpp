#include <stdio.h>
#include <string.h>
#include <aiapi.h>

String readNextRequest( FILE *f )
{
	bool prompt = false;
	if( f == NULL )
		{
			f = stdin;
			prompt = true;
		}

	String query;
	const int SIZE = 1024;
	char buffer[ SIZE ];
	while( !feof( f ) )
		{
			if( prompt )
				printf( "> " );

			*buffer = 0;
			fgets( buffer , SIZE , f );
			int len = strlen( buffer );

			// empty line is end of query
			if( len == 1 )
				return( query );

			query += buffer;
		}
	return( query );
}

void logXml( FILE *f , String prefix , Xml& xml )
{
	fprintf( f , "%s:\n" , ( const char * )prefix );
	String txt = xml.serialize();
	fprintf( f , "%s\n" , ( const char * )txt );
}

void logInfo( FILE *f , String s )
{
	if( f == NULL )
		f = stdout;
	fprintf( f , "INFO: %s\n" , ( const char * )s );
}

void logError( FILE *f , String s )
{
	if( f == NULL )
		f = stderr;
	fprintf( f , "ERROR: %s\n" , ( const char * )s );
}

void logException( FILE *f , String s )
{
	if( f == NULL )
		f = stderr;
	fprintf( f , "Exception: %s\n" , ( const char * )s );
}

bool makeRequest( AIApi& api , FILE *sin , FILE *sout )
{
	String msg = readNextRequest( sin );
	if( msg.isEmpty() )
		return( false );

	Xml request = api.readXmlRequest( msg );
	if( sin == NULL )
		logXml( stdout , "REQUEST" , request );
	if( sout != NULL )
		logXml( sout , "REQUEST" , request );

	Xml response = api.execute();
	if( sout != NULL )
		logXml( sout , "RESPONSE" , response );
	else
		logXml( stdout , "RESPONSE" , response );

	String status = response.getAttribute( "status" );
	if( status.equals( "Exception" ) )
		{
			String exception = response.getValue();
			logException( sout , exception );
		}

	return( true );
}

void logGreeting( FILE *sout )
{
	logInfo( sout , "---------------------------" );
	logInfo( sout , "AI console" );
}

void main( int argc , char **argv )
{
	// parameters
	String url;
	String fin;
	String fout;
	for( int k = 1; k < argc; k++ )
		{
			String arg = argv[ k ];
			if( arg.equals( "-s" ) )
				{
					url = argv[ ++k ];
					continue;
				}
			
			if( arg.equals( "-i" ) )
				{
					fin = argv[ ++k ];
					continue;
				}

			if( arg.equals( "-o" ) )
				{
					fout = argv[ ++k ];
					continue;
				}

			printf( "unknown option: %s\n" , argv[ k ] );
			return;
		}

	if( url.isEmpty() )
		{
			printf( "unknown server, usage: aiconsole -s <host>:<port> [-i <input file>] [-o <output file>]\n" );
			return;
		}

	FILE *sin = NULL;
	if( !fin.isEmpty() )
		{
			sin = fopen( fin , "rt" );
			if( sin == NULL )
				{
					printf( "cannot open input file (%s)\n" , ( const char * )fin );
					return;
				}
		}

	FILE *sout = NULL;
	if( !fout.isEmpty() )
		{
			sout = fopen( fout , "at" );
			if( sout == NULL )
				{
					printf( "cannot open output file (%s)\n" , ( const char * )fout );
					return;
				}
		}

	logGreeting( sout );

	AIApi api;
	try {
		api.connect( url );
		logInfo( sout , String( "connected to " ) + url );
	}
	catch( String e ) {
		logError( sout , String( "cannot connect: " ) + e );
	}
	catch( ... ) {
		logError( sout , "cannot connect for unknown reason" );
	}

	while( api.isConnected() )
		{
			try {
				if( !makeRequest( api , sin , sout ) )
					break;
			}
			catch ( String e ) {
				logError( sout , String( "cannot execute request: " ) + e );
			}
		}

	api.disconnect();
	logInfo( sout , "disconnected" );

	if( sin != NULL )
		fclose( sin );
	if( sout != NULL )
		fclose( sout );
}
