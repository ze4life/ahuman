#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

CortexRegion::CortexRegion() {
	attachLogger();
}

void CortexRegion::createRegion() {
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
}

NeuroPool *CortexRegion::getFeedForwardInputPool() {
	return( NULL );
}

NeuroLinkSource *CortexRegion::getNeuroLinkSource( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( NULL );
}

NeuroLinkTarget *CortexRegion::getNeuroLinkTarget( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( NULL );
}

