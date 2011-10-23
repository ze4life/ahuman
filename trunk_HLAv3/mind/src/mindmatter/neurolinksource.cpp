#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkSource::NeuroLinkSource( MindRegion *p_region ) {
	attachLogger();
	data = NULL;
	region = p_region;
	pfn = NULL;
}

void NeuroLinkSource::setSourceSignal( NeuroSignal *p_data ) {
	data = p_data;
}

void NeuroLinkSource::addNeuroLink( NeuroLink *link ) {
	links.add( link );
}

NeuroSignal *NeuroLinkSource::getSourceSignal( NeuroLink *link ) {
	if( data != NULL )
		return( data );

	if( pfn == NULL )
		return( NULL );

	// execute target handler
	try {
		return( ( region ->* pfn )( link , this ) );
	}
	catch( RuntimeException& e ) {
		logger.logError( "getSourceSignal: exception in handling message for NeuroLink id=" + link -> getId() );
		logger.printStack( e );
	}
	catch( ... ) {
		logger.logError( "getSourceSignal: unknown exception in handling message for NeuroLink id=" + link -> getId() );
	}

	return( NULL );
}

void NeuroLinkSource::sendMessage() {
	for( int k = 0; k < links.count(); k++ ) {
		NeuroLink *link = links.get( k );

		NeuroSignal *msgdata = NULL;
		if( data != NULL )
			msgdata = new NeuroSignal( data );
		MindMessage *msg = new MindMessage( link , msgdata );
		region -> sendMessage( msg );
	}
}
