#include "cognition_impl.h"

class NeoCortex : public Object , public MindArea , public Subscriber
{
	MapStringToClass<CognitiveProcessor> cortexMap;

// construction
public:
	NeoCortex() {
	};
	virtual ~NeoCortex() {
		cortexMap.destroy();
	}

	const char *getClass() { return( "NeoCortex" ); };

// MindArea interface
public:
	virtual void onCreateArea() {};
	virtual void onLoadArea() {};

	virtual void onBrainStop() {
		for( int k = 0; k < cortexMap.count(); k++ ) {
			CognitiveProcessor *cp = cortexMap.getClassByIndex( k );
			cp -> stop();
		}
	};

	virtual void onOpenMindLinkDestination( MindLink *link , String channelId ) {
		if( channelId.equals( "sensordata" ) ) {
			link -> subscribe( this , "sub.neocortex" );
		}
	};

	virtual void onBinaryMessage( Message *msg ) {
		ASSERT( msg -> isClassType( "cortexmessage" ) );

		// it is CortexMessage
		CortexMessage *cortexMessage = ( CortexMessage * )msg;
		
		// find cortex counterpart by source cortex map
		Cortex *source = cortexMessage -> getSourceCortex();
		CognitiveProcessor *processor = cortexMap.get( source -> getId() );

		// create processor if does not exists
		if( processor == NULL ) {
			processor = new CognitiveProcessor( source -> getId() );
			processor -> createCortexProcessor( this , source );
			cortexMap.add( source -> getId() , processor );
		}

		// pass cortex data to the processor
		processor -> processMessage( cortexMessage );
	}
};

/*#########################################################################*/
/*#########################################################################*/

MindArea *AICognitionImpl::createNeoCortex()
{
	NeoCortex *area = new NeoCortex();
	return( area );
}
