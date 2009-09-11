#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIHtmLibDebug::AIHtmLibDebug()
{
	logger.attach( "AINNLibDebug" );
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
	callSub = io.subscribe( channelIn , "htmlib" , this );
	callPub = io.createPublisher( channelOut , "htmlib" , "debug" );
}

void AIHtmLibDebug::exit()
{
	AIIO io;
	if( callPub != NULL )
		io.destroyPublisher( callPub );
	if( callSub != NULL )
		io.unsubscribe( callSub );
}

void AIHtmLibDebug::onMessage( Message *msg )
{
	XmlCall& call = msg -> toXmlCall();
	String fn = call.getFunctionName();

	try {
		if( fn.equals( "htmlib::testHelloWorld" ) )
			testHelloWorld( call );
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
}
