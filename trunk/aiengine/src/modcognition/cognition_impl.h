#ifndef	INCLUDE_AICOGNITION_IMPL_H
#define INCLUDE_AICOGNITION_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aisvcdb.h>
#include <aisvcio.h>

#include <aicognition.h>

/*#########################################################################*/
/*#########################################################################*/

class NeoCortexSensorsSubscriber;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AICognitionImpl : public AICognition , public Service
{
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Cognition" ); };

// external interface
public:
	AICognitionImpl();

private:
	static MindArea *createNeoCortex();

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

class NeoCortexSensorsSubscriber : public Object , public Subscriber
{
public:
	NeoCortexSensorsSubscriber() {};

	const char *getClass() { return( "NeoCortexSensorsSubscriber" ); };

public:
	// subscriber events
	virtual void onMessage( Message *msg );
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AICOGNITION_IMPL_H
