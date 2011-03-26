#include <ah_tools.h>
#include <ah_consoletool.h>
#include <adminapi\include\ah_adminapi.h>

/*#########################################################################*/
/*#########################################################################*/

ConsoleTool::ConsoleTool()
:	ToolBase( "ConsoleTool" ) {
}

ConsoleTool::~ConsoleTool() {
	logger.attachRoot();
}

int ConsoleTool::execute( int nargs , char **args ) {
	// parameters
	String url;
	String fin;
	String fout;
	for( int k = 0; k < nargs; k++ ) {
		String arg = args[ k ];
		if( arg.equals( "-s" ) ) {
			url = args[ ++k ];
			continue;
		}
			
		if( arg.equals( "-i" ) ) {
			fin = args[ ++k ];
			continue;
		}

		if( arg.equals( "-o" ) ) {
			fout = args[ ++k ];
			continue;
		}

		printf( "unknown option: %s\n" , args[ k ] );
		return( -1 );
	}

	if( url.isEmpty() ) {
		printf( "unknown server, usage: aiconsole -s <host>:<port> [-i <input file>] [-o <output file>]\n" );
		return( -1 );
	}

	FILE *sin = NULL;
	if( !fin.isEmpty() ) {
		sin = fopen( fin , "rt" );
		if( sin == NULL ) {
			printf( "cannot open input file (%s)\n" , ( const char * )fin );
			return( -2 );
		}
	}

	FILE *sout = NULL;
	if( !fout.isEmpty() ) {
		sout = fopen( fout , "at" );
		if( sout == NULL ) {
			printf( "cannot open output file (%s)\n" , ( const char * )fout );
			return( -2 );
		}
	}

	logGreeting( sout );

	api = new AdminApi;
	int result = 0;
	try {
		logInfo( sout , String( "connecting to " ) + url + "..." );
		api -> connect( url );
		logInfo( sout , String( "connected to " ) + url );

		result = executeCommands( sin , sout );
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
		result = -1;
	}
	catch( ... ) {
		logError( sout , "cannot connect for unknown reason" );
		result = -1;
	}

	return( 0 );
}

String ConsoleTool::readNextRequest( FILE *f ) {
	bool prompt = false;
	if( f == NULL ) {
		f = stdin;
		prompt = true;
	}

	String query;
	const int SIZE = 1024;
	char buffer[ SIZE ];
	while( !feof( f ) ) {
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

void ConsoleTool::logXml( FILE *f , String prefix , Xml& xml ) {
	fprintf( f , "%s:\n" , ( const char * )prefix );
	String txt = xml.serialize();
	fprintf( f , "%s\n" , ( const char * )txt );
}

void ConsoleTool::logInfo( FILE *f , String s ) {
	if( f == NULL )
		f = stdout;
	fprintf( f , "INFO: %s\n" , ( const char * )s );
}

void ConsoleTool::logError( FILE *f , String s ) {
	if( f == NULL )
		f = stderr;
	fprintf( f , "ERROR: %s\n" , ( const char * )s );
}

void ConsoleTool::logException( FILE *f , String s ) {
	if( f == NULL )
		f = stderr;
	fprintf( f , "Exception: %s\n" , ( const char * )s );
}

bool ConsoleTool::makeRequest( FILE *sin , FILE *sout ) {
	String msg = readNextRequest( sin );
	if( msg.isEmpty() )
		return( false );

	Xml request;
	try {
		request = api -> readXmlRequest( msg );
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
		return( true );
	}

	if( sin == NULL )
		logXml( stdout , "REQUEST" , request );
	if( sout != NULL )
		logXml( sout , "REQUEST" , request );
	
	Xml response;
	try {
		response = api -> execute();
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
		return( true );
	}

	if( sout != NULL )
		logXml( sout , "RESPONSE" , response );
	else
		logXml( stdout , "RESPONSE" , response );

	String status = response.getAttribute( "status" );
	if( status.equals( "Exception" ) ) {
		String exception = response.getValue();
		logException( sout , exception );
	}

	return( true );
}

void ConsoleTool::logGreeting( FILE *sout ) {
	logInfo( sout , "---------------------------" );
	logInfo( sout , "AI console" );
}

int ConsoleTool::executeCommands( FILE *sin , FILE *sout ) {
	int retval = 0;
	while( api -> isConnected() ) {
		try {
			if( !makeRequest( sin , sout ) ) {
				retval = -3;
				break;
			}
		}
		catch ( String e ) {
			logError( sout , String( "cannot execute request: " ) + e );
			retval = -3;
		}
	}

	api -> disconnect();
	logInfo( sout , "disconnected" );

	if( sin != NULL )
		fclose( sin );
	if( sout != NULL )
		fclose( sout );
		
	return( retval );
}
