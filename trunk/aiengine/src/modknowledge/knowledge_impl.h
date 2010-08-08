#ifndef	INCLUDE_AIKNOWLEDGE_IMPL_H
#define INCLUDE_AIKNOWLEDGE_IMPL_H

#include <aiengine.h>
#include <aiknowledge.h>
#include <aisvcdb.h>
#include <aisvcio.h>

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIKnowledgeImpl : public AIKnowledge , public Service
{
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Knowledge" ); };

// external interface
public:
	AIKnowledgeImpl();

	// Object interface

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIKNOWLEDGE_IMPL_H
