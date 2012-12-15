#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

MindAreaLink::MindAreaLink() {
	attachLogger();

	masterArea = NULL;
	slaveArea = NULL;

	session = NULL;
	iopub = NULL;
	iosub = NULL;

	links = new MindRegionLinkSet();
}

MindAreaLink::~MindAreaLink() {
	delete links;
}

void MindAreaLink::create( MindArea *p_masterArea , MindArea *p_slaveArea ) {
	masterArea = p_masterArea;
	slaveArea = p_slaveArea;
	Object::setInstance( masterArea -> getId() + "-" + slaveArea -> getId() );
}

void MindAreaLink::open( MessageSession *p_session , String channel ) {
	session = p_session;

	MindService *ms = MindService::getService();
	activeMemory = ms -> getActiveMemory();

	MessagingService *msgs = MessagingService::getService();

	// open source publisher
	String pubid = String( "PUB-" ) + getInstance();
	iopub = msgs -> createPublisher( session , channel , pubid , "xml" );

	// open master channel
	String subid = String( "SUB-" ) + getInstance();
	iosub = msgs -> subscribe( p_session , channel , subid , this );
}

void MindAreaLink::sendMessage( MindMessage *msg ) {
	iopub -> publish( session , msg );
}

void MindAreaLink::onMessage( Message *msg ) {
	MindMessage *mm = ( MindMessage * )msg;

	// ignore foreign links
	NeuroSignal *signal = mm ->getMsgData();
	if( mm -> getAreaLink() != this ) {
		logger.logInfo( "ignore different area link message id=" + mm -> getChannelMessageId() + ", signal id=" + signal -> getId() );
		return;
	}

	logger.logInfo( "execute area link message id=" + mm -> getChannelMessageId() + ", signal id=" + signal -> getId() );
	activeMemory -> execute( mm );
}

void MindAreaLink::addRegionLink( MindRegionLink *link ) {
	links -> addSetItem( link );
}
