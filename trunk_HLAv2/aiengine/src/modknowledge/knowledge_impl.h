#ifndef	INCLUDE_AIKNOWLEDGE_IMPL_H
#define INCLUDE_AIKNOWLEDGE_IMPL_H

#include <aiengine.h>
#include <aiknowledge.h>
#include <aisvcdb.h>
#include <aisvcio.h>
#include <aimedia.h>

/*#########################################################################*/
/*#########################################################################*/

class KnowledgeController;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIKnowledgeImpl : public AIKnowledge , public Service
{
private:
	AIEngine& engine;
	MapStringToClass<KnowledgeController> controllers;

public:
	// service
	virtual void createService( Xml config );
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Knowledge" ); };

	AIKnowledgeImpl();

// external interface
public:
	KnowledgeController *getKnowledgeController( String name );

private:
	void addKnowledgeController( Xml configControllers , KnowledgeController *controller );
};

// #############################################################################
// #############################################################################

class KnowledgeController : public Object
{
private:
	String name;

public:
	static KnowledgeController *createImageKnowledgeBase();

public:
	KnowledgeController( String p_name ) { name = p_name; };
	virtual ~KnowledgeController() {};

	virtual void createController( Xml config ) = 0;
	virtual void startController() = 0;
	virtual void stopController() = 0;

	String getName() { return( name ); };
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIKNOWLEDGE_IMPL_H
