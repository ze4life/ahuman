#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

NNStrategyBackPropagation::NNStrategyBackPropagation()
:	NNStrategy( logger )
{
	engine = AIEngine::getInstance();

	epochCount = 0;

	nuFixed = 0;
	mu = 0;
	wLimitMin = 0;
	wLimitMax = 0;

	smooth = 0;

	// rprop params
	rpropIncreaseFactor = 0;
	rpropDecreaseFactor = 0;
	rpropDeltaMin = 0;
	rpropDeltaMax = 0;
	rpropDeltaZero = 0;
	rpropDeltaZeroMin = 0;

	// quickporop params
	quickPropDecay = 0;
	quickPropMu = 0;
	quickPropMinStep = 0;

	// perceptron learn data
	execSamples = NULL;
}

NNStrategyBackPropagation *NNStrategyBackPropagation::newInit( NN *p_p )
{
	NNStrategyBackPropagation *o = new NNStrategyBackPropagation;
	o -> init( p_p );
	return( o );
}

void NNStrategyBackPropagation::init( NN *p_p )
{
	NNStrategy::attach( p_p );

	smooth = false;

	nuFixed = 0;
	wLimitMin = 0;
	wLimitMax = 0;
	mu = 0;

	// setup strategy data
	initialize( p_p );
}

NNStrategyBackPropagation::~NNStrategyBackPropagation()
{
	neuronData.free();
	connectionData.free();
}

void NNStrategyBackPropagation::setTrainingIncremental()
{
	trainingAlgorithm = FANN_TRAIN_INCREMENTAL;
}

void NNStrategyBackPropagation::setTrainingBatchSimple()
{
	trainingAlgorithm = FANN_TRAIN_BATCH;
	initBatch();
}

void NNStrategyBackPropagation::setTrainingBatchRProp()
{
	trainingAlgorithm = FANN_TRAIN_RPROP;
	initBatch();

	// default rprop params
	rpropIncreaseFactor = 1.2f;
	rpropDecreaseFactor = 0.5f;
	rpropDeltaMin = 0.0f;
	rpropDeltaMax = 50.0f;
	rpropDeltaZero = 0.0001f;
}

bool NNStrategyBackPropagation::isTrainingBatchRProp()
{
	return( trainingAlgorithm == FANN_TRAIN_RPROP );
}

void NNStrategyBackPropagation::setRPropFactor( float increaseFactor , float decreaseFactor )
{
	rpropIncreaseFactor = increaseFactor;
	rpropDecreaseFactor = decreaseFactor;
}

void NNStrategyBackPropagation::setRPropDelta( float deltaMin , float deltaMax , float deltaZero , float deltaZeroMin )
{
	rpropDeltaMin = deltaMin;
	rpropDeltaMax = deltaMax;
	rpropDeltaZero = deltaZero;
	rpropDeltaZeroMin = deltaZeroMin;
}

void NNStrategyBackPropagation::setQuickPropDecay( float decay )
{
	quickPropDecay = decay;
}

void NNStrategyBackPropagation::setQuickPropMu( float mu )
{
	quickPropMu = mu;
}

void NNStrategyBackPropagation::setQuickPropMinStep( float minStep )
{
	quickPropMinStep = minStep;
}

void NNStrategyBackPropagation::setTrainingBatchQuickProp()
{
	trainingAlgorithm = FANN_TRAIN_QUICKPROP;
	initBatch();
}

void NNStrategyBackPropagation::initBatch()
{
}

int NNStrategyBackPropagation::getEpochCount()
{
	return( epochCount );
}

// set strategy properties
void NNStrategyBackPropagation::setSmoothLearning( bool p_smooth )
{
	smooth = p_smooth;
}

void NNStrategyBackPropagation::setGradientRate( float p_value )
{
	nuFixed = p_value;
}

void NNStrategyBackPropagation::setSmoothRate( float p_value )
{
	mu = p_value;
}

bool NNStrategyBackPropagation::getSmooth()
{
	return( smooth );
}

float NNStrategyBackPropagation::getGradientRate()
{
	return( nuFixed );
}

