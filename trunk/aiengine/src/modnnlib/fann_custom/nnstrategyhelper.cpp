#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNStrategyHelper::NNStrategyHelper( Logger& p_logger )
:	engine( AIEngine::getInstance() ) ,
	logger( p_logger )
{
	p = NULL;
	st = NULL;
	ef = NULL;
	er = NULL;
	samplesLearn = NULL;
	samplesValidate = NULL;
}

void NNStrategyHelper::attach( NN *p_p )
{
	p = p_p;
}

void NNStrategyHelper::attach( NNStrategy *p_st )
{
	st = p_st;
}

void NNStrategyHelper::attach( NNFinder *p_ef )
{
	ef = p_ef;
}

void NNStrategyHelper::attach( NNRegression *p_er )
{
	er = p_er;
}

void NNStrategyHelper::attachSamples( NNSamples *p_samplesLearn , NNSamples *p_samplesValidate )
{
	samplesLearn = p_samplesLearn;
	samplesValidate = p_samplesValidate;
}

void NNStrategyHelper::showPerceptron( const char *preface )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "-------------------------------------" );
	logger.logInfo( String( preface ) + " - P#" + p -> getId() + 
		": nSensors=" + p -> getNSensors() +
		", nInputs=" + p -> getNInputs() +
		", nOutputs=" + p -> getNOutputs() +
		", nTargets=" + p -> getNTargets() );

	// show parts
	showSensors();
	showInputs();

	// show layers
	for( int k = 0; k < p -> getNLayers(); k++ )
		{
			NNLayer *layer = p -> getLayer( k );

			logger.logInfo( "-------------------------------------" );
			logger.logInfo( String( "Layer " ) + k + ":" );
			showLayer( layer );
		}

	showOutputs();
	showTargets();
	logger.logInfo( "-------------------------------------" );
}

void NNStrategyHelper::showSensors()
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "Sensors:" );
	for( int k = 0; k < p -> getNSensors(); k++ )
		{
			NNVariable::Mapping *vm = p -> getSensor( k );
			logger.logInfo( String( "s" ) + k + ": " + getVariable( vm , true ) );
		}
}

void NNStrategyHelper::showInputs()
{
	if( !logger.isLogAll() )
		return;

	// show inputs
	String s;
	const float * const *inputValues = p -> getInputs();
	for( int m = 0; m < p -> getNInputs(); m++ )
		{
			if( m > 0 )
				 s += ", ";
			s += String( "i" ) + m + "=" + *( inputValues[ m ] );
		}

	logger.logInfo( "Inputs: " + s );
}

void NNStrategyHelper::showOutputs()
{
	if( !logger.isLogAll() )
		return;

	// show inputs
	const float * const *outputValues = p -> getOutputs();
	String s;
	for( int m = 0; m < p -> getNInputs(); m++ )
		{
			if( m > 0 )
				 s += ", ";
			s += String( "o" ) + m + "=" + *( outputValues[ m ] );
		}
	logger.logInfo( "Outputs: " + s );
}

void NNStrategyHelper::showTargets()
{
	if( !logger.isLogAll() )
		return;

	// show inputs
	logger.logInfo( "Targets:" );
	for( int k = 0; k < p -> getNTargets(); k++ )
		{
			NNVariable::Mapping *vm = p -> getTarget( k );
			logger.logInfo( String( "t" ) + k + ": " + getVariable( vm , false ) );
		}
}

