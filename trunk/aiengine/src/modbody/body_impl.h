#ifndef	INCLUDE_AIBODY_IMPL_H
#define INCLUDE_AIBODY_IMPL_H

#include <aiengine.h>
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

#endif	// INCLUDE_AIBODY_IMPL_H
