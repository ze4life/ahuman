#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkTarget::NeuroLinkTarget() {
}

void NeuroLinkTarget::setHandler( MindRegion *p_region , MindRegion::NeuroLinkHandler p_pfn ) {
	region = p_region;
	pfn = p_pfn;
}

