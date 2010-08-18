#include "brain_impl.h"

void Cortex::processInputsUpdated()
{
}

void Cortex::processOutputsUpdated()
{
	if( nOutputs <= 0 )
		return;

	// distribute over links
	ClassList<MindLink>& links = area -> getMindLinks();
	for( int k = links.count() - 1; k >= 0; k-- ) {
		MindLink *link = links.get( k );

		// ignore non-source area
		if( link -> getSourceArea() != area )
			continue;

		// create message - copy output data
		BinaryMessage *msg = new BinaryMessage( nOutputs * sizeof( cortexvt ) );
		msg -> setArray( nOutputs , outputs );

		// pass message to the channel
		link -> publish( msg );
	}
}
