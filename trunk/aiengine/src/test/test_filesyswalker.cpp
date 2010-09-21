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
		ADD_METHOD( TestFileSysWalker::testChangeFocusDepth );
	}
	
// tests
public:

	void testChangeFocusUp( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 50 );
		doMoveFocus( 1 , percentToNeural( strength ) );
	}
	void testChangeFocusDown( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 50 );
		doMoveFocus( 2 , percentToNeural( strength ) );
	}
	void testChangeFocusIncrease( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 50 );
		doMoveFocus( 3 , percentToNeural( strength ) );
	}
	void testChangeFocusDecrease( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 50 );
		doMoveFocus( 4 , percentToNeural( strength ) );
	}
	void testChangeFocusDepth( XmlCall& call ) {
		int strength = call.getIntParam( "strength" , 50 );
		doMoveFocus( 5 , percentToNeural( strength ) );
	}

private:
	float percentToNeural( int strength ) {
		return( -1.f + strength / 50.f );
	}
	void doMoveFocus( int cmd , float strength ) {
		// encode cmd as middle of float region assigned to command
		int NUMBER_OF_CMDS = 5;
		float value = ( cmd - 0.5f ) * ( 1.f / NUMBER_OF_CMDS );
		value = value * 2 - 1;

		// find sensor
		Sensors *sensors = Sensors::getSensors();
		Sensor *fsw = sensors -> getSensor( "FileSysWalker" );

		// send command
		cortexvt *pv = fsw -> getInputs();
		pv[ 0 ] = value;
		pv[ 1 ] = strength;
		fsw -> processSensorControl();
	}
};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createFileSysWalkerTest() {
	return( new TestFileSysWalker );
}