String NNStrategyHelper::getVariable( NNVariable::Mapping *vm , bool isSensor )
{
	NNVariable *nv = vm -> var;
	switch( nv -> getType() )
		{
			case NNVariable::VarSimple :
				{
					NNVariableSimple *nvs = ( NNVariableSimple * )nv;
					Scale& scale = nvs -> getScale();
					String s;
					if( isSensor )
						if( scale.getDoScale() )
							s = String( "sensor/input scale [" ) + scale.getToMin() +
								", " + scale.getToMax() + 
								"] -> [" + scale.getFromMin() + 
								", " + scale.getFromMax() + "]";
						else
							s = "[sensor=input]";
					else
						if( scale.getDoScale() )
							s = String( "output/target scale [" ) + scale.getFromMin() +
								", " + scale.getFromMax() + 
								"] -> [" + scale.getToMin() + 
								", " + scale.getToMax() + "]";
						else
							s = "[output=target]";
					return( String( "var=" ) + nv -> getValue() + ": " + s );
				}
				break;
			case NNVariable::VarCategory :
				{
					NNVariableCategory *nvc = ( NNVariableCategory * )nv;
					return( String( "var=" ) + nv -> getValue() + ": categories=1-" + nvc -> getCategoryCount() );
				}
				break;
			default:
				return( "UNKNOWN VARIABLE TYPE" );
		}
}

String NNStrategyHelper::getCategoryVariableValues( NNVariableCategory::Mapping *vm )
{
	String s;
	int n = vm -> objs.var -> getRepresentationSize();
	FlatList<float *> *pv = vm -> pv;
	FlatList<float *> *pvBack = vm -> pvBack;
	for( int k = 0; k < n; k++ )
		{
			float actual = *( pv -> get( k ) );
			float expected = *( pvBack -> get( k ) );

			if( k > 0 )
				s += ",";
			s += actual;
			s += "(";
			s += expected;
			s += ")";
		}
	return( s );
}

void NNStrategyHelper::showPerceptronClasses2()
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "-------------------------------------" );
	logger.logInfo( "PERCEPTRON CLASSES (2 sensors)" );

	NNVariableSimple *nv0 = ( NNVariableSimple * )p -> getSensorVariable( 0 );
	NNVariableSimple *nv1 = ( NNVariableSimple * )p -> getSensorVariable( 1 );
	int nXAxis = 20;
	float stepXAxis = nv0 -> getScale().getFromRange() / nXAxis;
	int nYAxis = 20;
	float stepYAxis = nv1 -> getScale().getFromRange() / nYAxis;

	float s[ 2 ];
	float xFrom = nv0 -> getScale().getFromMin();
	float yFrom = nv1 -> getScale().getFromMin();
	for( int kx = 0; kx <= nXAxis; kx++ )
		{
			s[ 0 ] = xFrom + kx * stepXAxis;

			char l_buf[ 10 ];
			sprintf( l_buf , "%5.2f" , s[ 0 ] );
			String slog = String( "x=" ) + l_buf + ": ";
			String xlogT = " ";
			String xlogV = " ";
			for( int ky = 0; ky <= nYAxis; ky++ )
				{
					s[ 1 ] = yFrom + ky * stepYAxis;

					int classID;
					float probability;
					bool res = ef -> findClass( s , &classID , &probability );
					char c = ( probability > 0.8 )? '-' : '?';
					if( res )
						if( probability >= 0.8 )
							c = 'A' + classID - 1;
						else
							c = 'a' + classID - 1;

					slog += c;

					char vT;
					char vV;
					bool check1 = checkPointSymbol2( samplesLearn , s[ 0 ] , s[ 1 ] , stepXAxis , stepYAxis , vT );
					xlogT += ( check1 )? vT : '-';

					bool check2 = checkPointSymbol2( samplesValidate , s[ 0 ] , s[ 1 ] , stepXAxis , stepYAxis , vV );
					xlogV += ( check2 )? vV : '-';
				}
			logger.logInfo( slog + xlogT + xlogV );
		}
}

void NNStrategyHelper::showChanges( const char *preface , NNStrategyBackPropagation *bp )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "-------------------------------------" );
	logger.logInfo( String( preface ) + " - P#" + p -> getId() + 
		": nInputs=" + p -> getNSensors() +
		", nOutputs=" + p -> getNOutputs() );

	// show layers
	for( int k = 0; k < p -> getNLayers(); k++ )
		{
			NNLayer *layer = p -> getLayer( k );

			logger.logInfo( "-------------------------------------" );
			logger.logInfo( String( "Layer " ) + k + ":" );

			// show layer changes
			showLayerChanges( bp , layer );
		}
}

