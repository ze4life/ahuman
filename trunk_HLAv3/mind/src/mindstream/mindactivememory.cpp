#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindActiveMemory::MindActiveMemory() {
	attachLogger();
}

MindActiveMemory::~MindActiveMemory() {
	memoryObjects.destroy();
}

void MindActiveMemory::create( Xml config ) {
	Xml xmlTP = config.getFirstChild( "thread-pool" );
	threadPoolName = xmlTP.getProperty( "name" );

	Xml xmlFocus = config.getFirstChild( "memory-focus" );
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

void MindActiveMemory::execute( MindMessage *msg ) {
	NeuroLink *link = msg -> getNeuroLink();
	NeuroSignal *sourceData = msg -> getMsgData();
	String extId = sourceData -> getId();
	if( extId.isEmpty() ) {
		extId = msg -> getSourceMessageId();
		sourceData -> setId( extId );
	}

	NeuroLinkTarget *target = link -> getTarget();

	logger.logDebug( "execute: process link=" + link -> getId() + ", message id=" + msg -> getChannelMessageId() );
	target -> execute( link , sourceData );
}
