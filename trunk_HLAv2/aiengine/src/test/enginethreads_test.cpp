#include "test_impl.h"

/*#########################################################################*/
/*#########################################################################*/

class TestEngineThreads : public TestUnit , public Subscriber
{
// data
private:

// construction
public:
	TestEngineThreads() : TestUnit( "TestEngineThreads" ) {
	};
	~TestEngineThreads() {
	};

	virtual void init() {
		ADD_METHOD( TestEngineThreads::testThreadDump );
		ADD_METHOD( TestEngineThreads::testShowThread );
	}
	
// tests
public:

	void testThreadDump( XmlCall& call ) {
		bool showStack = call.getBooleanParam( "showStack" );
		AIEngine& engine = AIEngine::getInstance();
		engine.threadDumpAll( showStack );
	}

	void testShowThread( XmlCall& call ) {
		String thread = call.getParam( "threadName" );
		bool showStack = call.getBooleanParam( "showStack" );
		AIEngine& engine = AIEngine::getInstance();
		engine.threadDumpByName( thread , showStack );
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createEngineThreadsTest() {
	return( new TestEngineThreads );
}

