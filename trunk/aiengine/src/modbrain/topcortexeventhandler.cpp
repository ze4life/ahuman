#include "brain_impl.h"

void TopCortexEventHandler::onCreate( Cortex *cortex )
{
	svc = AIBrainImpl::getInstance();
	nextHandler -> onCreate( cortex );
}

void TopCortexEventHandler::onInputsUpdated( Cortex *cortex )
{
	nextHandler -> onInputsUpdated( cortex );
}

void TopCortexEventHandler::onOutputsUpdated( Cortex *cortex )
{
	nextHandler -> onOutputsUpdated( cortex );
}

