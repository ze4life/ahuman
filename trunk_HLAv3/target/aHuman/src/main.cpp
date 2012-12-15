#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

void execute( String etcpath , String component , String connector ) {
	// create service manager
	ServiceManager sm;
	sm.setRootLogLevel( Logger::LogLevelDebug );

	// add services
	sm.addService( new AHumanTarget( component , connector ) );
	sm.addService( MindService::newService() );
	sm.addPlatformServices();

	// configure all
	sm.configureDefault( etcpath );

	// execute services
	sm.execute();
}

int main(int argc, char** argv) {
	if( argc < 4 ) {
		printf( "Arguments: <config directory path> <initial message target component> <connector>\n" );
		return( -1 );
	}

	execute( argv[1] , argv[2] , argv[3] );
}

