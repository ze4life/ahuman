#ifndef	INCLUDE_AIHTMLIB_IMPL_H
#define INCLUDE_AIHTMLIB_IMPL_H

#include <aiengine.h>
#include <aihtmlib.h>
#include <aiio.h>
#include <aidb.h>

class AIHtmLibImpl;

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLibDebug : public Subscriber
{
public:
	AIHtmLibDebug();
	~AIHtmLibDebug();

public:
	void init( Xml config );
	void exit();

	virtual void onMessage( Message *msg );

// tests
private:
	void testHelloWorld( XmlCall& call );

private:
	Publisher *callPub;
	Subscription *callSub;
	Logger logger;
};

/*#########################################################################*/
/*#########################################################################*/

class AIHtmLibImpl : public AIHtmLib , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "HtmLib" ); };

// external interface
public:
	AIHtmLibImpl();
	static AIHtmLibImpl *getServiceImpl();

// internals
private:

private:
	AIEngine& engine;
	AIHtmLibDebug debug;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIHTMLIB_IMPL_H
