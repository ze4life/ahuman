#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class AIExpertFinder : public AINeuroNetwork
NNRegression::NNRegression()
:	engine( AIEngine::getInstance() )
{
	erf = AINNLibImpl::getServiceImpl() -> getRegressionFactory();

	p = NULL;
	trainSamples = NULL;
	psBP = NULL;

	bitTolerance = 0;
}

void NNRegression::create( const char *name , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets , int hiddenLayerSize )
{
	// create perceptron
	p = erf -> createDefaultPerceptron( name , sensors , targets , hiddenLayerSize );

	// create training strategy
	psBP = erf -> createDefaultStrategy( name , p );

	// create training samples
	trainSamples = p -> createSamples();

	logger.attach( this );
}

NNRegression::~NNRegression()
{
	freeData();
}

void NNRegression::freeData()
{
	if( psBP != NULL )
		delete psBP;
	if( p != NULL )
		delete p;
	if( trainSamples != NULL )
		delete trainSamples;

	psBP = NULL;
	p = NULL;
	trainSamples = NULL;
}

void NNRegression::learnStat( NNSamples *samplesLearn , NNSamples *samplesValidate , StatParams *sp , StatResults& res )
{
	NNStrategyHelper helper( logger );
	helper.attach( p );

	p -> clearValues();
	samplesLearn -> clearLearnData();
	// helper.showSamples( "LEARN SAMPLES" , samplesLearn );

	if( samplesValidate != NULL )
		{
			samplesValidate -> clearValidateData();
			// helper.showSamples( "VALIDATE SAMPLES" , samplesValidate );
		}

	// helper.showPerceptron( "BEFORE ALL" );

	// AIEngine& engine = AIEngine::getInstance();
	logger.logInfo( String( "learnStat RUN:" ) +
		" minIterations=" + sp -> minIterations +
		", maxIterations=" + sp -> maxIterations +
		", nHiddenNeurons=" + p -> getFirstLayer() -> getNonBiasNeuronCount() +
		", algorithm=" + sp -> algorithm +
		", gradientRate=" + sp -> gradientRate + 
		", initWeights=" + sp -> initWeights +
		", wMin=" + sp -> wMin +
		", wMax=" + sp -> wMax +
		", wRandomMin=" + sp -> wRandomMin +
		", steepness=" + sp -> steepness +
		", calculateHiddenInputRanges=" + sp -> calculateHiddenInputRanges +
		", errorFunctionLinear=" + sp -> errorFunctionLinear +
		", stopBitsPrecision=" + sp -> stopBitsPrecision +
		", momentum=" + sp -> momentum +
		", steepness=" + sp -> steepness +
		", increaseFactorRPROP=" + sp -> increaseFactorRPROP +
		", decreaseFactorRPROP=" + sp -> decreaseFactorRPROP + 
		", deltaMinRPROP=" + sp -> deltaMinRPROP +
		", deltaMaxRPROP=" + sp -> deltaMaxRPROP +
		", deltaZeroRPROP=" + sp -> deltaZeroRPROP +
		", deltaZeroMinRPROP=" + sp -> deltaZeroMinRPROP +
		", quickPropDecay=" + sp -> quickPropDecay +
		", quickPropMu=" + sp -> quickPropMu +
		", quickPropMinStep=" + sp -> quickPropMinStep +
		", maxRestarts=" + sp -> maxRestarts +
		", learSamplesCount=" + samplesLearn -> count() +
		", count=" + sp -> statCount );

	int epochCount;

	int min = 0, max = 0, sum = 0;
	int ok = 0;
	int setSensorsTotal = 0;
	int restartsTotal = 0;
	int epochCountTotal = 0;
	int validationFailuresTotal = 0;
	for( int k = 0; k < sp -> statCount; k++ )
		{
			int setSensorsStat;
			int restartsStat;
			int epochTotal;
			int validationFailuresStat;

			bool res = learnStatIteration( samplesLearn , samplesValidate , sp ,
				&epochCount , &epochTotal , &setSensorsStat , &restartsStat , &validationFailuresStat );

			setSensorsTotal += setSensorsStat;
			restartsTotal += restartsStat;
			epochCountTotal += epochTotal;
			validationFailuresTotal += validationFailuresStat;
			// logger.logInfo( String( "Stat iteration " ) + k + ": " + res );

			if( res )
				{
					ok++;
					if( epochCount > max )
						max = epochCount;
					if( epochCount < min || min == 0 )
						min = epochCount;
					sum += epochCount;
				}
		}

	int avg;
	if( ok > 0 )
		avg = ( int )( ( sum * 1.0f ) / ok );
	else
		avg = 0;

	ok = ( int )( ( ok * 100.0f ) / sp -> statCount );

	logger.logInfo( String( "RESULTS: succeed ratio=" ) + ok +
		", min=" + min + ", max(ok)=" + max + ", avg(ok)=" + avg +
		", setSensors=" + setSensorsTotal +
		", restarts=" + restartsTotal +
		", validationFailures=" + validationFailuresTotal +
		", epochCount(ok)=" + sum +
		", epochCountTotal=" + epochCountTotal );
	logger.logInfo( "---" );

	res.succeedRatio = ok;
	res.minEpochCount = min;
	res.maxEpochCount = max;
	res.avgEpochCount = avg;
	res.restartsTotal = restartsTotal;
	res.epochsTotal = epochCountTotal;
	res.setSensorsTotal = setSensorsTotal;
	res.validationFailures = validationFailuresTotal;
}

