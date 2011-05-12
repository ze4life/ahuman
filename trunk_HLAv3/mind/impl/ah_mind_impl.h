#ifndef	INCLUDE_AH_MIND_IMPL_H
#define INCLUDE_AH_MIND_IMPL_H

/*#########################################################################*/
/*#########################################################################*/

#include <platform/include/ah_platform.h>

class MindActiveMemory;
class MindActiveMemoryObject;

/*#########################################################################*/
/*#########################################################################*/

class MindActiveMemory : public Object {
public:
	MindActiveMemory();
	~MindActiveMemory();
	const char *getClass() { return( "MindActiveMemory" ); };

	// lifecycle
	void create( Xml config );
	void start();
	void stop();
	void destroy();

public:
	String threadPoolName;
	ClassList<MindActiveMemoryObject> memoryObjects;
};

/*#########################################################################*/
/*#########################################################################*/

class NeuroLink;

class MindActiveMemoryObject : public ThreadPoolTask {
public:
	MindActiveMemoryObject( int id );
	~MindActiveMemoryObject();
	virtual const char *getClass() { return( "MindActiveMemoryObject" ); };

	void setTargetItem( NeuroLink *link );
	void execute();
	bool needExecution();
	bool finished();

private:
	int activeMemoryObjectId;
	String name;
	NeuroLink *targetItem;
};

// #############################################################################
// #############################################################################

#endif // INCLUDE_AH_MIND_IMPL_H
