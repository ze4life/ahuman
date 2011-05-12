#include "ah_mind.h"
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindMessage::MindMessage( MindRegion *p_region ) 
:	Message( Message::MsgType_Binary ) { 
	region = p_region;
	size = 0;
	data = NULL; 
	setMessageType( "MindMessage" );
}

MindMessage::~MindMessage() {
	if( data != NULL )
		free( data );
}

void MindMessage::get( unsigned n , neurovt *values ) {
	ASSERTMSG( "message does not fit into buffer" , n >= size );
	memcpy( values , data , size * sizeof( float ) );
}
