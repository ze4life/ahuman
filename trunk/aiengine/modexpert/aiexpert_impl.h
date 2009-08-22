#ifndef	INCLUDE_AIEXPERT_IMPL_H
#define INCLUDE_AIEXPERT_IMPL_H

#include <math.h>

#include <aiengine.h>
#include <aiexpert.h>
#include <aimind.h>
#include <aiknowledge.h>
#include <aiio.h>
#include <aidb.h>

// neuro networks
#include "aiexpert_implfunc.h"
#include "aiexpert_implnn.h"
#include "aiexpert_implstrategy.h"
#include "aiexpert_implnet.h"

class AITokenParser;
class NNFinderFactory;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIExpertImpl : public AIExpert , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Expert" ); };

// external interface
public:
	AIExpertImpl();
	static AIExpertImpl *getServiceImpl();

	virtual void processMediaMessage( AIMessage *msg , AISession *session );

	NNFinderFactory *getFinderFactory() { return( &expertFinderFactory ); };
	NNRegressionFactory *getRegressionFactory() { return( &expertRegressionFactory ); };

// internals
private:
	void setupTokens();
	void processSentense( AISession *session , AISentense *st );

	// tests
	void testCreateBySamples();

private:
	AIEngine& engine;
	AITokenParser *tokenParser;

	NNFinderFactory expertFinderFactory;
	NNRegressionFactory expertRegressionFactory;
};

/*#########################################################################*/
/*#########################################################################*/

class AITokenParser : public Object
{
public:
	// AIObject interface

public:
	AITokenParser();
	~AITokenParser();

	void splitToSentenses( AIMessage *msg , ClassList<AISentense>& p_list );
	
private:
	AIToken *findToken( const char *s );

	const char *skipSpacing( const char *s );
	bool isSpacing( char c );

	AIEngine& engine;
	AIKnowledge knowledge;

	ClassList<AIToken> tokens;
};

#endif	// INCLUDE_AIEXPERT_IMPL_H
