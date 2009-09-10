#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

PublisherImpl::PublisherImpl( Channel *p_channel , String p_name , String p_msgtype ) 
{ 
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

String PublisherImpl::publish( const char *msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( this , msg ) ); 
}

String PublisherImpl::publish( Message *msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( this , msg ) ); 
}

String PublisherImpl::publish( XmlMessage *msg )
{
	ASSERT( channel != NULL );
	msg -> setMessageFromXml();
	return( channel -> publish( this , msg ) );
}

String PublisherImpl::publish( XmlCall *msg )
{
	ASSERT( channel != NULL );
	msg -> setMessageFromXml();
	return( channel -> publish( this , msg ) );
}

void PublisherImpl::disconnected()
{
	channel = NULL;
}

