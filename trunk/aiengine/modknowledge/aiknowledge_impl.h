#ifndef	INCLUDE_AIKNOWLEDGE_IMPL_H
#define INCLUDE_AIKNOWLEDGE_IMPL_H

#include <aiengine.h>
#include <aiknowledge.h>
#include <aidb.h>
#include <aiio.h>

class AISentenseImpl;
class AITokenImpl;
class AITokenListImpl;
class AITokenAssociations;
class AITokenAssocData;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIKnowledgeImpl : public AIKnowledge , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Knowledge" ); };

// external interface
public:
	AIKnowledgeImpl();

	// Object interface

// base class interface
public:
	void loadPrimaryInformation();
	void saveAllPersistent();

// internals
private:
	AIEngine& engine;
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIKNOWLEDGE_IMPL_H
