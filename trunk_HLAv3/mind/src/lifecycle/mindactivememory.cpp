#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindActiveMemory::MindActiveMemory() {
	threadPool = "am";
	focusSize = 0;
}

MindActiveMemory::~MindActiveMemory() {
	memoryObjects.destroy();
}

void MindActiveMemory::create( Xml config ) {
	Xml xmlTP = config.getFirstChild( "ThreadPool" );
	Xml xmlFocus = config.getFirstChild( "MemoryFocus" );
	focusSize = xmlFocus.getIntProperty( "objectCount" );

	createMemoryObjects();

	ThreadService *ts = ThreadService::getService();
	ts -> createThreadPool( threadPool , xmlTP , ( ClassList<ThreadPoolTask>& )memoryObjects );
}

void MindActiveMemory::createMemoryObjects() {
	for( int k = 0; k < focusSize; k++ ) {
		MindActiveMemoryObject *object = new MindActiveMemoryObject( k );
		memoryObjects.add( object );
	}
}

void MindActiveMemory::start() {
	ThreadService *ts = ThreadService::getService();
	ts -> startThreadPool( threadPool );
}

void MindActiveMemory::stop() {
	ThreadService *ts = ThreadService::getService();
	ts -> stopThreadPool( threadPool );
}

