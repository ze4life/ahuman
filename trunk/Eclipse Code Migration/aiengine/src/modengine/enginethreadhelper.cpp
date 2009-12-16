#include "aiengine_impl.h"

/*#########################################################################*/
/*#########################################################################*/

EngineThreadHelper::EngineThreadHelper()
{ 
	AIEngine& engine = AIEngine::getInstance();
	engine.addWorkerObject( "engineThreadHelper" , this );

	oldAIUnhandledExceptionTranslator = NULL;
	remains = false; 
}

EngineThreadHelper::~EngineThreadHelper()
{
}

EngineThreadHelper *EngineThreadHelper::getThreadObject()
{
	AIEngine& engine = AIEngine::getInstance();
	return( ( EngineThreadHelper * )engine.getWorkerObject( "engineThreadHelper" ) );
}
