#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

Service *MindService::newService() {
	return( new MindService() );
}

MindService::MindService() {
	lockStructure = rfc_hnd_semcreate();

	// construct items
	mindSpace = new MindSpace();
	mindMap = new MindMap();
	netSet = new MindNetSet();
	areaSet = new MindAreaSet();
	regionSet = new MindRegionSet();
	linkSet = new MindAreaLinkSet();
	activeMemory = new MindActiveMemory();

	target = NULL;
	session = NULL;
	areaIdSeq = 0;
	regionIdSeq = 0;
}

MindMap *MindService::getMindMap() {
	return( mindMap );
}

void MindService::configureService( Xml p_config ) {
	config = p_config;
}

void MindService::createService() {
	// create mind space
	logger.logInfo( "createService: creating mind space..." );
	Xml xmlMindSpace = config.getFirstChild( "MindSpace" );
	ASSERTMSG( xmlMindSpace.exists() , "createService: MindSpace is not present in mind configuration" );
	mindSpace -> createFromXml( xmlMindSpace );

	// load mind map
	logger.logInfo( "createService: creating mind map..." );
	Xml xmlMindMap = config.getFirstChild( "MindMap" );
	ASSERTMSG( xmlMindMap.exists() , "createService: MindMap is not present in mind configuration" );
	mindMap -> createFromXml( xmlMindMap );
}

void MindService::initService() {
	// create active memory
	Xml xmlActiveMemory = config.getFirstChild( "ActiveMemory" );
	ASSERTMSG( xmlActiveMemory.exists() , "createService: ActiveMemory is not present in brain configuration file" );
	activeMemory -> create( xmlActiveMemory );

	// create messaging session for mind services
	MessagingService *ms = MessagingService::getService();
	session = ms -> createSession();

	// create networks
	createNetworks();

	// create areas
	createAreas();

	// create regions in all areas
	areaSet -> initRegionsInAreaSet( target );

	// create links
	establishAreaLinks();
}

void MindService::runService() {
	// set initial thinking
	areaSet -> wakeupAreaSet( activeMemory );

	// start thinking
	activeMemory -> start();
}

void MindService::stopService() {
	// sent areas to sleep
	areaSet -> asleepAreaSet();

	// stop thinking
	activeMemory -> stop();
}

void MindService::exitService() {
	// exit areas
	areaSet -> exitAreaSet();

	// stop session
	if( session != NULL ) {
		MessagingService *ms = MessagingService::getService();
		ms -> closeSession( session );
		session = NULL;
	}
}

void MindService::destroyService() {
	areaSet -> destroyAreaSet();

	delete mindSpace;
	delete mindMap;
	delete netSet;
	delete areaSet;
	delete regionSet;
	delete linkSet;
	delete activeMemory;

	rfc_hnd_semdestroy( lockStructure );
}

void MindService::createNetworks() {
	ClassList<MindNetInfo>& list = mindMap -> getMindNets();
	for( int k = 0; k < list.count(); k++ ) {
		MindNetInfo *netinfo = list.get( k );
		netSet -> createNet( netinfo );
	}
}

void MindService::createAreas() {
	// construct only those that are configured
	createArea( "ThalamusArea" , &MindService::createThalamusArea );
	createArea( "PerceptionArea" , &MindService::createPerceptionArea );
	createArea( "HippocampusArea" , &MindService::createHippocampusArea );
	createArea( "ParietalArea" , &MindService::createParietalArea );
	createArea( "PrefrontalCortexArea" , &MindService::createPrefrontalCortexArea );
	createArea( "BasalGangliaArea" , &MindService::createBasalGangliaArea );
	createArea( "BrainStemArea" , &MindService::createBrainStemArea );
	createArea( "CranialNerveArea" , &MindService::createCranialNerveArea );
	createArea( "SpinalCordArea" , &MindService::createSpinalCordArea );
	createArea( "MotorNerveArea" , &MindService::createMotorNerveArea );
	createArea( "BodyFeelingNerveArea" , &MindService::createBodyFeelingNerveArea );
}

void MindService::createArea( String areaId , MindArea *(MindService::*pfn)() ) {
	// find area configuration
	MindAreaInfo *areaInfo = mindMap -> getAreaById( areaId );
	ASSERTMSG( areaInfo != NULL , "constructArea: warning - " + areaId + " mind area is not configured in mind configuration" );

	// check need running
	if( !areaInfo -> runEnabled() ) {
		logger.logInfo( "constructArea: " + areaId + " mind area is skipped from running" );
		return;
	}

	// construct area
	MindArea *area = (this ->* pfn)();
	if( area == NULL ) {
		logger.logInfo( "constructArea: " + areaId + " mind area is not created - ignore" );
		return;
	}

	addMindArea( area );
}

void MindService::setMindTarget( MindTarget *p_target ) {
	target = p_target;
}

void MindService::addMindArea( MindArea *area ) {
	// add mind area
	MindAreaInfo *areaInfo = mindMap -> getAreaById( area -> getClass() );
	ASSERTMSG( areaInfo != NULL , "constructArea: areas is not present in mind configuration" );

	// configure area
	area -> configure( areaInfo );

	// create area independent content 
	area -> create();

	// add to set
	areaSet -> addMindArea( area );

	logger.logInfo( "addMindArea: MindArea added name=" + areaInfo -> getAreaId() );
}

// mind links
void MindService::establishAreaLinks() {
	// create area links
	ClassList<MindAreaLinkInfo>& list = mindMap -> getLinks();
	for( int k = 0; k < list.count(); k++ ) {
		MindAreaLinkInfo *info = list.get( k );
		String masterAreaId = info -> getMasterAreaId();
		String slaveAreaId = info -> getSlaveAreaId();

		// check presense of areas
		MindArea *masterArea = areaSet -> getMindArea( masterAreaId );
		MindArea *slaveArea = areaSet -> getMindArea( slaveAreaId );
		
		// ignore link if area is not configured to start
		if( masterArea == NULL || slaveArea == NULL )
			continue;

		// create link
		MindAreaLink *link = masterArea -> createMindLink( slaveArea , info , session );
		linkSet -> addSetItem( link );
	}
}

MindArea *MindService::getMindArea( String areaId ) {
	return( areaSet -> getMindArea( areaId ) );
}

// cortex
MindRegion *MindService::getMindRegion( String regionId ) {
	MindRegion *region = regionSet -> getSetItemById( regionId );
	ASSERTMSG( region != NULL , "getMindRegion: region is not found by id=" + regionId );
	return( region );
}

ExcitatoryLink *MindService::createExcitatoryLink( MindRegionLink *link ) {
	return( new ExcitatoryLink( link ) );
}

InhibitoryLink *MindService::createInhibitoryLink( MindRegionLink *link ) {
	return( new InhibitoryLink( link ) );
}

ModulatoryLink *MindService::createModulatoryLink( MindRegionLink *link ) {
	return( new ModulatoryLink( link ) );
}

MindArea *MindService::createThalamusArea() { return( NULL ); };
MindArea *MindService::createHippocampusArea() { return( NULL ); };
MindArea *MindService::createParietalArea() { return( NULL ); };
MindArea *MindService::createPrefrontalCortexArea() { return( NULL ); };
MindArea *MindService::createBasalGangliaArea() { return( NULL ); };
MindArea *MindService::createBrainStemArea() { return( NULL ); };
MindArea *MindService::createCranialNerveArea() { return( NULL ); };
MindArea *MindService::createSpinalCordArea() { return( NULL ); };
MindArea *MindService::createMotorNerveArea() { return( NULL ); };
MindArea *MindService::createBodyFeelingNerveArea() { return( NULL ); };
