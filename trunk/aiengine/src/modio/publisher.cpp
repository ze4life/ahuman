/*#########################################################################
 * This class is responsible to publish the message for processing.
/*#########################################################################*/
#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

/*#########################################################################*/

/*
 * Constructor to initialize the instance with the required parameters.
 * @param p_session is the pointer to session.
 * @param p_channel is the channel instance
 * @param p_name is the publisher name
 * @param p_msgtype is the message type
 */
PublisherImpl::PublisherImpl( Session *p_session , Channel *p_channel , String p_name , String p_msgtype ) 
{
	session = p_session;
	channel = p_channel; 
	name = p_name; 
	msgtype = p_msgtype; 
}

/*
 * Default destructor of the class.
 */
PublisherImpl::~PublisherImpl() 
{
}

/*
 * Returns the channel.
 */
Channel *PublisherImpl::getChannel()
{
	return( channel );
}


/*
 * Return the message type.
 */
const String& PublisherImpl::getMsgType()
{
	return( msgtype );
}

/*
 * Publish the message to the channel.
 * @param p_session is the session.
 * @param msg is the message
 */
String PublisherImpl::publish( Session *p_session , const char *msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( p_session , this , msg ) ); 
}

/*
 * Publish the message to the channel.
 * @param p_session is the session.
 * @param msg is the message
 */

String PublisherImpl::publish( Session *p_session , Message *msg )
{
	ASSERT( channel != NULL );
	return( channel -> publish( p_session , this , msg ) ); 
}

/*
 * Disconnects the channel.
 */
void PublisherImpl::disconnected()
{
	channel = NULL;
}

