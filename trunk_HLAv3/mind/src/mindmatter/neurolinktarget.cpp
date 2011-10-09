#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkTarget::NeuroLinkTarget() {
	attachLogger();
	region = NULL;
	pfn = NULL;
}

void NeuroLinkTarget::setHandler( MindRegion *p_region , MindRegion::NeuroLinkHandler p_pfn ) {
	region = p_region;
	pfn = p_pfn;
}

void NeuroLinkTarget::execute( NeuroLink *link , NeuroVector *sourceData ) {
	// execute target handler
	try {
		( region ->* pfn )( link , sourceData );
	}
	catch( RuntimeException& e ) {
		logger.logError( "Exception in handling message for NeuroLink id=" + link -> getId() );
		logger.printStack( e );
	}
	catch( ... ) {
		logger.logError( "Unknown exception in handling message for NeuroLink id=" + link -> getId() );
	}
}
