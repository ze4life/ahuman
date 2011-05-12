#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLink::MindAreaLink( MindAreaLinkInfo *p_info ) {
	info = p_info;

	MindService *mm = MindService::getService();

	String masterAreaId = info -> getMasterAreaId();
	String slaveAreaId = info -> getSlaveAreaId();
	sourceArea = mm -> getMindArea( masterAreaId );
	destinationArea = mm -> getMindArea( slaveAreaId );

	session = NULL;
	iosub = NULL;
	iopub = NULL;
}

MindAreaLink::~MindAreaLink() {
}

void MindAreaLink::open( MessageSession *p_session ) {
	session = p_session;
	String channelId = info -> getChannelId();
	String ioid =  info -> getMasterAreaId() + "-" +  info -> getSlaveAreaId();

	MessagingService *ms = MessagingService::getService();
	iosub = ms -> subscribe( session , channelId , ioid , this );
	iopub = ms -> createPublisher( session , channelId ,  ioid , "MindAreaLinkMsg" );
}

MessageSubscription *MindAreaLink::subscribeSelector( MessageSubscriber *handler , String name , String selector ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getChannelId();
	MessageSubscription *sub = ms -> subscribeSelector( session , channelId , selector , channelId + "-" + name , handler );
	return( sub );
}

MessageSubscription *MindAreaLink::subscribe( MessageSubscriber *handler , String name )
{
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getChannelId();
	MessageSubscription *sub = ms -> subscribe( session , channelId , channelId + "-" + name , handler );
	return( sub );
}

void MindAreaLink::onMessage( Message *msg ) {
	logger.logInfo( "MindAreaLink::onMessage - not implemented" );
}
