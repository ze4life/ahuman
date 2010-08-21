#include "cognition_impl.h"

class NeoCortex : public Object , public MindArea
{
	NeoCortexSensorsSubscriber *sensorsSub;

// construction
public:
	NeoCortex() {
		sensorsSub = new NeoCortexSensorsSubscriber();
	};
	virtual ~NeoCortex() {
		delete sensorsSub;
	}

	const char *getClass() { return( "NeoCortex" ); };

// MindArea interface
public:
	virtual void onCreateArea() {};
	virtual void onLoadArea() {};

	virtual void onOpenMindLinkDestination( MindLink *link , String channelId ) {
		if( channelId.equals( "sensordata" ) ) {
			link -> subscribe( sensorsSub , "neocortex" );
		}
	};
};

MindArea *AICognitionImpl::createNeoCortex()
{
	NeoCortex *area = new NeoCortex();
	return( area );
}