float NNStrategyBackPropagation::getSmoothRate()
{
	return( mu );
}

NNStrategyBackPropagation::NeuronData *NNStrategyBackPropagation::getNeuronData( NNNeuron *pn )
{
	return( neuronData.get( pn ) );
}

NNStrategyBackPropagation::ConnectionData *NNStrategyBackPropagation::getConnectionData( NNConnection *ic )
{
	return( connectionData.get( ic ) );
}

void NNStrategyBackPropagation::attach( NN *p_p )
{
	initialize( p_p );
}

// learn functions
void NNStrategyBackPropagation::initialize( NN *p_p )
{
	NNStrategy::attach( p_p );

	// create arrays
	neuronData.allocate( p -> getNNeurons() );
	connectionData.allocate( p -> getNConnections() );
	for( int k = 0; k < p -> getNLayers(); k++ )
		{
			NNLayer *layer = p -> getLayer( k );

			// input connections
			for( int m = 0; m < layer -> getNeuronCount(); m++ )
				{
					// neuron data
					NNNeuron *pn = layer -> getNeuron( m );
					NeuronData *nd = neuronData.addCalloc( pn );
					
					// connections
					for( int z = 0; z < pn -> getNInputs(); z++ )
						{
							NNConnection *ic = pn -> getInputData( z );
							ConnectionData *wd = connectionData.addCalloc( ic );
							wd -> nd = nd;
							wd -> weightPtr = &ic -> weight;
						}
				}
		}
}

NNSamples *NNStrategyBackPropagation::getSamples()
{
	return( execSamples );
}

bool NNStrategyBackPropagation::learn( NNSamples *p_samples , NNWeights *pwBest , float *pvar )
{
	execSamples = p_samples;

	NNErrorFunction *ef = NNStrategy::getErrorFunction();
	NNStopFunction *sf = NNStrategy::getStopFunction();

	sf -> setModeMany( p_samples );

	// prepare internals
	clearDataBeforeLearn();

	// learn new samples
	bool res = false;
	for( epochCount = 0;; )
		{
			bool checkStop = sf -> stopConditionFound( epochCount + 1 , &res );
			helper.showSamplesActual( String( "Actual sample values: epoch #" ) + epochCount , p_samples );

			// cancel cycle if stop condition found
			if( checkStop )
				{
					if( pvar != NULL )
						*pvar = sf -> getCurrentErrorValue();
					break;
				}

			epochCount++;
			float variance;
			helper.showPerceptron( String( "before doEpoch: iteration=" ) + epochCount );
			res = doEpoch( p_samples , &variance );

			// check if epoch failed
			if( !res )
				break;
		}

	logger.logInfo( String( "FINALLY - " ) + 
		( ( res )? "SUCCEEDED" : "FAILED" ) );
	helper.showPerceptron( "end of learn" );
	return( res );
}

bool NNStrategyBackPropagation::learn( NNSample *sample , NNWeights *pwBest , float *pvar )
{
	NNSamples xs( sample -> getNSensors() , sample -> getNTargets() );
	xs.add( sample );

	return( learn( &xs , pwBest , pvar ) );
}

/*#########################################################################*/
/*#########################################################################*/

bool NNStrategyBackPropagation::doEpoch( NNSamples *samples , float *pv )
{
	bool res = false;
	switch( trainingAlgorithm )
		{
			case FANN_TRAIN_INCREMENTAL : res = iterateSamplesOneByOne( samples , pv ); break;
			case FANN_TRAIN_BATCH : res = iterateSamplesSimpleBatch( samples , pv ); break;
			case FANN_TRAIN_RPROP : res = iterateSamplesRProp( samples , pv ); break;
			case FANN_TRAIN_QUICKPROP : res = iterateSamplesQuickProp( samples , pv ); break;
			default :
				throw RuntimeError( "unknown trainingAlgorithm" );
		}

	// helper.showPerceptronClasses2();

	// helper.showChanges( "changes after epoch" , this );
	return( res );
}

