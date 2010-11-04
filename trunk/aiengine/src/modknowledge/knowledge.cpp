
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
	imageKnowledgeBase = new ImageKnowledgeBase();
}

void AIKnowledgeImpl::runService()
{
	imageKnowledgeBase -> startKnowledgeSource();
}

void AIKnowledgeImpl::exitService()
{
	imageKnowledgeBase -> stopKnowledgeSource();
}

void AIKnowledgeImpl::destroyService()
{
	delete imageKnowledgeBase;
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/
