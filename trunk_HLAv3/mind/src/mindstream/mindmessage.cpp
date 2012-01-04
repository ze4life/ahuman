#include "ah_mind.h"
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindMessage::MindMessage( NeuroLink *p_link )
:	Message( Message::MsgType_Binary ) { 
	link = p_link;
	data = NULL;

	MindRegionLink *regionLink = link -> getRegionLink();
	if( link != NULL )
		areaLink = regionLink -> getAreaLink();
	else
		areaLink = NULL;
}

MindMessage::MindMessage( NeuroLink *p_link , NeuroSignal *p_data )
:	Message( Message::MsgType_Binary ) { 
	link = p_link;
	data = p_data;

	MindRegionLink *regionLink = link -> getRegionLink();
	if( link != NULL )
		areaLink = regionLink -> getAreaLink();
	else
		areaLink = NULL;
}

MindMessage::~MindMessage() {
	if( data != NULL )
		delete data;
}

NeuroSignal *MindMessage::getMsgData() { 
	if( data != NULL )
		return( data ); 
	
	NeuroLinkSource *source = link -> getSource();
	NeuroSignal *ns = source -> getLinkSignal( link );

	data = ns;
	ASSERTMSG( ns != NULL , "MindMessage::getMsgData: returned NULL signal from NeuroLinkSource, NeuroLink id=" + link -> getId() );
	return( ns );
}
