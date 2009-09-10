#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

SubscriptionImpl::SubscriptionImpl( Channel *p_channel , String p_name , Subscriber *p_sub )
{
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

