#include <ah_platform.h>

/*#########################################################################*/
/*#########################################################################*/

Service *EnvService::newService() {
	return( new EnvService() );
}

void EnvService::destroyService() {
	for( int k = 0; k < configs.count(); k++ ) {
		Xml *doc = configs.getClassByIndex( k );
		doc -> destroy();
	}
	configs.destroy();
}

Xml EnvService::loadXml( String fileName )
{
	// check whether already loaded
	Xml *doc = configs.get( fileName );
	if( doc == NULL ) {
		// init instance
		String path = configDir + "/" + fileName;
		doc = new Xml( Xml::load( path ) );

		configs.add( fileName , doc );
	}

	return( *doc );
}

String EnvService::getConfigurationPath( String etcpath )
{
	return( configDir + "/" + etcpath );
}

