//#########################################################################
// This class is responsible to process the message depending upon the
// type of message.
//#########################################################################
#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

/*
 * Constructor to initialize the instance with the required parameters.
 * @param p_session is the pointer to session.
 * @param p_channel is the channel instance
 * @param p_name is the subscription name
 * @param p_sub is the subscriber
 */
SubscriptionImpl::SubscriptionImpl( Session *p_session , Channel *p_channel , String p_name , Subscriber *p_sub )
{
	session = p_session;
	channel = p_channel;
	name = p_name;
	sub = p_sub;
}

/*
 * Returns the channel.
 */
Channel *SubscriptionImpl::getChannel()
{
	return( channel );
}

/*
 * Disconnects the channel.
 */
void SubscriptionImpl::disconnected()
{
    /* TODO; need to see if the memory is free after channel pointer is
        no longer required */
	channel = NULL;
}

/*
 * Process the message deepnding upon the type.
 * @param msg is the message to be processed.
 */
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

