#ifndef	INCLUDE_AH_MESSAGING_H
#define INCLUDE_AH_MESSAGING_H

/*#########################################################################*/
/*#########################################################################*/

#include "ah_services.h"

class Message;
class TextMessage;
class BinaryMessage;
class Publisher;
class Subscriber;
class Subscription;
class XmlMessage;
class XmlCall;
class Channel;
class Session;

/*#########################################################################*/
/*#########################################################################*/

class MessagingService : public Service {
public:
	// sessions
	Session *createSession();
	void closeSession( Session *session );

	// topics publishers and subscribers
	Publisher *createPublisher( Session *session , String channel , String pubName , String msgtype );
	Subscription *subscribe( Session *session , String channel , String subName , Subscriber *sub );
	Subscription *subscribeSelector( Session *session , String channel , String selector , String subName , Subscriber *sub );
	bool destroyPublisher( Publisher *pub );
	bool unsubscribe( Subscription *sub );

public:
	virtual const char *getServiceName() { return( "MessagingService" ); };
	virtual void configureService( Xml config ) {};
	virtual void createService() {};
	virtual void initService() {};
	virtual void runService() {};
	virtual void stopService() {};
	virtual void exitService() {};
	virtual void destroyService() {};

// engine helpers
protected:
	MessagingService() {};
public:
	static Service *newService();
	MessagingService *getService() { return( ( MessagingService * )ServiceManager::getInstance().getService( "MessagingService" ) ); };
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
	virtual void onTextMessage( TextMessage *msg ) {};
	virtual void onXmlMessage( XmlMessage *msg ) {};
	virtual void onXmlCall( XmlCall *msg ) {};
	virtual void onBinaryMessage( Message *msg ) {};
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

	void setSession( Session *p_session ) { session = p_session; };
	Session *getSession() { return( session ); };

protected:
	const MsgType baseType;
	const String classType;

private:
	Session *session;
	String id;
	String extid;
	String source;
};

/*#########################################################################*/
/*#########################################################################*/

// message
class TextMessage : public Message
{
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

class XmlMessage : public TextMessage
{
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
