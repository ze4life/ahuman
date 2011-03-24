#include <ah_platform.h>
#include <ah_messaging_impl.h>

/*#########################################################################
 * This class is responsible to process the message depending upon the
 * type of message.
/*#########################################################################*/

/*#########################################################################*/
/*#########################################################################*/

/*
 * Constructor to initialize the instance with the required parameters.
 * @param p_session is the pointer to session.
 * @param p_channel is the channel instance
 * @param p_name is the subscription name
 * @param p_sub is the subscriber
 */
MessageSubscription::MessageSubscription( MessageSession *p_session , MessageChannel *p_channel , String p_name , MessageSubscriber *p_sub ) {
	session = p_session;
	channel = p_channel;
	name = p_name;
	sub = p_sub;
}

/*
 * Returns the channel.
 */
MessageChannel *MessageSubscription::getChannel() {
	return( channel );
}

/*
 * Disconnects the channel.
 */
void MessageSubscription::disconnected() {
    /* TODO; need to see if the memory is free after channel pointer is
        no longer required */
	channel = NULL;
}

/*
 * Process the message depending upon the type.
 * @param msg is the message to be processed.
 */
void MessageSubscription::processMessage( Message *msg ) {
	// verify selector
	if( !selector.isEmpty() )
		if( !isMatchSelector( msg ) )
			return;

	Logger logger = channel -> getLogger();
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
		logger.logError( "processMessage: i/o channel id=" + channel -> getName() + ", subscription=" + name + ": exception when processing message" );
		logger.printStack( e );
	}
	catch ( ... ) {
		logger.printStack();
		logger.logError( "processMessage: i/o channel id=" + channel -> getName() + ", subscription=" + name + ": unknown exception" );
	}
}

void MessageSubscription::setSelector( String p_selector ) {
	selector = p_selector;
}

bool MessageSubscription::isMatchSelector( Message *msg ) {
	// for now, check only message type as selector contents
	const String& type = msg -> getClassType();
	if( type.isEmpty() )
		return( false );

	return( selector.find( type ) >= 0 );
}

