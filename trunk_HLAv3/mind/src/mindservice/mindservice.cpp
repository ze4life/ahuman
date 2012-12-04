#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

neurovt_state	NEURON_SYNAPTIC_THRESHOLD_INITIAL_pQ;
neurovt_state	NEURON_SYNAPTIC_THRESHOLD_MIN_pQ;
neurovt_state	NEURON_ACTION_POTENTIAL_BY_SIGNAL_pQ;
neurovt_state	NEURON_MEMBRANE_POTENTIAL_BY_ACTION_POTENTIAL_pQ;
neurovt_state	NEURON_MEMBRANE_THRESHOLD_INITIAL_pQ;
neurovt_state	NEURON_FIRE_OUTPUT_BY_MEMBRANE_POTENTIAL_pQ;
neurovt_state	NEURON_INHIBIT_DELAY_ms;
neurovt_state	NEURON_FIRE_OUTPUT_SILENT_ms;
neurovt_state	NEURON_FIRE_IMPULSE_pQ;
neurovt_state	NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms;
neurovt_state	NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms;
int				NEURON_CONNECTIVITY_UPDATE_FACTOR;
RFC_INT64		NEURON_FULL_RELAX_ms;

/*#########################################################################*/
/*#########################################################################*/

Service *MindService::newService() {
	return( new MindService() );
}

MindService::MindService() {
	lockStructure = rfc_hnd_semcreate();

	// construct items
	mindSpace = NULL;
	mindMap = NULL;
	areaSet = NULL;
	regionSet = NULL;
	linkSet = NULL;
	activeMemory = NULL;

	target = NULL;
	session = NULL;
	areaIdSeq = 0;
	regionIdSeq = 0;
}

MindActiveMemory *MindService::getActiveMemory() {
	return( activeMemory );
}

MindMap *MindService::getMindMap() {
	return( mindMap );
}

void MindService::configureService( Xml p_config ) {
	config = p_config;

	// variables
	Xml configVar = config.getChildNode( "neural-networks" );
	NEURON_SYNAPTIC_THRESHOLD_INITIAL_pQ = configVar.getIntProperty( "NEURON_SYNAPTIC_THRESHOLD_INITIAL_pQ" );
	NEURON_SYNAPTIC_THRESHOLD_MIN_pQ = configVar.getIntProperty( "NEURON_SYNAPTIC_THRESHOLD_MIN_pQ" );
	NEURON_ACTION_POTENTIAL_BY_SIGNAL_pQ = configVar.getIntProperty( "NEURON_ACTION_POTENTIAL_BY_SIGNAL_pQ" );
	NEURON_MEMBRANE_POTENTIAL_BY_ACTION_POTENTIAL_pQ = configVar.getIntProperty( "NEURON_MEMBRANE_POTENTIAL_BY_ACTION_POTENTIAL_pQ" );
	NEURON_MEMBRANE_THRESHOLD_INITIAL_pQ = configVar.getIntProperty( "NEURON_MEMBRANE_THRESHOLD_INITIAL_pQ" );
	NEURON_FIRE_OUTPUT_BY_MEMBRANE_POTENTIAL_pQ = configVar.getIntProperty( "NEURON_FIRE_OUTPUT_BY_MEMBRANE_POTENTIAL_pQ" );
	NEURON_INHIBIT_DELAY_ms = configVar.getIntProperty( "NEURON_INHIBIT_DELAY_ms" );
	NEURON_FIRE_OUTPUT_SILENT_ms = configVar.getIntProperty( "NEURON_FIRE_OUTPUT_SILENT_ms" );
	NEURON_FIRE_IMPULSE_pQ = configVar.getIntProperty( "NEURON_FIRE_IMPULSE_pQ" );
	NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms = configVar.getIntProperty( "NEURON_POTENTIAL_DISCHARGE_RATE_pQ_per_ms" );
	NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms = configVar.getIntProperty( "NEURON_OUTPUT_DISCHARGE_RATE_pQ_per_ms" );
	NEURON_CONNECTIVITY_UPDATE_FACTOR = configVar.getIntProperty( "NEURON_CONNECTIVITY_UPDATE_FACTOR" );
	NEURON_FULL_RELAX_ms = configVar.getIntProperty( "NEURON_FULL_RELAX_ms" );
}

