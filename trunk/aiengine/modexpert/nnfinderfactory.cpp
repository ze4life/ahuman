
#include "aiexpert_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNFinderFactory::NNFinderFactory()
:	engine( AIEngine::getInstance() ) ,
	internalDiffForDerivative( 0.01f ) ,
	internalMinValue( -1 ) ,
	internalMaxValue( 1 ) ,
	boolTrue( 1 ) ,
	boolFalse( 0 )
{
	erf = NULL;
	nPerceptronIDLast = 0;
	factoryStatSamples = NULL;

	p1 = NULL;
	p1s = NULL;
	p2 = NULL;
	p2s = NULL;
	vars = new NNVariables;
}

NNFinderFactory::~NNFinderFactory()
{
	freeData();
	delete vars;
}

void NNFinderFactory::freeData()
{
	if( p1 != NULL )
		delete p1;
	if( p2 != NULL )
		delete p2;
	if( p1s != NULL )
		delete p1s;
	if( p2s != NULL )
		delete p2s;

	p1 = NULL;
	p2 = NULL;
	p1s = NULL;
	p2s = NULL;
}

void NNFinderFactory::init()
{
	erf = AIExpertImpl::getServiceImpl() -> getRegressionFactory();

	AIDB db;
	db.load( vars , "FinderFactory" );

	if( !db.load( this , "simple" ) )
		createInitial();
}

NNFinder *NNFinderFactory::create( NNSamples *trainSet )
{
	ASSERT( false );
	return( NULL );
}

String NNFinderFactory::getNewId()
{
	return( String( "EFF" ) + ++nPerceptronIDLast );
}

// samples
NNSamples *NNFinderFactory::createSamples( int nSensors , int nClusters )
{
	NNSamples *samples = new NNSamples( nSensors , nClusters );
	return( samples );
}

NNSample *NNFinderFactory::addSample( NNSamples *samples , float *sensors , int classID )
{
	NNSample *sample = samples -> add();
	memcpy( sample -> getSensors() , sensors , sample -> getNSensors() * sizeof( float ) );

	float *targets = sample -> getTargets();
	for( int k = 1; k <= sample -> getNTargets(); k++ )
		*targets++ = ( k == classID )? boolTrue : boolFalse;

	sample -> setClusterID( classID );

	return( sample );
}

// create first version of perceptrons
void NNFinderFactory::createInitial()
{
	nPerceptronIDLast = 0;

	// create variables
	vars = new NNVariables;
	vars -> create( 1000 );

	// create perceptron p1: map network parameters to finder parameters
	createInitialP1( &p1 , &p1s );

	// create perceptron p2: map finder parameters to success metrics
	createInitialP2( &p2 , &p2s );

	// create samples
	factoryStatSamples = new NNSamples( p2 -> getNSensors() , p2 -> getNTargets() );
	factoryStatSamples -> setLimitRandom( 1000 );

	// save this
	save();
}

void NNFinderFactory::save()
{
	AIDB db;
	db.save( this , "simple" );
	db.save( vars , "FinderFactory" );
}

NN *NNFinderFactory::createDefaultPerceptron( const char *name , ClassList<NNVariable>& sensors , NNVariable *target , int hiddenLayerSize )
{
	// create perceptron
	bool useBias = true;
	int nSensors = sensors.count();

	int nTargets = target -> getRepresentationSize();
	NN *pp = NN::newInit( name , nSensors , nTargets , useBias );

	// set network structure
	NNInductionFunction fi; 
	fi.setWeightedSum();

	NNActivationFunction fa; 
	fa.initSigmoidSymmetric();
	fa.setNoScaleInput( true );
	fa.setSteepness( 1 );

	NNLayer *pl1 = pp -> addLayer( hiddenLayerSize , &fi , &fa , useBias );
	useBias = false;
	NNLayer *pl2 = pp -> addLayer( nTargets , &fi , &fa , useBias );

	pp -> joinLayersDirect();
	pp -> joinSensors( sensors );
	ClassList<NNVariable> targets;
	targets.add( target );
	pp -> joinTargets( targets );
	pp -> createFinally();

	// adjust network parameters
	pp -> setInputRanges( internalMinValue , internalMaxValue );
	pp -> setOutputRanges( internalMinValue , internalMaxValue );

	pp -> setBiasValues( internalMaxValue );

	return( pp );
}

