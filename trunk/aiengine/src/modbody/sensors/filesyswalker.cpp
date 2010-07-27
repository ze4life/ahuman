#include "../body_impl.h"

// #############################################################################
// #############################################################################

class SensorFileSysWalker : public Attractor , public CortexEventHandler
{
public:
	SensorFileSysWalker() {
	}

	virtual ~SensorFileSysWalker() {};

	void createAttractor( MindArea *area ) {
		AIBrain brain;
		cortex = brain.createCortex( area , "CortexHardcoded" , 0 , 1 , 1 , this );
	}

	virtual Cortex *getCortex() {
		return( cortex );
	}

private:
	Cortex *cortex;
};

// #############################################################################
// #############################################################################

Attractor *Attractor::createFileSysWalker( MindArea *area )
{
	SensorFileSysWalker *att = new SensorFileSysWalker();
	att -> createAttractor( area );
	return( att );
}

