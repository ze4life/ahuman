#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

PublisherImpl::PublisherImpl( Session *p_session , Channel *p_channel , String p_name , String p_msgtype ) 
{
	session = p_session;
	channel = p_channel; 
	name = p_name; 
	msgtype = p_msgtype; 
}

PublisherImpl::~PublisherImpl() 
{
}

Channel *PublisherImpl::getChannel()
{
	return( channel );
}

const String& PublisherImpl::getMsgType()
{
	return( msgtype );
}

String PublisherImpl::publish( Session *p_session , const char *msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( p_session , this , msg ) ); 
}

String PublisherImpl::publish( Session *p_session , Message *msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( p_session , this , msg ) ); 
}

void PublisherImpl::disconnected()
{
	channel = NULL;
}

