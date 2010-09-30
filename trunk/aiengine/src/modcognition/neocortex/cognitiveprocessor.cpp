#include "../cognition_impl.h"

void CognitiveProcessor::createCortexProcessor( Cortex *inputs )
{
	cortex = inputs;
}

void CognitiveProcessor::processMessage( CortexMessage *msg )
{
	logger.logInfo( "message received sourceid=" + msg -> getSourceId() + 
		", type=" + msg -> getType() +
		", msgid=" + msg -> getChannelMessageId() );
}

