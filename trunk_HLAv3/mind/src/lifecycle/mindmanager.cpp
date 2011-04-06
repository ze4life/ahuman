#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

Service *MindManager::newService() {
	return( new MindManager() );
}

MindManager::MindManager() {
	mindMap = new MindMap();
	lockStructure = ( RFC_HND )NULL;
	sessionId = 0;
	cortexId = 0;
	activeMemory = NULL;
}

MindMap *MindManager::getMindMap() {
	return( mindMap );
}

void MindManager::configureService( Xml p_config ) {
	config = p_config;
}

void MindManager::createService() {
	// load mind map
	logger.logInfo( "createService: reading mind map..." );
	Xml xmlMindMap = config.getFirstChild( "MindMap" );
	ASSERTMSG( xmlMindMap.exists() , "createService: MindMap is not present in brain configuration file" );

	mindMap -> createFromXml( xmlMindMap );

	// cortex handlers
	int index = 0;
	// index = cortexFactories.add( &AIBrainImpl::onCreateXXXCortex ); mapCortexFactoryIndex.add( "XXX" , index );

	// lock
	lockStructure = rfc_hnd_semcreate();

	// create active memory
	activeMemory = new MindActiveMemory();
}

void MindManager::initService() {
	// create active memory
	Xml xmlActiveMemory = config.getFirstChild( "ActiveMemory" );
	ASSERTMSG( xmlActiveMemory.exists() , "createService: ActiveMemory is not present in brain configuration file" );
	activeMemory -> create( xmlActiveMemory );

	// create IO session
	MessagingService *ms = MessagingService::getService();
	ioBrainSession = ms -> createSession();

	// now always create all registered mind areas
	for( int k = mindAreas.count() - 1; k >= 0; k-- ) {
		MindArea *area = mindAreas.getClassByIndex( k );
		area -> onCreateArea();
	}
}

void MindManager::runService() {
	// enable areas to live
	for( int k = mindAreas.count() - 1; k >= 0; k-- ) {
		MindArea *area = mindAreas.getClassByIndex( k );
		area -> onBrainStart();
	}

	// start thinking
	activeMemory -> start();
}

void MindManager::stopService() {
	// stop thinking
	if( activeMemory != NULL )
		activeMemory -> stop();

	// inform areas about exit
	for( int k = mindAreas.count() - 1; k >= 0; k-- ) {
		MindArea *area = mindAreas.getClassByIndex( k );
		area -> onBrainStop();
	}
}

void MindManager::exitService() {
}

void MindManager::destroyService() {
	// drop memory
	if( activeMemory != NULL )
		delete activeMemory;

	// drop cortexes
	mapCortex.destroy();

	// static data
	if( mindMap != NULL )
		delete mindMap;

	if( lockStructure != ( RFC_HND )NULL )
		rfc_hnd_semdestroy( lockStructure );

	delete this;
}

// mind areas
void MindManager::addMindArea( String areaId , MindArea *area ) {
	MindAreaInfo *info = mindMap -> getAreaById( areaId );
	ASSERTMSG( info != NULL , "Unknown mind area: id=" + areaId );

	ASSERTMSG( mindAreas.get( areaId ) == NULL , "duplicate area to be added: " + areaId );
	mindAreas.add( areaId , area );
	area -> attach( areaId );
	
	// create links for this area
	ClassList<MindLinkInfo>& links = mindMap -> getLinks();
	for( int k = links.count() - 1; k >= 0; k-- ) {
		MindLinkInfo *linkInfo = links.get( k );
		
		String masterAreaId = linkInfo -> getMasterAreaId();
		String slaveAreaId = linkInfo -> getSlaveAreaId();

		// create only if new
		if( masterAreaId.equals( areaId ) ||
			slaveAreaId.equals( areaId ) ) {
			// find areas
			MindArea *masterArea = getMindArea( masterAreaId );
			if( masterArea == NULL )
				continue;

			MindArea *slaveArea = getMindArea( slaveAreaId );
			if( slaveArea == NULL )
				continue;
		
			// create area
			createMindLink( linkInfo , masterArea , slaveArea );
		}
	}
}

MindArea *MindManager::getMindArea( String areaId ) {
	return( mindAreas.get( areaId ) );
}

// cortex
Cortex *MindManager::getCortex( String cortexId ) {
	Cortex *cortex = mapCortex.get( cortexId );
	ASSERTMSG( cortex != NULL , "cortex is not found by id=" + cortexId );
	return( cortex );
}

void MindManager::registerCortex( Cortex *cortex , MindArea *area , const MindLocation& relativeLocation ) {
	lock();
	String id = cortex -> getId();
	if( id.isEmpty() ) {
		id = String( "CTX" ) + sessionId + "S" + ++cortexId + "C";
		cortex -> setId( id );
	}

	if( mapCortex.get( id ) != NULL ) {
		unlock();
		ASSERTFAILED( "Cortex has non-uniqie id=" + id );
		return;
	}

	mapCortex.add( id , cortex );
	unlock();

	area -> addCortex( cortex , relativeLocation );
	logger.logInfo( "registerCortex: cortex created - id=" + id + ", type=" + cortex -> getNetType() + 
		", size=" + cortex -> getNSize() + ", inputs=" + cortex -> getNInputs() + ", outputs=" + cortex -> getNOutputs() );
}

// mind area links
MindLink *MindManager::createMindLink( MindLinkInfo *linkInfo , MindArea *masterArea , MindArea *slaveArea ) {
	// create link
	MindLink *link = new MindLink( linkInfo );
	link -> open( ioBrainSession );
	mindLinks.add( link );

	masterArea -> addMindLink( link );
	slaveArea -> addMindLink( link );

	return( link );
}

Cortex *MindManager::createNeoCortex( MindArea *area , MindLocation& relativeLocation ) {
	// create adapter
	Cortex *cortex = createCortexAdapter( "neocortex" , area , relativeLocation );

	// register cortex
	registerCortex( cortex , area , relativeLocation );
	return( cortex );
}

void MindManager::registerSensorCortex( MindArea *area , MindLocation& relativeLocation , Cortex *cortex ) {
	int inputs = cortex -> getNInputs();
	int outputs = cortex -> getNOutputs();

	// create absolute location
	const MindLocation& areaLocation = area -> getLocation();
	MindLocation cortexLocation = areaLocation.getAbsoluteLocation( relativeLocation );

	// register cortex
	registerCortex( cortex , area , cortexLocation );
}

Cortex *MindManager::createCortexAdapter( String cortexType , MindArea *area , MindLocation& relativeLocation ) {
	return( NULL );
}
