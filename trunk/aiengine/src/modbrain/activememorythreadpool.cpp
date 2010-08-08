#include "brain_impl.h"

ActiveMemoryThreadPool::ActiveMemoryThreadPool()
{
}

ActiveMemoryThreadPool::~ActiveMemoryThreadPool()
{
	threads.destroy();
}

void ActiveMemoryThreadPool::configure( Xml config )
{
	nThreads = config.getIntProperty( "threadCount" );
	operationsPerSecond = config.getIntProperty( "operationsPerSecond" );
	secondsPerCycle = config.getIntProperty( "secondsPerCycle" );
	maxLoad = config.getIntProperty( "maxLoad" );
}

void ActiveMemoryThreadPool::create( ClassList<ActiveMemoryObject>& objects )
{
	int nObjects = objects.count();
	if( nThreads > nObjects )
		nThreads = nObjects;

	ASSERTMSG( nThreads > 1 , "nThreads is invalid" );

	int nWhole = nObjects / nThreads;
	int nPart = nObjects % nThreads;

	// as a model, each operation is followed by sleep period to allow rest of the mind
	// execute time plus sleep time is operation time
	// we have limit for operations stated that 30K neurons are active in the same time
	// operations are performed by network
	// we consider each network to have 300 neurons (it is drived by areas which split mind area into neurons)
	// final expected throughput is 100 operations (networks) are performed simultaneously
	// it generally means 100 threads are required

	// split objects by threads
	int nFrom = 0;
	for( int k = 0; k < nThreads; k++ ) {
		// calculate number of objects for thread
		int n = nWhole;
		if( nPart ) {
			n++;
			nPart--;
		}

		// create list of objects
		ClassList<ActiveMemoryObject> threadObjects;
		threadObjects.allocate( n );
		for( int j = 0; j < n; j++ )
			threadObjects.add( objects.get( nFrom + j ) );

		// create thread (suspended) and add to the pool
		ActiveMemoryThread *thread = new ActiveMemoryThread( k , threadObjects );
		threads.add( thread );

		// configure thread
		thread -> setOperationsPerSecond( operationsPerSecond );
		thread -> setSecondsPerCycle( secondsPerCycle );
		thread -> setMaxLoad( ( float )maxLoad );

		nFrom += n;
	}
}

void ActiveMemoryThreadPool::start()
{
	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ActiveMemoryThread *thread = threads.get( k );
		thread -> create();
	}
}

void ActiveMemoryThreadPool::suspend()
{
	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ActiveMemoryThread *thread = threads.get( k );
		thread -> suspend();
	}
}

void ActiveMemoryThreadPool::resume()
{
	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ActiveMemoryThread *thread = threads.get( k );
		thread -> resume();
	}
}

void ActiveMemoryThreadPool::stop()
{
	// iterate by threads
	for( int k = threads.count() - 1; k >= 0; k-- ) {
		ActiveMemoryThread *thread = threads.get( k );
		thread -> stop();
	}
}