void NNStrategyHelper::showDelta()
{
	if( !logger.isLogAll() )
		return;

	 NNStrategyBackPropagation *bp =  ( NNStrategyBackPropagation * )st;
	for( int k = 0; k < p -> getNLayers(); k++ )
		{
			NNLayer *pl = p -> getLayer( k );
			logger.logInfo( String( "Layer " ) + k + ":" );

			for( int m = 0; m < pl -> getNonBiasNeuronCount(); m++ )
				{
					NNNeuron *pn = pl -> getNeuron( m );
					NNStrategyBackPropagation::NeuronData *nd = bp -> getNeuronData( pn );
					logger.logInfo( String( "o" ) + m + ": error=" + nd -> errorSignal + ", delta=" + nd -> delta );
				}
		}
}

void NNStrategyHelper::evaluateHistoryImpactBP( NNSamples *samples , NNLayer *layer , int p_output )
{
	if( !logger.isLogAll() )
		return;

	// for each history item except learned
	logger.logInfo( "====================================================" );
	char l_buf[ 1024 ];
	sprintf( l_buf , "HISTORY IMPACT for output %d:" , p_output );
	logger.logInfo( l_buf );

	// show changes for samples
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			evaluateSampleImpactBP( sample , layer , p_output );
		}
}

String NNStrategyHelper::getChangeStringBP( NNLayer *layer , int p_neuron )
{
	NNStrategyBackPropagation *strategy = ( NNStrategyBackPropagation * )st;
	NNNeuron *pn = layer -> getNeuron( p_neuron );

	String l_changes = String( "dW=" );
	for( int k = 0; k < pn -> getNInputs(); k++ )
		{
			NNConnection *ic = pn -> getInputData( k );
			NNStrategyBackPropagation::ConnectionData *wd = strategy -> getConnectionData( ic );

			if( k > 0 )
				l_changes += " ";
			float change = wd -> change;
			l_changes += change;
		}
			
	return( l_changes );
}

void NNStrategyHelper::evaluateSampleImpactBP( NNSample *sample , NNLayer *layer , int p_output )
{
	if( !logger.isLogAll() )
		return;

	NNStrategyBackPropagation *strategy = ( NNStrategyBackPropagation * )st;

	// before change
	float s0 = *layer -> getS( p_output );
	NNErrorFunction *ef = strategy -> getErrorFunction();
	float v0 = ef -> getErrorSampleProgress( sample );

	String l_changes = getChangeStringBP( layer , p_output );

	// do change
	strategy -> applyChanges();
	p -> execute();

	// evaluate change
	float sUsed = *layer -> getS( p_output );
	float vUsed = ef -> getErrorSampleProgress( sample );

	// show new state
	logger.logInfo( String( "SAMPLE " ) + sample -> getId() +
		": s=" + s0 + " v=" + v0 + " -> s=" + sUsed + " v=" + vUsed + 
		" (" + l_changes + ")" );

	// restore weights
	strategy -> rollbackChanges();
}

float NNStrategyHelper::getMaxHistoryVariance( NNSamples *samples )
{
	float maxVariance = 0;
	NNErrorFunction *ef = st -> getErrorFunction();
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			p -> setSensors( sample );

			float variance = ef -> getErrorSampleProgress( sample );
			if( variance > maxVariance )
				maxVariance = variance;
		}

	return( maxVariance );
}

void NNStrategyHelper::showHistoryImpact( NNSamples *samples )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "IMPACT FOR SAMPLES:" );
	float maxVariance = 0;

	NNErrorFunction *ef = st -> getErrorFunction();
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			float varianceOld = sample -> getError();

			p -> setSensors( sample );
			float variance = ef -> getErrorSampleProgress( sample );

			if( variance > maxVariance )
				maxVariance = variance;

			logger.logInfo( String( "SAMPLE " ) + k + ": new variance=" + variance + 
				", old variance=" + varianceOld + ", " + ( ( variance <= varianceOld )? "GOOD" : "BAD" ) );
		}

	logger.logInfo( String( "MAX VARIANCE=" ) + maxVariance );
}

