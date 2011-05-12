#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindRegionSet::getMindRegion( String regionId ) {
	return( map.get( regionId ) );
}

void MindRegionSet::addMindRegion( MindRegion *region ) {
	list.add( region );
	map.add( region -> getId() , region );
}

void MindRegionSet::exitRegionSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> exitRegion();
}

void MindRegionSet::destroyRegionSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> destroyRegion();
}

