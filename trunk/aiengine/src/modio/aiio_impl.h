#ifndef	INCLUDE_AIIO_IMPL_H
#define INCLUDE_AIIO_IMPL_H

#include <aiengine.h>
#include <aiio.h>
#include <aiexpert.h>
#include <aimedia.h>

class IOQueue;
class Channel;
class PublisherImpl;
class SubscriptionImpl;

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
	virtual Publisher *createPublisher( String channel , String pubName , String msgtype );
	virtual Subscription *subscribe( String channel , String subName , Subscriber *sub );
	virtual bool destroyPublisher( Publisher *publisher );
	virtual bool unsubscribe( Subscription *subscription );

private:
	void createChannel( Xml config );
	Channel *getChannel( String name );
	void lock();
	void unlock();
	void closeAllChannels();

// internals
private:
	AIEngine& engine;

	rfc_lock *dataLock;
	MapStringToClass<Channel> mapChannels; // channel name to class
};

// #############################################################################
// #############################################################################

// input/output messages
class Channel : public Object
{
public:
	Channel( String msgid , String name , bool sync );
	~Channel();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };

public:
	String getName();
	void open();
	void close();
	String publish( PublisherImpl *pub , const char *msg );
	String publish( PublisherImpl *pub , Message *msg );

	// subscribers and publishers
	void addSubscription( String key , SubscriptionImpl *sub );
	void deleteSubscription( String key );
	void addPublisher( String key , PublisherImpl *pub );
	void deletePublisher( String key );
	Publisher *getDefaultPublisher();

	// read messages and call subscribers
	void processMessages();

private:
	String getNewMessageId();
	void subscribeEvent( Message *p_msg );
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
	IOQueue *messages;
	MapStringToClass<SubscriptionImpl> subs;
	MapStringToClass<PublisherImpl> pubs;
	Publisher *defaultPublisher;
};

/*#########################################################################*/
/*#########################################################################*/

class PublisherImpl : public Publisher
{
public:
	PublisherImpl( Channel *p_channel , String p_name , String p_msgtype );
	virtual ~PublisherImpl();

	virtual String publish( const char *msg );
	virtual String publish( Message *msg );
	virtual String publish( XmlMessage *msg );
	virtual String publish( XmlCall *msg );
	virtual Channel *getChannel();
	virtual const String& getMsgType();

	void disconnected();

	Channel *channel;
	String name;
	String msgtype;
};

/*#########################################################################*/
/*#########################################################################*/

class SubscriptionImpl : public Subscription
{
public:
	SubscriptionImpl( Channel *p_channel , String p_name , Subscriber *p_sub );
	virtual Channel *getChannel();

	void disconnected();

public:
	Channel *channel;
	String name;
	Subscriber *sub;
};

// #############################################################################
// #############################################################################

// sync queue
class IOQueue : public Object
{
public:
	IOQueue( String p_queueId );
	~IOQueue();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };

public:
	void addMessage( Message *p_str );
	Message *getNextMessage();
	Message *getNextMessageNoLock();
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
