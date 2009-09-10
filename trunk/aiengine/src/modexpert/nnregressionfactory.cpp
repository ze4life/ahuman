
#include "aiexpert_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNRegressionFactory::NNRegressionFactory()
:	engine( AIEngine::getInstance() ) ,
	internalDiffForDerivative( 0.01f ) ,
	internalMinValue( -1 ) ,
	internalMaxValue( 1 )
{
	nPerceptronIDLast = 0;
	vars = NULL;
}

NNRegressionFactory::~NNRegressionFactory()
{
	freeData();
}

void NNRegressionFactory::freeData()
{
	if( vars != NULL )
		delete vars;

	vars = NULL;
}

void NNRegressionFactory::init()
{
	AIDB db;
	if( !db.load( this , "simple" ) )
		createInitial();
}

String NNRegressionFactory::getNewId()
{
	return( String( "ERF" ) + ++nPerceptronIDLast );
}

// create first version of perceptrons
void NNRegressionFactory::createInitial()
{
	nPerceptronIDLast = 0;

	// save this
	save();
}

void NNRegressionFactory::save()
{
	AIDB db;
	db.save( this , "simple" );
}

NN *NNRegressionFactory::createDefaultPerceptron( const char *name , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets , int hiddenLayerSize )
{
	// create perceptron
	bool useBias = true;
	NN *pp = NN::newInit( name , sensors.count() , targets.count() , useBias );

	// set network structure
	NNInductionFunction fi; 
	fi.setWeightedSum();

	NNActivationFunction fa; 
	fa.initSigmoidSymmetric();
	fa.setNoScaleInput( true );
	fa.setSteepness( 1 );

	NNLayer *pl1 = pp -> addLayer( hiddenLayerSize , &fi , &fa , useBias );
	useBias = false;
	int nOutputs = NNVariables::getRepresentationSize( targets );
	NNLayer *pl2 = pp -> addLayer( nOutputs , &fi , &fa , useBias );

	pp -> joinSensors( sensors );
	pp -> joinTargets( targets );
	pp -> joinLayersDirect();
	pp -> createFinally();

	// adjust network parameters
	pp -> setInputRanges( internalMinValue , internalMaxValue );
	pp -> setOutputRanges( internalMinValue , internalMaxValue );

	pp -> setBiasValues( internalMaxValue );

	return( pp );
}

NNStrategyBackPropagation *NNRegressionFactory::createDefaultStrategy( const char *instance , const NN *p )
{
	// create main strategy
	NNStrategyBackPropagation *ps = NNStrategyBackPropagation::newInit( const_cast<NN *>( p ) );
	ps -> setInstance( instance );

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

	// weight control
	ps -> setWeightRange( -1500 , 1500 );

	return( ps );
}

// samples
NNSamples *NNRegressionFactory::createSamples( int nSensors , int nTargets )
{
	NNSamples *samples = new NNSamples( nSensors , nTargets );
	return( samples );
}

// create derivaton perceptron
NN *NNRegressionFactory::createDerivationPerceptron( NNVariables *vars , NN *p , NNSamples *pSamples , int sensorFrom , int sensorTo , float ( *targetFunction )( NN *p ) )
{
	int nDerivationSensors = sensorTo - sensorFrom + 1;
	ASSERT( nDerivationSensors > 0 );

	// create perceptron - sensors are the same, targets are required derivatives of target function by given sensor
	int nSrcSensors = p -> getNSensors();
	int nSrcTargets = p -> getNTargets();
	int nDstTargets = nDerivationSensors;
	int hiddenLayerSize = ( nDstTargets + nSrcSensors ) / 2;

	// variables
	// sensors are the same
	ClassList<NNVariable> sensors;
	for( int k = 0; k < p -> getNSensors(); k++ )
		sensors.add( p -> getSensorVariable( k ) );

	// targets are derivatives - owned by NN variables
	ClassList<NNVariable> targets;
	for( int k1 = sensorFrom; k1 <= sensorTo; k1++ )
		for( k = 0; k < p -> getNSensors(); k++ )
			targets.add( vars -> addCommonNumberDerivative() );

	NN *pd = createDefaultPerceptron( String( p -> getId() ) + "#D" , sensors , targets , hiddenLayerSize );

	// create main strategy
	String instance;
	const char *pInstance = p -> getInstance();
	if( pInstance != NULL && *pInstance != 0 )
		instance = String( pInstance ) + "::derivative";
	NNStrategyBackPropagation *psBPd = createDefaultStrategy( instance , pd );

	// populate derivation samples - in the same points as training set
	NNSamples pdSamples( nSrcSensors , nDstTargets );
	for( int m = 0; m < pSamples -> count(); m++ )
		{
			NNSample *sample = pSamples -> getByPos( m );
			NNSample *sampleD = pdSamples.add();
			sampleD -> setSensors( sample -> getSensors() );

			getDerivatives( p , sensorFrom , sensorTo , sample , sampleD -> getTargets() , targetFunction );
		}

	// learn derivative perceptron
	bool res = psBPd -> learn( &pdSamples , NULL , NULL );
	ASSERT( res );

	return( pd );
}

