#include "../body_impl.h"

// #############################################################################
// #############################################################################

class SensorFileSysWalker : public Object , public Attractor
{
private:
	AIEngine& engine;
	float *vin;
	float *vout;

public:
	SensorFileSysWalker( MindArea *area ) 
	:	Attractor( area , 1 , 1 ) ,
		engine( AIEngine::getInstance() ) {
		// data
		vin = Cortex::getInputs();
		vout = Cortex::getOutputs();
		// poll setup
		Attractor::setPollInterval( 100 );
		Attractor::setPollState( false );

		logger.attach( this );
	}

	virtual ~SensorFileSysWalker() {};
	virtual const char *getClass() { return( "SensorFileSysWalker" ); };

	virtual void onCortexRun() {
		logger.logInfo( "SensorFileSysWalker: produce sensor data..." );
		*vout = 1;
		// trigger standard brain action
		Cortex::processOutputsUpdated();
	}
};

// #############################################################################
// #############################################################################

Attractor *Attractor::createFileSysWalker( MindArea *area )
{
	SensorFileSysWalker *att = new SensorFileSysWalker( area );
	return( att );
}

