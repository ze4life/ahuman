
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
	tokenList = NULL;
	tokenAssoc = NULL;
}

void AIKnowledgeImpl::initService()
{
	AITokenAssociations::createSerializeObject();

	tokenList = new AITokenListImpl();
	tokenAssoc = new AITokenAssociations();
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
	delete tokenList;
	delete tokenAssoc;

	delete this;
}

/*#########################################################################*/
/*#########################################################################*/

AITokenList *AIKnowledgeImpl::getTokenList() 
{ 
	return( tokenList ); 
}

void AIKnowledgeImpl::loadPrimaryInformation()
{
	tokenList -> load();
	tokenAssoc -> load();
}

AISentense *AIKnowledgeImpl::createSentense()
{
	return( new AISentenseImpl() );
}

void AIKnowledgeImpl::associate( AISession *session , AIToken *leftToken , AIToken *rightToken )
{
	tokenAssoc -> addAssoc( session , leftToken , rightToken );
}

void AIKnowledgeImpl::saveAllPersistent()
{
	tokenList -> save();
	tokenAssoc -> save();
}