void NNStrategyHelper::calculateVarianceAndDelta( NNLayer *layer , NNSample *sample , float *s , float *v , float *dVdS )
{
	NNErrorFunction *ef = st -> getErrorFunction();

	// calculate variance
	p -> executeFromLayerWithoutS( layer );
	float variance = ef -> getErrorForBP( sample );

	// calculate derivative
	float derDiff = fabs( *s / 10000 );
	*s += derDiff;
	p -> executeFromLayerWithoutS( layer );

	float derVariance = ef -> getErrorForBP( sample );
	float derivative = ( derVariance - variance ) / derDiff;

	*v = variance;
	*dVdS = derivative;
}

void NNStrategyHelper::showSamplesVariance( NNSamples *samples )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "SAMPLE VARIANCES:" );

	for( int s = 0; s < samples -> count(); s++ )
		{
			NNSample *sample = samples -> getByPos( s );
			p -> setSensors( sample );
			logger.logInfo( String( "#" ) + sample -> getId() + ": lastVariance=" + sample -> getError() );
		}
}

void NNStrategyHelper::showSamplesVariance( NNSamples *samples , NNWeights *pw )
{
	if( !logger.isLogAll() )
		return;

	pw -> setToPerceptron();

	logger.logInfo( "SAMPLE VARIANCES: " );
	
	NNErrorFunction *ef = st -> getErrorFunction();
	for( int s = 0; s < samples -> count(); s++ )
		{
			NNSample *sample = samples -> getByPos( s );
			p -> setSensors( sample );
			float sampleError = ef -> getErrorSampleProgress( sample );

			logger.logInfo( String( "#" ) + sample -> getId() +
				": variance=" + sampleError );
		}
}

void NNStrategyHelper::showFunction( NNActivationFunction *f )
{
	if( !logger.isLogAll() )
		return;

	Scale *is = f -> getInputScale();
	Scale *os = f -> getOutputScale();

	String inputScale;
	if( f -> getNoScaleInput() )
		inputScale = "[input as is]";
	else
		inputScale = String( "[" ) + 
			is -> getFromMin() + ", " + is -> getFromMax() + "] -> [" +
			is -> getToMin() + ", " + is -> getToMax() + "]";

	String outputScale;
	if( f -> getNoScaleOutput() )
		outputScale = "[output as is]";
	else
		outputScale = String( "[" ) + 
			os -> getFromMin() + ", " + os -> getFromMax() + "] -> [" +
			os -> getToMin() + ", " + os -> getToMax() + "]";

	logger.logInfo( String( f -> getName() ) + ": " +
		inputScale + " => F => " + outputScale );
}

void NNStrategyHelper::showLayer( NNLayer *layer )
{
	if( !logger.isLogAll() )
		return;

	// weights
	for( int k = 0; k < layer -> getNeuronCount(); k++ )
		showNeuron( layer , k );
}

void NNStrategyHelper::showNeuron( NNLayer *layer , int p_neuron )
{
	if( !logger.isLogAll() )
		return;

	NNNeuron *pn = layer -> getNeuron( p_neuron );

	// function
	showFunction( pn -> getActivationFunction() );

	String l_p = String( "o" ) + p_neuron + ": [s=" + (*pn -> getS()) + ", output=" + pn -> getOutput() + "]";
	for( int m = 0; m < pn -> getNInputs(); m++ )
		{
			NNConnection *ic = pn -> getInputData( m );
			l_p += String( ", w" ) + m + "=" + ic -> weight;
		}

	logger.logInfo( l_p );
}

