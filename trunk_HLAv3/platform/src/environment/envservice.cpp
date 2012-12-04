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

void EnvService::setConfigurationPath( String etcpath ) {
	configDir = etcpath;
}

String EnvService::getConfigurationPath( String etcpath ) {
	return( configDir + "/" + etcpath );
}

void EnvService::configureAll( String etcpath ) {
	logger.logInfo( "CONFIGURING SERVICES using etcpath=" + etcpath );
	setConfigurationPath( etcpath );

	// configure platform
	configurePlatform();
	// configure services
	configureServices();
}

void EnvService::configurePlatform() {
	// read main configuration file
	Xml cfgMain = loadXml( "main.xml" );

	// configure platform
	Xml cfgPlatform = cfgMain.getChildNode( "platform" );
	ASSERTMSG( cfgPlatform.exists() , "Platform configuration is not defined" );

	ServiceManager& sm = ServiceManager::getInstance();

	// configure lifecycle
	Xml cfgLifecycleSection = cfgPlatform.getChildNode( "lifecycle" );
	Xml cfgLifecycle = getConfigurationData( cfgLifecycleSection , "platform" , "lifecycle" );
	sm.configureLifecycle( cfgLifecycle );

	// configure logging
	Xml cfgLoggingSection = cfgPlatform.getChildNode( "logging" );
	Xml cfgLogging = getConfigurationData( cfgLoggingSection , "platform" , "logging" );
	sm.configureLogging( cfgLogging );
}

void EnvService::configureServices() {
	// read main configuration file
	Xml cfgMain = loadXml( "main.xml" );

	// configure services
	ServiceManager& sm = ServiceManager::getInstance();
	ClassList<Service>& list = sm.getServices();
	Xml cfgServices = cfgMain.getChildNode( "services" );

	for( int k = 0; k < list.count(); k++ ) {
		// configure service
		Service *svc = list.get( k );
		String name = svc -> getServiceName();
		
		// get service configuration
		logger.logInfo( "Configure service name=" + name );
		Xml svcSection = cfgServices.getChildNamedNode( "service" , name );

		// if section is not present, service is ignored
		if( !svcSection.exists() ) {
			svc -> isCreate = svc -> isInit = svc -> isRun = false;
			logger.logInfo( "Service is not present in configuration, skipped - name=" + name );
			continue;
		}

		Xml cfgSvc = getConfigurationData( svcSection , "service" , name );

		// configure service
		svc -> configureLifecycle( svcSection );

		// ignore servic e if not going to be created
		if( svc -> isCreate )
			svc -> configureService( cfgSvc );
	}
}

Xml EnvService::loadXml( String fileName ) {
	// check whether already loaded
	Xml *doc = configs.get( fileName );
	if( doc == NULL ) {
		// init instance
		String path = getConfigurationPath( fileName );
		doc = new Xml( Xml::load( path ) );

		configs.add( fileName , doc );
	}

	return( *doc );
}

Xml EnvService::getConfigurationData( Xml section , String objectType , String objectName ) {
	String id = objectType + ": name=" + objectName;
	ASSERTMSG( section.exists() , "Unable to find configuration for " + id );

	// use configuration section if file is not defined
	String svcFile = section.getProperty( "configuration" , "" );
	if( svcFile.isEmpty() )
		return( section );

	Xml cfgSvc = loadXml( svcFile );
	ASSERTMSG( cfgSvc.exists() , "Unable to load configuration file for " + id + ", path=" + getConfigurationPath( svcFile ) );

	return( cfgSvc );
}
