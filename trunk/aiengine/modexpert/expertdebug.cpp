#include "aiexpert_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AIExpertDebug::AIExpertDebug()
{
	logger.attach( "AIExpertDebug" );
	callSub = NULL;
	callPub = NULL;
}

AIExpertDebug::~AIExpertDebug()
{
}

void AIExpertDebug::init( Xml config )
{
	// subscribe to debug calls
	Xml debug = config.getChildNode( "debug" );
	String channelIn = debug.getProperty( "channel.in" );
	String channelOut = debug.getProperty( "channel.out" );

	AIIO io;
	callSub = io.subscribe( channelIn , "expert" , this );
	callPub = io.createPublisher( channelOut , "expert" , "debug" );
}

void AIExpertDebug::exit()
{
	AIIO io;
	if( callPub != NULL )
		io.destroyPublisher( callPub );
	if( callSub != NULL )
		io.unsubscribe( callSub );
}

void AIExpertDebug::onMessage( AIMessage *msg )
{
	XmlCall call;
	call.attach( msg );
	String fn = call.getName();

	try {
		if( fn.equals( "expert::createbysamples" ) )
			testCreateBySamples( call );
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
void AIExpertDebug::testCreateBySamples( XmlCall& call )
{
	// create samples to check factory
	float inputN = -1;
	float inputY = 1;
	float inputMin[2] = { inputN , inputN };
	float inputMax[2] = { inputY , inputY };
	int classCount = 1;
	int sensorCount = 2;

	AIExpertImpl *expert = AIExpertImpl::getServiceImpl();
	NNFinderFactory *ff = expert -> getFinderFactory();
	NNSamples *samplesLearn = ff -> createSamples( sensorCount , classCount );

	// fill samples
	Random rnd;
	rnd.createRangeRandomsFloat( inputN , inputY );
	float vi[2];

	for( int z1 = 100; z1--; )
		{
			vi[0] = rnd.getRandomFloat();
			vi[1] = rnd.getRandomFloat();
			int clusterID = ( vi[0] < 0 || vi[1] < 0 )? 0 : 1;
			ff -> addSample( samplesLearn , vi , clusterID );
		}

	// create finder
	NNFinder *ef = ff -> create( samplesLearn );
	
	delete ef;
	delete samplesLearn;
}
