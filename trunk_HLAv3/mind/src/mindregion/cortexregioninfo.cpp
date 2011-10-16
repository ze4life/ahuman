#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

CortexRegionInfo::CortexRegionInfo() {
	nCols = 0;
	regionSideSize = 0;
	useSpatialPooler = true;
	useTemporalPooler = true;
	nTemporalDepth = 4;
}

CortexRegionInfo::~CortexRegionInfo() {
}

void CortexRegionInfo::setColumnCount( int p_nCols ) {
	nCols = p_nCols;
	regionSideSize = ( int )sqrt( ( double )nCols );
}

void CortexRegionInfo::setUsingSpatialPooler( bool p_useSpatialPooler ) {
	useSpatialPooler = p_useSpatialPooler;
}

void CortexRegionInfo::setUsingTemporalPooler( bool p_useTemporalPooler ) {
	useTemporalPooler = p_useTemporalPooler;
}

void CortexRegionInfo::setTemporalDepth( int p_nDepth ) {
	nTemporalDepth = p_nDepth;
}

int CortexRegionInfo::getColumnCount() {
	return( nCols );
}

int CortexRegionInfo::getRegionSideSize() {
	return( regionSideSize );
}

bool CortexRegionInfo::isUsingSpatialPooler() {
	return( useSpatialPooler );
}

bool CortexRegionInfo::isUsingTemporalPooler() {
	return( useTemporalPooler );
}

int CortexRegionInfo::getTemporalDepth() {
	return( nTemporalDepth );
}

