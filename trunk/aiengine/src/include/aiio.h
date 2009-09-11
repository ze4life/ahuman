#ifndef	INCLUDE_AIIO_H
#define INCLUDE_AIIO_H

class Message;
class Publisher;
class Subscriber;
class Subscription;
class XmlMessage;
class XmlCall;
class Channel;

/*#########################################################################*/
/*#########################################################################*/

class AIIO
{
public:
	// topics publishers and subscribers
	virtual Publisher *createPublisher( String channel , String pubName , String msgtype )
		{ return( thisPtr -> createPublisher( channel , pubName , msgtype ) ); };
	virtual Subscription *subscribe( String channel , String subName , Subscriber *sub )
		{ return( thisPtr -> subscribe( channel , subName , sub ) ); };
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

class Publisher
{
public:
	virtual ~Publisher() {};
	virtual String publish( const char *msg ) = 0;
	virtual String publish( Message *msg ) = 0;
	virtual String publish( XmlMessage *msg ) = 0;
	virtual String publish( XmlCall *msg ) = 0;
	virtual Channel *getChannel() = 0;
	virtual const String& getMsgType() = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class Subscriber
{
public:
	virtual void onMessage( Message *msg ) = 0;
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

private:
	MsgType msgBaseType;
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
	String sendResponse( Publisher *pub );
	String sendResponseException( Publisher *pub , RuntimeException& e );
	String sendResponseUnknownException( Publisher *pub );
	String sendUnknownResponse();

private:
	Channel *channelIn;
	Channel *channelOut;

	String requestId;
	String functionName;
	Xml params;
	Xml xmlResponse;
	bool responseSent;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIIO_H
