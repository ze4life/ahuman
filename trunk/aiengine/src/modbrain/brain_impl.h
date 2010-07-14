#ifndef	INCLUDE_AIBRAIN_IMPL_H
#define INCLUDE_AIBRAIN_IMPL_H

#include <aiengine.h>
#include <aibrain.h>
#include <aisvcdb.h>
#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIBrainImpl : public AIBrain , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Brain" ); };

// external interface
public:
	AIBrainImpl();

	// Object interface

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIBRAIN_IMPL_H
