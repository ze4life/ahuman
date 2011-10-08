#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaNet::MindAreaNet( MindNet *p_net , MindAreaNetInfo *p_areaNetInfo ) {
	net = p_net;
	netInfo = p_areaNetInfo;
}

void MindAreaNet::addRegion( MindRegion *region ) {
	regions.add( region );
}

ClassList<MindRegion>& MindAreaNet::getRegions() {
	return( regions );
}

MindNet *MindAreaNet::getNet() {
	return( net );
}

MindAreaNetInfo *MindAreaNet::getNetInfo() {
	return( netInfo );
}
