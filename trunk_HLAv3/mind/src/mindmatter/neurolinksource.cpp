#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NeuroLinkSource::NeuroLinkSource() {
	data = NULL;
}

void NeuroLinkSource::setSourceVector( NeuroVector *p_data ) {
	data = p_data;
}

void NeuroLinkSource::addNeuroLink( NeuroLink *link ) {
	links.add( link );
}

NeuroVector *NeuroLinkSource::getSourceVector() {
	return( data );
}

void NeuroLinkSource::sendMessage( MindRegion *region ) {
	for( int k = 0; k < links.count(); k++ ) {
		NeuroLink *link = links.get( k );

		NeuroVector *msgdata = new NeuroVector( data );
		MindMessage *msg = new MindMessage( link , msgdata );
		region -> sendMessage( msg );
	}
}

