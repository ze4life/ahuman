#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNStopFunction::NNStopFunction()
:	engine( AIEngine::getInstance() )
{
	p = NULL;
	functionType = FANN_STOPFUNC_EMPTY;
	execSamples = NULL;
	execSample = NULL;
	modeOne = false;
	desiredError = 0;
	bitFailLimit = 0;
	maxFailedNeurons = 0;
	minIterations = 0;
	maxIterations = 100;
	ef = NULL;
	currentError = 0;
}

NNStopFunction::~NNStopFunction()
{
}

void NNStopFunction::attach( NN *p_p )
{
	p = p_p;
}

NNStopFunction *NNStopFunction::newInit( NN *p_p , NNErrorFunction *p_ef )
{
	NNStopFunction *f = new NNStopFunction();
	f -> attach( p_p );
	f -> ef = p_ef;
	return( f );
}

void NNStopFunction::set( const NNStopFunction *p_p )
{
	ef = p_p -> ef;
	functionType = p_p -> functionType;
	currentError = 0;
	desiredError = p_p -> desiredError;
	bitFailLimit = p_p -> bitFailLimit;
	maxFailedNeurons = p_p -> maxFailedNeurons;
	minIterations = p_p -> minIterations;
	maxIterations = p_p -> maxIterations;
}

void NNStopFunction::setErrorFunction( NNErrorFunction *p_ef )
{
	ef = p_ef;
}

// stop modes
void NNStopFunction::setModeMSEOne( NNSample *sample , float p_desiredError )
{
	functionType = FANN_STOPFUNC_OUTPUTMSE;
	execSample = sample;
	execSamples = NULL;
	modeOne = true;
	desiredError = p_desiredError;

	bitFailLimit = 0;
	maxFailedNeurons = 0;
}

void NNStopFunction::setModeMSEMany( NNSamples *samples , float p_desiredError )
{
	functionType = FANN_STOPFUNC_OUTPUTMSE;
	execSample = NULL;
	execSamples = samples;
	modeOne = false;
	desiredError = p_desiredError;

	bitFailLimit = 0;
	maxFailedNeurons = 0;
}

void NNStopFunction::setModeMSE( float p_desiredError )
{
	functionType = FANN_STOPFUNC_OUTPUTMSE;
	desiredError = p_desiredError;

	bitFailLimit = 0;
	maxFailedNeurons = 0;
}

void NNStopFunction::setModeBitsOne( NNSample *sample , float p_bitFailLimit , int p_maxFailedNeurons )
{
	setModeBits( p_bitFailLimit , p_maxFailedNeurons );
	setModeOne( sample );
}

void NNStopFunction::setModeBitsMany( NNSamples *samples , float p_bitFailLimit , int p_maxFailedNeurons )
{
	setModeBits( p_bitFailLimit , p_maxFailedNeurons );
	setModeMany( samples );
}

void NNStopFunction::setModeBits( float p_bitFailLimit , int p_maxFailedNeurons )
{
	functionType = FANN_STOPFUNC_OUTPUTBIT;
	bitFailLimit = p_bitFailLimit;
	maxFailedNeurons = p_maxFailedNeurons;

	desiredError = 0;
}

void NNStopFunction::setModeOne( NNSample *sample )
{
	execSample = sample;
	execSamples = NULL;
	modeOne = true;
}

void NNStopFunction::setModeMany( NNSamples *samples )
{
	execSample = NULL;
	execSamples = samples;
	modeOne = false;
}

float NNStopFunction::getCurrentErrorValue()
{
	return( currentError );
}

// get function value
bool NNStopFunction::stopConditionFound( int epoch , bool *psuccess )
{
	if( epoch > maxIterations )
		{
			*psuccess = false;
			return( true );
		}

	*psuccess = true;
	if( epoch <= minIterations )
		return( false );

	ASSERT( execSample != NULL || execSamples != NULL );
	switch( functionType )
		{
			case FANN_STOPFUNC_OUTPUTMSE :	return( stopConditionFoundMSE() );
			case FANN_STOPFUNC_OUTPUTBIT :	return( stopConditionFoundBits() );
		}
	throw RuntimeError( "stop function not defined" );
}

float NNStopFunction::calculateErrorValue()
{
	switch( functionType )
		{
			case FANN_STOPFUNC_OUTPUTMSE :	return( calculateErrorValueMSE() );
			case FANN_STOPFUNC_OUTPUTBIT :	return( calculateErrorValueBits() );
		}
	throw RuntimeError( "stop function not defined" );
}