bool NNStrategyBackPropagation::iterateSamplesOneByOne( NNSamples *samples , float *pv )
{
	float learnMaxVariance = 0;
	bool res = false;
	NNErrorFunction *ef = NNStrategy::getErrorFunction();

	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );

			float precision;
			if( !iterateOneSample( sample , &precision ) )
				continue;

			res = true;
			if( precision > learnMaxVariance )
				learnMaxVariance = precision;
		}

	if( res )
		*pv = learnMaxVariance;

	return( res );
}

bool NNStrategyBackPropagation::iterateSamplesSimpleBatch( NNSamples *samples , float *pv )
{
	float learnMaxVariance = 0;
	bool res = false;
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			p -> setSensors( sample );

			// init/back propagate error signal
			updateDelta( sample );
			// helper.showDelta( this );

			updateSlopesBatch( sample , k == 0 );
		}

	res = updateWeightsSimpleBatch( samples , &learnMaxVariance );
	if( res )
		*pv = learnMaxVariance;

	return( res );
}

bool NNStrategyBackPropagation::iterateSamplesRProp( NNSamples *samples , float *pv )
{
	float learnMaxVariance = 0;
	bool res = false;
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			p -> setSensors( sample );

			// init/back propagate error signal
			updateDelta( sample );
			updateSlopesBatch( sample , k == 0 );
		}

	res = updateWeightsIRPropM( samples , &learnMaxVariance );
	if( res )
		*pv = learnMaxVariance;

	return( res );
}

bool NNStrategyBackPropagation::iterateSamplesQuickProp( NNSamples *samples , float *pv )
{
	float learnMaxVariance = 0;
	bool res = false;
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			p -> setSensors( sample );

			// init/back propagate error signal
			updateDelta( sample );
			updateSlopesBatch( sample , k == 0 );
		}

	helper.showDelta();
	res = updateWeightsQuickProp( samples , &learnMaxVariance );
	if( res )
		*pv = learnMaxVariance;

	return( res );
}

bool NNStrategyBackPropagation::iterateOneSample( NNSample *sample , float *variance )
{
	NNErrorFunction *ef = NNStrategy::getErrorFunction();

	// set input data
	float startError = ef -> getErrorSampleProgress( sample );

	// show initial state
	// helper.showPerceptron( "===>> BEFORE adjust weights" );

	// initialise delta
	updateDelta( sample );
	// helper.showDelta( this );

	// make change to fit sample, calculate new output
	float newError = 0;
	bool res = adjustWeights( sample );
	if( res )
		{	
			p -> execute();
			newError = ef -> getErrorSampleProgress( sample );
			*variance = newError;
		}

	// helper.showPerceptron( "===>> AFTER adjust weights" );

	return( res );
}

void NNStrategyBackPropagation::clearDataBeforeLearn()
{
	// clear slopes
	for( int k = 0; k < connectionData.count(); k++ )
		{
			ConnectionData *wd = connectionData.getClassByIndex( k );
			wd -> slope = 0;
			wd -> slopePrev = 0;

			// clear changes
			if( trainingAlgorithm == FANN_TRAIN_RPROP )
				wd -> change = rpropDeltaZero;
			else
				wd -> change = 0;
		}
}

void NNStrategyBackPropagation::updateSlopesBatch( NNSample *sample , bool init )
{
	// by layer
	for( int k = 0; k < p -> getNLayers(); k++ )
		{
			NNLayer *pl = p -> getLayer( k );
			for( int m = 0; m < pl -> getNeuronCount(); m++ )
				{
					NNNeuron *pn = pl -> getNeuron( m );
					NeuronData *nd = neuronData.get( pn );

					for( int z = 0; z < pn -> getNInputs(); z++ )
						{
							NNConnection *ic = pn -> getInputData( z );
							ConnectionData *wd = connectionData.get( ic );

							float input = *( ic -> inputPtr );
							wd -> slope += input * nd -> delta;
						}
				}
		}
}

bool NNStrategyBackPropagation::updateWeightsSimpleBatch( NNSamples *samples , float *learnMaxVariance )
{
	const float epsilon = nuFixed / samples -> count();

	// for all weights
	for( int k = 0; k < connectionData.count(); k++ )
		{
			ConnectionData *wd = connectionData.getClassByIndex( k );
			wd -> change = wd -> slope * epsilon;
			*wd -> weightPtr += wd -> change;
			wd -> slope = 0;
		}

	return( true );
}

