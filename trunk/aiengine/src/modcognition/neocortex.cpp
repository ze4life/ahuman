#include "cognition_impl.h"

class NeoCortex : public MindArea
{
// construction
public:
	NeoCortex() {};

// MindArea interface
public:
	virtual void createArea() {
	};
	virtual void loadArea() {
	}
};

MindArea *AICognitionImpl::createNeoCortex()
{
	NeoCortex *area = new NeoCortex();
	return( area );
}