bool NNStopFunction::stopConditionFoundMSE()
{
	float mse = 0;
	if( modeOne )
		{
			mse = ef -> getErrorMSE( execSample );
			execSample -> setError(	mse );
		}
	else
		{
			for( int k = 0; k < execSamples -> count(); k++ )
				{
					execSample = execSamples -> getByPos( k );
					float mseOne = ef -> getErrorMSE( execSample );

					execSample -> setError(	mseOne );
					mse += mseOne;
				}
		}

	return( mse <= desiredError );
}

float NNStopFunction::calculateErrorValueMSE()
{
	return( ef -> getErrorMSE( execSample ) );
}

bool NNStopFunction::stopConditionFoundBits()
{
	// iterate samples
	currentError = 0;
	int bits = 0;
	if( modeOne )
		bits = calculateBits( execSample );
	else
		bits = calculateBits( execSamples );

	//engine.logInfo( String( "stopConditionFoundBits: bits=" ) + bits +
	//	", maxFailedNeurons=" + maxFailedNeurons );

	return( bits <= maxFailedNeurons );
}

int NNStopFunction::calculateBits( NNSamples *samples )
{
	int bits = 0;
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );

			int bitsSample = calculateBits( sample );
			bits += bitsSample;
		}

	return( bits );
}

int NNStopFunction::calculateBits( NNSample *sample )
{
	p -> setSensors( sample );
	p -> updateBackRepresentation( sample -> getTargets() );

	int bits = 0;
	float errorMax = 0;
	for( int k = 0; k < p -> getNTargets(); k++ )
		{
			float neuronDiff = ef -> getErrorSignalForBits( k );
			currentError += neuronDiff * neuronDiff;

			neuronDiff = ABS( neuronDiff );
			if( neuronDiff >= bitFailLimit )
				bits++;

			if( neuronDiff > errorMax )
				errorMax = neuronDiff;
		}

	sample -> setError(	errorMax );
	return( bits );
}

float NNStopFunction::calculateErrorValueBits()
{
	int bits = 0;
	float errorMax = 0;
	for( int k = 0; k < p -> getNTargets(); k++ )
		{
			float neuronDiff = ef -> getErrorSignalForBits( k );
			currentError += neuronDiff * neuronDiff;

			neuronDiff = ABS( neuronDiff );
			if( neuronDiff >= bitFailLimit )
				bits++;

			if( neuronDiff > errorMax )
				errorMax = neuronDiff;
		}

	return( errorMax );
}

void NNStopFunction::setMaxIterations( int p_value )
{
	maxIterations = p_value;
}

int NNStopFunction::getMaxIterations()
{
	return( maxIterations );
}

void NNStopFunction::setMinIterations( int p_value )
{
	minIterations = p_value;
}

int NNStopFunction::getMinIterations()
{
	return( minIterations );
}

const char *NNStopFunction::NAME = "NNStopFunction";

void NNStopFunction::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNStopFunction::onCreate );
	so -> addFieldInt( "functionType" );
	so -> addFieldFloat( "desiredError" );
	so -> addFieldFloat( "bitFailLimit" );
	so -> addFieldInt( "maxFailedNeurons" );
	so -> addFieldInt( "minIterations" );
	so -> addFieldInt( "maxIterations" );
}

void NNStopFunction::serialize( SerializeObject& so )
{
	so.setPropInt( functionType , "functionType" );
	so.setPropFloat( desiredError , "desiredError" );
	so.setPropFloat( bitFailLimit , "bitFailLimit" );
	so.setPropInt( maxFailedNeurons , "maxFailedNeurons" );
	so.setPropInt( minIterations , "minIterations" );
	so.setPropInt( maxIterations , "maxIterations" );
}

void NNStopFunction::deserialize( Object *parent , SerializeObject& so )
{
	functionType = ( StopFunction )so.getPropInt( "functionType" );
	desiredError = so.getPropFloat( "desiredError" );
	bitFailLimit = so.getPropFloat( "bitFailLimit" );
	maxFailedNeurons = so.getPropInt( "maxFailedNeurons" );
	minIterations = so.getPropInt( "minIterations" );
	maxIterations = so.getPropInt( "maxIterations" );
}
