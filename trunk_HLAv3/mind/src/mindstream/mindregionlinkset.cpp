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

int MindRegionLinkSet::getCount() {
	return( list.count() );
}