bool NNStrategyBackPropagation::updateWeightsIRPropM( NNSamples *samples , float *learnMaxVariance )
{
	// for all weights
	for( int k = 0; k < connectionData.count(); k++ )
		{
			ConnectionData *wd = connectionData.getClassByIndex( k );
			doChangeWeightIRPropM( wd -> weightPtr , &wd -> change , &wd -> slopePrev , &wd -> slope );
		}

	return( true );
}

void NNStrategyBackPropagation::doChangeWeightIRPropM( float *pw , float *pChange , float *pSlopePrev , float *pSlope )
{
	float prevStep = *pChange;
	prevStep = getMax( prevStep , rpropDeltaZeroMin );
	float prevSlope = *pSlopePrev;
	float slope = *pSlope;

	// check sign
	float change;
	if( ( prevSlope >= 0 && slope >= 0 ) ||
		( prevSlope <= 0 && slope <= 0 ) )
		change = *pChange = getMin( prevStep * rpropIncreaseFactor , rpropDeltaMax );
	else
		{
			change = *pChange = getMax( prevStep * rpropDecreaseFactor , rpropDeltaMin );
			slope = 0;
		}

	// check slope
	float weight = *pw;
	if( slope < 0 )
		{
			weight -= change;
			if( weight < wLimitMin )
				weight = wLimitMin;
		}
	else
		{
			weight += change;
			if( weight > wLimitMax )
				weight = wLimitMax;
		}

	*pw = weight;
	*pSlopePrev = slope;
	*pSlope = 0;
}

void NNStrategyBackPropagation::doChangeWeightQuickProp( int numData , float *pw , float *pChange , float *pSlopePrev , float *pSlope )
{
	float weight = *pw;
	float prevStep = *pChange;
	float change = 0;

	float epsilon = nuFixed / numData;
	float shrinkFactor = quickPropMu / ( 1.0f + quickPropMu );

	float slope = *pSlope + quickPropDecay * weight;
	float slopePrev = *pSlopePrev;

	// The step must always be in direction opposite to the slope
	if( prevStep > quickPropMinStep )
		{
			// If last step was positive...
			// Add in linear term if current slope is still positive
			if( slope > 0 )
				change += epsilon * slope;

			// If current slope is close to or larger than prev slope...
			if( slope > shrinkFactor * slopePrev )
				change += quickPropMu * prevStep;	// Take maximum size negative step
			else
				change += prevStep * slope / ( slopePrev - slope );	// use quadratic estimate
		}
	else
	if( prevStep < -quickPropMinStep )
		{
			// If last step was negative...
			// Add in linear term if current slope is still negative
			if( slope < 0 )
				change += epsilon * slope;

			// If current slope is close to or more neg than prev slope...
			if( slope < shrinkFactor * slopePrev )
				change += quickPropMu * prevStep;	// Take maximum size negative step
			else
				change += prevStep * slope / ( slopePrev - slope );	// use quadratic estimate
		}
	else
		{
			// Last step was zero, so use only linear term
			change += epsilon * slope;
		}

	*pChange = change;

	weight += change;
	if( weight < wLimitMin )
		weight = wLimitMin;
	else
	if( weight > wLimitMax )
		weight = wLimitMax;

	*pw = weight;
	*pSlopePrev = slope;
	*pSlope = 0;
}

bool NNStrategyBackPropagation::updateWeightsQuickProp( NNSamples *samples , float *learnMaxVariance )
{
	int numData = samples -> count();

	// for all weights
	for( int k = 0; k < connectionData.count(); k++ )
		{
			ConnectionData *wd = connectionData.getClassByIndex( k );
			doChangeWeightQuickProp( numData , wd -> weightPtr , &wd -> change , &wd -> slopePrev , &wd -> slope );
		}

	return( true );
}