bool NNRegression::learnStatIteration( NNSamples *samplesLearn , NNSamples *samplesValidate , StatParams *sp ,
	int *pepochCount , int *pepochCountTotal , int *psetSensorsStat , int *restartsDone , int *pvalidationFailures )
{
	int epochCount = 0;
	int sensorsStat = 0;

	// clearn learn data from previous run
	samplesLearn -> clearLearnData();
	if( samplesValidate != NULL )
		samplesValidate -> clearValidateData();

	p -> clearExecuteStat();

	// network structure already created in init
	// adjust network parameters
	if( sp -> calculateHiddenInputRanges )
		{
			float calculateRatio = 1;
			p -> calculateLayerInputRanges( sp -> wMin , sp -> wMax , calculateRatio );
		}
	else
		p -> setLayerInputRangesUnlimited();

	// create main strategy
	NNStrategyBackPropagation *ps = erf -> createDefaultStrategy( "Regression::Stat" , p );
	ps -> setGradientRate( sp -> gradientRate );
	ps -> setWeightRange( sp -> wMin , sp -> wMax );
	
	switch( sp -> algorithm )
		{
			case 1 :	
				ps -> setTrainingIncremental(); 
				break;
			case 2 :	
				ps -> setTrainingBatchSimple(); 
				break;
			case 3 :	
				ps -> setTrainingBatchRProp(); 
				ps -> setRPropFactor( sp -> increaseFactorRPROP , sp -> decreaseFactorRPROP );
				ps -> setRPropDelta( sp -> deltaMinRPROP , sp -> deltaMaxRPROP , sp -> deltaZeroRPROP , sp -> deltaZeroMinRPROP );
				break;
			case 4 :	
				ps -> setTrainingBatchQuickProp(); 
				ps -> setQuickPropDecay( sp -> quickPropDecay );
				ps -> setQuickPropMu( sp -> quickPropMu );
				ps -> setQuickPropMinStep( sp -> quickPropMinStep );
				break;
		}

	NNErrorFunction *ef = ps -> getErrorFunction();
	if( sp -> errorFunctionLinear )
		ef -> setTranslationLinear();
	else
		ef -> setTranslationTanh();

	NNStopFunction *sf = ps -> getStopFunction();
	int maxFailedNeurons = 0;
	sf -> setModeBitsMany( samplesLearn , sp -> stopBitsPrecision , maxFailedNeurons );
	sf -> setMinIterations( sp -> minIterations );
	sf -> setMaxIterations( sp -> maxIterations );

	// set validate
	NNValidateFunction *vf = p -> getValidateFunction();
	float avgFailedNeurons = 0;
	bitTolerance = sp -> stopBitsPrecision * 1.5;
	vf -> setValidateAvgOutputBits( bitTolerance , avgFailedNeurons );

	if( sp -> momentum > 0 )
		{
			ps -> setSmoothLearning( true );
			ps -> setSmoothRate( sp -> momentum );
		}
	else
		ps -> setSmoothLearning( false );

	NNStrategyHelper& localHelper = ps -> getHelper();
	localHelper.attach( this );
	localHelper.attachSamples( samplesLearn , samplesValidate );

	// learn all
	NNWeights pw( p );

	// iteratte with restarts
	float variance;
	bool res = false;
	int restarts = 0;
	int epochCountTotal = 0;
	int validationFailures = 0;
	for( int k = 0;; k++ )
		{
			// init weights
			learnStatInitWeights( p , ps , sp -> initWeights , sp -> wRandomMin , sp -> wRandomMax );

			// do learn
			// localHelper.showPerceptron( "before learn" );
			res = ps -> learn( samplesLearn , &pw , &variance );
			epochCountTotal += ps -> getEpochCount();
			if( res ) 
				{
					// double-check validation logic
					float error;
					ASSERT( p -> validate( samplesLearn , &error ) );

					// validate results using validation set
					if( samplesValidate == NULL )
						break;

					// find generalization success
					float errorValidate;
					res = p -> validate( samplesValidate , &errorValidate );

					// stop training if validation succeeded
					if( res )
						break;

					validationFailures++;
					logger.logInfo( String( "learnStat: validation failed - trainError=" ) + error +
						", trainSetCount=" + samplesLearn -> count() +
						", validateSetCount=" + samplesValidate -> count() +
						", generalizationError=" + errorValidate );

					// show all samples where validate failed
					// localHelper.showValidateFailedSamples( samplesValidate );
				}

			if( k >= sp -> maxRestarts )
				break;

			// do restart
			restarts++;
			//logger.logInfo( String( "Restart #" ) + restarts + 
			//	": setSensors=" + pp -> getSetSensorsStat() + 
			//	", epochCountTotal=" + epochCountTotal );
		}
	*restartsDone = restarts;

	sensorsStat = p -> getExecuteStat();
	epochCount = ps -> getEpochCount();

	*pepochCount = epochCount;
	*pepochCountTotal = epochCountTotal;
	*psetSensorsStat = sensorsStat;
	*pvalidationFailures = validationFailures;

	delete ps;

	return( res );
}

