#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

void NeuroLinkSet::sendData( neurovt *data , int size ) {
	for( int k = 0; k < list.count(); k++ )
		list.get( k ) -> sendData( data , size );
}
