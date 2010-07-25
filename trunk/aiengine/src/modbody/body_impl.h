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

	// Object interface

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

// any sensor or effector
// each generally has both actions and senses
// sensors have actions controlling treir focus and other metrics controlling data capture
// effectors have senses with direct feedback from environment to action
// set of senses or set of actions form two specific cortexes with corresponding inputs or outputs
class Attractor
{
// construction
public:
	static Attractor *createFileSysWalker();

public:
	Attractor() {};
	virtual ~Attractor() {};

// operations
public:
	virtual Cortex *getSensesCortex() = 0;
	virtual Cortex *getActionsCortex() = 0;
};

#endif	// INCLUDE_AIBODY_IMPL_H
