#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NucleiRegionInfo::NucleiRegionInfo() {
	totalNeurons = 0;
}

NucleiRegionInfo::~NucleiRegionInfo() {
}

void NucleiRegionInfo::setTotalSize( int nNeurons ) {
	totalNeurons = nNeurons;
}

int NucleiRegionInfo::getTotalSize() {
	return( totalNeurons );
}

int NucleiRegionInfo::getSideSize() {
	return( ( int )sqrt( ( double )totalNeurons ) );
}