void NNStrategyBackPropagation::updateDelta( NNSample *sample )
{
	NNErrorFunction *ef = NNStrategy::getErrorFunction();

	// clear errors
	for( int z = neuronData.count() - 1; z >= 0; z-- )
		{
			NeuronData *nd = neuronData.getClassByIndex( z );
			nd -> errorSignal = nd -> delta = 0;
		}

	p -> updateBackRepresentation( sample -> getTargets() );
	for( int m = p -> getNLayers() - 1; m >= 0; m-- )
		{
			NNLayer *layer = p -> getLayer( m );
			bool lastLayer = ( p -> getLastLayer() == layer );

			for( int k = 0; k < layer -> getNonBiasNeuronCount(); k++ )
				{
					NNNeuron *pn = layer -> getNeuron( k );
					NeuronData *nd = neuronData.get( pn );

					float derivative = pn -> getActivationDerivative();

					// init errors on final layer
					if( lastLayer )
						{
							float error = ef -> getErrorSignalForBP( k );
							nd -> errorSignal = error;
						}

					// create input error from output
					float delta = nd -> errorSignal * derivative;
					nd -> delta = delta;

					// walk connections
					NNInductionFunction *ifn = pn -> getInductionFunction();
					float s = *pn -> getS();

					for( int z = 0; z < pn -> getNInputs(); z++ )
						{
							NNConnection *ic = pn -> getInputData()[ z ];
							NNNeuron *pnPrev = ic -> sourceNeuron;
							if( pnPrev == NULL )
								continue;

							NeuronData *ndPrev = neuronData.get( pnPrev );
							float connectionDerivative = ifn -> getDerivative( s , ic );

							float error = delta * connectionDerivative;
							ndPrev -> errorSignal += error;
						}
				}
		}
}

bool NNStrategyBackPropagation::adjustWeights( NNSample *sample )
{
	// for all weights
	bool hasChange = false;
	for( int k = 0; k < connectionData.count(); k++ )
		{
			NNConnection *ic = connectionData.getKeyByIndex( k );
			ConnectionData *wd = connectionData.getClassByIndex( k );

			float errorSignalCurrent = wd -> nd -> errorSignal;
			float inputValue = *( ic -> inputPtr );
			float previousChange = wd -> change;
			float deltaCurrent = wd -> nd -> delta;

			float change;
			if( smooth )
				change = mu * deltaCurrent * inputValue + ( 1 - mu ) * previousChange;
			else
				change = nuFixed * deltaCurrent * inputValue;

			// check weight limits
			float weightCurrent = ic -> weight;
			float changeUsed = change;
			if( compareFloats( change , 0 ) != 0 )
				{
					if( weightCurrent + change < wLimitMin )
						changeUsed = wLimitMin - weightCurrent;
					else
					if( weightCurrent + change > wLimitMax )
						changeUsed = wLimitMax - weightCurrent;
					hasChange = true;
				}

			wd -> change = changeUsed;
			ic -> weight += changeUsed;
		}

	return( hasChange );
}

float NNStrategyBackPropagation::updateFromLayer( NNSample *sample , NNLayer *layer )
{
	// calculate outputs up to last layer, correct delta
	p -> executeFromLayer( layer );
	updateDelta( sample );

	// estimate difference from target
	NNErrorFunction *ef = NNStrategy::getErrorFunction();
	float var = ef -> getErrorSampleProgress( sample );

	return( var );
}

void NNStrategyBackPropagation::applyChanges()
{
	// for all weights
	for( int k = 0; k < connectionData.count(); k++ )
		{
			ConnectionData *wd = connectionData.getClassByIndex( k );
			*wd -> weightPtr += wd -> change;
		}
}

void NNStrategyBackPropagation::rollbackChanges()
{
	// for all weights
	for( int k = 0; k < connectionData.count(); k++ )
		{
			ConnectionData *wd = connectionData.getClassByIndex( k );
			*wd -> weightPtr -= wd -> change;
		}
}

void NNStrategyBackPropagation::setWeightRange( float p_valueMin , float p_valueMax )
{
	wLimitMin = p_valueMin;
	wLimitMax = p_valueMax;
}

const char *NNStrategyBackPropagation::NAME = "NNStrategyBackPropagation";