NNStrategyBackPropagation *NNFinderFactory::createDefaultStrategy( const NN *p )
{
	// create main strategy
	NNStrategyBackPropagation *ps = NNStrategyBackPropagation::newInit( const_cast<NN *>( p ) );
	float gradientRate = 1.5f;
	ps -> setGradientRate( gradientRate );
	ps -> setTrainingBatchQuickProp();

	NNErrorFunction *ef = ps -> getErrorFunction();
	ef -> setTranslationTanh();

	NNStopFunction *sf = ps -> getStopFunction();
	sf -> setErrorFunction( ef );
	float stopBitsPrecision = 0.1f;
	int maxFailedNeurons = 0;
	sf -> setModeBits( stopBitsPrecision , maxFailedNeurons );
	int maxIterations = 100;
	sf -> setMaxIterations( maxIterations );

	// set validate
	NNValidateFunction *vf = p -> getValidateFunction();
	float avgFailedNeurons = 0;
	float bitTolerance = stopBitsPrecision * 1.5;
	vf -> setValidateAvgOutputBits( bitTolerance , avgFailedNeurons );

	ps -> setSmoothLearning( false );

	float quickPropDecay = -0.0001f;
	float quickPropMu = 1.75f;
	float quickPropMinStep = 0.001f;
	ps -> setQuickPropDecay( quickPropDecay );
	ps -> setQuickPropMu( quickPropMu );
	ps -> setQuickPropMinStep( quickPropMinStep );

	return( ps );
}

void NNFinderFactory::createInitialP1( NN **pp , NNStrategyBackPropagation **ps )
{
	ClassList<NNVariable> sensors;
	int nSrcProps = NNFinderFactorySample::getTrainSampleSensors( vars , sensors );
	ClassList<NNVariable> targets;
	int nDstProps = NNFinderFactorySample::getTrainSampleTargets( vars , targets );
	int nUseHiddenNeurons = ( nSrcProps + nDstProps ) / 2;
	NN *p = erf -> createDefaultPerceptron( "ExperFinderFactory::P1" , sensors , targets , nUseHiddenNeurons );

	// adjust network parameters
	p -> clearExecuteStat();

	// weights
	p -> initWeightsByWidrowNguyen();

	// strategy
	NNStrategyBackPropagation *s = erf -> createDefaultStrategy( "ExperFinderFactory::P1S" , p );

	// adjust stop and validate
	NNValidateFunction *vf = p -> getValidateFunction();
	NNStopFunction *sf = s -> getStopFunction();

	float stopBitsPrecision = 0.1f;
	float avgFailedNeurons = 0;
	float bitTolerance = stopBitsPrecision * 1.5f;
	float totalFailedNeurons = 0;

	vf -> setValidateAvgOutputBits( bitTolerance , avgFailedNeurons );
	sf -> setModeBits( stopBitsPrecision , totalFailedNeurons );
	sf -> setMaxIterations( 1000 );

	*pp = p;
	*ps = s;
}

void NNFinderFactory::createInitialP2( NN **pp , NNStrategyBackPropagation **ps )
{
	ClassList<NNVariable> sensors;
	int nSrcProps = NNFinderFactorySample::getStatSampleSensors( vars , sensors );
	ClassList<NNVariable> targets;
	int nDstProps = NNFinderFactorySample::getStatSampleTargets( vars , targets );
	int nUseHiddenNeurons = ( nSrcProps + nDstProps ) / 2;
	NN *p = erf -> createDefaultPerceptron( "ExperFinderFactory::P2" , sensors , targets , nUseHiddenNeurons );

	// adjust network parameters
	p -> clearExecuteStat();

	// weights
	p -> initWeightsByWidrowNguyen();

	// strategy
	NNStrategyBackPropagation *s = erf -> createDefaultStrategy( "ExperFinderFactory::P2S" , p );

	// adjust stop and validate
	NNValidateFunction *vf = p -> getValidateFunction();
	NNStopFunction *sf = s -> getStopFunction();

	float stopBitsPrecision = 0.1f;
	float avgFailedNeurons = 0;
	float bitTolerance = stopBitsPrecision * 1.5f;
	float totalFailedNeurons = 0;

	vf -> setValidateAvgOutputBits( bitTolerance , avgFailedNeurons );
	sf -> setModeBits( stopBitsPrecision , totalFailedNeurons );

	*pp = p;
	*ps = s;
}

