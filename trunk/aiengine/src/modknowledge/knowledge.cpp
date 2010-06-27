
#include "aiknowledge_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIKnowledge::AIKnowledge() 
{ 
	thisPtr = static_cast<AIKnowledgeImpl *>( AIEngine::getInstance().getService( "Knowledge" ) ); 
}

/* static */ Service *AIKnowledge::createService()
{
	Service *svc = new AIKnowledgeImpl();
	AIEngine::getInstance().registerService( svc , "Knowledge" );
	return( svc );
}

AIKnowledgeImpl::AIKnowledgeImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIKnowledgeImpl::initService()
{
}

void AIKnowledgeImpl::runService()
{
}

void AIKnowledgeImpl::exitService()
{
}

void AIKnowledgeImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
