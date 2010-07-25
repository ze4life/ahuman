
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
}

void AIBrainImpl::initService()
{
	// load mind map
	logger.logInfo( "reading mind map..." );
	Xml xml = Service::getConfig();
	xml = xml.getFirstChild( "MindMap" );
	ASSERTMSG( xml.exists() , "MindMap is not present in brain configuration file" );

	mindMap -> createFromXml( xml );
}

void AIBrainImpl::runService()
{
}

void AIBrainImpl::exitService()
{
}

void AIBrainImpl::destroyService()
{
	if( mindMap != NULL )
		delete mindMap;
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
