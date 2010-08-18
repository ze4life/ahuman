#include "brain_impl.h"

MindLink::MindLink( MindLinkInfo *p_info )
{
	info = p_info;

	AIBrainImpl *bi = AIBrainImpl::getInstance();

	String masterAreaId = info -> getMasterAreaId();
	String slaveAreaId = info -> getSlaveAreaId();
	sourceArea = bi -> getMindArea( masterAreaId );
	destinationArea = bi -> getMindArea( slaveAreaId );

	session = NULL;
	iosub = NULL;
	iopub = NULL;
}

MindLink::~MindLink()
{
}

void MindLink::open( Session *p_session )
{
	session = p_session;
	String channelId = info -> getChannelId();
	String ioid =  info -> getMasterAreaId() + "-" +  info -> getSlaveAreaId();

	AIIO io;
	iosub = io.subscribe( session , channelId , ioid , this );
	iopub = io.createPublisher( session , channelId ,  ioid , "MindLinkMsg" );
}

void MindLink::publish( Message *msg )
{
	iopub -> publish( session , msg );
}

void MindLink::onMessage( Message *msg )
{
}