NNSample *NNFinderFactory::addFactoryStatSample()
{
	return( factoryStatSamples -> add() );
}

// train factory function
void NNFinderFactory::trainFactorySample( NNSample *fs )
{
	p2s -> learn( fs , NULL , NULL );
}

void NNFinderFactory::mixFactoryStatSamples( NNSamples *stat , NNSamples *mix )
{
	// handle separately
	NNSamples ss( stat -> sizeIn() , stat -> sizeOut() );
	AIDB db;
	db.load( &ss , "ffstat" );

	// adjust
	NNFinderFactorySample::adjustDimensions( &ss );

	// add stat and get mix
	ss.add( stat );
	mix -> add( &ss );

	// save back to file
	db.save( &ss , "ffstat" );
}

void NNFinderFactory::convertStatToFactory( NNSamples *mix , NNSamples *fts )
{
	for( int k = 0; k < mix -> count(); k++ )
		{
			NNSample *fe = mix -> getByPos( k );
			NNSample *fs = fts -> add();

			NNFinderFactorySample ffs( fs , fe );
			ffs.completeFS( p2 );
		}
}

void NNFinderFactory::trainFactorySamples()
{
	NNStrategyHelper& helper = p1s -> getHelper();
	// Preconditions:
	// factorySamples: unprocessed stat factory samples
	// finderFactorySamples.odb: all previously known factorySamples (handle props added after previous run!)
	// local - trainSamples: training set - mix of file factory samples and new factory samples

	// 1. mix with file stored
	NNSamples mix( p2 );
	mixFactoryStatSamples( factoryStatSamples , &mix );

	// 2. convert samples to train format
	NNSamples fts( p1 );
	convertStatToFactory( &mix , &fts );

	// 3. do train NN1
	// helper.showSamples( "Collected factory samples" , factorySamples );
	AIDB db;
	// db.save( p1s , "strategyBefore" );
	// db.save( p1 , "netBeforeTrain" );
	db.save( &fts , "trainingSet" );
	bool res = p1s -> learn( &fts , NULL , NULL );
	ASSERT( res );
	helper.showSamplesActual( "Finally trained" , &fts );

	// 3. save factory
	save();
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNFinderFactory::NAME = "NNFinderFactory";

void NNFinderFactory::createSerializeObject()
{
	// register this class
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNFinderFactory::onCreate );

	so -> addFieldInt( "nPerceptronIDLast" );
	so -> addFieldObject( "p1" , NN::getSerializeObject() );
	so -> addFieldObject( "p2" , NN::getSerializeObject() );
	so -> addFieldObject( "p1s" , NNStrategyBackPropagation::getSerializeObject() );
	so -> addFieldObject( "p2s" , NNStrategyBackPropagation::getSerializeObject() );
	so -> addFieldObject( "factorySamples" , NNSamples::getSerializeObject() );
}

void NNFinderFactory::serialize( SerializeObject& so )
{
	so.setPropInt( nPerceptronIDLast , "nPerceptronIDLast" );
	so.setPropObject( p1 , "p1" , false );
	so.setPropObject( p2 , "p2" , false );
	so.setPropObject( p1s , "p1s" , false );
	so.setPropObject( p2s , "p2s" , false );
	so.setPropObject( factoryStatSamples , "factorySamples" , false );
}

void NNFinderFactory::deserialize( Object *parent , SerializeObject& so )
{
	freeData();

	nPerceptronIDLast = so.getPropInt( "nPerceptronIDLast" );
	p1 = ( NN * )so.getPropObject( "p1" , true );
	p2 = ( NN * )so.getPropObject( "p2" , true );
	p1s = ( NNStrategyBackPropagation * )so.getPropObject( "p1s" , true );
	p1s -> attach( p1 );
	p2s = ( NNStrategyBackPropagation * )so.getPropObject( "p2s" , true );
	p2s -> attach( p2 );

	factoryStatSamples = ( NNSamples * )so.getPropObject( "factorySamples" , true );
	if( factoryStatSamples == NULL )
		{
			factoryStatSamples = new NNSamples( p2 -> getNSensors() , p2 -> getNTargets() );
			factoryStatSamples -> setLimitRandom( 1000 );
		}
}
