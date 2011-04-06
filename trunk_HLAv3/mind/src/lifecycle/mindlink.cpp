#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindLink::MindLink( MindLinkInfo *p_info ) {
	info = p_info;

	MindManager *mm = MindManager::getService();

	String masterAreaId = info -> getMasterAreaId();
	String slaveAreaId = info -> getSlaveAreaId();
	sourceArea = mm -> getMindArea( masterAreaId );
	destinationArea = mm -> getMindArea( slaveAreaId );

	session = NULL;
	iosub = NULL;
	iopub = NULL;
}

MindLink::~MindLink() {
}

void MindLink::open( MessageSession *p_session ) {
	session = p_session;
	String channelId = info -> getChannelId();
	String ioid =  info -> getMasterAreaId() + "-" +  info -> getSlaveAreaId();

	MessagingService *ms = MessagingService::getService();
	iosub = ms -> subscribe( session , channelId , ioid , this );
	iopub = ms -> createPublisher( session , channelId ,  ioid , "MindLinkMsg" );

	destinationArea -> onOpenMindLinkDestination( this , channelId );
	sourceArea -> onOpenMindLinkSource( this , channelId );
}

void MindLink::transferOutputs( Cortex *cortex ) {
	// create message and grab data
	CortexMessage *msg = new CortexMessage( cortex );
	msg -> capture();

	// send
	iopub -> publish( session , msg );
}

MessageSubscription *MindLink::subscribeSelector( MessageSubscriber *handler , String name , String selector ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getChannelId();
	MessageSubscription *sub = ms -> subscribeSelector( session , channelId , selector , channelId + "-" + name , handler );
	return( sub );
}

MessageSubscription *MindLink::subscribe( MessageSubscriber *handler , String name )
{
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getChannelId();
	MessageSubscription *sub = ms -> subscribe( session , channelId , channelId + "-" + name , handler );
	return( sub );
}

void MindLink::onMessage( Message *msg ) {
}
