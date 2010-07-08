#ifndef	INCLUDE_AICOMMANDS_IMPL_H
#define INCLUDE_AICOMMANDS_IMPL_H

#include <aiengine.h>
#include <aiintelligence.h>
#include <aisvcdb.h>
#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIIntelligenceImpl : public AIIntelligence , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Intelligence" ); };

// external interface
public:
	AIIntelligenceImpl();

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AICOMMANDS_IMPL_H
