
#include "aiengine.h"

/*#########################################################################*/
/*#########################################################################*/

// argv[1] = configuration files directory
int main( int argc , char* argv[] )
{
	if( argc != 2 ) {
		fprintf( stderr , "Syntax: aiengine <config files dir>\n" );
		return( -1 );
	}

	return( AIEngine::run( argv[ 1 ] ) );
}
