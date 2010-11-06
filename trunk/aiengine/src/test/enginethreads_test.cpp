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
	}
	
// tests
public:

	void testThreadDump( XmlCall& call ) {
		AIEngine& engine = AIEngine::getInstance();
		engine.threadDump();
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createEngineThreadsTest() {
	return( new TestEngineThreads );
}

