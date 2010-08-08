
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
	AIEngine::getInstance().registerService( svc , "Brain" );
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
	Xml xml = Service::getConfig();
	Xml xmlMindMap = xml.getFirstChild( "MindMap" );
	ASSERTMSG( xmlMindMap.exists() , "MindMap is not present in brain configuration file" );

	mindMap -> createFromXml( xmlMindMap );

	// cortex handlers
	int index = 0;
	index = cortexFactories.add( &AIBrainImpl::createHardcodedCortex ); mapCortexFactoryIndex.add( "CortexHardcoded" , index );
	index = cortexFactories.add( &AIBrainImpl::createHardcodedInputsCortex ); mapCortexFactoryIndex.add( "CortexHardcodedInputs" , index++ );
	index = cortexFactories.add( &AIBrainImpl::createHardcodedOutputsCortex ); mapCortexFactoryIndex.add( "CortexHardcodedOutputs" , index++ );

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
		area -> createArea();
	}
}

void AIBrainImpl::runService()
{
	// start thinking
	activeMemory -> start();
}

void AIBrainImpl::exitService()
{
	// stop thinking
	if( activeMemory != NULL )
		activeMemory -> stop();
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

Cortex *AIBrainImpl::createCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler )
{
	// find cortex factory
	int index = mapCortexFactoryIndex.get( netType );
	ASSERTMSG( index >= 0 , "Unable to find cortex type=" + netType );
	CortexFactory factory = cortexFactories.get( index );

	// create cortex
	TopCortexEventHandler *topHandler = new TopCortexEventHandler;
	topHandler -> nextHandler = handler;
	Cortex *cortex = ( this ->* factory ) ( area , netType , size , inputs , outputs );
	cortex -> setHandler( topHandler );
	ASSERTMSG( cortex != NULL , "Unable to create cortex type=" + netType );

	// register cortex
	lock();
	String id = String( "CTX" ) + sessionId + "S" + ++cortexId + "C";
	cortex -> setId( id );
	mapCortex.add( id , cortex );
	unlock();

	logger.logInfo( "cortex created: id=" + id + ", type=" + netType + ", size=" + size + ", inputs=" + inputs + ", outputs=" + outputs );
	topHandler -> onCreate( cortex );
	return( cortex );
}

Cortex *AIBrainImpl::createHardcodedCortex( MindArea *area , String netType , int size , int inputs , int outputs )
{
	allocateArea( area , inputs + outputs );
	Cortex *cortex = new Cortex( area , inputs , 0 , outputs );
	return( cortex );
}

Cortex *AIBrainImpl::createHardcodedInputsCortex( MindArea *area , String netType , int size , int inputs , int outputs )
{
	allocateArea( area , inputs );
	Cortex *cortex = new Cortex( area , inputs , 0 , 0 );
	return( cortex );
}

Cortex *AIBrainImpl::createHardcodedOutputsCortex( MindArea *area , String netType , int size , int inputs , int outputs )
{
	allocateArea( area , outputs );
	Cortex *cortex = new Cortex( area , 0 , 0 , outputs );
	return( cortex );
}

// mind area links
MindLink *AIBrainImpl::createMindLink( MindLinkInfo *linkInfo , MindArea *masterArea , MindArea *slaveArea )
{
	// create link
	MindLinkImpl *link = new MindLinkImpl( linkInfo );
	link -> open( ioBrainSession );
	mindLinks.add( link );
	return( link );
}
