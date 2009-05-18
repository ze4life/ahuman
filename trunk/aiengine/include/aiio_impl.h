#ifndef	INCLUDE_AIIO_IMPL_H
#define INCLUDE_AIIO_IMPL_H

#include <aiengine.h>
#include <aiio.h>
#include <aiexpert.h>
#include <aimedia.h>

class AIIOQueue;

typedef void *AI_PORT;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIIOImpl : public AIIO , public Object , public Service
{
	// service
	virtual void initService();
	virtual void runService();
	virtual void exitService();
	virtual void destroyService();
	virtual const char *getName() { return( "IO" ); };

// external interface
public:
	AIIOImpl();

	virtual AISession *connect( String p_user , const String p_channeltype , void *p_media );
	virtual void lockChannels( bool p_lock );
	virtual void disconnect( int p_session );
	virtual AISession *getSessionById( int p_session );

	virtual AIMessage *createMessage( String message , String type );
	virtual void destroyMessage( AIMessage *message );

	// AIObject interface

private:	
	void closeSession( int id );

	bool canUserConnect( String user );
	void closeAllSessions();
	void enableConnections( bool p_enable );

	void on_message_to_media( AIMessage *msg , void *p_userdata );
	void on_message_to_expert( AIMessage *msg , void *p_userdata );

// internals
private:
	AIEngine& engine;

	rfc_ptrmap *mapIdToSession;
	rfc_lock *connectionDataLock;
	int lastSessionId;
	bool acceptConnections;
};

// #############################################################################
// #############################################################################

// session
class AISessionImpl : public AISession
{
public:
	virtual void sendMessageToExpert( AIMessage *message );

	virtual int getId() { return( id ); };
	virtual String getChannelType() { return( channeltype ); };
	virtual String getChannelTypeUser() { return( channeltypeuser ); };
	virtual void *getMedia() { return( media ); };

	virtual AIDuplexChannel *getChannel() { return( channel ); };

	virtual bool isSessionOpen() { return( sessionOpen ); };
	virtual bool isMediaOpen() { return( mediaOpen ); };

	virtual void close();
	virtual void setMediaOpen( bool p_open );

	// AIObject interface

public:
	AISessionImpl( int p_id , String p_channeltype , String p_user , void *p_media );
	~AISessionImpl();

	void setChannel( AIDuplexChannel *p_channel );
	void closeReflect();

private:
	AIEngine& engine;
	AIIO io;

	AIDuplexChannel *channel;

	int id;
	String channeltype;
	String channeltypeuser;
	void *media;

	bool sessionOpen;
	bool mediaOpen;
};

// #############################################################################
// #############################################################################

// message
class AIMessageImpl : public AIMessage
{
public:
	virtual const char *getMessage();
	virtual const char *getType();

	virtual const char *getId();
	virtual void setId( const char *id );

	// AIObject interface

public:
	AIMessageImpl( const String p_msg , const String p_type );

	String id;
	String message;
	String type;
};

// #############################################################################
// #############################################################################

// input/output messages
class AIDuplexChannelImpl : public AIDuplexChannel
{
public:
	virtual AISession *getSession();

	virtual void addLeftMessage( AIMessage *p_msg );
	virtual void addRightMessage( AIMessage *p_msg );

	virtual AIMessage *getNextLeftMessage();
	virtual AIMessage *getNextRightMessage();

	virtual AIMessage *getNextLeftMessageNoLock();
	virtual AIMessage *getNextRightMessageNoLock();

	virtual void subscribeLeftMessage( AIIO::subscribeFunction p_f , bool p_sync , void *p_userdata );
	virtual void subscribeRightMessage( AIIO::subscribeFunction p_f , bool p_sync , void *p_userdata );

	virtual void open();
	virtual void close();
	virtual bool isOpen() { return( opened ); };

	// AIObject interface

// #############################################################################
// #############################################################################

public:
	AIDuplexChannelImpl( AISession *p_session );
	~AIDuplexChannelImpl();

	// executing in separate thread
	void threadMainLeft();
	void threadMainRight();

	void closeReflect();

private:
	AIEngine& engine;
	AIIO io;
	AIMedia media;
	AIExpert expert;

	AISession *session;

	bool opened;

	RFC_THREAD threadIDLeft;
	RFC_THREAD threadIDRight;

	AIIOQueue *leftMessages;
	AIIOQueue *rightMessages;

	AIIO::subscribeFunction cbSubscribeLeft;
	AIIO::subscribeFunction cbSubscribeRight;

	bool syncLeft;
	bool syncRight;
	void *userdataLeft;
	void *userdataRight;
};

// #############################################################################
// #############################################################################

// sync queue
class AIIOQueue : public Object
{
public:
	AIIOQueue( const char *p_queueId );
	~AIIOQueue();

	void addMessage( AIMessage *p_str );
	AIMessage *getNextMessage();
	AIMessage *getNextMessageNoLock();
	void makeEmptyAndWakeup();
	bool isEmpty();
	const char *getId() { return( queueId ); };

	// AIObject interface

private:
	void clearMessages();

private:
	AIEngine& engine;
	AIIO io;

	String queueId;
	int queueMessageId;
	rfc_lock *queueLock;
	RFC_HND queueWakeupEvent;
	rfc_list *queueMessages;
};

#endif	// INCLUDE_AIIO_IMPL_H
