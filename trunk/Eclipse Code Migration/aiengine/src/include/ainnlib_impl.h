#ifndef	INCLUDE_AINNLIB_IMPL_H
#define INCLUDE_AINNLIB_IMPL_H

#include <math.h>

#include <aiengine.h>
#include <ainnlib.h>
#include <aimind.h>
#include <aiknowledge.h>
#include <aiio.h>
#include <aidb.h>

// neuro networks
#include "ainnlib_implfunc.h"
#include "ainnlib_implnn.h"
#include "ainnlib_implstrategy.h"
#include "ainnlib_implnet.h"

class NNFinderFactory;
class AINNLibImpl;

/*#########################################################################*/
/*#########################################################################*/

class AINNLibDebug : public Subscriber
{
public:
	AINNLibDebug();
	~AINNLibDebug();

public:
	void init( Xml config );
	void exit();

	virtual void onMessage( Message *msg ) {};
	virtual void onXmlMessage( XmlMessage *msg ) {};
	virtual void onXmlCall( XmlCall *msg );

// tests
private:
	void testCreateBySamples( XmlCall& call );
	void testFinderXOR( XmlCall& call );
	void testFinderLearn( XmlCall& call );
	void testFinderFactory( XmlCall& call );

private:
	Publisher *callPub;
	Subscription *callSub;
	Logger logger;
};

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AINNLibImpl : public AINNLib , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "NNLib" ); };

// external interface
public:
	AINNLibImpl();
	static AINNLibImpl *getServiceImpl();

	NNFinderFactory *getFinderFactory() { return( &finderFactory ); };
	NNRegressionFactory *getRegressionFactory() { return( &regressionFactory ); };

// internals
private:

private:
	AIEngine& engine;
	AINNLibDebug debug;

	NNFinderFactory finderFactory;
	NNRegressionFactory regressionFactory;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AINNLIB_IMPL_H
