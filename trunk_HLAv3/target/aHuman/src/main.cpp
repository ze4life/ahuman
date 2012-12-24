#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

void execute( String etcpath ) {
	// create service manager
	ServiceManager sm;
	sm.setRootLogLevel( Logger::LogLevelDebug );

	// add services
	sm.addService( new AHumanTarget() );
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

	execute( argv[1] );
}

