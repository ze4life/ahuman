#include "aihtmview.h"
#include "aihtmops.h"

AIHtmOps::AIHtmOps()
{
}

AIHtmOps::~AIHtmOps()
{
}

bool AIHtmOps::connect( const char *url )
{
	try {
		api.connect( url );
	}
	catch( String s ) {
		wxMessageBox( ( const char * )( String( "Cannot connect: " ) + s ) );
		return( false );
	}
	return( true );
}

void AIHtmOps::disconnect()
{
	api.disconnect();
}

void AIHtmOps::createCortex( int p_width , int p_height )
{
	api.createXmlRequest();
	api.setFunctionName( "htmlib::testCreateHtm" );
	api.setParam( "cortexName" , "htmview" );
	api.setIntParam( "sizeH" , p_width );
	api.setIntParam( "sizeV" , p_height );

	try {
		Xml res = api.execute();
		String status = res.getAttribute( "status" );
		if( !status.equals( "ok" ) )
			wxMessageBox( ( const char * )status );
	}
	catch( String s ) {
		wxMessageBox( ( const char * )s );
	}
}

void AIHtmOps::sendPicture( const char *hexbytes )
{
	Xml xml = api.createXmlRequest();
	api.setFunctionName( "htmlib::testViewPicture" );
	api.setParam( "cortexName" , "htmview" );
	Xml txt = xml.addElement( "picture" );
	txt.addTextElement( "picture" , hexbytes );

	try {
			Xml res = api.execute();
			String status = res.getAttribute( "status" );
			if( !status.equals( "ok" ) )
				wxMessageBox( ( const char * )( String( "sendPicture failed: " ) + status ) );
	}
	catch( String s ) {
		wxMessageBox( ( const char * )( String( "Exception: " ) + s ) );
	}
}
