#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

SubscriptionImpl::SubscriptionImpl( Session *p_session , Channel *p_channel , String p_name , Subscriber *p_sub )
{
	session = p_session;
	channel = p_channel;
	name = p_name;
	sub = p_sub;
}

Channel *SubscriptionImpl::getChannel()
{
	return( channel );
}

void SubscriptionImpl::disconnected()
{
	channel = NULL;
}

void SubscriptionImpl::processMessage( Message *msg )
{
	switch( msg -> getMsgBaseType() )
		{
			case Message::MsgType_Text :
				sub -> onMessage( msg );
				break;
			case Message::MsgType_Xml :
				sub -> onXmlMessage( ( XmlMessage * )msg );
				break;
			case Message::MsgType_XmlCall :
				sub -> onXmlCall( ( XmlCall * )msg );
				break;
			default:
				ASSERTFAILED( String( "Uknown message type for message: " ) + msg -> getChannelMessageId() );
		}
}

