#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkTarget::NeuroLinkTarget( MindRegion *p_region ) {
	attachLogger();

	region = p_region;
	pfn = NULL;
}

void NeuroLinkTarget::setHandler( MindRegion::NeuroLinkTargetHandler p_pfn ) {
	pfn = p_pfn;
}

void NeuroLinkTarget::execute( NeuroLink *link , NeuroSignal *sourceData ) {
	// execute target handler
	try {
		( region ->* pfn )( link , this , sourceData );
	}
	catch( RuntimeException& e ) {
		logger.logError( "execute: exception in handling signal id=" + sourceData -> getId() + " for NeuroLink id=" + link -> getId() );
		logger.printStack( e );
	}
	catch( ... ) {
		logger.logError( "execute: unknown exception in handling signal id=" + sourceData -> getId() + " for NeuroLink id=" + link -> getId() );
	}
}
