#ifndef	INCLUDE_AIKNOWLEDGE_IMPL_H
#define INCLUDE_AIKNOWLEDGE_IMPL_H

#include <aiengine.h>
#include <aiknowledge.h>
#include <aidb.h>
#include <aiio.h>

class AISentenseImpl;
class AITokenImpl;
class AITokenListImpl;
class AITokenAssociations;
class AITokenAssocData;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIKnowledgeImpl : public AIKnowledge , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Knowledge" ); };

// external interface
public:
	AIKnowledgeImpl();
	virtual AITokenList *getTokenList();

	virtual AISentense *createSentense();
	virtual void associate( AISession *session , AIToken *leftToken , AIToken *rightToken );

	// Object interface

// base class interface
public:
	void loadPrimaryInformation();
	void saveAllPersistent();

// internals
private:
	AIEngine& engine;
	AITokenListImpl *tokenList;
	AITokenAssociations *tokenAssoc;
};

// #############################################################################
// #############################################################################

class AISentenseImpl : public AISentense
{
public:
	virtual void addToken( AIToken *p_token );
	virtual ClassList<AIToken>& getTokens() { return( tokens ); };

	// Object interface

public:
	AISentenseImpl();
	~AISentenseImpl();

private:
	ClassList<AIToken> tokens;
};

// #############################################################################
// #############################################################################

class AITokenImpl : public AIToken
{
public:
	virtual const char *getText();
	virtual int getOrderPos() { return( orderPos ); };

	// Object interface

public:
	AITokenImpl( const char *p_name , int orderPos );
	~AITokenImpl();

private:
	String name;
	int orderPos;
};

// #############################################################################
// #############################################################################

class AITokenListImpl : public AITokenList
{
// external interface
public:
	virtual ClassList<AIToken>& getTokens() { return( tokens ); };
	virtual int getTokenCount() { return( tokens.count() ); };
	virtual AIToken *getTokenByOrder( int p_order );

	// Object interface

// internal interface
public:
	AITokenListImpl();
	~AITokenListImpl();

	void load();
	void save();

private:
	ClassList<AIToken> tokens;
};

// #############################################################################
// #############################################################################

class AITokenAssociations : public Object
{
public:
	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new AITokenAssociations ); };
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	String getPK();

public:
	AITokenAssociations();
	~AITokenAssociations();

	void load();
	void save();

	void addAssoc( AISession *session , AIToken *left , AIToken *right );
	AITokenAssocData *getAssoc( AIToken *left , AIToken *right );

private:
	AIEngine& engine;
	AIKnowledge knowledge;
	AIDB db;

	AITokenAssocData **assocMatrix;
	int matrixSize;
};

// #############################################################################
// #############################################################################

class AITokenAssocData : public Object
{
public:
	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new AITokenAssocData ); };
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	String getPK();

public:
	AITokenAssocData();
	AITokenAssocData( AIToken *left , AIToken *right );
	~AITokenAssocData();

	void addUsage( AISession *session );
	bool isStrong() { return( strong ); };
	AIToken *getLeft() { return( left ); };
	AIToken *getRight() { return( right ); };

private:
	AIToken *left;
	AIToken *right;
	bool strong;
	int usageCount;
	int usageCountThreshold;
};

#endif	// INCLUDE_AIKNOWLEDGE_IMPL_H
