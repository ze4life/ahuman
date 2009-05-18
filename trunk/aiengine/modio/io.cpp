
#include <aiio_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AIIO::AIIO() 
{ 
	thisPtr = static_cast<AIIOImpl *>( AIEngine::getInstance().getService( "AIIO" ) ); 
}

/* static */ Service *AIIO::createService()
{
	Service *svc = new AIIOImpl();
	AIEngine::getInstance().registerService( svc , "AIIO" );
	return( svc );
}

AIIOImpl::AIIOImpl() 
:	engine( AIEngine::getInstance() )
{ 
	connectionDataLock = rfc_lock_create();
	mapIdToSession = rfc_map_ptrcreate();
	lastSessionId = 0;
	acceptConnections = false;
}

void AIIOImpl::initService()
{
}

void AIIOImpl::runService()
{
	enableConnections( true );
}

void AIIOImpl::exitService()
{
	closeAllSessions();
}

void AIIOImpl::destroyService()
{
	rfc_lock_destroy( connectionDataLock );
	rfc_map_ptrdrop( mapIdToSession );

	delete this;
}

void AIIOImpl::on_message_to_media( AIMessage *msg , void *p_userdata )
{
	AISession *session = ( AISession * )p_userdata;
	lockChannels( true );

	AIMedia media;
	media.sendMessageToUser( msg , session );
	lockChannels( false );
}

void AIIOImpl::on_message_to_expert( AIMessage *msg , void *p_userdata )
{
	AISession *session = ( AISession * )p_userdata;
	lockChannels( true );

	AIExpert expert;
	expert.processMediaMessage( msg , session );
	lockChannels( false );
}

/*#########################################################################*/
/*#########################################################################*/

AISession *AIIOImpl::connect( String p_channeltype , String p_user , void *p_media )
{
	if( !canUserConnect( p_user ) )
		return( NULL );

	// check already connected
	rfc_lock_exclusive( connectionDataLock );

	// create session
	lastSessionId++;
	AISessionImpl *session = new AISessionImpl( lastSessionId , p_channeltype , p_user , p_media );
	rfc_map_ptradd( mapIdToSession , ( void * )session -> getId() , ( unsigned long )session );

	// create message channel
	AIDuplexChannelImpl *channel = new AIDuplexChannelImpl( session );
	session -> setChannel( channel );

	// subscribe and run - left=initiator, right=io
	channel -> subscribeLeftMessage( static_cast<AIIO::subscribeFunction>( on_message_to_media ) , false , session );
	channel -> subscribeRightMessage( static_cast<AIIO::subscribeFunction>( on_message_to_expert ) , false , session );
	channel -> open();

	rfc_lock_release( connectionDataLock );
	return( session );
}

void AIIOImpl::disconnect( int p_session )
{
	AISessionImpl *session = ( AISessionImpl * )getSessionById( p_session );
	if( session == NULL )
		return;

	// close session
	if( session -> isSessionOpen() )
		session -> closeReflect();

	// close channel
	AIDuplexChannelImpl *channel = ( AIDuplexChannelImpl * )session -> getChannel();
	if( channel -> isOpen() )
		channel -> closeReflect();

	// close media
	if( session -> isMediaOpen() )
		{
			AIMedia media;
			media.closeMediaReflect( session );
			session -> setMediaOpen( false );
		}

	// remove from session map
	rfc_lock_exclusive( connectionDataLock );
	rfc_map_ptrremove( mapIdToSession , ( void * )session -> getId() );
	rfc_lock_release( connectionDataLock );

	// delete classes
	session -> setChannel( NULL );
	delete channel;
	delete session;
}

AISession *AIIOImpl::getSessionById( int p_session )
{
	rfc_lock_shared( connectionDataLock );
	AISession *session = NULL;
	rfc_map_ptrcheck( mapIdToSession , ( void * )p_session , ( unsigned long * )&session );
	rfc_lock_release( connectionDataLock );

	return( session );
}

void AIIOImpl::lockChannels( bool p_lock )
{
	if( p_lock )
		rfc_lock_shared( connectionDataLock );
	else
		rfc_lock_release( connectionDataLock );
}

void AIIOImpl::closeAllSessions()
{
	rfc_lock_exclusive( connectionDataLock );

	// disable connections
	enableConnections( false );

	// close all channels
	while( rfc_map_ptrcount( mapIdToSession ) > 0 )
		{
			AISession *session = ( AISession * )rfc_map_ptrget( mapIdToSession , 0 );

			// close given channel
			rfc_lock_release( connectionDataLock );
			disconnect( session -> getId() );
			rfc_lock_exclusive( connectionDataLock );
		}

	rfc_lock_release( connectionDataLock );
}

void AIIOImpl::enableConnections( bool p_enable )
{
	acceptConnections = p_enable;
}

bool AIIOImpl::canUserConnect( String user )
{
	if( !acceptConnections )
		return( false );

	return( true );
}

AIMessage *AIIOImpl::createMessage( String message , String type )
{
	return( new AIMessageImpl( message , type ) );
}

void AIIOImpl::destroyMessage( AIMessage *message )
{
	AIMessageImpl *msg = ( AIMessageImpl * )message;
}

