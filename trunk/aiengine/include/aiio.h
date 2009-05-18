#ifndef	INCLUDE_AIIO_H
#define INCLUDE_AIIO_H

class AIMessage;
class AISession;
class AIDuplexChannel;

/*#########################################################################*/
/*#########################################################################*/

class AIIO
{
public:
	typedef void ( AIIO::*subscribeFunction )( AIMessage *p_msg , void *userdata );

	virtual AISession *connect( String p_user , const String p_channeltype , void *p_initiator )
		{ return( thisPtr -> connect( p_user , p_channeltype , p_initiator ) ); };

	virtual void lockChannels( bool p_lock )
		{ thisPtr -> lockChannels( p_lock ); };

	virtual void disconnect( int p_session )
		{ thisPtr -> disconnect( p_session ); };

	virtual AISession *getSessionById( int p_session )
		{ return( thisPtr -> getSessionById( p_session ) ); };

	virtual AIMessage *createMessage( String message , String type )
		{ return( thisPtr -> createMessage( message , type ) ); };

	virtual void destroyMessage( AIMessage *message )
		{ thisPtr -> destroyMessage( message ); };

	virtual void subscribeEvent( subscribeFunction pf , AIMessage *message , void *userdata )
		{ thisPtr -> subscribeEvent( pf , message , userdata ); };

// engine helpers
public:
	static Service *createService();
	AIIO *thisPtr;
	AIIO();
};

/*#########################################################################*/
/*#########################################################################*/

// session
class AISession : public Object
{
public:
	virtual void sendMessageToExpert( AIMessage *message ) = 0;

	virtual int getId() = 0;
	virtual String getChannelType() = 0;
	virtual String getChannelTypeUser() = 0;
	virtual void *getMedia() = 0;
	virtual AIDuplexChannel *getChannel() = 0;

	virtual bool isSessionOpen() = 0;
	virtual bool isMediaOpen() = 0;

	virtual void close() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

// message
class AIMessage : public Object
{
public:
	virtual const char *getMessage() = 0;
	virtual const char *getType() = 0;

	virtual const char *getId() = 0;
	virtual void setId( const char *id ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

// input/output messages
class AIDuplexChannel : public Object
{
// interface
public:
	virtual AISession *getSession() = 0;

	virtual void open() = 0;
	virtual void close() = 0;
	virtual bool isOpen() = 0;

	virtual void addLeftMessage( AIMessage *p_msg ) = 0;
	virtual void addRightMessage( AIMessage *p_msg ) = 0;

	virtual AIMessage *getNextLeftMessage() = 0;
	virtual AIMessage *getNextRightMessage() = 0;

	virtual AIMessage *getNextLeftMessageNoLock() = 0;
	virtual AIMessage *getNextRightMessageNoLock() = 0;

	virtual void subscribeLeftMessage( AIIO::subscribeFunction p_f , bool p_sync , void *p_userdata ) = 0;
	virtual void subscribeRightMessage( AIIO::subscribeFunction p_f , bool p_sync , void *p_userdata ) = 0;
};

#endif	// INCLUDE_AIIO_H