void NNStrategyHelper::showLayerChanges( NNStrategyBackPropagation *bp , NNLayer *layer )
{
	if( !logger.isLogAll() )
		return;

	// weights
	for( int k = 0; k < layer -> getNeuronCount(); k++ )
		{
			NNNeuron *pn = layer -> getNeuron( k );
			String l_p = String( "o" ) + k + ": ";

			for( int m = 0; m < pn -> getNInputs(); m++ )
				{
					NNConnection *ic = pn -> getInputData( m );
					NNStrategyBackPropagation::ConnectionData *wd = bp -> getConnectionData( ic );

					if( m > 0 )
						l_p += ", ";
					l_p += String( "dw" ) + m + "=" + wd -> change;

					if( bp -> isTrainingBatchRProp() )
						l_p += String( " (slope=" ) + wd -> slope + ")";
				}

			logger.logInfo( l_p );
		}
}

void NNStrategyHelper::showSamples( const char *prefix , NNSamples *samples )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( prefix );
	for( int k = 0; k < samples -> count(); k++ )
		showSample( samples -> getByPos( k ) );
}

void NNStrategyHelper::showSamplesActual( const char *prefix , NNSamples *samples )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( prefix );
	for( int k = 0; k < samples -> count(); k++ )
		showSampleActual( samples -> getByPos( k ) );
}

void NNStrategyHelper::showValidateFailedSamples( NNSamples *samples )
{
	if( !logger.isLogAll() )
		return;

	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			if( !sample -> isValidateFailed() )
				continue;

			logger.logInfo( "VALIDATE FAILED FOR SAMPLE:" );
			showSample( sample );
		}

	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			if( !sample -> isValidateFailed() )
				continue;

			p -> setSensors( sample );
			showPerceptron( String( "PERCEPTRON STATE FOR SAMPLE #" ) + sample -> getId() );
		}
}

void NNStrategyHelper::showSample( NNSample *sample )
{
	if( !logger.isLogAll() )
		return;

	String sensorsS;
	const float *sensors = sample -> getSensors();
	for( int k = 0; k < sample -> getNSensors(); k++ )
		{
			if( k > 0 )
				sensorsS += ", ";
			sensorsS += sensors[ k ];
		}

	String targetsS;
	const float *targets = sample -> getTargets();
	for( int k = 0; k < sample -> getNTargets(); k++ )
		{
			if( k > 0 )
				targetsS += ", ";
			targetsS += targets[ k ];
		}

	if( sample -> isValidateFailed() )
		targetsS += String( " (validate failed: error=" ) + sample -> getValidateError() + ")";

	logger.logInfo( String( "SAMPLE #" ) + sample -> getId() + 
		": f( " + sensorsS + " ) = " + targetsS );
}

void NNStrategyHelper::showSampleActual( NNSample *sample )
{
	if( !logger.isLogAll() )
		return;

	String sensorsS;
	const float *sensors = sample -> getSensors();
	for( int k = 0; k < sample -> getNSensors(); k++ )
		{
			if( k > 0 )
				sensorsS += ", ";
			sensorsS += sensors[ k ];
		}

	p -> setSensors( sample );
	p -> updateBackRepresentation( sample -> getTargets() );

	String targetsSP;
	const float *targets = sample -> getTargets();
	for( int k = 0; k < sample -> getNTargets(); k++ )
		{
			if( k > 0 )
				targetsSP += ", ";
			targetsSP += targets[ k ];
		}

	String targetsSA;
	ASSERT( p -> getNTargets() == sample -> getNTargets() );
	for( int k = 0; k < p -> getNTargets(); k++ )
		{
			if( k > 0 )
				targetsSA += ", ";
			NNVariable *nv = p -> getTargetVariable( k );

			float value = nv -> getValue();
			targetsSA += value;

			if( nv -> getType() == NNVariable::VarCategory )
				{
					NNVariable::Mapping *vm = p -> getTarget( k );
					targetsSA += String( "=[" ) + getCategoryVariableValues( ( NNVariableCategory::Mapping * )vm ) + "]";
				}
		}

	NNStopFunction *sf = st -> getStopFunction();
	float error = sf -> calculateErrorValue();

	logger.logInfo( String( "SAMPLE #" ) + sample -> getId() + 
		": f( " + sensorsS + " ) = ( " + targetsSP + " )" +
		", actual=( " + targetsSA + " )" +
		" - error=" + error );
}

