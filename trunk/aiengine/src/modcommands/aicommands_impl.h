#ifndef	INCLUDE_AICOMMANDS_IMPL_H
#define INCLUDE_AICOMMANDS_IMPL_H

#include <aiengine.h>
#include <aicommands.h>
#include <aidb.h>
#include <aiio.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AICommandsImpl : public AICommands , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Commands" ); };

// external interface
public:
	AICommandsImpl();

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AICOMMANDS_IMPL_H
