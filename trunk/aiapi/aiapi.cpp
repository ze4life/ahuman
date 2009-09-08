
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
