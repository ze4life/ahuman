#include "stdafx.h"

void execute( String etcpath )
{
	// create services
	ServiceManager sm;
	sm.setRootLogLevel( Logger::LogLevelDebug );
	Logger logger;
	logger.attachRoot();

	try {
		sm.addPlatformServices();

		// configure all
		sm.configureDefault( etcpath );

		// create and configured services
		sm.createServices();
		sm.initServices();
		sm.runServices();

		// wait for completion
		sm.waitRunDefault();
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
	}

	// cleanup
	try {
		if( sm.isRunning() )
			sm.stopServices();
		if( sm.isCreated() )
			sm.exitServices();
		sm.destroyServices();
	}
	catch( RuntimeException& e ) {
		logger.printStack( e );
	}
}

int main(int argc, char** argv)
{
	if( argc < 2 ) {
		printf( "Arguments: [config directory path]\n" );
		return( -1 );
	}

	execute( argv[1] );
}

