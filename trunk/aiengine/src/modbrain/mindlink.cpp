#include "brain_impl.h"

MindLinkImpl::MindLinkImpl( MindLinkInfo *p_info )
{
	info = p_info;
	session = NULL;
	iosub = NULL;
}

MindLinkImpl::~MindLinkImpl()
{
}

void MindLinkImpl::open( Session *session )
{
	String channelId = info -> getChannelId();

	AIIO io;
	iosub = io.subscribe( session , channelId , channelId , this );
}

void MindLinkImpl::onMessage( Message *msg )
{
}

