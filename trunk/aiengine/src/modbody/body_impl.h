#ifndef	INCLUDE_AIBODY_IMPL_H
#define INCLUDE_AIBODY_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aisvcdb.h>
#include <aisvcio.h>

#include <aibody.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIBodyImpl : public AIBody , public Service
{
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Body" ); };

// external interface
public:
	AIBodyImpl();

private:
	static MindArea *createSensors();
	static MindArea *createEffectors();
	static MindArea *createBiology();
	static MindArea *createPhysiology();

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

// any body element
// each generally has two direction - input and output cortexes
// internal cortex implementation is fully hard-coded
// sensors have actions controlling their focus and other metrics controlling data capture
// effectors have senses with direct feedback from environment to action
// does not have state persisted while AI is not running
// created on AI start
class Attractor : public Cortex
{
	bool pollState;
	int pollNextMs;
	int pollIntervalMs;

// construction
public:
	Attractor( MindArea *area , int inputs , int outputs )
	:	Cortex( area , inputs , 0 , outputs ) {
		pollState = false;
		pollNextMs = 0;
		pollIntervalMs = 0;
	};
	virtual ~Attractor() {};

	// sensors
	static Attractor *createFileSysWalker( MindArea *area );

	// cortex overridables
	virtual void onCortexRun() = 0;

// operations
public:
	// poll setup
	void setPollState( bool state ) { pollState = state; };
	void setPollInterval( int intervalMs ) {
		pollIntervalMs = intervalMs;
	}

	// poll state
	bool getPollState() { return( pollState ); };
	int getPollInterval( int timeNowMs ) {
		return( pollNextMs - timeNowMs );
	}

	// do poll iteration
	void runPoll() {
		onCortexRun();
		pollNextMs = Timer::timeNow() + pollIntervalMs;
	}
};

#endif	// INCLUDE_AIBODY_IMPL_H
