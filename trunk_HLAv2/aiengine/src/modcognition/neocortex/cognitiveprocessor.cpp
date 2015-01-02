#include "../cognition_impl.h"

CognitiveProcessor::CognitiveProcessor( String name )
{
	Object::setInstance( name );
}

void CognitiveProcessor::createCortexProcessor( MindArea *area , Cortex *inputs )
{
	inputsCortex = inputs;

	// get source inputs location - in destination area coords
	const BrainLocation& inputsLocationLocal = inputs -> getAreaLocation();
	BrainLocation inputsSurfaceLocal = inputsLocationLocal.getOutputsSurface();
	MindArea *sourceArea = inputs -> getArea();
	const BrainLocation& sourceAreaLocation = sourceArea -> getLocation();
	BrainLocation inputsSurface = sourceAreaLocation.getAbsoluteLocation( inputsSurfaceLocal );
	inputAreaSize = inputsSurface.getSurfaceSize();

	// get cortex location
	const BrainLocation& areaLocation = area -> getLocation();
	BrainLocation location = areaLocation.getRelativeLocation( inputsSurface );
	areaLocation.moveInside( location );

	int nRegions = 3;
	int nSize = 2 + nRegions;
	location.resize( 0 , 0 , nSize );
	location.setOrientationZ( true );

	// use cortex factory
	AIBrain brain;
	cognitiveCortex = brain.createNeoCortex( area , location , inputs );
}

void CognitiveProcessor::processMessage( CortexMessage *msg )
{
	logger.logInfo( "processMessage: message received sourceid=" + msg -> getSourceId() + 
		", classType=" + msg -> getClassType() +
		", msgid=" + msg -> getChannelMessageId() );

	// set to cortex inputs
	cortexvt *cv = cognitiveCortex -> getInputs();
	msg -> get( inputAreaSize , cv );
	cognitiveCortex -> processInputsUpdated();
}
