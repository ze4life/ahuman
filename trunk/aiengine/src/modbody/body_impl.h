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
// construction
public:
	Attractor( MindArea *area , int inputs , int outputs )
	:	Cortex( area , inputs , 0 , outputs ) {};
	virtual ~Attractor() {};

	// sensors
	static Attractor *createFileSysWalker( MindArea *area );

// operations
public:
};

#endif	// INCLUDE_AIBODY_IMPL_H
