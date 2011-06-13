#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

void MindAreaLinkSet::addSetItem( MindAreaLink *link ) {
	list.add( link );
}

void MindAreaLinkSet::sendOutputData( MindRegion *region , neurovt *data , int size ) {
	for( int k = 0; k < list.count(); k++ ) {
		MindAreaLink *link = list.get( k );
		link -> sendOutputData( region , data , size );
	}
}

