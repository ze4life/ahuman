#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIHtmLibDebug::AIHtmLibDebug()
{
	logger.attach( "HtmLibDebug" );
	callSub = NULL;
	callPub = NULL;
}

AIHtmLibDebug::~AIHtmLibDebug()
{
}

void AIHtmLibDebug::init( Xml config )
{
	// subscribe to debug calls
	Xml debug = config.getChildNode( "debug" );
	String channelIn = debug.getProperty( "channel.in" );
	String channelOut = debug.getProperty( "channel.out" );

	AIIO io;
	callSub = io.subscribe( NULL , channelIn , "htmlib" , this );
	callPub = io.createPublisher( NULL , channelOut , "htmlib" , "debug" );
}

void AIHtmLibDebug::exit()
{
	AIIO io;
	if( callPub != NULL )
		io.destroyPublisher( callPub );
	if( callSub != NULL )
		io.unsubscribe( callSub );
}

void AIHtmLibDebug::onXmlCall( XmlCall *msg )
{
	Xml xml = msg -> getXml();
	logger.logInfo( String( "received function call: " ) + xml.getHeading() );
	XmlCall& call = *msg;
	String fn = call.getFunctionName();

	try {
		if( fn.equals( "htmlib::testHelloWorld" ) )
			testHelloWorld( call );
		else 
		if( fn.equals( "htmlib::testCreateHtm" ) )
			testCreateHtm( call );
		else 
		if( fn.equals( "htmlib::testViewPicture" ) )
			testViewPicture( call );
		else 
			return;

		Xml res = call.getResponse();
		if( res.exists() )
			return;

		res = call.createResponse();
		res.setAttribute( "status" , "ok" );
		call.sendResponse( callPub );
	}
	catch ( RuntimeException& e ) {
		call.sendResponseException( callPub , e );
		e.printStack( logger );
	}
	catch( ... ) {
		call.sendResponseUnknownException( callPub );
		logger.logError( "Unknown exception:" );
		logger.printStack();
	}
}

// tests
void AIHtmLibDebug::testHelloWorld( XmlCall& call )
{
	HtmCortex ctx;

	int sizeH = call.getIntParam( "sizeH" , 100 );
	int sizeV = call.getIntParam( "sizeV" , 100 );
	ctx.create( sizeH , sizeV );

	HtmHelper helper( logger );
	helper.showCortex( &ctx );

	HtmRect rc = ctx.getRect();
	ctx.recalculate( rc );
}

void AIHtmLibDebug::testCreateHtm( XmlCall& call )
{
	Session *session = call.getSession();

	String name = call.getParam( "cortexName" );
	int sizeH = call.getIntParam( "sizeH" );
	int sizeV = call.getIntParam( "sizeV" );

	HtmCortex *ctx = new HtmCortex;
	session -> setObject( ctx , name );
	
	ctx -> create( sizeH , sizeV );
	HtmHelper helper( logger );
	helper.showCortex( ctx );
}

void AIHtmLibDebug::testViewPicture( XmlCall& call )
{
	Session *session = call.getSession();

	String name = call.getParam( "cortexName" );
	HtmCortex *ctx = ( HtmCortex * )session -> getObject( name );
	ASSERTMSG( ctx != NULL , String( "[" ) + name + "]: unknown cortex" );

	Xml xml = call.getXml();
	Xml picture = xml.getChildNode( "picture" );
	String text = picture.getValue();
	
	int nh = ctx -> getInputsSizeH();
	int nv = ctx -> getInputsSizeV();
	ASSERT( ( nv * ( nh * 6 + 1 ) - 1 ) == text.length() );

	const char *p = text;
	unsigned char z[ 4 ]; z[0] = z[1] = z[2] = z[3] = 0;
	int *x = ( int * )z; // rgb0
	TwoIndexArray<int>& values = ctx -> getInputs();
	for( int v = 0; v < nv; v++ )
		{
			int *hv = values[ v ];
			for( int h = 0; h < nh; h++ )
				{
					for( int d = 0; d < 3; d++ )
						{
							char c = *p++;
							unsigned char cc = ( c >= 'A' && c <= 'F' )? c + 10 - 'A' : c - '0';
							c = *p++;
							z[ d ] = ( cc << 4 ) | ( ( c >= 'A' && c <= 'F' )? c + 10 - 'A' : c - '0' );
						}

					hv[ h ] = *x;
				}
			if( v != nv - 1 )
				ASSERT( *p++ == '\n' );
		}
	ASSERT( *p == 0 );
	
	HtmRect rc = ctx -> getRect();
	ctx -> recalculate( rc );

	HtmHelper helper( logger );
	helper.showCortexMemorySize( ctx );
}
