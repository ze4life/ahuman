#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLink::MindAreaLink() {
	attachLogger();

	masterArea = NULL;
	slaveArea = NULL;

	session = NULL;
	masterSubscription = NULL;
	slaveSubscription = NULL;
	links = new MindRegionLinkSet();
}

MindAreaLink::~MindAreaLink() {
	delete links;
}

void MindAreaLink::create( MindArea *p_masterArea , MindArea *p_slaveArea ) {
	masterArea = p_masterArea;
	slaveArea = p_slaveArea;
}

void MindAreaLink::createRegionLinks() {
	MindService *ms = MindService::getService();

	// create region mapping
}

void MindAreaLink::open( MessageSession *p_session ) {
	session = p_session;

	MindService *ms = MindService::getService();
	activeMemory = ms -> getActiveMemory();

	MessagingService *msgs = MessagingService::getService();

	// open master channel
	String masterChannelId = info -> getMasterChannelId();
	if( !masterChannelId.isEmpty() ) {
		String masterIOId =  info -> getMasterAreaId() + "-" +  info -> getSlaveAreaId();
		masterSubscription = msgs -> subscribe( NULL , masterChannelId , masterIOId , this );
	}

	// open slave channel
	String slaveChannelId = info -> getSlaveChannelId();
	if( !slaveChannelId.isEmpty() ) {
		String slaveIOId =  info -> getSlaveAreaId() + "-" +  info -> getMasterAreaId();
		slaveSubscription = msgs -> subscribe( NULL , slaveChannelId , slaveIOId , this );
	}
}

MessageSubscription *MindAreaLink::subscribeMaster( MessageSubscriber *handler , String name ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getMasterChannelId();
	MessageSubscription *sub = ms -> subscribe( NULL , channelId , channelId + "-" + name , handler );
	return( sub );
}

MessageSubscription *MindAreaLink::subscribeMasterSelector( MessageSubscriber *handler , String name , String selector ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getMasterChannelId();
	MessageSubscription *sub = ms -> subscribeSelector( NULL , channelId , selector , channelId + "-" + name , handler );
	return( sub );
}

MessageSubscription *MindAreaLink::subscribeSlave( MessageSubscriber *handler , String name ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getSlaveChannelId();
	MessageSubscription *sub = ms -> subscribe( NULL , channelId , channelId + "-" + name , handler );
	return( sub );
}

MessageSubscription *MindAreaLink::subscribeSlaveSelector( MessageSubscriber *handler , String name , String selector ) {
	MessagingService *ms = MessagingService::getService();
	String channelId = info -> getSlaveChannelId();
	MessageSubscription *sub = ms -> subscribeSelector( NULL , channelId , selector , channelId + "-" + name , handler );
	return( sub );
}

void MindAreaLink::onBinaryMessage( BinaryMessage *msg ) {
	MindMessage *mm = ( MindMessage * )msg;

	// ignore foreign links
	if( mm -> getAreaLink() != this )
		return;

	activeMemory -> execute( mm );
}

void MindAreaLink::addRegionLink( MindRegionLink *link ) {
	links -> addSetItem( link );
}
