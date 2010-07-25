#include "../body_impl.h"

// #############################################################################
// #############################################################################

class SensorFileSysWalker : public Attractor
{
public:
	SensorFileSysWalker() {
	}

	virtual ~SensorFileSysWalker() {};

	Cortex *getSensesCortex() {
		return( NULL );
	}

	Cortex *getActionsCortex() {
		return( NULL );
	}
};

// #############################################################################
// #############################################################################

Attractor *Attractor::createFileSysWalker()
{
	return( new SensorFileSysWalker() );
}

