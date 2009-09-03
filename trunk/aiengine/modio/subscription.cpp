#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AISubscriptionImpl::AISubscriptionImpl( AIChannel *p_channel , String p_name , AISubscriber *p_sub )
{
	channel = p_channel;
	name = p_name;
	sub = p_sub;
}

void AISubscriptionImpl::disconnected()
{
	channel = NULL;
}

