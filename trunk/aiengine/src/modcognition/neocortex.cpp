#include "cognition_impl.h"

class NeoCortex : public MindArea
{
// construction
public:
	NeoCortex() {};

// MindArea interface
public:
	virtual void onCreateArea() {
	};
	virtual void onLoadArea() {
	}
};

MindArea *AICognitionImpl::createNeoCortex()
{
	NeoCortex *area = new NeoCortex();
	return( area );
}
