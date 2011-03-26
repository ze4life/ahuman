#include <ah_adminapi.h>
#include <ah_adminapi_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AdminApi::AdminApi() {
	socket = new AdminApiSocket;

	initThread();
}

AdminApi::~AdminApi() {
	if( lastRequest.exists() )
		lastRequest.destroy();
	if( lastResponse.exists() )
		lastResponse.destroy();

	delete socket;

	exitThread();
}

void AdminApi::connect( String url ) {
	socket -> connect( url );
}

Xml AdminApi::execute() {
	if( lastResponse.exists() )
		lastResponse.destroy();

	lastResponse = socket -> execute( lastRequest );
	return( lastResponse );
}

void AdminApi::disconnect() {
	socket -> disconnect();
}

bool AdminApi::isConnected() {
	return( socket -> isConnected() );
}

Xml AdminApi::createXmlRequest() {
	if( lastRequest.exists() )
		lastRequest.destroy();

	lastRequest = Xml::create( "xmlcall" );
	return( lastRequest );
}

Xml AdminApi::loadXmlRequest( String fileName ) {
	if( lastRequest.exists() )
		lastRequest.destroy();
	
	lastRequest = Xml::load( fileName );
	ASSERTMSG( lastRequest.exists() , "Unable to load file path=" + fileName );
	ASSERTMSG( lastRequest.getName().equals( "xmlcall" ) , "Loaded file is not request" );

	return( lastRequest );
}

Xml AdminApi::readXmlRequest( const char *data ) {
	if( lastRequest.exists() )
		lastRequest.destroy();
	
	lastRequest = Xml::read( data , "xmlcall" );

	return( lastRequest );
}

void AdminApi::setFunctionName( String name ) {
	ASSERTMSG( lastRequest.exists() , "Request needs to be created" );
	lastRequest.setAttribute( "name" , name );
}

void AdminApi::setParam( String name , String value )
{
	ASSERTMSG( lastRequest.exists() , "Request needs to be created" );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );

	p.setProperty( name , value );			
}

void AdminApi::setBooleanParam( String name , bool value ) {
	ASSERTMSG( lastRequest.exists() , "Request needs to be created" );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );

	p.setBooleanProperty( name , value );			
}

void AdminApi::setIntParam( String name , int value ) {
	ASSERTMSG( lastRequest.exists() , "Request needs to be created" );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );

	p.setIntProperty( name , value );			
}

void AdminApi::setFloatParam( String name , float value ) {
	ASSERTMSG( lastRequest.exists() , "Request needs to be created" );
	Xml p = lastRequest.getFirstChild( "parameters" );
	if( !p.exists() )
		p = lastRequest.addElement( "parameters" );

	p.setFloatProperty( name , value );			
}

void AdminApi::initThread() {
	socket -> initThread();
}

void AdminApi::exitThread()
{
	socket -> exitThread();
}
