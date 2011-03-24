#ifndef	INCLUDE_AH_MESSAGING_H
#define INCLUDE_AH_MESSAGING_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_services.h"

class Message;
class TextMessage;
class BinaryMessage;
class MessagePublisher;
class MessageSubscriber;
class MessageSubscription;
class XmlMessage;
class XmlCall;
class MessageChannel;
class MessageSession;

/*#########################################################################*/
/*#########################################################################*/

class MessagingService : public Service {
public:
	// sessions
	MessageSession *createSession();
	void closeSession( MessageSession *session );

	// topics publishers and subscribers
	MessagePublisher *createPublisher( MessageSession *session , String channel , String pubName , String msgtype );
	MessageSubscription *subscribe( MessageSession *session , String channel , String subName , MessageSubscriber *sub );
	MessageSubscription *subscribeSelector( MessageSession *session , String channel , String selector , String subName , MessageSubscriber *sub );
	bool destroyPublisher( MessagePublisher *pub );
	bool unsubscribe( MessageSubscription *sub );

public:
	virtual const char *getServiceName() { return( "MessagingService" ); };
	virtual void configureService( Xml config );
	virtual void createService();
	virtual void initService();
	virtual void runService();
	virtual void stopService();
	virtual void exitService();
	virtual void destroyService();

// engine helpers
protected:
	MessagingService() {};
public:
	static Service *newService();
	static MessagingService *getService() { return( ( MessagingService * )ServiceManager::getInstance().getService( "MessagingService" ) ); };

// internals
private:
	MessageChannel *createChannel( Xml config );
	MessageChannel *getChannel( String name );
	void lock();
	void unlock();
	void openAllChannels();
	void startAllChannels();
	void closeAllChannels();

private:
	Xml config;
	rfc_lock *dataLock;
	int lastSessionId;
	MapStringToClass<MessageChannel> mapChannels; // channel name to class
	MapIntToClass<MessageSession> sessions;
};

/*#########################################################################*/
/*#########################################################################*/

class MessageSession {
public:
	int getSessionId();
	void setObject( Object *o , String name );
	Object *getObject( String name );

public:
	MessageSession( int id );
	~MessageSession();

// internals
private:
	int sessionId;
	rfc_lock *dataLock;
	MapStringToClass<Object> objects;
};

/*#########################################################################*/
/*#########################################################################*/

class MessagePublisher {
public:
	MessagePublisher( MessageSession *session , MessageChannel *p_channel , String p_name , String p_msgtype );
	~MessagePublisher();

public:
	String publish( MessageSession *session , const char *msg );
	String publish( MessageSession *session , Message *msg );
	MessageChannel *getChannel();
	const String& getMsgType();

// internals
public:
	void disconnected();

public:
	MessageSession *session;
	MessageChannel *channel;
	String name;
	String msgtype;
};

/*#########################################################################*/
/*#########################################################################*/

class MessageSubscriber {
public:
	virtual void onMessage( Message *msg ) {};
	virtual void onTextMessage( TextMessage *msg ) {};
	virtual void onXmlMessage( XmlMessage *msg ) {};
	virtual void onXmlCall( XmlCall *msg ) {};
	virtual void onBinaryMessage( Message *msg ) {};
};

/*#########################################################################*/
/*#########################################################################*/

class MessageSubscription {
public:
	MessageChannel *getChannel();
	void setSelector( String selector );
	void disconnected();

public:
	MessageSubscription( MessageSession *session , MessageChannel *p_channel , String p_name , MessageSubscriber *p_sub );
	~MessageSubscription() {};

// internals
public:
	void processMessage( Message *msg );

private:
	bool isMatchSelector( Message *msg );

public:
	MessageSession *session;
	MessageChannel *channel;
	String selector;
	String name;
	MessageSubscriber *sub;
};

/*#########################################################################*/
/*#########################################################################*/

// message
class Message {
public:
	typedef enum {
		MsgType_Unknown = 0 ,
		MsgType_Text = 1 ,
		MsgType_Xml = 2 ,
		MsgType_XmlCall = 3 ,
		MsgType_Binary = 4
	} MsgType;

public:
	Message( MsgType baseType , const char *classType );
	virtual ~Message();

	virtual void postExecute() {};

	MsgType getBaseType() { return( baseType ); };
	const String& getClassType() { return( classType ); };

	XmlCall& toXmlCall();

	bool isClassType( const char *p_classType ) const {
		return( classType.equals( p_classType ) );
	}

	void setSourceId( const char *p_id ) { source = p_id; };
	const String& getSourceId() { return( source ); };

	void setSourceMessageId( const char *p_id ) { extid = p_id; };
	const String& getSourceMessageId() { return( extid ); };

	void setChannelMessageId( const char *p_id ) { id = p_id; };
	const String& getChannelMessageId() { return( id ); };

	void setSession( MessageSession *p_session ) { session = p_session; };
	MessageSession *getSession() { return( session ); };

protected:
	const MsgType baseType;
	const String classType;

private:
	MessageSession *session;
	String id;
	String extid;
	String source;
};

/*#########################################################################*/
/*#########################################################################*/

// message
class TextMessage : public Message {
public:
	TextMessage() : Message( Message::MsgType_Text , NULL ) {};
	TextMessage( const char *classType ) : Message( Message::MsgType_Text , classType ) {};

protected:
	TextMessage( MsgType p_baseType , const char *p_classType ) : Message( p_baseType , p_classType ) {};

public:
	void setText( const char *p_txt ) { message = p_txt; };
	const String& getText() { return( message ); };

private:
	String message;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlMessage : public TextMessage {
public:
	XmlMessage( const char *txt );
	XmlMessage( Xml xml );
	virtual ~XmlMessage();

	virtual void postExecute() {};

protected:
	XmlMessage( MsgType p_baseType , const char *p_classType ) : TextMessage( p_baseType , p_classType ) {};

public:
	void setXml( Xml p_xml ) { xml = p_xml; };
	void setXmlFromString( const char *p_xml ) { TextMessage::setText( p_xml ); };
	Xml getXml();
	void setXmlFromMessage( const char *type );
	void setMessageFromXml();

private:
	Xml xml;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlCall : public XmlMessage {
public:
	XmlCall( MessageChannel *channelIn , MessageChannel *channelOut , const char *txt );
	virtual ~XmlCall();

	virtual void postExecute();

	void setXmlFromMessage();

	// request
	String getClassName();
	String getFunctionName();
	String getParam( String paramName );
	String getParam( String paramName , String defaultValue );
	int getIntParam( String paramName );
	int getIntParam( String paramName , int defaultValue );
	bool getBooleanParam( String paramName );
	float getFloatParam( String paramName );
	float getFloatParam( String paramName , float defaultValue );

	// response
	Xml getResponse();
	Xml createResponse();
	Xml createStatusResponse( String status );
	String sendResponse( MessagePublisher *pub );
	String sendResponseException( MessagePublisher *pub , RuntimeException& e );
	String sendResponseUnknownException( MessagePublisher *pub );
	String sendUnknownResponse();
	String sendStatusResponse( String status );

private:
	MessageChannel *channelIn;
	MessageChannel *channelOut;

	String requestId;
	String name;
	String className;
	String functionName;
	Xml params;
	Xml xmlResponse;
	bool responseSent;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AH_MESSAGING_H
