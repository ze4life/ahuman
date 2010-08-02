#include "../body_impl.h"

// #############################################################################
// #############################################################################

class SensorFileSysWalker : public Object , public Attractor , public CortexEventHandler
{
private:
	AIEngine& engine;
	Cortex *cortex;

public:
	SensorFileSysWalker() 
	: engine( AIEngine::getInstance() ) {
		cortex = NULL;
	}

	virtual ~SensorFileSysWalker() {};
	virtual const char *getClass() { return( "SensorFileSysWalker" ); };

	void createAttractor( MindArea *area ) {
		AIBrain brain;
		cortex = brain.createCortex( area , "CortexHardcoded" , 0 , 1 , 1 , this );
	}

	virtual Cortex *getCortex() {
		return( cortex );
	}

	virtual void onCreate( Cortex *cortex ) {
	};

	virtual void onRun() {
		logger.logInfo( "run thread..." );
	}
};

// #############################################################################
// #############################################################################

Attractor *Attractor::createFileSysWalker( MindArea *area )
{
	SensorFileSysWalker *att = new SensorFileSysWalker();
	att -> createAttractor( area );
	return( att );
}

