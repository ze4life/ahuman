#include "../body_impl.h"

class Eye : public Sensor, public Object{

public:
	AIEngine& engine;

	Eye( MindArea *area ) :	Sensor( "EyeSensor" , area , CortexIOSizeInfo( 20 , 2 ) ) ,
		engine( AIEngine::getInstance() ) {

	}

	virtual ~Eye() {

	}

	virtual const char *getClass() {
		return( "Eye" ); 
	}

	virtual void startSensor(){

	}
	virtual void stopSensor(){

	}
	virtual void processSensorControl(){

	}
	virtual bool executeSensorControl(){
		return true;
	}
	virtual void produceSensorData() {

	}

};

Sensor *Sensor::createEye( MindArea *area ){
	Eye *att = new Eye( area );
	return( att );
}