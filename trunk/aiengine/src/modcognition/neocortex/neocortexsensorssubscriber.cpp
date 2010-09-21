#include "../cognition_impl.h"

void NeoCortexSensorsSubscriber::onMessage( Message *msg )
{
	logger.logInfo( "NeoCortexSensorsSubscriber: message received source=" + msg -> getSourceId() + ", msgid=" + msg -> getChannelMessageId() );
}