void NNRegression::learnStatInitWeights( NN *pp , NNStrategyBackPropagation *ps , char type , float wRandomMin , float wRandomMax )
{
	static float staticWeights[] = {
		0.042544f , 0.569077f , -0.263886f , 0.106337f , 0.137073f ,
		0.073324f , 0.198080f , 0.264549f , 0.385635f , 0.481844f ,
		0.559038f , 0.156244f , 0.104723f
	};

	randoms4Weights.createRangeRandomsFloat( wRandomMin , wRandomMax );
	switch( type )
		{
			case 'S' :
				pp -> initWeightsStatic( staticWeights , 13 );
				break;
			case 'N' :
				pp -> initWeightsByWidrowNguyen();
				break;
			case 'R' :
				pp -> initWeightsRandom( randoms4Weights );
				break;
			default :
				ASSERT( false );
		}
}

bool NNRegression::getTargets( const float *sensors , FlatList<float>& targets )
{
	p -> setSensors( sensors );
	targets.clear();

	int n = p -> getNTargets();
	targets.create( n );

	for( int k = 0; k < n; k++ )
		targets[ k ] = p -> getTargetVariable( k ) -> getValue();

	return( true );
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNRegression::NAME = "NNRegression";

void NNRegression::createSerializeObject()
{
	// register this class
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNRegression::onCreate );

	so -> addFieldObject( "perceptron" , NN::getSerializeObject() );
	so -> addFieldObject( "strategyBackPropagation" , NNStrategyBackPropagation::getSerializeObject() );
	so -> addFieldFloat( "bitTolerance" );
	so -> addFieldObject( "trainSamples" , NNSamples::getSerializeObject() );
}

void NNRegression::serialize( SerializeObject& so )
{
	so.setPropObject( p , "perceptron" , false );
	so.setPropObject( psBP , "strategyBackPropagation" , false );
	so.setPropFloat( bitTolerance , "bitTolerance" );
	so.setPropObject( trainSamples , "trainSamples" , false );
}

void NNRegression::deserialize( Object *parent , SerializeObject& so )
{
	freeData();

	p = ( NN * )so.getPropObject( "perceptron" , true );
	psBP = ( NNStrategyBackPropagation * )so.getPropObject( "strategyBackPropagation" , true );
	psBP -> attach( p );

	bitTolerance = so.getPropFloat( "bitTolerance" );

	trainSamples = ( NNSamples * )so.getPropObject( "trainSamples" , true );
}
