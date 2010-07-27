
#include "brain_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIBrain::AIBrain() 
{ 
	thisPtr = static_cast<AIBrainImpl *>( AIEngine::getInstance().getService( "Brain" ) ); 
}

/* static */ Service *AIBrain::createService()
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
}

void AIBrainImpl::initService()
{
	// load mind map
	logger.logInfo( "reading mind map..." );
	Xml xml = Service::getConfig();
	xml = xml.getFirstChild( "MindMap" );
	ASSERTMSG( xml.exists() , "MindMap is not present in brain configuration file" );

	mindMap -> createFromXml( xml );

	// cortex handlers
	int index = 0;
	index = cortexFactories.add( &AIBrainImpl::createHardcodedCortex ); mapCortexFactoryIndex.add( "CortexHardcoded" , index );
	index = cortexFactories.add( &AIBrainImpl::createHardcodedInputsCortex ); mapCortexFactoryIndex.add( "CortexHardcodedInputs" , index++ );
	index = cortexFactories.add( &AIBrainImpl::createHardcodedOutputsCortex ); mapCortexFactoryIndex.add( "CortexHardcodedOutputs" , index++ );

	// lock
	lockStructure = rfc_hnd_semcreate();
}

void AIBrainImpl::runService()
{
	// now always create all registered mind areas
	for( int k = mindAreas.count() - 1; k >= 0; k-- ) {
		MindArea *area = mindAreas.getClassByIndex( k );
		area -> createArea();
	}
}

void AIBrainImpl::exitService()
{
}

void AIBrainImpl::destroyService()
{
	if( lockStructure != ( RFC_HND )NULL )
		rfc_hnd_semdestroy( lockStructure );

	if( mindMap != NULL )
		delete mindMap;

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
	logger.logInfo( "create cortex: type=" + netType + ", size=" + size + ", inputs=" + inputs + ", outputs=" + outputs );

	// find cortex factory
	int index = mapCortexFactoryIndex.get( netType );
	ASSERTMSG( index >= 0 , "Unable to find cortex type=" + netType );
	CortexFactory factory = cortexFactories.get( index );

	// create cortex
	Cortex *cortex = ( this ->* factory ) ( area , netType , size , inputs , outputs , handler );
	ASSERTMSG( cortex != NULL , "Unable to create cortex type=" + netType );

	// register cortex
	lock();
	String id = String( "CTX" ) + sessionId + "S" + ++cortexId + "C";
	cortex -> setId( id );
	mapCortex.add( id , cortex );
	unlock();

	return( cortex );
}

Cortex *AIBrainImpl::createHardcodedCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler )
{
	allocateArea( area , inputs + outputs );
	CortexHardcoded *cortex = new CortexHardcoded( area , inputs , outputs , handler );
	return( cortex );
}

Cortex *AIBrainImpl::createHardcodedInputsCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler )
{
	allocateArea( area , inputs );
	CortexHardcoded *cortex = new CortexHardcoded( area , inputs , 0 , handler );
	return( cortex );
}

Cortex *AIBrainImpl::createHardcodedOutputsCortex( MindArea *area , String netType , int size , int inputs , int outputs , CortexEventHandler *handler )
{
	allocateArea( area , outputs );
	CortexHardcoded *cortex = new CortexHardcoded( area , 0 , outputs , handler );
	return( cortex );
}