void NNStrategyHelper::showScanPoint( int id , NNScanPoint *ps , ClassList<NNStrategyScanItem>& randomValues )
{
	if( !logger.isLogAll() )
		return;

	NNWeights *pw = ps -> getWeights();

	String s = String( "point " ) + id + ": ";
	for( int k = 0; k < randomValues.count(); k++ )
		{
			if( k > 0 )
				s += ", ";

			NNStrategyScanItem *item = randomValues.get( k );
			s += item -> index;
			s += "=";
			s += pw -> getVarValue( item -> index );
		}
	s += " - variance=";
	s += ps -> getVariance();
	logger.logInfo( s );
}

/*#########################################################################*/
/*#########################################################################*/

void NNStrategyHelper::onStartLearnSample( NNSample *sample )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "-> onStartLearnSample" );

	if( sample == NULL )
		return;

	logger.logInfo( "" );
	logger.logInfo( "NEW SAMPLE:" );
	logger.logInfo( "======================================================" );
	showSample( sample );
}

void NNStrategyHelper::onStartIterateOneSample( NNSample *sample , float startError )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "-> onStartLearnSampleOne" );


	logger.logInfo( "" );
	logger.logInfo( "==================================================" );

	String msg = String( "START LEARN SAMPLE " ) + sample -> getId();
	showSample( sample );
	showPerceptron( "INITIAL NET STATE:" );

	logger.logInfo( String( "INITIAL NORMALIZED ERROR: " ) + startError );
	logger.logInfo( "==================================================" );
}

void NNStrategyHelper::onStopIterateOneSample( bool hasChanges , NNSample *sample , float oldError , float newError )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "-> onStopLearnSampleOne" );
	if( hasChanges )
		logger.logInfo( String( "SAMPLE #" ) + sample -> getId() + " LEARN RESULT: " + oldError + " -> " + newError );
	else
		logger.logInfo( String( "SAMPLE #" ) + sample -> getId() + " LEARN RESULT: no changes" );

	showPerceptron( "state" );
}

void NNStrategyHelper::showAxisError( int *axisIndex , float *axisErrorData , int nVars )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "axis sorted by error:" );
	for( int k = 0; k < nVars; k++ )
		logger.logInfo( String( "#" ) + k + "; AXIS " + axisIndex[ k ] + " - " + axisErrorData[ axisIndex[ k ] ] );
}

void NNStrategyHelper::showIndexes( MultiIndexIterator& mi , float error )
{
	if( !logger.isLogAll() )
		return;

	String s = "showIndexes:";
	for( int k = 0; k < mi.getNumberOfAxis(); k++ )
		{
			s += " ";
			s += mi.getAxisIndex( k );
		}
	s += ", error=";
	s += error;
	s += ", index=";
	s += mi.getGlobalIndex();
	logger.logInfo( s );
}

void NNStrategyHelper::showIndexesAround( MultiIndexIterator& mi , float error )
{
	if( !logger.isLogAll() )
		return;

	String s = "showIndexesAround:";
	for( int k = 0; k < mi.getNumberOfAxis(); k++ )
		{
			s += " ";
			s += mi.getAxisIndexAround( k );
		}
	s += ", error=";
	s += error;
	s += ", index=";
	s += mi.getGlobalIndexAround();
	logger.logInfo( s );
}

void NNStrategyHelper::showWeights( NNWeights *pw )
{
	if( !logger.isLogAll() )
		return;

	String s = "VARS: ";

	float *w = pw -> getData();
	for( int k = 0; k < pw -> getNVars(); k++ )
		{
			if( k > 0 )
				s += ", ";
			s += k;
			s += "w=";
			s += w[ k ];
		}

	logger.logInfo( s );
}

