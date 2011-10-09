#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLink::MindAreaLink( MindAreaLinkInfo *p_info ) {
	attachLogger();
	info = p_info;

	MindService *mm = MindService::getService();

	String masterAreaId = info -> getMasterAreaId();
	String slaveAreaId = info -> getSlaveAreaId();
	sourceArea = mm -> getMindArea( masterAreaId );
	destinationArea = mm -> getMindArea( slaveAreaId );

	session = NULL;
	iosub = NULL;
	links = new MindRegionLinkSet();
}

MindAreaLink::~MindAreaLink() {
	delete links;
}

void MindAreaLink::open( MessageSession *p_session ) {
	session = p_session;
	String channelId = info -> getChannelId();
	String ioid =  info -> getMasterAreaId() + "-" +  info -> getSlaveAreaId();

	MindService *ms = MindService::getService();
	activeMemory = ms -> getActiveMemory();

	MessagingService *msgs = MessagingService::getService();
	iosub = msgs -> subscribe( NULL , channelId , ioid , this );
}

MessageSubscription *MindAreaLink::subscribeSelector( MessageSubscriber *handler , String name , String selector ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getChannelId();
	MessageSubscription *sub = ms -> subscribeSelector( NULL , channelId , selector , channelId + "-" + name , handler );
	return( sub );
}

MessageSubscription *MindAreaLink::subscribe( MessageSubscriber *handler , String name ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getChannelId();
	MessageSubscription *sub = ms -> subscribe( NULL , channelId , channelId + "-" + name , handler );
	return( sub );
}

void MindAreaLink::onBinaryMessage( BinaryMessage *msg ) {
	MindMessage *mm = ( MindMessage * )msg;
	activeMemory -> execute( mm );
}

void MindAreaLink::addRegionLink( MindRegionLink *link ) {
	links -> addSetItem( link );
}