void NNRegressionFactory::getDerivatives( NN *p , int sensorFrom , int sensorTo , NNSample *sample , float *targets , float ( *targetFunction )( NN *p ) )
{
	// iterate targets
	for( int k = sensorFrom; k <= sensorTo; k++ )
		{
			// get one point
			p -> setSensors( sample );
			float t1 = ( *targetFunction )( p );

			// get second point
			float *pv = p -> getInputPtr( k );
			*pv += internalDiffForDerivative;
			p -> execute();
			float t2 = ( *targetFunction )( p );

			// get derivative value
			float dv = ( t2 - t1 ) / internalDiffForDerivative;
			*targets++ = dv;
		}
}

void NNRegressionFactory::scaleBySamplesSimple( NNSamples *samples , NNVariables *vars , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets )
{
	// scale inputs
	for( int k = 0; k < samples -> sizeIn(); k++ )
		{
			float minV , maxV;
			samples -> getSensorRange( k , &minV , &maxV );

			ASSERT( minV < maxV );
			NNVariable *var = vars -> addCommonNumber( true , minV , true , maxV );
			sensors.add( var );
		}

	// scale outputs
	for( k = 0; k < samples -> sizeOut(); k++ )
		{
			float minV , maxV;
			samples -> getTargetRange( k , &minV , &maxV );

			ASSERT( minV < maxV );
			NNVariable *var = vars -> addCommonNumber( true , minV , true , maxV );
			targets.add( var );
		}
}

void NNRegressionFactory::scaleBySamplesStddev( NNSamples *samples , NNVariables *vars , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets )
{
	// scale inputs
	for( int k = 0; k < samples -> sizeIn(); k++ )
		{
			float meanV , stddevV;
			samples -> getSensorStat( k , &meanV , &stddevV );

			NNVariable *var = vars -> addCommonNumber( true , meanV - stddevV , true , meanV + stddevV );
			sensors.add( var );
		}

	// scale outputs
	for( k = 0; k < samples -> sizeOut(); k++ )
		{
			float meanV , stddevV;
			samples -> getTargetStat( k , &meanV , &stddevV );

			NNVariable *var = vars -> addCommonNumber( true , meanV - stddevV , true , meanV + stddevV );
			targets.add( var );
		}
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNRegressionFactory::NAME = "NNRegressionFactory";

void NNRegressionFactory::createSerializeObject()
{
	// register this class
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNRegressionFactory::onCreate );

	so -> addFieldInt( "nPerceptronIDLast" );
	so -> addFieldObject( "variables" , NNVariables::getSerializeObject() );
}

void NNRegressionFactory::serialize( SerializeObject& so )
{
	so.setPropInt( nPerceptronIDLast , "nPerceptronIDLast" );
	so.setPropObject( vars , "variables" , false );
}

void NNRegressionFactory::deserialize( Object *parent , SerializeObject& so )
{
	freeData();

	vars = ( NNVariables * )so.getPropObject( "variables" , true );
	nPerceptronIDLast = so.getPropInt( "nPerceptronIDLast" );
}

