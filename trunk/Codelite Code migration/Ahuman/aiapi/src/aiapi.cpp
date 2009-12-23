
#include "aiapi_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIApi::AIApi()
{
	api = new AIApiImpl;
}

AIApi::~AIApi()
{
	if( lastRequest.exists() )
		api -> destroyXml( lastRequest );
	if( lastResponse.exists() )
		api -> destroyXml( lastResponse );
	delete api;
}

void AIApi::connect( String url )
{
	api -> connect( url );
}

Xml AIApi::execute()
{
	if( lastResponse.exists() )
		api -> destroyXml( lastResponse );
	lastResponse = api -> execute( lastRequest );
	return( lastResponse );
}

void AIApi::disconnect()
{
	api -> disconnect();
}

bool AIApi::isConnected()
{
	return( api -> isConnected() );
}

Xml AIApi::createXmlRequest()
{
	if( lastRequest.exists() )
		api -> destroyXml( lastRequest );

	lastRequest = api -> createXmlRequest( "xmlcall" );
	return( lastRequest );
}

Xml AIApi::loadXmlRequest( String fileName )
{
	if( lastRequest.exists() )
		api -> destroyXml( lastRequest );
	
	lastRequest = api -> loadXmlRequest( fileName , "xmlcall" );
	return( lastRequest );
}

Xml AIApi::readXmlRequest( const char *data )
{
	if( lastRequest.exists() )
		api -> destroyXml( lastRequest );
	
	lastRequest = api -> readXmlRequest( data , "xmlcall" );
	return( lastRequest );
}

void AIApi::setFunctionName( String name )
{
	ASSERT( lastRequest.exists() );
	lastRequest.setAttribute( "name" , name );
}

void AIApi::setParam( String name , String value )
{
	ASSERT( lastRequest.exists() );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );
	p.setProperty( name , value );			
}

void AIApi::setBooleanParam( String name , bool value )
{
	ASSERT( lastRequest.exists() );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );
	p.setBooleanProperty( name , value );			
}

void AIApi::setIntParam( String name , int value )
{
	ASSERT( lastRequest.exists() );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );
	p.setIntProperty( name , value );			
}

void AIApi::setFloatParam( String name , float value )
{
	ASSERT( lastRequest.exists() );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );
	p.setFloatProperty( name , value );			
}

void AIApi::initThread()
{
	AIApiSocket::initSocketLib();
}

void AIApi::exitThread()
{
	AIApiSocket::exitSocketLib();
}

/*#########################################################################*/
/*#########################################################################*/
