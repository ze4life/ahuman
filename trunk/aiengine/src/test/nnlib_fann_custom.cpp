
#include "test_impl.h"
#include "../libnn/fann_custom/fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

class TestFannCustom : public TestUnit {
// construction
public:
	TestFannCustom() : TestUnit( "TestFannCustom" ) {};

	virtual void init() {
		ADD_METHOD( TestFannCustom::testCreateBySamples );
		ADD_METHOD( TestFannCustom::testFinderXOR );
		ADD_METHOD( TestFannCustom::testFinderLearn );
		ADD_METHOD( TestFannCustom::testFinderFactory );
	}
	
// tests
private:

void testCreateBySamples( XmlCall& call ) {
	// create samples to check factory
	float inputN = -1;
	float inputY = 1;
	float inputMin[2] = { inputN , inputN };
	float inputMax[2] = { inputY , inputY };
	int classCount = 1;
	int sensorCount = 2;

	NNFinderFactory *ff = LibFannCustom::getInstance() -> getFinderFactory();
	NNSamples *samplesLearn = ff -> createSamples( sensorCount , classCount );

	// fill samples
	Random rnd;
	rnd.createRangeRandomsFloat( inputN , inputY );
	float vi[2];

	for( int z1 = 100; z1--; ) {
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

void testFinderXOR( XmlCall& call ) {
	NNFinderFactory *ff = LibFannCustom::getInstance() -> getFinderFactory();

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
	NNVariables xvars;
	xvars.createLocal();
	ClassList<NNVariable> sensors;
	sensors.add( xvars.addCommonNumber( true , -1 , true , 1 ) );
	sensors.add( xvars.addCommonNumber( true , -1 , true , 1 ) );
	NNVariable *target = xvars.addCommonCategory( 2 );

	NNFinder finder;
	finder.create( "TMP" , sensors , target , sp.hiddenLayerSize );
	NNSamples samplesLearn( finder.getNN() );

	float s[2]; float t;
	s[0] = -1; s[1] = -1; t = 0;	samplesLearn.add( s , &t );
	s[0] = -1; s[1] = 1; t = 1;		samplesLearn.add( s , &t );
	s[0] = 1; s[1] = -1; t = 1;		samplesLearn.add( s , &t );
	s[0] = 1; s[1] = 1; t = 0;		samplesLearn.add( s , &t );
	
	NNFinder::StatResults res;
	finder.learnStat( &samplesLearn , NULL , &sp , res );
}

void testFinderLearn( XmlCall& call ) {
	NNFinderFactory *ff = LibFannCustom::getInstance() -> getFinderFactory();

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

	// sensors & targets
	NNVariables xvars;
	xvars.createLocal();
	ClassList<NNVariable> sensors;
	sensors.add( xvars.addCommonNumber( true , -1 , true , 1 ) );
	sensors.add( xvars.addCommonNumber( true , -1 , true , 1 ) );
	NNVariable *target = xvars.addCommonCategory( classCount );

	int caseNum = 1;
	for( int kHiddenNeurons = 3; kHiddenNeurons < 4; kHiddenNeurons++ ) {
		sp.hiddenLayerSize = kHiddenNeurons;

		NNFinder finder;
		finder.create( "TMP" , sensors , target , sp.hiddenLayerSize );
		// db.save( &finder , "xor2-3-1" );

		NNSamples samplesValidate( finder.getNN() );
		for( int z2 = 10; z2--; ) {
			vi[0] = rnd.getRandomFloat();
			vi[1] = rnd.getRandomFloat();
			int clusterID = ( vi[0] < 0 || vi[1] < 0 )? 0 : 1;
			ff -> addSample( &samplesValidate , vi , clusterID );
		}

		for( int kTrainCount = 50; kTrainCount <= 100; kTrainCount += 10 ) {
			sp.gradientRate = ( sp.algorithm == 1 )? 0.7f : 1.5f;

			NNSamples samplesLearn( finder.getNN() );
			for( int z1 = kTrainCount; z1--; ) {
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

void testFinderFactory( XmlCall& call ) {
	NNRegressionFactory *ff = LibFannCustom::getInstance() -> getRegressionFactory();

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

	for( int k = 0; k < 10; k++ ) {
		sp.gradientRate = 1.5f + k * 0.1f;

		NNRegression::StatResults res;
		reg.learnStat( &samplesLearn , NULL , &sp , res );
	}
}

};

/*#########################################################################*/
/*#########################################################################*/

TestUnit *TestUnit::createFannCustomTest() {
	return( new TestFannCustom );
}

