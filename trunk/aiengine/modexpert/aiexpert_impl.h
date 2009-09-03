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

class NNFinderFactory;
class AIExpertImpl;

/*#########################################################################*/
/*#########################################################################*/

class AIExpertDebug : public AISubscriber
{
public:
	AIExpertDebug();
	~AIExpertDebug();

public:
	void init( Xml config );
	void exit();

	virtual void onMessage( AIMessage *msg );

// tests
private:
	void testCreateBySamples( XmlCall& call );

private:
	AIPublisher *callPub;
	AISubscription *callSub;
	Logger logger;
};

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

	NNFinderFactory *getFinderFactory() { return( &expertFinderFactory ); };
	NNRegressionFactory *getRegressionFactory() { return( &expertRegressionFactory ); };

// internals
private:

private:
	AIEngine& engine;
	AIExpertDebug debug;

	NNFinderFactory expertFinderFactory;
	NNRegressionFactory expertRegressionFactory;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIEXPERT_IMPL_H
