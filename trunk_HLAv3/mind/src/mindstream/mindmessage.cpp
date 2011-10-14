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

MindMessage::MindMessage( NeuroLink *p_link , NeuroVector *p_data )
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

NeuroVector *MindMessage::getMsgData() { 
	if( data != NULL )
		return( data ); 
	
	NeuroLinkSource *source = link -> getSource();
	return( source -> getSourceVector() );
}
