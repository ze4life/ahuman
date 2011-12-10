#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

CortexRegionInfo::CortexRegionInfo() {
	sizeX = 0;
	sizeY = 0;
	useSpatialPooler = true;
	useTemporalPooler = true;
	temporalDepth = 0;
}

CortexRegionInfo::~CortexRegionInfo() {
}

void CortexRegionInfo::setUsingSpatialPooler( bool p_useSpatialPooler ) {
	useSpatialPooler = p_useSpatialPooler;
}

void CortexRegionInfo::setUsingTemporalPooler( bool p_useTemporalPooler ) {
	useTemporalPooler = p_useTemporalPooler;
}

void CortexRegionInfo::setTemporalDepth( int p_nDepth ) {
	temporalDepth = p_nDepth;
}

void CortexRegionInfo::setSizeInfo( int nx , int ny ) {
	sizeX = nx;
	sizeY = ny;
}

void CortexRegionInfo::getSizeInfo( int *nx , int *ny ) {
	*nx = sizeX;
	*ny = sizeY;
}

bool CortexRegionInfo::isUsingSpatialPooler() {
	return( useSpatialPooler );
}

bool CortexRegionInfo::isUsingTemporalPooler() {
	return( useTemporalPooler );
}

int CortexRegionInfo::getTemporalDepth() {
	return( temporalDepth );
}

void CortexRegionInfo::setSpatialPoolerSize( int size ) {
	spatialPoolerSize = size;
}

void CortexRegionInfo::setTemporalPoolerSize( int size ) {
	temporalPoolerSize = size;
}

int CortexRegionInfo::getSpatialPoolerSize() {
		return( spatialPoolerSize );
}

int CortexRegionInfo::getTemporalPoolerSize() {
		return( temporalPoolerSize );
}

