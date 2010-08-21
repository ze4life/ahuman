#include "../cognition_impl.h"

void NeoCortexSensorsSubscriber::onMessage( Message *msg )
{
	logger.logInfo( "message received source=" + msg -> getSourceId() + ", msgid=" + msg -> getChannelMessageId() );
}
