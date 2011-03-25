#include "stdafx.h"

void execute( String etcpath )
{
	// create services
	ServiceManager sm;
	sm.setRootLogLevel( Logger::LogLevelDebug );
	Logger logger;
	logger.attachRoot();

	logger.logInfo( "AL/aWee: PREPARE TO START/CONFIGURING..." );

	try {
		sm.addPlatformServices();

		// configure all
		sm.configureDefault( etcpath );

		logger.logInfo( "--------------------" );
		logger.logInfo( "AL/aWee: STARTING..." );
		logger.logInfo( "--------------------" );

		// create and run services
		sm.createServices();
		sm.initServices();
		sm.runServices();

		// wait for completion
		logger.logInfo( "--------------------" );
		logger.logInfo( "AL/aWee: RUNNING..." );
		logger.logInfo( "--------------------" );
		sm.waitRunDefault();
	}
	catch( RuntimeException& e ) {
		logger.logInfo( "----------------------------------" );
		logger.logInfo( "AL/aWee: STARTUP/RUNTIME EXCEPTION" );
		logger.logInfo( "----------------------------------" );

		logger.printStack( e );
	}

	// cleanup
	try {
		logger.logInfo( "--------------------" );
		logger.logInfo( "AL/aWee: STOPPING..." );
		logger.logInfo( "--------------------" );

		sm.stopServices();
		sm.exitServices();
		sm.destroyServices();

		logger.logInfo( "----------------" );
		logger.logInfo( "AL/aWee: STOPPED" );
		logger.logInfo( "----------------" );
	}
	catch( RuntimeException& e ) {
		logger.logInfo( "------------------------------" );
		logger.logInfo( "AL/aWee: EXCEPTION ON SHUTDOWN" );
		logger.logInfo( "------------------------------" );
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