void NNStrategyBackPropagation::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNStrategyBackPropagation::onCreate );

	so -> addFieldFloat( "nuFixed" );
	so -> addFieldFloat( "wLimitMin" );
	so -> addFieldFloat( "wLimitMax" );

	so -> addFieldInt( "trainingAlgorithm" );
	so -> addFieldBool( "smooth" );
	so -> addFieldFloat( "mu" );

	so -> addFieldFloat( "rpropIncreaseFactor" );
	so -> addFieldFloat( "rpropDecreaseFactor" );
	so -> addFieldFloat( "rpropDeltaMin" );
	so -> addFieldFloat( "rpropDeltaMax" );
	so -> addFieldFloat( "rpropDeltaZero" );
	so -> addFieldFloat( "rpropDeltaZeroMin" );

	so -> addFieldFloat( "quickPropDecay" );
	so -> addFieldFloat( "quickPropMu" );
	so -> addFieldFloat( "quickPropMinStep" );

	so -> addFieldObject( "stopFunction" , NNStopFunction::getSerializeObject() );
	so -> addFieldObject( "errorFunction" , NNErrorFunction::getSerializeObject() );
}

void NNStrategyBackPropagation::serialize( SerializeObject& so )
{
	so.setPropFloat( nuFixed , "nuFixed" );
	so.setPropFloat( wLimitMin , "wLimitMin" );
	so.setPropFloat( wLimitMax , "wLimitMax" );

	so.setPropInt( trainingAlgorithm , "trainingAlgorithm" );
	so.setPropBool( smooth , "smooth" );
	so.setPropFloat( mu , "mu" );

	so.setPropFloat( rpropIncreaseFactor , "rpropIncreaseFactor" );
	so.setPropFloat( rpropDecreaseFactor , "rpropDecreaseFactor" );
	so.setPropFloat( rpropDeltaMin , "rpropDeltaMin" );
	so.setPropFloat( rpropDeltaMax , "rpropDeltaMax" );
	so.setPropFloat( rpropDeltaZero , "rpropDeltaZero" );
	so.setPropFloat( rpropDeltaZeroMin , "rpropDeltaZeroMin" );

	so.setPropFloat( quickPropDecay , "quickPropDecay" );
	so.setPropFloat( quickPropMu , "quickPropMu" );
	so.setPropFloat( quickPropMinStep , "quickPropMinStep" );

	so.setPropObject( stopFunction , "stopFunction" );
	so.setPropObject( errorFunction , "errorFunction" );
}

void NNStrategyBackPropagation::deserialize( Object *parent , SerializeObject& so )
{
	nuFixed = so.getPropFloat( "nuFixed" );
	wLimitMin = so.getPropFloat( "wLimitMin" );
	wLimitMax = so.getPropFloat( "wLimitMax" );

	trainingAlgorithm = ( TrainingAlgorithm )so.getPropInt( "trainingAlgorithm" );
	smooth = so.getPropBool( "smooth" );
	mu = so.getPropFloat( "mu" );

	rpropIncreaseFactor = so.getPropFloat( "rpropIncreaseFactor" );
	rpropDecreaseFactor = so.getPropFloat( "rpropDecreaseFactor" );
	rpropDeltaMin = so.getPropFloat( "rpropDeltaMin" );
	rpropDeltaMax = so.getPropFloat( "rpropDeltaMax" );
	rpropDeltaZero = so.getPropFloat( "rpropDeltaZero" );
	rpropDeltaZeroMin = so.getPropFloat( "rpropDeltaZeroMin" );

	quickPropDecay = so.getPropFloat( "quickPropDecay" );
	quickPropMu = so.getPropFloat( "quickPropMu" );
	quickPropMinStep = so.getPropFloat( "quickPropMinStep" );

	NNErrorFunction *ef = ( NNErrorFunction * )so.getPropObject( "errorFunction" , false );
	errorFunction.set( ef );

	NNStopFunction *sf = ( NNStopFunction * )so.getPropObject( "stopFunction" , false );
	stopFunction.set( sf );
	stopFunction.setErrorFunction( &errorFunction );
}
