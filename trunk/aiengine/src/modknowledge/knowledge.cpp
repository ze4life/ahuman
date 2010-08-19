
#include "knowledge_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIKnowledge::AIKnowledge() 
{ 
	thisPtr = static_cast<AIKnowledgeImpl *>( AIEngine::getInstance().getService( "Knowledge" ) ); 
}

/* static */ Service *AIKnowledge::newService()
{
	Service *svc = new AIKnowledgeImpl();
	return( svc );
}

AIKnowledgeImpl::AIKnowledgeImpl()
:	engine( AIEngine::getInstance() )
{
}

void AIKnowledgeImpl::createService()
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
