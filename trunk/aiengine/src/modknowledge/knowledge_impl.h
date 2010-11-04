#ifndef	INCLUDE_AIKNOWLEDGE_IMPL_H
#define INCLUDE_AIKNOWLEDGE_IMPL_H

#include <aiengine.h>
#include <aiknowledge.h>
#include <aisvcdb.h>
#include <aisvcio.h>
#include <aimedia.h>

/*#########################################################################*/
/*#########################################################################*/

class ImageKnowledgeBase;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIKnowledgeImpl : public AIKnowledge , public Service
{
private:
	AIEngine& engine;
	ImageKnowledgeBase *imageKnowledgeBase;

public:
	// service
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "Knowledge" ); };

	AIKnowledgeImpl();

// external interface
public:
	ImageKnowledgeBase *getKnowledgeBase() { return( imageKnowledgeBase ); };
};

// #############################################################################
// #############################################################################

class ImageKnowledgeBase : public Object , public Subscriber {
private:
	AIEngine& engine;
	RFC_HND thread;

	String externalChannel;
	String commandChannel;
	String responseChannel;

	Publisher *publisher;
	Subscription *subscription;

public:
	ImageKnowledgeBase();
	virtual const char *getClass() { return( "ImageKnowledgeBase" ); };

public:
	virtual void onTextMessage( TextMessage *msg );
	void configure( Xml config );
	void startKnowledgeSource();
	void stopKnowledgeSource();

private:
	void processQuery( String command );
};

// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIKNOWLEDGE_IMPL_H
