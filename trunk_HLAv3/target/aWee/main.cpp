#include "stdafx.h"

void execute( String etcpath )
{
	// create services
	ServiceManager sm;
	try {
		sm.addPlatformServices();

		// configure all
		sm.configureDefault( etcpath );

		// create configured services
		sm.createServices();
		sm.destroyServices();
	}
	catch( RuntimeException& e ) {
		Logger logger;
		logger.attachRoot();
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

