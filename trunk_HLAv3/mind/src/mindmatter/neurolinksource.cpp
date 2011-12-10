#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkSource::NeuroLinkSource( MindRegion *p_region , String p_entity ) {
	attachLogger();

	entity = p_entity;
	sourceSignal = NULL;
	sourcePool = NULL;
	region = p_region;
	pfn = NULL;

	region -> getSourceSizes( entity , &sizeX , &sizeY );
}

void NeuroLinkSource::setSourceSignal( NeuroSignal *p_data ) {
	sourceSignal = p_data;
}

void NeuroLinkSource::setSourcePool( NeuroPool *p_data ) {
	sourcePool = p_data;
}

void NeuroLinkSource::addNeuroLink( NeuroLink *link ) {
	links.add( link );
}

int NeuroLinkSource::getSizeX() {
	return( sizeX );
}

int NeuroLinkSource::getSizeY() {
	return( sizeY );
}

NeuroSignal *NeuroLinkSource::getSourceSignal( NeuroLink *link ) {
	// use callback function
	if( pfn != NULL ) {
		// execute source handler
		try {
			NeuroSignal *signal = ( region ->* pfn )( link , this );
			return( signal );
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

	// use fixed source signal
	if( sourceSignal != NULL )
		return( sourceSignal );

	// use source pool
	if( sourcePool != NULL ) {
		// create from pool
		NeuroSignal *signal = new NeuroSignal( link -> getSizeX() , link -> getSizeY() );
		signal -> createFromPool( sourcePool );
		return( signal );
	}

	return( NULL );
}

void NeuroLinkSource::sendMessage() {
	for( int k = 0; k < links.count(); k++ ) {
		NeuroLink *link = links.get( k );

		NeuroSignal *signal = NULL;
		if( sourceSignal != NULL )
			signal = new NeuroSignal( sourceSignal );
		MindMessage *msg = new MindMessage( link , signal );
		region -> sendMessage( msg );
	}
}
