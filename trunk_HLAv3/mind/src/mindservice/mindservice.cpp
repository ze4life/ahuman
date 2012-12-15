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
	ClassList<MindAreaDef>& areaDefSet = mindMap -> getMindAreas();
	for( int k = 0; k < areaDefSet.count(); k++ ) {
		MindAreaDef *areaInfo = areaDefSet.get( k );
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
	area -> createRegions( target );
	MindRegionSet *areaRegions = area -> getRegionSet();
	regionSet -> addRegionSet( areaRegions );

	logger.logInfo( "addMindArea: created mind area name=" + areaInfo -> getAreaId() );
	areaSet -> addMindArea( area );
}

MindArea *MindService::getMindArea( String areaId ) {
	return( areaSet -> getMindArea( areaId ) );
}

MindRegion *MindService::getMindRegion( String regionId ) {
	MindRegion *region = regionSet -> getSetItemById( regionId );
	ASSERTMSG( region != NULL , "getMindRegion: region is not found by id=" + regionId );
	return( region );
}

MindRegion *MindService::createRegion( String implementation , String type , MindArea *area , MindRegionInfo *info ) {
	MindRegion *region = NULL;
	if( implementation.equals( "original" ) ) {
		if( type.equals( "neocortex" ) )
			region = new NeocortexRegion( area );
		else if( type.equals( "allocortex" ) )
			region = new AllocortexRegion( area );
		else if( type.equals( "nucleus" ) )
			region = new NucleiRegion( area );
		else
			ASSERTFAILED( "unknown region type=" + type );
	}
	else if( implementation.equals( "mock" ) ) {
		region = new MockRegion( type , area );
	}

	region -> createRegion( info );

	return( region );
}

void MindService::setMindTarget( MindTarget *p_target ) {
	target = p_target;
}

// mind links
void MindService::establishAreaLinks() {
	ClassList<MindCircuitDef>& circuits = mindMap -> getMindCircuits();
	for( int k = 0; k < circuits.count(); k++ )
		addCircuitLinks( circuits.get( k ) );
}

void MindService::addCircuitLinks( MindCircuitDef *circuitDef ) {
	logger.logInfo( "addCircuitLinks: create cicuit name=" + circuitDef -> getName() );

	ClassList<MindCircuitConnectionDef>& connections = circuitDef -> getConnections();
	for( int k = 0; k < connections.count(); k++ )
		addCircuitConnection( circuitDef , connections.get( k ) );
}

void MindService::addCircuitConnection( MindCircuitDef *circuitDef , MindCircuitConnectionDef *connectionDef ) {
	// get/create area link
	String srcRegionName = connectionDef -> getSrcRegion();
	MindRegion *srcRegion = regionSet -> getSetItemById( srcRegionName );
	ASSERTMSG( srcRegion != NULL , "circuit=" + circuitDef -> getName() + ": unknown region=" + srcRegionName );
	String dstRegionName = connectionDef -> getDstRegion();
	MindRegion *dstRegion = regionSet -> getSetItemById( dstRegionName );
	ASSERTMSG( dstRegion != NULL , "circuit=" + circuitDef -> getName() + ": unknown region=" + dstRegionName );
	ASSERTMSG( srcRegion != dstRegion , "circuit=" + circuitDef -> getName() + ": cannot connect region to itself, name=" + dstRegionName );

	// check link like this is already created
	String type = connectionDef -> getTypeName();
	String key = type + "." + srcRegionName + "." + dstRegionName;
	if( regionConnectionMap.get( key ) != NULL )
		return;

	// create
	MindConnectionTypeDef *connectionType = connectionDef -> getType();
	createRegionConnection( connectionType , srcRegion , dstRegion );

	// add to map
	regionConnectionMap.add( key , connectionType );
}

void MindService::createRegionConnection( MindConnectionTypeDef *connectionType , MindRegion *srcRegion , MindRegion *dstRegion ) {
	ClassList<MindConnectionLinkTypeDef>& links = connectionType -> getLinks();
	for( int k = 0; k < links.count(); k++ )
		createNeuroLink( links.get( k ) , srcRegion , dstRegion );
}

