#include "brain_impl.h"

ActiveMemory::ActiveMemory()
{
	threadPool = new ActiveMemoryThreadPool();
}

ActiveMemory::~ActiveMemory()
{
	delete threadPool;
	memoryObjects.destroy();
}

void ActiveMemory::create( Xml config )
{
	configure( config );
	createMemoryObjects();
	createThreadPool();
}

void ActiveMemory::configure( Xml config )
{
	Xml xml = config.getFirstChild( "ThreadPool" );
	threadPool -> configure( xml );

	xml = config.getFirstChild( "MemoryFocus" );
	focusSize = xml.getIntProperty( "objectCount" );
}

void ActiveMemory::createMemoryObjects()
{
	for( int k = 0; k < focusSize; k++ ) {
		ActiveMemoryObject *object = new ActiveMemoryObject( k );
		memoryObjects.add( object );
	}
}

void ActiveMemory::createThreadPool()
{
	threadPool -> create( memoryObjects );
}

void ActiveMemory::start()
{
	threadPool -> start();
	threadPool -> resume();
}

void ActiveMemory::stop()
{
	threadPool -> suspend();
	threadPool -> stop();
}

