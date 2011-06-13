#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

void MindRegionLinkSet::exitRegionLinkSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> exitRegionLink();
}

void MindRegionLinkSet::destroyRegionLinkSet() {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> destroyRegionLink();
}

void MindRegionLinkSet::addSetItem( MindRegionLink *link ) {
	list.add( link );
}

void MindRegionLinkSet::sendOutputData( MindRegion *region , neurovt *data , int size ) {
	for( int k = 0; k < list.count(); k++ ) {
		MindRegionLink *link = list.get( k );
		if( link -> getSrcRegion() == region )
			list.get( k ) -> sendOutputData( data , size );
	}
}

