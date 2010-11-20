/*#########################################################################
 * This class is responsible to process the message depending upon the
 * type of message.
/*#########################################################################*/
#include "io_impl.h"

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
 * Process the message depending upon the type.
 * @param msg is the message to be processed.
 */
void SubscriptionImpl::processMessage( Message *msg )
{
	// verify selector
	if( !selector.isEmpty() )
		if( !isMatchSelector( msg ) )
			return;

	try {
		switch( msg -> getBaseType() ) {
			case Message::MsgType_Text :
				sub -> onTextMessage( ( TextMessage * )msg );
				break;
			case Message::MsgType_Xml :
				sub -> onXmlMessage( ( XmlMessage * )msg );
				break;
			case Message::MsgType_XmlCall :
				sub -> onXmlCall( ( XmlCall * )msg );
				break;
			case Message::MsgType_Binary :
				sub -> onBinaryMessage( msg );
				break;
			default:
				sub -> onMessage( msg );
				break;
		}
	}
	catch ( RuntimeException& e ) {
		Logger logger = channel -> getLogger();
		logger.logError( "processMessage: i/o channel id=" + channel -> getName() + ", subscription=" + name + ": exception when processing message" );
		e.printStack( logger );
	}
	catch ( ... ) {
		Logger logger = channel -> getLogger();
		logger.logError( "processMessage: i/o channel id=" + channel -> getName() + ", subscription=" + name + ": unknown exception" );
		logger.printStack();
	}
}

void SubscriptionImpl::setSelector( String p_selector )
{
	selector = p_selector;
}

bool SubscriptionImpl::isMatchSelector( Message *msg )
{
	// for now, check only message type as selector contents
	const String& type = msg -> getClassType();
	if( type.isEmpty() )
		return( false );

	return( selector.find( type ) >= 0 );
}

