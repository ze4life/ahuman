#include "body_impl.h"

class Sensors : public MindArea
{
// construction
public:
	Sensors() {};

	void createAttractors() {
		Attractor::createFileSysWalker( this );
	}

// MindArea interface
public:
	virtual void createArea() {
		createAttractors();
	};
	virtual void loadArea() {
		// for body areas create and load are the same
		createArea();
	}
};

MindArea *AIBodyImpl::createSensors()
{
	Sensors *area = new Sensors();
	return( area );
}
