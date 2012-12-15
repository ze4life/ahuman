#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegionInfo::MindRegionInfo() {
	sizeX = 0;
	sizeY = 0;
	useSpatialPooler = true;
	useTemporalPooler = true;
	temporalDepth = 0;
}

MindRegionInfo::~MindRegionInfo() {
}

void MindRegionInfo::setId( String p_id ) {
	id = p_id;
	Object::setInstance( id );
}

void MindRegionInfo::setType( MindRegionTypeDef *p_typeDef ) {
	typeDef = p_typeDef;
}

void MindRegionInfo::setUsingSpatialPooler( bool p_useSpatialPooler ) {
	useSpatialPooler = p_useSpatialPooler;
}

void MindRegionInfo::setUsingTemporalPooler( bool p_useTemporalPooler ) {
	useTemporalPooler = p_useTemporalPooler;
}

void MindRegionInfo::setTemporalDepth( int p_nDepth ) {
	temporalDepth = p_nDepth;
}

void MindRegionInfo::setSizeInfo( int nx , int ny ) {
	sizeX = nx;
	sizeY = ny;
}

void MindRegionInfo::getSizeInfo( int *nx , int *ny ) {
	*nx = sizeX;
	*ny = sizeY;
}

void MindRegionInfo::setSpatialPoolerSize( int size ) {
	spatialPoolerSize = size;
}

void MindRegionInfo::setTemporalPoolerSize( int size ) {
	temporalPoolerSize = size;
}

