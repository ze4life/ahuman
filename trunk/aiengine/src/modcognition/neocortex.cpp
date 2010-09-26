#include "cognition_impl.h"

class NeoCortex : public Object , public MindArea
{
	CognitiveProcessor *cortexFileSys;

// construction
public:
	NeoCortex() {
		cortexFileSys = CognitiveProcessor::createFileSysCortex();
	};
	virtual ~NeoCortex() {
		delete cortexFileSys;
	}

	const char *getClass() { return( "NeoCortex" ); };

// MindArea interface
public:
	virtual void onCreateArea() {
	};
	virtual void onLoadArea() {};

	virtual void onOpenMindLinkDestination( MindLink *link , String channelId ) {
		if( channelId.equals( "sensordata" ) ) {
			link -> subscribe( cortexFileSys , "sub.filesys" , "FileSysWalker" );
		}
	};
};

MindArea *AICognitionImpl::createNeoCortex()
{
	NeoCortex *area = new NeoCortex();
	return( area );
}
