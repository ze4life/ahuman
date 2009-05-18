
#include <aiio_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AISessionImpl::AISessionImpl( int p_id , String p_channeltype , String p_user , void *p_media )
:	engine( AIEngine::getInstance() )
{
	channel = NULL;

	id = p_id;
	channeltype = p_channeltype;
	channeltypeuser = p_user;
	media = p_media;

	sessionOpen = true;
	mediaOpen = true;
}

AISessionImpl::~AISessionImpl()
{
}

void AISessionImpl::close()
{
	io.disconnect( id );
}

void AISessionImpl::closeReflect()
{
	sessionOpen = false;
}

void AISessionImpl::setMediaOpen( bool p_open )
{
	mediaOpen = p_open;
}

void AISessionImpl::sendMessageToExpert( AIMessage *message )
{
	channel -> addRightMessage( message );
}

void AISessionImpl::setChannel( AIDuplexChannel *p_channel )
{
	channel = p_channel;
}

