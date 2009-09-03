#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

XmlCall::XmlCall()
{
	msg = NULL;
}

XmlCall::~XmlCall()
{
	if( xmlResponse.exists() )
		AIEngine::getInstance().destroyXmlDoc( xmlResponse );
}

void XmlCall::attach( AIMessage *p_msg )
{
	msg = p_msg;
	Xml xml = msg -> getXml( "request" );
	
	id = xml.getAttribute( "requestId" );
	name = xml.getAttribute( "name" );
	params = xml.getChildNode( "parameters" );
}

// request
String XmlCall::getName()
{
	return( name );
}

String XmlCall::getParam( String paramName )
{
	return( params.getProperty( paramName ) );
}

int XmlCall::getIntParam( String paramName )
{
	return( params.getIntProperty( paramName ) );
}

bool XmlCall::getBooleanParam( String paramName )
{
	return( params.getBooleanProperty( paramName ) );
}

float XmlCall::getFloatParam( String paramName )
{
	return( params.getFloatProperty( paramName ) );
}

// response 
Xml XmlCall::createResponse()
{
	ASSERT( !xmlResponse.exists() );
	
	xmlResponse = AIEngine::getInstance().createXml( "response" );
	xmlResponse.setAttribute( "requestId" , id );
	xmlResponse.setAttribute( "name" , name );

	return( xmlResponse );
}

String XmlCall::sendResponse( AIPublisher *pub )
{
	ASSERT( xmlResponse.exists() );
	return( pub -> publish( xmlResponse ) );
}

String XmlCall::sendResponseException( AIPublisher *pub , RuntimeException& e )
{
	String error = e.printStack();
	Xml res = createResponse();
	res.setAttribute( "status" , "Exception" );
	res.addTextElement( "exception" , error );
	String msg = sendResponse( pub );

	return( msg );
}

String XmlCall::sendResponseUnknownException( AIPublisher *pub )
{
	Xml res = createResponse();
	res.setAttribute( "status" , "Exception" );
	res.addTextElement( "exception" , "Unknown Error" );
	String msg = sendResponse( pub );

	return( msg );
}
