#include "test_impl.h"
#include "aibrain.h"
#include "..\modbody\body_impl.h"

/*#########################################################################*/
/*#########################################################################*/

class TestFileSysWalker : public TestUnit {
// construction
public:
	TestFileSysWalker() : TestUnit( "TestFileSysWalker" ) {};

	virtual void init() {
		ADD_METHOD( TestFileSysWalker::testChangeFocusUp );
		ADD_METHOD( TestFileSysWalker::testChangeFocusDown );
		ADD_METHOD( TestFileSysWalker::testChangeFocusIncrease );
		ADD_METHOD( TestFileSysWalker::testChangeFocusDecrease );
	}
	
// tests
public:

	void testChangeFocusUp( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 50 );
		float cmd = -0.8f;
		doMoveFocus( cmd , percentToNeural( strength ) );
	}
	void testChangeFocusDown( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 0 );
		float cmd = -0.3f;
		doMoveFocus( cmd , percentToNeural( strength ) );
	}
	void testChangeFocusIncrease( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 0 );
		float cmd = 0.3f;
		doMoveFocus( cmd , percentToNeural( strength ) );
	}
	void testChangeFocusDecrease( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 0 );
		float cmd = 0.8f;
		doMoveFocus( cmd , percentToNeural( strength ) );
	}

private:
	float percentToNeural( int strength ) {
		return( -1.f + strength / 50.f );
	}
	void doMoveFocus( float cmd , float strength ) {
		// find sensor
		Sensors *sensors = Sensors::getSensors();
		Sensor *fsw = sensors -> getSensor( "FileSysWalker" );

		// send command
		cortexvt *pv = fsw -> getInputs();
		pv[ 0 ] = cmd;
		pv[ 1 ] = strength;
		fsw -> processSensorControl();
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createFileSysWalkerTest() {
	return( new TestFileSysWalker );
}

