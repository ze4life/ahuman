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

class ImageKnowledgeBase: public Object{

private:
	AIEngine& engine;
	RFC_HND thread;
	String query;
	static ImageKnowledgeBase *instance;
	ImageKnowledgeBase();
public:
	virtual void startKnowledgeSource();
	virtual void stopKnowledgeSource();
	static ImageKnowledgeBase* getInstance(){
		if(instance == NULL){
			instance = new ImageKnowledgeBase();
		}
		return instance;
	}
	//virtual void imageDataGrabber(void*);
	virtual const char *getClass() { return( "ImageKnowledgeBase" ); };
};

class ImageQueryProcessor: public Subscriber, public Object{
public:
	ImageQueryProcessor();
	virtual void onMessage(Message *msg );
	virtual const char *getClass() { return( "ImageQueryProcessor" ); };
private:
	void processQuery(Message *msg);
	AIEngine& engine;
	SOCKET sock;
	SOCKADDR_IN add;
};	
// #############################################################################
// #############################################################################

#endif	// INCLUDE_AIKNOWLEDGE_IMPL_H
