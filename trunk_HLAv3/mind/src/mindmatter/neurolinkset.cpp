#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

void NeuroLinkSet::addSetItem( NeuroLink *link ) {
	list.add( link );
}

void NeuroLinkSet::projectData( neurovt *data , int size ) {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> projectData( data , size );
}
