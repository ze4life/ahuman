#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AINNLibDebug::AINNLibDebug()
{
	logger.attach( "AINNLibDebug" );
	callSub = NULL;
	callPub = NULL;
}

AINNLibDebug::~AINNLibDebug()
{
}

void AINNLibDebug::init( Xml config )
{
	// subscribe to debug calls
	Xml debug = config.getChildNode( "debug" );
	String channelIn = debug.getProperty( "channel.in" );
	String channelOut = debug.getProperty( "channel.out" );

	AIIO io;
	callSub = io.subscribe( channelIn , "nnlib" , this );
	callPub = io.createPublisher( channelOut , "nnlib" , "debug" );
}

void AINNLibDebug::exit()
{
	AIIO io;
	if( callPub != NULL )
		io.destroyPublisher( callPub );
	if( callSub != NULL )
		io.unsubscribe( callSub );
}

void AINNLibDebug::onMessage( Message *msg )
{
	XmlCall& call = msg -> toXmlCall();
	String fn = call.getFunctionName();

	try {
		if( fn.equals( "nnlib::testCreateBySamples" ) )
			testCreateBySamples( call );
		else
		if( fn.equals( "nnlib::testFinderPlay" ) )
			testFinderPlay( call );
		else
		if( fn.equals( "nnlib::testFinderFactory" ) )
			testFinderFactory( call );
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
void AINNLibDebug::testCreateBySamples( XmlCall& call )
{
	// create samples to check factory
	float inputN = -1;
	float inputY = 1;
	float inputMin[2] = { inputN , inputN };
	float inputMax[2] = { inputY , inputY };
	int classCount = 1;
	int sensorCount = 2;

	AINNLibImpl *nnlib = AINNLibImpl::getServiceImpl();
	NNFinderFactory *ff = nnlib -> getFinderFactory();
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

void AINNLibDebug::testFinderPlay( XmlCall& call )
{
	AINNLibImpl *nnlib = AINNLibImpl::getServiceImpl();
	NNFinderFactory *ff = nnlib -> getFinderFactory();

	NNFinder::StatParams sp;
	memset( &sp , 0 , sizeof( NNFinder::StatParams ) );

	// premium parameters
	sp.hiddenLayerSize = call.getIntParam( "hiddenLayerSize" , 3 );
	sp.stopBitsPrecision = call.getFloatParam( "stopBitsPrecision" , 0.1f );

	// iterate
	sp.statCount = call.getIntParam( "statCount" , 10 );
	sp.maxIterations = call.getIntParam( "maxIterations" , 100 );
	sp.algorithm = call.getIntParam( "algorithm" , 1 );
	sp.initWeights = call.getParam( "initWeights" , "N" ).getChar( 0 );
	sp.gradientRate = call.getFloatParam( "gradientRate" , 0.7f );
	sp.wMin = call.getFloatParam( "wMin" , -1500 );
	sp.wMax = call.getFloatParam( "wMax" , 1500 );
	sp.wRandomMin = call.getFloatParam( "wRandomMin" , -0.5f );
	sp.wRandomMax = call.getFloatParam( "wRandomMax" , 0.5f );
	sp.calculateHiddenInputRanges = call.getBooleanParam( "calculateHiddenInputRanges" );
	sp.errorFunctionLinear = call.getBooleanParam( "errorFunctionLinear" );
	sp.momentum = call.getFloatParam( "momentum" , 0 );
	sp.steepness = call.getFloatParam( "steepness" , 1 );
	sp.increaseFactorRPROP = call.getFloatParam( "increaseFactorRPROP" , 1.2f );
	sp.decreaseFactorRPROP = call.getFloatParam( "decreaseFactorRPROP" , 0.5f );
	sp.deltaMinRPROP = call.getFloatParam( "deltaMinRPROP" , 0 );
	sp.deltaMaxRPROP = call.getFloatParam( "deltaMaxRPROP" , 50 );
	sp.deltaZeroRPROP = call.getFloatParam( "deltaZeroRPROP" , 0.1f );
	sp.deltaZeroMinRPROP = call.getFloatParam( "deltaZeroMinRPROP" , 0.0001f );
	sp.quickPropDecay = call.getFloatParam( "quickPropDecay" , -0.0001f );
	sp.quickPropMu = call.getFloatParam( "quickPropMu" , 1.75f );
	sp.quickPropMinStep = call.getFloatParam( "quickPropMinStep" , 0.001f );
	sp.maxRestarts = call.getIntParam( "maxRestarts" , 10 );

	// train data
	int classCount = 2;
	// NNSamples samplesLearn( inputCount , classCount );
	// NNSamples samplesValidate( inputCount , classCount );

	// find negatives test
	Random rnd;
	rnd.createRangeRandomsFloat( 0 , 1 );
	float vi[2];

	// db.save( &samplesLearn , "sampleLearn" );
	// db.save( &samplesValidate , "sampleValidate" );

	// db.load( &samplesLearn , "sampleLearn" );
	// db.load( &samplesValidate , "sampleValidate" );

	/*
	for( int k = 0; k < 10; k++ )
		{
			NNSamples samplesLearn( inputCount , classCount );
			NNSamples samplesValidate( inputCount , classCount );
			for( int z1 = 10 + k * 10; z1--; )
				{
					vi[0] = rnd.getRandomFloat();
					vi[1] = rnd.getRandomFloat();
					int clusterID = ( vi[0] < 0 || vi[1] < 0 )? 0 : 1;
					finder.addSample( &samplesLearn , vi , clusterID );
				}

			for( int z2 = 10; z2--; )
				{
					vi[0] = rnd.getRandomFloat();
					vi[1] = rnd.getRandomFloat();
					int clusterID = ( vi[0] < 0 || vi[1] < 0 )? 0 : 1;
					finder.addSample( &samplesValidate , vi , clusterID );
				}

			NNFinder::StatResults res;
			finder.learnStat( &samplesLearn , &samplesValidate , 
				maxIterations , algorithm , initWeights , gradientRate , 
				wMin , wMax , wRandomMin , wRandomMax , 
				calculateHiddenInputRanges , errorFunctionLinear , stopBitsPrecision ,
				momentum , steepness ,
				increaseFactorRPROP , decreaseFactorRPROP , 
				deltaMinRPROP , deltaMaxRPROP , deltaZeroRPROP , deltaZeroMinRPROP , 
				quickPropDecay , quickPropMu , quickPropMinStep ,
				maxRestarts , statCount , res );
		}
	*/

	// sensors & targets
	NNVariables xvars;
	xvars.createLocal();
	ClassList<NNVariable> sensors;
	sensors.add( xvars.addCommonNumber( true , -1 , true , 1 ) );
	sensors.add( xvars.addCommonNumber( true , -1 , true , 1 ) );
	NNVariable *target = xvars.addCommonCategory( classCount );

	int caseNum = 1;
	for( int kHiddenNeurons = 3; kHiddenNeurons < 4; kHiddenNeurons++ )
		{
			sp.hiddenLayerSize = kHiddenNeurons;

			NNFinder finder;
			finder.create( "TMP" , sensors , target , sp.hiddenLayerSize );
			// db.save( &finder , "xor2-3-1" );

			NNSamples samplesValidate( finder.getNN() );
			for( int z2 = 10; z2--; )
				{
					vi[0] = rnd.getRandomFloat();
					vi[1] = rnd.getRandomFloat();
					int clusterID = ( vi[0] < 0 || vi[1] < 0 )? 0 : 1;
					ff -> addSample( &samplesValidate , vi , clusterID );
				}

			for( int kAlg = 3; kAlg <= 4; kAlg++ )
				for( int kTrainCount = 50; kTrainCount <= 100; kTrainCount += 10 )
					{
						sp.algorithm = kAlg;
						sp.gradientRate = ( kAlg == 1 )? 0.7 : 1.5;

						NNSamples samplesLearn( finder.getNN() );
						for( int z1 = kTrainCount; z1--; )
							{
								vi[0] = rnd.getRandomFloat();
								vi[1] = rnd.getRandomFloat();
								int clusterID = ( vi[0] < 0 || vi[1] < 0 )? 0 : 1;
								ff -> addSample( &samplesLearn , vi , clusterID );
							}

						NNFinder::StatResults res;
						finder.learnStat( &samplesLearn , &samplesValidate , &sp , res );

						// factory data
						NNSample *fe = ff -> addFactoryStatSample();
						NNFinderFactorySample ffs( NULL , fe );
						ffs.setStat( &samplesLearn , &samplesValidate , &sp , res );
					}
		}

	ff -> trainFactorySamples();
}

void AINNLibDebug::testFinderFactory( XmlCall& call )
{
	AINNLibImpl *nnlib = AINNLibImpl::getServiceImpl();
	NNRegressionFactory *ff = nnlib -> getRegressionFactory();

	NNRegression::StatParams sp;
	memset( &sp , 0 , sizeof( NNRegression::StatParams ) );

	// premium parameters
	sp.hiddenLayerSize = 3;
	sp.stopBitsPrecision = 0.1f;

	// iterate
	sp.statCount = 10;
	sp.minIterations = 0;
	sp.maxIterations = 100;
	sp.algorithm = 4;
	sp.initWeights = 'N';
	sp.gradientRate = 0.7f;
	sp.wMin = -1500;
	sp.wMax = 1500;
	sp.wRandomMin = -0.5f;
	sp.wRandomMax = 0.5f;
	sp.calculateHiddenInputRanges = false;
	sp.errorFunctionLinear = false;
	sp.stopBitsPrecision = 0.001f;
	sp.momentum = 0.1f;
	sp.steepness = 1;
	sp.increaseFactorRPROP = 1.2f;
	sp.decreaseFactorRPROP = 0.5f;
	sp.deltaMinRPROP = 0;
	sp.deltaMaxRPROP = 50;
	sp.deltaZeroRPROP = 0.1f;
	sp.deltaZeroMinRPROP = 0.0001f;
	sp.quickPropDecay = -0.0001f;
	sp.quickPropMu = 1.75f;
	sp.quickPropMinStep = 0.001f;
	sp.maxRestarts = 10;

	// train data
	NNSamples samplesLearn;
	AIDB db;
	db.load( &samplesLearn , "p1Samples" );

	// sensors and targets
	NNVariables vars;
	ClassList<NNVariable> sensors;
	NNFinderFactorySample::getTrainSampleSensors( &vars , sensors );
	ClassList<NNVariable> targets;
	NNFinderFactorySample::getTrainSampleTargets( &vars , targets );

	NNRegression reg;
	reg.create( "TMP" , sensors , targets , sp.hiddenLayerSize );

	for( int k = 0; k < 10; k++ )
		{
			sp.gradientRate = 1.5 + k * 0.1f;

			NNRegression::StatResults res;
			reg.learnStat( &samplesLearn , NULL , &sp , res );
		}
}
