#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindActiveMemory::MindActiveMemory() {
}

MindActiveMemory::~MindActiveMemory() {
	memoryObjects.destroy();
}

void MindActiveMemory::create( Xml config ) {
	Xml xmlTP = config.getFirstChild( "ThreadPool" );
	String threadPoolName = xmlTP.getProperty( "name" );

	Xml xmlFocus = config.getFirstChild( "MemoryFocus" );
	int focusSize = xmlFocus.getIntProperty( "objectCount" );

	// create memory objects
	for( int k = 0; k < focusSize; k++ ) {
		MindActiveMemoryObject *object = new MindActiveMemoryObject( k );
		memoryObjects.add( object );
	}

	// create thread pool
	ThreadService *ts = ThreadService::getService();
	ts -> createThreadPool( threadPoolName , xmlTP , ( ClassList<ThreadPoolTask>& )memoryObjects );
}

void MindActiveMemory::start() {
	ThreadService *ts = ThreadService::getService();
	ts -> startThreadPool( threadPoolName );
}

void MindActiveMemory::stop() {
	ThreadService *ts = ThreadService::getService();
	ts -> stopThreadPool( threadPoolName );
}

