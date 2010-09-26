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

	destinationArea -> onOpenMindLinkDestination( this , channelId );
	sourceArea -> onOpenMindLinkSource( this , channelId );
}

void MindLink::publish( BinaryMessage *msg )
{
	iopub -> publish( session , msg );
}

Subscription *MindLink::subscribe( Subscriber *handler , String name , String selector )
{
	AIIO io;
	String channelId = info -> getChannelId();
	Subscription *sub = io.subscribeSelector( session , channelId , selector , channelId + "-" + name , handler );
	return( sub );
}

void MindLink::onMessage( Message *msg )
{
}
