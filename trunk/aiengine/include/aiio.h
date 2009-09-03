#ifndef	INCLUDE_AIIO_H
#define INCLUDE_AIIO_H

class AIMessage;
class AIPublisher;
class AISubscriber;
class AISubscription;

/*#########################################################################*/
/*#########################################################################*/

class AIIO
{
public:
	// topics publishers and subscribers
	virtual AIPublisher *createPublisher( String channel , String pubName , String msgtype )
		{ return( thisPtr -> createPublisher( channel , pubName , msgtype ) ); };
	virtual AISubscription *subscribe( String channel , String subName , AISubscriber *sub )
		{ return( thisPtr -> subscribe( channel , subName , sub ) ); };
	virtual bool destroyPublisher( AIPublisher *pub )
		{ return( thisPtr -> destroyPublisher( pub ) ); };
	virtual bool unsubscribe( AISubscription *sub )
		{ return( thisPtr -> unsubscribe( sub ) ); };

// engine helpers
public:
	static Service *createService();
	AIIO *thisPtr;
	AIIO();
};

/*#########################################################################*/
/*#########################################################################*/

class AIPublisher
{
public:
	virtual ~AIPublisher() {};
	virtual String publish( String msg ) = 0;
	virtual String publish( Xml msg ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class AISubscriber
{
public:
	virtual void onMessage( AIMessage *msg ) = 0;
};

/*#########################################################################*/
/*#########################################################################*/

class AISubscription
{
public:
	virtual ~AISubscription() {};
};

/*#########################################################################*/
/*#########################################################################*/

// message
class AIMessage
{
public:
	AIMessage();
	~AIMessage();

	Xml getXml( const char *type );
	void setFromXml();

public:
	String id;
	String extid;
	String type;
	String source;
	String message;

private:
	Xml xml;
};

/*#########################################################################*/
/*#########################################################################*/

class XmlCall
{
public:
	XmlCall();
	~XmlCall();

	void attach( AIMessage *msg );

	// request
	String getName();
	String getParam( String paramName );
	int getIntParam( String paramName );
	bool getBooleanParam( String paramName );
	float getFloatParam( String paramName );

	// response 
	Xml createResponse();
	String sendResponse( AIPublisher *pub );
	String sendResponseException( AIPublisher *pub , RuntimeException& e );
	String sendResponseUnknownException( AIPublisher *pub );

private:
	AIMessage *msg;

	String id;
	String name;
	Xml params;
	Xml xmlResponse;
};

/*#########################################################################*/
/*#########################################################################*/

#endif	// INCLUDE_AIIO_H
