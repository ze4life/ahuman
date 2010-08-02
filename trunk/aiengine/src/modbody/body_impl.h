#ifndef	INCLUDE_AIBODY_IMPL_H
#define INCLUDE_AIBODY_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aibody.h>
#include <aisvcdb.h>
#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIBodyImpl : public AIBody , public Service
{
	// service
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
// sensors have actions controlling treir focus and other metrics controlling data capture
// effectors have senses with direct feedback from environment to action
// does not have state persisted while AI is not running
// created on AI start
class Attractor
{
// construction
public:
	Attractor() {};
	virtual ~Attractor() {};

	// sensors
	static Attractor *createFileSysWalker( MindArea *area );

// operations
public:
	// hardcoded cortex that process inputs as actions, outputs as feedback
	virtual Cortex *getCortex() = 0;
};

#endif	// INCLUDE_AIBODY_IMPL_H
