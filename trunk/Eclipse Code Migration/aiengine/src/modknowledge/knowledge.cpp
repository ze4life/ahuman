
#include "aiknowledge_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIKnowledge::AIKnowledge() 
{ 
	thisPtr = static_cast<AIKnowledgeImpl *>( AIEngine::getInstance().getService( "AIKnowledge" ) ); 
}

/* static */ Service *AIKnowledge::createService()
{
	Service *svc = new AIKnowledgeImpl();
	AIEngine::getInstance().registerService( svc , "AIKnowledge" );
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
	loadPrimaryInformation();
}

void AIKnowledgeImpl::exitService()
{
	saveAllPersistent();
}

void AIKnowledgeImpl::destroyService()
{
	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

void AIKnowledgeImpl::loadPrimaryInformation()
{
}

void AIKnowledgeImpl::saveAllPersistent()
{
}

