#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNStrategy::NNStrategy( Logger& p_logger )
:	engine( AIEngine::getInstance() ) ,
	helper( p_logger )
{
	p = NULL;
	helper.attach( this );
}

NNStrategy::~NNStrategy()
{
}

void NNStrategy::attach( NN *p_p )
{
	p = p_p;
	errorFunction.attach( p );
	stopFunction.attach( p );
	helper.attach( p );
}

NN& NNStrategy::getNN()
{
	return( *p );
}

NNStrategyHelper& NNStrategy::getHelper()
{
	return( helper );
}

NNStopFunction *NNStrategy::getStopFunction()
{
	return( &stopFunction );
}

NNErrorFunction *NNStrategy::getErrorFunction()
{
	return( &errorFunction );
}
