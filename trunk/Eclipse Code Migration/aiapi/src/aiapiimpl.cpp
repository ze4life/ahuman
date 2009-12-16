
#include "aiapi_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIApiImpl::AIApiImpl()
{
	lastRequestNumber = 0;
	requestWaitTime = 30000;
	connected = false;
}

AIApiImpl::~AIApiImpl()
{
	if( connected )
		disconnect();
}

void AIApiImpl::setXmlRequestId( Xml req )
{
	String requestId = String( "REQ-" ) + ++lastRequestNumber;
	req.setAttribute( "requestId" , requestId );
}

Xml AIApiImpl::createXmlRequest( const char *contentName )
{
	TiXmlDocument *doc = new TiXmlDocument();
	TiXmlElement *top = new TiXmlElement( contentName );
	doc -> LinkEndChild( top );
	
	Xml xml;
	xml.attach( doc , top );

	setXmlRequestId( xml );

	return( xml );
}

void AIApiImpl::destroyXml( Xml xml )
{
	if( xml.exists() )
		{
			TiXmlDocument *doc = ( TiXmlDocument * )xml.doc;
			delete doc;

			xml.doc = NULL;
			xml.node = NULL;
		}
}

Xml AIApiImpl::loadXmlRequest( String fileName , const char *contentName )
{
	TiXmlDocument *doc = new TiXmlDocument;
	if( !doc -> LoadFile( fileName ) )
		{
			delete doc;
			ASSERTMSG( false , "AIApi::loadXmlRequest: cannot load xml file" );
		}

	TiXmlElement *top;
	try {
		top = doc -> FirstChildElement( contentName );
	}
	catch( ... ) {
		delete doc;
		ASSERTMSG( false , "AIApiImpl::loadXml: invalid content type in xml data" );
	}

	Xml xml;
	xml.attach( doc , top );

	setXmlRequestId( xml );

	return( xml );
}

Xml AIApiImpl::readXmlRequest( const char *data , const char *contentName )
{
	Xml xml = readXml( data , contentName );
	setXmlRequestId( xml );
	return( xml );
}

Xml AIApiImpl::readXml( const char *data , const char *contentName )
{
	TiXmlDocument *doc = new TiXmlDocument;
	doc -> Parse( data );
	if( doc -> Error() )
		{
			delete doc;
			ASSERTMSG( false , "AIApiImpl::readXml: cannot read xml data" );
		}

	TiXmlElement *top;
	try {
		top = doc -> FirstChildElement( contentName );
	}
	catch( ... ) {
		delete doc;
		ASSERTMSG( false , "AIApiImpl::readXml: invalid content type in xml data" );
	}

	Xml xml;
	xml.attach( doc , top );
	return( xml );
}

Xml AIApiImpl::execute( Xml req )
{
	ASSERT( connected );

	// get request ID
	String requestId = req.getAttribute( "requestId" );
	String s = req.serialize();
	socket.sendMessage( s );

	// receive result
	Timer timer( requestWaitTime );
	while( timer.go() )
		{
			String res = socket.recvMessage( requestWaitTime );
			if( res.isEmpty() )
				{
					disconnect();
					ASSERTMSG( false , "connection is closed from server side" );
				}

			Xml xml = readXml( res , "xmlcallresult" );
			String id = xml.getAttribute( "requestId" );
			if( id.equals( requestId ) )
				return( xml );

			destroyXml( xml );
		}

	ASSERT( false );
}

void AIApiImpl::connect( String url )
{
	lastRequestNumber = 0;

	const char *p = strrchr( url , ':' );
	ASSERT( p != NULL );
	
	int port = atoi( p + 1 );
	String host = url.getMid( 0 , p - ( const char * )url );

	socket.open( host , ( unsigned short )port );
	connected = true;
}

void AIApiImpl::disconnect()
{
	connected = false;
	socket.close();
}

bool AIApiImpl::isConnected()
{
	return( connected );
}