void NNStrategyHelper::showScanPoint( int id , NNScanPoint *ps )
{
	if( !logger.isLogAll() )
		return;

	NNWeights *pw = ps -> getWeights();

	logger.logInfo( "VARS:" );
	
	String s = "ID=";
	s += id;
	s += ", ERROR=";
	s += ps -> getVariance();
	s += ": ";

	float *w = pw -> getData();
	for( int k = 0; k < pw -> getNVars(); k++ )
		{
			if( k > 0 )
				s += ", ";
			s += k;
			s += "w=";
			s += w[ k ];
		}

	logger.logInfo( s );
}

void NNStrategyHelper::showScanIteration( NNSamples *samples , NNWeights *sp , ClassList<NNScanPoint> *best , ClassList<NNStrategyScanItem>& axisValues , int countRuns , int minPoints , int bestChanges , float wChangeLimit )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "===========" );
	logger.logInfo( "NNStrategyHelper::showScanIteration:" );

	// search results
	NNScanPoint *psFirst = best -> first();
	NNScanPoint *psLast = best -> last();

	String s;
	for( int k = 0; k < axisValues.count(); k++ )
		{
			NNStrategyScanItem *item = axisValues.get( k );
			if( k > 0 )
				s += ", ";
			s += item -> index;
		}
	logger.logInfo( "SEARCH:" );
	showWeights( sp );
	logger.logInfo( String( "runs=" ) + countRuns +
		", minPoints=" + minPoints +
		", changes=" + bestChanges +
		", changeLimit=" + wChangeLimit +
		", searchItems={" + s + "} of " + sp -> getNVars() +
		", best first error=" + psFirst -> getVariance() +
		", best last error=" + psLast -> getVariance() );

	// show best
	for( int b = 0; b < best -> count(); b++ )
		{
			NNScanPoint *ps = best -> get( b );
			showScanPoint( b , ps , axisValues );
			showSamplesVariance( samples , ps -> getWeights() );
		}
	logger.logInfo( "===========" );
}

void NNStrategyHelper::showBestPoints( ClassList<NNScanPoint> *best )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "===========" );
	logger.logInfo( "NNStrategyHelper::showBestPoints:" );
	for( int b = 0; b < best -> count(); b++ )
		{
			NNScanPoint *ps = best -> get( b );
			showScanPoint( b , ps );
		}
	logger.logInfo( "===========" );
}

void NNStrategyHelper::showScanSlices( ClassList<NNStrategyScanItem>& axes , float *data , int axisItems , int pointsToCheck )
{
	if( !logger.isLogAll() )
		return;

	logger.logInfo( "===========" );
	logger.logInfo( "NNStrategyHelper::showScanSlices:" );

	MultiIndexIterator mi( axisItems - 2 , pointsToCheck );
	mi.start();
	while( mi.next() )
		{
			showIndexes( mi , 0 );

			int fieldNumber = mi.getGlobalIndex();
			int total = pointsToCheck * pointsToCheck;
			float *pf = data + fieldNumber * total;

			// find error range
			float errorMin = 0;
			float errorMax = 0;
			errorMin = errorMax = *pf;
			for( int k = 1; k < total; k++ )
				if( pf[ k ] < errorMin )
					errorMin = pf[ k ];
				else
				if( pf[ k ] > errorMax )
					errorMax = pf[ k ];

			// show slice
			logger.logInfo( String( "SLICE #" ) + fieldNumber +
				": errorMin(0)=" + errorMin + ", errorMax(9)=" + errorMax );
			
			float delta = errorMax - errorMin;
			if( delta <= 0 )
				{
					logger.logInfo( String( "SLICE #" ) + fieldNumber +
						": all error values are the same - " + errorMin );
					continue;
				}

			for( int k1 = 0; k1 < pointsToCheck; k1++ )
				{
					String s = ":";
					for( int k2 = 0; k2 < pointsToCheck; k2++ )
						{
							float v = *pf++;
							int pp = 0;
							if( v > errorMin )
								{
									pp = 1 + ( int )( 9 * ( v - errorMin ) / delta );
									if( pp >= 10 )
										pp = 9;
								}
							s += ( char )( '0' + pp );
						}
					logger.logInfo( s );
				}
		}

	logger.logInfo( "===========" );
}

