#include "ah_mind.h"
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindMessage::MindMessage( NeuroLink *p_link )
:	Message( Message::MsgType_Binary ) { 
	link = p_link;
	data = NULL;
}

MindMessage::MindMessage( NeuroLink *p_link , NeuroVector *p_data )
:	Message( Message::MsgType_Binary ) { 
	link = p_link;
	data = p_data;
}

MindMessage::~MindMessage() {
	if( data != NULL )
		delete data;
}

NeuroVector *MindMessage::getMsgData() { 
	if( data != NULL )
		return( data ); 
	return( link -> getSourceData() );
}
