
#include "brain_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIBrain::AIBrain() 
{ 
	thisPtr = static_cast<AIBrainImpl *>( AIEngine::getInstance().getService( "Brain" ) ); 
}

/* static */ Service *AIBrain::newService()
{
	Service *svc = new AIBrainImpl();
	return( svc );
}

AIBrainImpl::AIBrainImpl()
:	engine( AIEngine::getInstance() )
{
	mindMap = new MindMap;
	lockStructure = ( RFC_HND )NULL;
	sessionId = 0;
	cortexId = 0;
	activeMemory = NULL;
}

AIBrainImpl *AIBrainImpl::getInstance()
{
	return( ( AIBrainImpl * )AIEngine::getInstance().getService( "Brain" ) );
}

void AIBrainImpl::createService()
{
	// load mind map
	logger.logInfo( "reading mind map..." );
	Xml xml = Service::getConfigService();
	Xml xmlMindMap = xml.getFirstChild( "MindMap" );
	ASSERTMSG( xmlMindMap.exists() , "MindMap is not present in brain configuration file" );

	mindMap -> createFromXml( xmlMindMap );

	// cortex handlers
	int index = 0;
	// index = cortexFactories.add( &AIBrainImpl::onCreateXXXCortex ); mapCortexFactoryIndex.add( "XXX" , index );

	// lock
	lockStructure = rfc_hnd_semcreate();

	// create active memory
	Xml xmlActiveMemory = xml.getFirstChild( "ActiveMemory" );
	ASSERTMSG( xmlActiveMemory.exists() , "ActiveMemory is not present in brain configuration file" );

	activeMemory = new ActiveMemory();
	activeMemory -> create( xmlActiveMemory );
}

void AIBrainImpl::initService()
{
	// create IO session
	AIIO io;
	ioBrainSession = io.createSession();

	// now always create all registered mind areas
	for( int k = mindAreas.count() - 1; k >= 0; k-- ) {
		MindArea *area = mindAreas.getClassByIndex( k );
		area -> onCreateArea();
	}
}

void AIBrainImpl::runService()
{
	// enable areas to live
	for( int k = mindAreas.count() - 1; k >= 0; k-- ) {
		MindArea *area = mindAreas.getClassByIndex( k );
		area -> onBrainStart();
	}

	// start thinking
	activeMemory -> start();
}

void AIBrainImpl::exitService()
{
	// stop thinking
	if( activeMemory != NULL )
		activeMemory -> stop();

	// inform areas about exit
	for( int k = mindAreas.count() - 1; k >= 0; k-- ) {
		MindArea *area = mindAreas.getClassByIndex( k );
		area -> onBrainStop();
	}
}

void AIBrainImpl::destroyService()
{
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

/*#########################################################################*/
/*#########################################################################*/

// mind areas
void AIBrainImpl::addMindArea( String areaId , MindArea *area )
{
	ASSERTMSG( mindAreas.get( areaId ) == NULL , "duplicate area to be added: " + areaId );
	mindAreas.add( areaId , area );
	area -> setId( areaId );

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

MindArea *AIBrainImpl::getMindArea( String areaId )
{
	return( mindAreas.get( areaId ) );
}

void AIBrainImpl::allocateArea( MindArea *area , int size )
{
	String id = area -> getId();
	MindAreaInfo *info = mindMap -> getAreaById( id );
	info -> allocate( size );
}

// cortex
Cortex *AIBrainImpl::getCortex( String cortexId )
{
	Cortex *cortex = mapCortex.get( cortexId );
	ASSERTMSG( cortex != NULL , "cortex is not found by id=" + cortexId );
	return( cortex );
}

Cortex *AIBrainImpl::createCortex( MindArea *area , String netType , int size , int inputs , int outputs )
{
	// find cortex factory
	int index = mapCortexFactoryIndex.get( netType );
	ASSERTMSG( index >= 0 , "Unable to find cortex type=" + netType );
	CortexFactory factory = cortexFactories.get( index );

	// create cortex
	Cortex *cortex = ( this ->* factory ) ( area , netType , size , inputs , outputs );
	ASSERTMSG( cortex != NULL , "Unable to create cortex type=" + netType );
	area -> onCreateCortex( cortex );

	// register cortex
	lock();
	String id = String( "CTX" ) + sessionId + "S" + ++cortexId + "C";
	cortex -> setId( id );
	mapCortex.add( id , cortex );
	unlock();

	logger.logInfo( "cortex created: id=" + id + ", type=" + netType + ", size=" + size + ", inputs=" + inputs + ", outputs=" + outputs );
	area -> onAddCortex( cortex );
	return( cortex );
}

void AIBrainImpl::addHardcodedCortex( MindArea *area , Cortex *cortex )
{
	int inputs = cortex -> getNInputs();
	int outputs = cortex -> getNOutputs();
	allocateArea( area , inputs + outputs );

	// register cortex
	lock();
	String id = String( "CTX" ) + sessionId + "S" + ++cortexId + "C";
	cortex -> setId( id );
	mapCortex.add( id , cortex );
	unlock();

	logger.logInfo( "hardcoded cortex registered: id=" + id + ", inputs=" + inputs + ", outputs=" + outputs );
	area -> onAddCortex( cortex );
}

// mind area links
MindLink *AIBrainImpl::createMindLink( MindLinkInfo *linkInfo , MindArea *masterArea , MindArea *slaveArea )
{
	// create link
	MindLink *link = new MindLink( linkInfo );
	link -> open( ioBrainSession );
	mindLinks.add( link );

	masterArea -> addMindLink( link );
	slaveArea -> addMindLink( link );

	return( link );
}