void NNStrategyHelper::onCheckGlobalMinBySubset( int point , MultiIndexIterator& mi , bool beyond , float error , float errorMin , int countChecked , bool final , int *axisIndex , int startIndexPos )
{
	if( !logger.isLogAll() )
		return;

	showIndexes( mi , ( beyond )? 0 : 1 );

	if( !final )
		return;

	String sIndex = "";
	for( int k = 0; k < mi.getNumberOfAxis(); k++ )
		{
			if( k > 0 )
				sIndex += ", ";
			sIndex += axisIndex[ startIndexPos + k ];
		}

	String s = String( "POINT " ) + point + " - SUBSET " + sIndex + ": ";
	if( error < errorMin )
		s += String( "not a minimum - error=" ) + error + " found";
	else
		s += String( "MIN after " ) + countChecked + " iterations";

	logger.logInfo( s );
}

void NNStrategyHelper::onDoLearnScan( NNSamples *samples , int iterationsDone , int timePassed , int numberOfIterations , ClassList<NNStrategyScanIteration>& runByPrecision , NNScanPoint *spBest , bool loopDetected )
{
	if( !logger.isLogAll() )
		return;

	// get performance
	int rate = ( int )( ( iterationsDone * 1000.0f ) / timePassed );

	float bestError = spBest -> getVariance();
	logger.logInfo( String( "FIND: total " ) + iterationsDone + 
		" iterations, best error=" + bestError + 
		", timePassed=" + timePassed +
		", iterationsPerSecond=" + rate + 
		" (expected=" + numberOfIterations + ")" );

	// show final
	logger.logInfo( "FINAL STATE:" );
	if( loopDetected )
		logger.logInfo( "LOOP DETECTED" );

	NNWeights pwSave( p );
	pwSave.getFromPerceptron();

	NNWeights *pwBest = spBest -> getWeights();
	pwBest -> setToPerceptron();
	showPerceptron( "onDoLearnScan" );
	showSamplesVariance( samples , pwBest );

	// show other mins
	for( int k = 0; k < runByPrecision.count(); k++ )
		{
			NNStrategyScanIteration *run = runByPrecision[ k ];
			ClassList<NNScanPoint>& bestPoints = run -> getBestPoints();

			// show best points for given run
			logger.logInfo( "===================================" );
			for( int b = 0; b < bestPoints.count(); b++ )
				{
					NNScanPoint *point = bestPoints[ b ];
					logger.logInfo( String( "RUN searchArea=" ) + run -> getSearchArea() +
						": point=" + point -> getId() +
						", error=" + point -> getVariance() );
					showWeights( point -> getWeights() );
				}
		}

	pwSave.setToPerceptron();
}

bool NNStrategyHelper::checkPointSymbol2( NNSamples *samples , float s0 , float s1 , float stepXAxis , float stepYAxis , char& classID )
{
	float s0from = s0 - stepXAxis / 2;
	float s0to = s0 + stepXAxis / 2;

	float s1from = s1 - stepYAxis / 2;
	float s1to = s1 + stepYAxis / 2;

	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			float *sensors = sample -> getSensors();

			if( sensors[ 0 ] >= s0from && sensors[ 0 ] < s0to )
				if( sensors[ 1 ] >= s1from && sensors[ 1 ] < s1to )
					{
						if( sample -> getClusterID() > 0 )
							classID = 'A' + sample -> getClusterID() - 1;
						else
							classID = '0';
						return( true );
					}
		}
		
	return( false );
}

