#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLink::MindAreaLink( MindAreaLinkInfo *p_info , MindArea *p_masterArea , MindArea *p_slaveArea ) {
	attachLogger();
	info = p_info;

	masterArea = p_masterArea;
	slaveArea = p_slaveArea;

	session = NULL;
	masterSubscription = NULL;
	slaveSubscription = NULL;
	links = new MindRegionLinkSet();
}

MindAreaLink::~MindAreaLink() {
	delete links;
}

void MindAreaLink::createRegionLinks() {
	MindService *ms = MindService::getService();

	// create region mapping
}

void MindAreaLink::createNetRegionLinks( MindNet *net , MindAreaNet *masterNet , MindAreaNet *slaveNet ) {
	ClassList<MindRegion>& masterRegions = masterNet -> getRegions();
	ClassList<MindRegion>& slaveRegions = slaveNet -> getRegions();

	// make linear topological mapping
	int n1 = masterRegions.count();
	int n2 = slaveRegions.count();
	if( n1 == 0 || n2 == 0 )
		return;

	// mapping factor
	int k2 = 0;
	for( int k1 = 0; k1 < n1; k1++ ) {
		MindRegion *masterRegion = masterRegions.get( k1 );

		// find terminal index for k1 mapping
		int n2k1 = 10 * n2 * k1 / n1;
		if( n2k1 % 5 > 5 )
			n2k1 = n2k1/10 + 1;
		else
			n2k1 = n2k1/10;
		if( n2k1 >= n2 )
			n2k1 = n2 - 1;

		for( ; k2 <= n2k1; k2++ ) {
			MindRegion *slaveRegion = slaveRegions.get( k1 );
			createNetRegionLink( net , masterRegion , slaveRegion );
		}
	}
}

void MindAreaLink::createNetRegionLink( MindNet *net , MindRegion *masterRegion , MindRegion *slaveRegion ) {
	logger.logDebug( "createNetRegionLink: create link net=" + net -> getName() + ", masterRegion=" + masterRegion -> getFullRegionId() + ", slaveRegion=" + slaveRegion -> getFullRegionId() + "..." );

	MindRegionLink *link = new MindRegionLink( this );
	link -> createRegionLink( net , masterRegion , slaveRegion );
	addRegionLink( link );
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
