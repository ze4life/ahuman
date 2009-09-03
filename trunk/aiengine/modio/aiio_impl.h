#ifndef	INCLUDE_AIIO_IMPL_H
#define INCLUDE_AIIO_IMPL_H

#include <aiengine.h>
#include <aiio.h>
#include <aiexpert.h>
#include <aimedia.h>

class AIIOQueue;
class AIChannel;
class AIPublisherImpl;
class AISubscriptionImpl;

/*#########################################################################*/
/*#########################################################################*/

// derives knowledge from io, activates mind
class AIIOImpl : public AIIO , public Service
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

	// topics publishers and subscribers
	virtual AIPublisher *createPublisher( String channel , String pubName , String msgtype );
	virtual AISubscription *subscribe( String channel , String subName , AISubscriber *sub );
	virtual bool destroyPublisher( AIPublisher *publisher );
	virtual bool unsubscribe( AISubscription *subscription );

private:
	void createChannel( Xml config );
	AIChannel *getChannel( String name );
	void lock();
	void unlock();
	void closeAllChannels();

// internals
private:
	AIEngine& engine;

	rfc_lock *dataLock;
	MapStringToClass<AIChannel> mapChannels; // channel name to class
};

// #############################################################################
// #############################################################################

// input/output messages
class AIChannel : public Object
{
public:
	AIChannel( String msgid , String name , bool sync );
	~AIChannel();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };

public:
	String getName();
	void open();
	void close();
	String publish( AIPublisherImpl *pub , const char *msg );
	String publish( AIPublisherImpl *pub , Xml xml , const char *type );

	// subscribers and publishers
	void addSubscription( String key , AISubscriptionImpl *sub );
	void deleteSubscription( String key );
	void addPublisher( String key , AIPublisherImpl *pub );
	void deletePublisher( String key );

	// read messages and call subscribers
	void processMessages();

private:
	String getNewMessageId();
	void subscribeEvent( AIMessage *p_msg );
	void lock();
	void unlock();
	void disconnectSubscriptions();
	void disconnectPublishers();

// #############################################################################
// #############################################################################

private:
	String name;
	bool opened;
	bool sync;
	bool run;
	int queueMessageId;

	rfc_lock *channelLock;
	RFC_THREAD threadID;
	AIIOQueue *messages;
	MapStringToClass<AISubscriptionImpl> subs;
	MapStringToClass<AIPublisherImpl> pubs;
};

/*#########################################################################*/
/*#########################################################################*/

class AIPublisherImpl : public AIPublisher
{
public:
	AIPublisherImpl( AIChannel *p_channel , String p_name , String p_msgtype );
	virtual ~AIPublisherImpl();

	virtual String publish( String msg );
	virtual String publish( Xml msg );

	void disconnected();

	AIChannel *channel;
	String name;
	String msgtype;
};

/*#########################################################################*/
/*#########################################################################*/

class AISubscriptionImpl : public AISubscription
{
public:
	AISubscriptionImpl( AIChannel *p_channel , String p_name , AISubscriber *p_sub );

	void disconnected();

public:
	AIChannel *channel;
	String name;
	AISubscriber *sub;
};

// #############################################################################
// #############################################################################

// sync queue
class AIIOQueue : public Object
{
public:
	AIIOQueue( String p_queueId );
	~AIIOQueue();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };

public:
	void addMessage( AIMessage *p_str );
	AIMessage *getNextMessage();
	AIMessage *getNextMessageNoLock();
	void makeEmptyAndWakeup();
	bool isEmpty();
	const char *getId() { return( queueId ); };

private:
	void clearMessages();

private:
	AIEngine& engine;
	AIIO io;

	String queueId;
	rfc_lock *queueLock;
	RFC_HND queueWakeupEvent;
	rfc_list *queueMessages;
};

#endif	// INCLUDE_AIIO_IMPL_H
