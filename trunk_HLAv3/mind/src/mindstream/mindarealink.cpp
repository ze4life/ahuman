#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLink::MindAreaLink() {
	attachLogger();

	masterArea = NULL;
	slaveArea = NULL;

	session = NULL;
	listenSubscription = NULL;
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

void MindAreaLink::open( MessageSession *p_session , String channel ) {
	session = p_session;

	MindService *ms = MindService::getService();
	activeMemory = ms -> getActiveMemory();

	MessagingService *msgs = MessagingService::getService();

	// open master channel
	String subid = masterArea -> getId() + "-" + slaveArea -> getId();
	listenSubscription = msgs -> subscribe( p_session , channel , subid , this );
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
