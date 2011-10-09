#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaNet::MindAreaNet( MindArea *p_area , MindNet *p_net , MindAreaNetInfo *p_areaNetInfo ) {
	area = p_area;
	net = p_net;
	netInfo = p_areaNetInfo;
}

void MindAreaNet::addRegion( MindRegion *region ) {
	ASSERTMSG( region -> getArea() == area , "Only owned regions can be added to area network" );
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
