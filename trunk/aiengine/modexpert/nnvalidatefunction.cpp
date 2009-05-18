
#include <aiexpert_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NNValidateFunction::NNValidateFunction()
:	engine( AIEngine::getInstance() )
{
	p = NULL;
	functionType = FANN_VALIDATEFUNC_EMPTY;

	desiredError = 0;
	bitFailLimit = 0;
	avgFailedNeurons = 0;
}

NNValidateFunction::~NNValidateFunction()
{
}

void NNValidateFunction::attach( NN *p_p )
{
	p = p_p;
}

void NNValidateFunction::setValidateAvgOutputMSE( float error )
{
	functionType = FANN_VALIDATEFUNC_AVGOUTPUTMSE;

	desiredError = error;
	bitFailLimit = 0;
	avgFailedNeurons = 0;
}

void NNValidateFunction::setValidateAvgOutputBits( float p_bitFailLimit , float p_avgFailedNeurons )
{
	functionType = FANN_VALIDATEFUNC_AVGOUTPUTBIT;

	desiredError = 0;
	bitFailLimit = p_bitFailLimit;
	avgFailedNeurons = p_avgFailedNeurons;
}

bool NNValidateFunction::validate( NNSample *sample , float *error )
{
	switch( functionType )
		{
			case FANN_VALIDATEFUNC_AVGOUTPUTMSE :
				return( validateAvgOutputMSE( sample , error ) );
			case FANN_VALIDATEFUNC_AVGOUTPUTBIT :
				return( validateAvgOutputBit( sample , error ) );
		}

	throw RuntimeError( "Unknown function" );
}

bool NNValidateFunction::validate( NNSamples *samples , float *error )
{
	samples -> clearValidateData();

	// sum of errors, failed if any fails
	float errorMany = 0;
	bool res = true;
	for( int k = 0; k < samples -> count(); k++ )
		{
			NNSample *sample = samples -> getByPos( k );
			float errorOne;
			if( !validate( sample , &errorOne ) )
				{
					res = false;
					sample -> setValidateFailed( errorOne );
				}

			errorMany += errorOne;
		}

	*error = errorMany;
	return( res );
}

bool NNValidateFunction::validateAvgOutputMSE( NNSample *sample , float *error )
{
	p -> setSensors( sample );
	p -> updateBackRepresentation( sample -> getTargets() );

	// calculate MSE by internal outputs
	const float * const *outputs = p -> getOutputs();
	float * const *outputsExpected = p -> getOutputsRestoredFromTargets();

	float ev = 0;
	for( int k = 0; k < p -> getNOutputs(); k++ )
		{
			float diff = ( *( outputsExpected[ k ] ) - *( outputs[ k ] ) ) / 2;
			ev += diff * diff;
		}

	ev /= p -> getNOutputs();
	*error = ev;

	return( ev <= desiredError );
}

bool NNValidateFunction::validateAvgOutputBit( NNSample *sample , float *error )
{
	p -> setSensors( sample );
	p -> updateBackRepresentation( sample -> getTargets() );

	const float * const *outputs = p -> getOutputs();
	float * const *outputsExpected = p -> getOutputsRestoredFromTargets();

	float ev = 0;
	for( int k = 0; k < p -> getNTargets(); k++ )
		{
			float diff = ( *( outputsExpected[ k ] ) - *( outputs[ k ] ) ) / 2;
			if( diff > bitFailLimit )
				ev += 1;
		}

	ev /= p -> getNOutputs();
	*error = ev;

	return( ev <= avgFailedNeurons );
}

void NNValidateFunction::set( NNValidateFunction *pf )
{
	functionType = pf -> functionType;
	desiredError = pf -> desiredError;
	bitFailLimit = pf -> bitFailLimit;
	avgFailedNeurons = pf -> avgFailedNeurons;
}

// Object interface
const char *NNValidateFunction::NAME = "NNValidateFunction";

void NNValidateFunction::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNValidateFunction::onCreate );

	so -> addFieldInt( "functionType" );
	so -> addFieldFloat( "desiredError" );
	so -> addFieldFloat( "bitFailLimit" );
	so -> addFieldFloat( "avgFailedNeurons" );
}

void NNValidateFunction::serialize( SerializeObject& so )
{
	so.setPropInt( functionType , "functionType" );
	so.setPropFloat( desiredError , "desiredError" );
	so.setPropFloat( bitFailLimit , "bitFailLimit" );
	so.setPropFloat( avgFailedNeurons , "avgFailedNeurons" );
}

void NNValidateFunction::deserialize( Object *parent , SerializeObject& so )
{
	functionType = ( ValidateFunction )so.getPropInt( "functionType" );
	desiredError = so.getPropFloat( "desiredError" );
	bitFailLimit = so.getPropFloat( "bitFailLimit" );
	avgFailedNeurons = so.getPropFloat( "avgFailedNeurons" );
}
