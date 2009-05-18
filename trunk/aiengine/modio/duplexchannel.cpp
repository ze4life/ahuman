
#include <aiio_impl.h>

/*#########################################################################*/
/*#########################################################################*/

static 	unsigned		__stdcall threadMainFunctionLeft( void *p_arg )
{
	AIDuplexChannelImpl *ptr = ( AIDuplexChannelImpl * )p_arg;
	Logger& logger = ptr -> getLogger();
	AIEngine& engine = AIEngine::getInstance();
	engine.workerStarted();
	
	int status = 0;
	try {
		ptr -> threadMainLeft();
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
		status = -12;
	}
	catch ( ... ) {
		logger.logError( "threadMainFunctionLeft: unknown exception" );
		logger.printStack();
		status = -13;
	}

	engine.workerExited( status );
	return( status );
}

static 	unsigned		__stdcall threadMainFunctionRight( void *p_arg )
{
	AIDuplexChannelImpl *ptr = ( AIDuplexChannelImpl * )p_arg;
	Logger& logger = ptr -> getLogger();
	AIEngine& engine = AIEngine::getInstance();
	engine.workerStarted();
	
	int status = 0;
	try {
		ptr -> threadMainRight();
	}
	catch ( RuntimeException& e ) {
		e.printStack( logger );
		status = -12;
	}
	catch ( ... ) {
		logger.logError( "threadMainFunctionRight: unknown exception" );
		logger.printStack();
		status = -13;
	}

	engine.workerExited( status );
	return( status );
}

/*#########################################################################*/
/*#########################################################################*/

// input/output messages
// class AIIODuplexChannel
AIDuplexChannelImpl::AIDuplexChannelImpl( AISession *p_session )
:	engine( AIEngine::getInstance() )
{
	session = p_session;

	opened = false;

	memset( &threadIDLeft , 0 , sizeof( RFC_THREAD ) );
	memset( &threadIDRight , 0 , sizeof( RFC_THREAD ) );
	
	cbSubscribeLeft = NULL;
	cbSubscribeRight = NULL;

	leftMessages = new AIIOQueue( "CL" );
	rightMessages = new AIIOQueue( "AI" );

	syncLeft = false;
	syncRight = false;
	userdataLeft = NULL;
	userdataRight = NULL;

	logger.attach( this );
}

AIDuplexChannelImpl::~AIDuplexChannelImpl()
{
	delete leftMessages;
	delete rightMessages;
}

void AIDuplexChannelImpl::open()
{
	// create channel threads
	if( !syncLeft )
		{
			engine.workerCreated();
			if( rfc_thr_process( &threadIDLeft , ( void * )this , threadMainFunctionLeft ) )
				{
					logger.logError( "AIDuplexChannelImpl::open - cannot start listening thread" );
					engine.workerExited( threadIDLeft , -10 );
					return;
				}
		}

	if( !syncRight )
		{
			engine.workerCreated();
			if( rfc_thr_process( &threadIDRight , ( void * )this , threadMainFunctionRight ) )
				{
					logger.logError( "AIDuplexChannelImpl::open - cannot start listening thread" );
					engine.workerExited( threadIDRight , -11 );
					return;
				}
		}

	opened = true;
}

void AIDuplexChannelImpl::close()
{
	session -> close();
}

void AIDuplexChannelImpl::addLeftMessage( AIMessage *p_msg )
{
	if( !isOpen() )
		{
			logger.logError( "addLeftMessage: cannot add message - closed" );
			return;
		}

	if( syncLeft )
		io.subscribeEvent( cbSubscribeLeft , p_msg , userdataLeft );
	else
		leftMessages -> addMessage( p_msg );
}

void AIDuplexChannelImpl::addRightMessage( AIMessage *p_msg )
{ 
	if( !isOpen() )
		{
			logger.logError( "addRightMessage: cannot add message - closed" );
			return;
		}

	if( syncRight )
		io.subscribeEvent( cbSubscribeRight , p_msg , userdataRight );
	else
		rightMessages -> addMessage( p_msg ); 
}

AIMessage *AIDuplexChannelImpl::getNextLeftMessage() 
{ 
	if( !isOpen() )
		return( NULL );

	return( leftMessages -> getNextMessage() ); 
}

AIMessage *AIDuplexChannelImpl::getNextRightMessage() 
{ 
	if( !isOpen() )
		return( NULL );

	return( rightMessages -> getNextMessage() ); 
}

AIMessage *AIDuplexChannelImpl::getNextLeftMessageNoLock() 
{ 
	return( leftMessages -> getNextMessageNoLock() ); 
}

AIMessage *AIDuplexChannelImpl::getNextRightMessageNoLock() 
{ 
	return( rightMessages -> getNextMessageNoLock() ); 
}

void AIDuplexChannelImpl::subscribeLeftMessage( AIIO::subscribeFunction p_f , bool p_sync , void *p_userdata )
{
	cbSubscribeLeft = p_f;
	userdataLeft = p_userdata;
	syncLeft = p_sync;
}

void AIDuplexChannelImpl::subscribeRightMessage( AIIO::subscribeFunction p_f , bool p_sync , void *p_userdata )
{
	cbSubscribeRight = p_f;
	userdataRight = p_userdata;
	syncRight = p_sync;
}

// executing in separate thread
void AIDuplexChannelImpl::threadMainLeft()
{
	logger.logInfo( String( "DUPLEXCHANNEL: opened left queue=" ) + leftMessages -> getId() );
	while( isOpen() || !leftMessages -> isEmpty() ) 
		{
			// get next message
			AIMessage *message = leftMessages -> getNextMessage();
			if( message == NULL )
				break;

			// log
			logger.logInfo( String( "QUEUE: extracted message=" ) + message -> getId() );

			// pass message
			io.subscribeEvent( cbSubscribeLeft , message , userdataLeft );
			io.destroyMessage( message );
		}

	logger.logInfo( String( "DUPLEXCHANNEL: closed queue=" ) + leftMessages -> getId() );
}

void AIDuplexChannelImpl::threadMainRight()
{
	logger.logInfo( String( "DUPLEXCHANNEL: opened right queue=" ) + rightMessages -> getId() );

	while( isOpen() || !rightMessages -> isEmpty() )
		{
			// get next message
			AIMessage *message = rightMessages -> getNextMessage();
			if( message == NULL )
				break;

			// log
			logger.logInfo( String( "QUEUE: extracted message=" ) + message -> getId() );

			// pass message
			io.subscribeEvent( cbSubscribeRight , message , userdataRight );
			io.destroyMessage( message );
		}

	logger.logInfo( String( "DUPLEXCHANNEL: closed queue=" ) + rightMessages -> getId() );
}

AISession *AIDuplexChannelImpl::getSession()
{
	return( session );
}

void AIDuplexChannelImpl::closeReflect()
{
	if( !isOpen() )
		return;

	// cancel channel thread
	opened = false;

	leftMessages -> makeEmptyAndWakeup();
	rightMessages -> makeEmptyAndWakeup();

	// wait for thread to cancel
	if( cbSubscribeLeft != NULL )
		rfc_thr_waitexit( &threadIDLeft );

	if( cbSubscribeRight != NULL )
		rfc_thr_waitexit( &threadIDRight );
}

