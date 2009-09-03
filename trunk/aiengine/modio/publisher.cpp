#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIPublisherImpl::AIPublisherImpl( AIChannel *p_channel , String p_name , String p_msgtype ) 
{ 
	channel = p_channel; 
	name = p_name; 
	msgtype = p_msgtype; 
}

AIPublisherImpl::~AIPublisherImpl() 
{
}

String AIPublisherImpl::publish( String msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( this , msg ) ); 
}

String AIPublisherImpl::publish( Xml msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( this , msg , msg.getName() ) );
}

void AIPublisherImpl::disconnected()
{
	channel = NULL;
}

