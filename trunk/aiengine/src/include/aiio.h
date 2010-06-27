#ifndef	INCLUDE_AIIO_H
#define INCLUDE_AIIO_H

class Message;
class Publisher;
class Subscriber;
class Subscription;
class XmlMessage;
class XmlCall;
class Channel;
class Session;

/*#########################################################################*/
/*#########################################################################*/

class AIIO
{
public:
	// sessions
	virtual Session *createSession()
		{ return( thisPtr -> createSession() ); };
	virtual void closeSession( Session *session )
		{ thisPtr -> closeSession( session ); };

	// topics publishers and subscribers
	virtual Publisher *createPublisher( Session *session , String channel , String pubName , String msgtype )
		{ return( thisPtr -> createPublisher( session , channel , pubName , msgtype ) ); };
	virtual Subscription *subscribe( Session *session , String channel , String subName , Subscriber *sub )
		{ return( thisPtr -> subscribe( session , channel , subName , sub ) ); };
	virtual bool destroyPublisher( Publisher *pub )
		{ return( thisPtr -> destroyPublisher( pub ) ); };
	virtual bool unsubscribe( Subscription *sub )
		{ return( thisPtr -> unsubscribe( sub ) ); };

// engine helpers
public:
	static Service *createService();
	AIIO *thisPtr;
	AIIO();
};

/*#########################################################################*/
/*#########################################################################*/

class Session
{
public:
	Session() {};
	virtual ~Session() {};

public:
	virtual int getSessionId() = 0;
	virtual void setObject( Object *o , String name ) = 0;
	virtual Object *getObject( String name ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class Publisher
{
public:
	virtual ~Publisher() {};
	virtual String publish( Session *session , const char *msg ) = 0;
	virtual String publish( Session *session , Message *msg ) = 0;
	virtual Channel *getChannel() = 0;
	virtual const String& getMsgType() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class Subscriber
{
public:
	virtual void onMessage( Message *msg ) {};
	virtual void onXmlMessage( XmlMessage *msg ) {};
	virtual void onXmlCall( XmlCall *msg ) {};
};

/*#########################################################################*/
/*#########################################################################*/

class Subscription
{
public:
	virtual Channel *getChannel() = 0;

	virtual ~Subscription() {};
};

/*#########################################################################*/
/*#########################################################################*/

// message
class Message
{
public:
	typedef enum {
		MsgType_Unknown = 0 ,
		MsgType_Text = 1 ,
		MsgType_Xml = 2 ,
		MsgType_XmlCall = 3
	} MsgType;

public:
	Message();
	virtual ~Message();
	virtual void postExecute() {};

	XmlCall& toXmlCall();

	MsgType getMsgBaseType() { return( msgBaseType ); };

	void setType( const char *p_type ) { type = p_type; };
	const String& getType() { return( type ); };

	void setSourceId( const char *p_id ) { source = p_id; };
	const String& getSourceId() { return( source ); };

	void setSourceMessageId( const char *p_id ) { extid = p_id; };
	const String& getSourceMessageId() { return( extid ); };

	void setChannelMessageId( const char *p_id ) { id = p_id; };
	const String& getChannelMessageId() { return( id ); };

	void setText( const char *p_txt ) { message = p_txt; };
	const String& getText() { return( message ); };

	void setSession( Session *p_session ) { session = p_session; };
	Session *getSession() { return( session ); };

protected:
	MsgType msgBaseType;
private:
	Session *session;
	String id;
	String extid;
	String type;
	String source;
	String message;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlMessage : public Message
{
public:
	XmlMessage( const char *txt );
	XmlMessage( Xml xml );
	virtual ~XmlMessage();
	virtual void postExecute() {};

public:
	Xml getXml();
	void setXmlFromMessage( const char *type );
	void setMessageFromXml();

private:
	Xml xml;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlCall : public XmlMessage
{
public:
	XmlCall( Channel *channelIn , Channel *channelOut , const char *txt );
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
	String sendResponse( Publisher *pub );
	String sendResponseException( Publisher *pub , RuntimeException& e );
	String sendResponseUnknownException( Publisher *pub );
	String sendUnknownResponse();
	String sendStatusResponse( String status );

private:
	Channel *channelIn;
	Channel *channelOut;

	String requestId;
	String className;
	String functionName;
	Xml params;
	Xml xmlResponse;
	bool responseSent;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIIO_H
