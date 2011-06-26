#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionLink::MindRegionLink() {
	src = NULL;
	dst = NULL;
	links = new NeuroLinkSet();

	attachLogger();
}

MindRegion *MindRegionLink::getSrcRegion() {
	return( src );
}

MindRegion *MindRegionLink::getDstRegion() {
	return( dst );
}

void MindRegionLink::createRegionLink( MindRegion *srcRegion , MindRegion *dstRegion ) {
	src = srcRegion;
	dst = dstRegion;

	srcRegion -> createNeuroLinks( dstRegion );
}

void MindRegionLink::exitRegionLink() {
}

void MindRegionLink::destroyRegionLink() {
	delete links;
	links = NULL;
}

void MindRegionLink::sendOutputData( neurovt *data , int size ) {
	logger.logDebug( "sendOutputData: srcregion=" + src -> getRegionId() + ", dstregion=" + dst -> getRegionId() );
	links -> sendData( data , size );
}