NeuroLink *MindService::createNeuroLink( MindConnectionLinkTypeDef *linkDef , MindRegion *srcRegion , MindRegion *dstRegion ) {
	// handle direction
	MindRegion *linkSrcRegion = ( linkDef -> isBackward() )? dstRegion : srcRegion;
	MindRegion *linkDstRegion = ( linkDef -> isBackward() )? srcRegion : dstRegion;

	// check pools
	NeuroLinkSource *srcConnector = linkSrcRegion -> getNeuroLinkSource( linkDef -> getSrcConnector() );
	NeuroLinkTarget *dstConnector = linkDstRegion -> getNeuroLinkTarget( linkDef -> getDstConnector() );

	// ignore if any connector is not present
	if( srcConnector == NULL || dstConnector == NULL )
		return( NULL );

	// create region link
	MindRegionLink *regionLink = createRegionLink( linkSrcRegion , linkDstRegion );

	// check neurolink exists
	String linkType = linkDef -> getName();
	String key = linkType + "-" + linkSrcRegion -> getRegionId() + "-" + linkDstRegion -> getRegionId();
	if( regionNeuroLinkMap.get( key ) != NULL )
		return( NULL );

	// create neurolink
	NeuroLinkInfo info;
	info.setLinkDef( linkDef );
	info.setNeuroTransmitter( linkDef -> getNeurotransmitter() );
	info.setRegionLink( regionLink );
	NeuroLink *neurolink = createNeuroLink( linkDef -> getImplementation() , linkDef -> getType() , srcConnector , dstConnector , &info );
	if( neurolink == NULL )
		return( NULL );

	regionNeuroLinkMap.add( key , neurolink );
	regionLink -> addNeuroLink( neurolink );

	logger.logInfo( "createNeuroLink: neurolink created type=" + linkDef -> getType() + 
		", implementation=" + linkDef -> getImplementation() + ", srcRegion=" + linkSrcRegion -> getRegionId() + 
		", dstRegion=" + linkDstRegion -> getRegionId() );
	return( neurolink );
}

MindRegionLink *MindService::createRegionLink( MindRegion *srcRegion , MindRegion *dstRegion ) {
	// create area link if areas are different
	MindArea *linkSrcArea = srcRegion -> getArea();
	MindArea *linkDstArea = dstRegion -> getArea();
	MindAreaLink *areaLink = NULL;
	if( linkSrcArea != linkDstArea )
		areaLink = createAreaLink( linkSrcArea , linkDstArea );

	// check already created
	String key = srcRegion -> getRegionId() + "." + dstRegion -> getRegionId();
	MindRegionLink *regionLink = regionLinkMap.get( key );
	if( regionLink != NULL )
		return( regionLink );

	// create region link
	regionLink = new MindRegionLink( areaLink );
	regionLink -> createRegionLink( srcRegion , dstRegion );
	regionLinkMap.add( key , regionLink );
	
	// add to area link
	if( areaLink != NULL )
		areaLink -> addRegionLink( regionLink );

	return( regionLink );
}

MindAreaLink *MindService::createAreaLink( MindArea *masterArea , MindArea *slaveArea ) {
	// check area link exists
	String key = masterArea -> getId() + "." + slaveArea -> getId();
	MindAreaLink *link = areaLinkMap.get( key );
	if( link != NULL )
		return( link );

	// create link
	link = new MindAreaLink;
	link -> create( masterArea , slaveArea );
	areaLinkMap.add( key , link );

	// add to link set
	masterArea -> addSlaveLink( link );
	slaveArea -> addMasterLink( link );
	linkSet -> addSetItem( link );
	logger.logInfo( "createMindAreaLink: create link masterArea=" + masterArea -> getId() + ", slaveArea=" + slaveArea -> getId() + "..." );

	// start process area link messages
	String channel = "CHANNEL." + masterArea -> getId() + "." + slaveArea -> getId();
	link -> open( session , channel );
	return( link );
}

NeuroLink *MindService::createNeuroLink( String implementation , String typeName , NeuroLinkSource *src , NeuroLinkTarget *dst , NeuroLinkInfo *info ) {
	NeuroLink *link = NULL;
	if( implementation.equals( "original" ) ) {
		if( typeName.equals( "excitatory" ) )
			link = new ExcitatoryLink( src , dst );
		else if( typeName.equals( "inhibitory" ) )
			link = new InhibitoryLink( src , dst );
		else if( typeName.equals( "modulatory" ) )
			link = new ModulatoryLink( src , dst );
		else
			ASSERTFAILED( "unknown region type=" + typeName );
	}
	else if( implementation.equals( "mock" ) ) {
		link = new MockLink( typeName , src , dst );
	}

	link -> createNeuroLink( info );
	src -> addNeuroLink( link );

	return( link );
}

