#include "brain_impl.h"

ActiveMemoryObject::ActiveMemoryObject( int id )
{
	activeMemoryObjectId = id;
	name = String( "AMO" ) + id;
	logger.attach( name );
}

ActiveMemoryObject::~ActiveMemoryObject()
{
}

void ActiveMemoryObject::setCortex( Cortex *cortex )
{
}

void ActiveMemoryObject::execute()
{
	double x = 0;
	for( int k = 0; k < 10000; k++ )
		x += log( ( double )k );
}