void MindService::createService() {
	// construct items
	mindSpace = new MindSpace();
	mindMap = new MindMap();
	areaSet = new MindAreaSet();
	regionSet = new MindRegionSet();
	linkSet = new MindAreaLinkSet();
	activeMemory = new MindActiveMemory();

	// create mind space
	logger.logInfo( "createService: creating mind space..." );
	Xml xmlMindSpace = config.getFirstChild( "mind-space" );
	ASSERTMSG( xmlMindSpace.exists() , "createService: mind-space is not present in mind configuration" );
	mindSpace -> createFromXml( xmlMindSpace );

	// load mind map
	logger.logInfo( "createService: creating mind map..." );
	Xml xmlMindMap = config.getFirstChild( "mind-map" );
	ASSERTMSG( xmlMindMap.exists() , "createService: mind-map is not present in mind configuration" );
	mindMap -> createFromXml( xmlMindMap );
}

void MindService::initService() {
	// create active memory
	Xml xmlActiveMemory = config.getFirstChild( "active-memory" );
	ASSERTMSG( xmlActiveMemory.exists() , "createService: active-memory is not present in brain configuration file" );
	activeMemory -> create( xmlActiveMemory );

	// create messaging session for mind services
	MessagingService *ms = MessagingService::getService();
	session = ms -> createSession();

	// create areas
	createAreas();

	// create regions in all areas
	areaSet -> create( target );

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
	areaSet -> suspendAreaSet();

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
	delete areaSet;
	delete regionSet;
	delete linkSet;
	delete activeMemory;

	rfc_hnd_semdestroy( lockStructure );
}

void MindService::createAreas() {
	// construct configured area set
	ClassList<MindAreaDef>& areaSet = mindMap -> getMindAreas();
	for( int k = 0; k < areaSet.count(); k++ ) {
		MindAreaDef *areaInfo = areaSet.get( k );
		createArea( areaInfo );
	}
}

void MindService::createArea( MindAreaDef *areaInfo ) {
	// check need running
	if( !areaInfo -> runEnabled() ) {
		logger.logInfo( "constructArea: mind area is ignored, disabled in mind configuration name=" + areaInfo -> getAreaId() );
		return;
	}

	// construct area
	MindArea *area = new MindArea();
	area -> configure( areaInfo );

	// add to list
	addMindArea( area );
}

void MindService::setMindTarget( MindTarget *p_target ) {
	target = p_target;
}

void MindService::addMindArea( MindArea *area ) {
	// add mind area
	MindAreaDef *areaInfo = mindMap -> getAreaDefById( area -> getClass() );
	ASSERTMSG( areaInfo != NULL , String( "addMindArea: mind area is not present in mind configuration name=" ) + area -> getClass() );

	// ignore area if configured not enabled
	if( !areaInfo -> runEnabled() ) {
		logger.logInfo( "addMindArea: mind area is ignored, disabled  in configuration name=" + areaInfo -> getAreaId() );
		return;
	}

	// add to set
	areaSet -> addMindArea( area );

	logger.logInfo( "addMindArea: mind area added name=" + areaInfo -> getAreaId() );
}

// mind links
void MindService::establishAreaLinks() {
}

void MindService::createMindAreaLink( MindArea *masterArea , MindArea *slaveArea ) {
	// create link
	MindAreaLink *link = new MindAreaLink();
	link -> create( masterArea , slaveArea );

	// add to link set
	masterArea -> addSlaveLink( link );
	slaveArea -> addMasterLink( link );
	linkSet -> addSetItem( link );
	logger.logInfo( "createMindAreaLink: create link masterArea=" + masterArea -> getId() + ", slaveArea=" + slaveArea -> getId() + "..." );

	// create region-to-region links
	link -> createRegionLinks();

	// start process area link messages
	link -> open( session , masterArea -> getId() );
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
