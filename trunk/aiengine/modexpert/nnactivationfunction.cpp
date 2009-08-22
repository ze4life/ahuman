
#include "aiexpert_impl.h"

const char *NNActivationFunction::functionNames[ 20 ] = {
	NULL , NULL , NULL , NULL , NULL ,
	NULL , NULL , NULL , NULL , NULL ,
	NULL , NULL , NULL , NULL , NULL ,
	NULL , NULL , NULL , NULL , NULL };

/*#########################################################################*/
/*#########################################################################*/

void NNActivationFunction::initLinear()
{
	initFunction( FANN_LINEAR , true , false );
}

void NNActivationFunction::initLinearPiece()
{
	initFunction( FANN_LINEAR_PIECE , false , true );
}

void NNActivationFunction::initLinearPieceSymmetric()
{
	initFunction( FANN_LINEAR_PIECE_SYMMETRIC , true , true );
}

void NNActivationFunction::initSigmoid()
{
	initFunction( FANN_SIGMOID , false , true );
}

void NNActivationFunction::initSigmoidSymmetric()
{
	initFunction( FANN_SIGMOID_SYMMETRIC , true , true );
}

void NNActivationFunction::initSigmoidStepwise()
{
	initFunction( FANN_SIGMOID_STEPWISE , false , true );
}

void NNActivationFunction::initSigmoidSymmetricStepwise()
{
	initFunction( FANN_SIGMOID_SYMMETRIC_STEPWISE , true , true );
}

void NNActivationFunction::initThreshold()
{
	initFunction( FANN_THRESHOLD , false , true );
}

void NNActivationFunction::initThresholdSymmetric()
{
	initFunction( FANN_THRESHOLD_SYMMETRIC , true , true );
}

void NNActivationFunction::initGaussian()
{
	initFunction( FANN_GAUSSIAN , false , true );
}

void NNActivationFunction::initGaussianSymmetric()
{
	initFunction( FANN_GAUSSIAN_SYMMETRIC , true , true );
}

void NNActivationFunction::initElliot()
{
	initFunction( FANN_ELLIOT , false , true );
}

void NNActivationFunction::initElliotSymmetric()
{
	initFunction( FANN_ELLIOT_SYMMETRIC , true , true );
}

void NNActivationFunction::initSin()
{
	initFunction( FANN_SIN , false , true );
}

void NNActivationFunction::initSinSymmetric()
{
	initFunction( FANN_SIN_SYMMETRIC , true , true );
}

void NNActivationFunction::initCos()
{
	initFunction( FANN_COS , false , true );
}

void NNActivationFunction::initCosSymmetric()
{
	initFunction( FANN_COS_SYMMETRIC , true , true );
}

/*#########################################################################*/
/*#########################################################################*/

// class NNActivationFunction : public Object
NNActivationFunction::NNActivationFunction()
{
	functionType = FANN_EMPTY;
	symmetric = false;
	steepness = 1;
}

NNActivationFunction::~NNActivationFunction()
{
}

void NNActivationFunction::initFunction( ActivationFunction ft , bool p_symmetric , bool scaleOutputs )
{
	functionType = ft;
	symmetric = p_symmetric;

	if( scaleOutputs )
		setOutputFunction( ( symmetric )? -1 : 0 , 1 );
}

// get string function name representation
const char *NNActivationFunction::getName()
{
	// init names
	if( functionNames[ FANN_EMPTY ] == NULL )
		{
#define SETFUNC( x ) functionNames[ FANN_##x ] = #x
			SETFUNC( EMPTY );
			SETFUNC( LINEAR );
			SETFUNC( LINEAR_PIECE );
			SETFUNC( LINEAR_PIECE_SYMMETRIC );
			SETFUNC( SIGMOID );
			SETFUNC( SIGMOID_SYMMETRIC );
			SETFUNC( SIGMOID_STEPWISE );
			SETFUNC( SIGMOID_SYMMETRIC_STEPWISE );
			SETFUNC( THRESHOLD );
			SETFUNC( THRESHOLD_SYMMETRIC );
			SETFUNC( GAUSSIAN );
			SETFUNC( GAUSSIAN_SYMMETRIC );
			SETFUNC( ELLIOT );
			SETFUNC( ELLIOT_SYMMETRIC );
			SETFUNC( SIN );
			SETFUNC( SIN_SYMMETRIC );
			SETFUNC( COS );
			SETFUNC( COS_SYMMETRIC );
#undef SETFUNC
		}

	return( functionNames[ functionType ] );
}

void NNActivationFunction::setSteepness( float value )
{
	steepness = value;
}

float NNActivationFunction::getSteepness()
{
	return( steepness );
}

// get function value - non-scaled input, 
float NNActivationFunction::getOutput( float value )
{
	// scale input
	float inputScaled = inputScale.scale( value );

	// use steepness
	float inputFunction = inputScaled * steepness;

	// call original function
	float outputFunction = getOutputFunction( inputFunction );

	// scale output
	float output = outputScale.scale( outputFunction );

	return( output );
}

// get derivative by desired output (steepness is intentionally not used for derivative)
float NNActivationFunction::getDerivative( float input , float output )
{
	// unscale output
	float outputFunction = outputScale.unscale( output );
	float inputFunction = inputScale.scale( input );

	// call original function
	float derivativeFunction = getDerivativeFunction( inputFunction , outputFunction );

	// scale derivative
	float derivative = derivativeFunction;
	if( outputScale.getDoScale() )
		derivative *= outputScale.getRate();
	if( inputScale.getDoScale() )
		derivative *= inputScale.getRate();

	return( derivative );
}

// scale functions
void NNActivationFunction::setNoScaleInput( bool value )
{
	inputScale.setDoScale( ( value )? false : true );
}

void NNActivationFunction::setNoScaleOutput( bool value )
{
	outputScale.setDoScale( ( value )? false : true );
}

bool NNActivationFunction::getNoScaleInput()
{
	return( ( inputScale.getDoScale() )? false : true );
}

bool NNActivationFunction::getNoScaleOutput()
{
	return( ( outputScale.getDoScale() )? false : true );
}

void NNActivationFunction::setInputRange( float minReal , float maxReal )
{
	inputScale.setRangeFrom( minReal , maxReal );
}

Scale *NNActivationFunction::getInputScale()
{
	return( &inputScale );
}

void NNActivationFunction::setOutputRange( float minDesired , float maxDesired )
{
	outputScale.setRangeTo( minDesired , maxDesired );
}

Scale *NNActivationFunction::getOutputScale()
{
	return( &outputScale );
}

float NNActivationFunction::scaleInputValue( float value )
{
	return( inputScale.scale( value ) );
}

float NNActivationFunction::scaleOutputValue( float value )
{
	return( outputScale.scale( value ) );
}

float NNActivationFunction::unscaleInputValue( float value )
{
	return( inputScale.unscale( value ) );
}

float NNActivationFunction::unscaleOutputValue( float value )
{
	return( outputScale.unscale( value ) );
}

void NNActivationFunction::setInputFunction( float minFunction , float maxFunction )
{
	inputScale.setRangeTo( minFunction , maxFunction );
}

void NNActivationFunction::setOutputFunction( float minFunction , float maxFunction )
{
	outputScale.setRangeFrom( minFunction , maxFunction );
}

float NNActivationFunction::getLinear( float v1, float r1, float v2, float r2, float x )
{
	return( r1 + ( r2-r1 ) * ( x-v1 ) / (v2-v1) );
}

float NNActivationFunction::getStepwise( float v1, float v2, float v3, float v4, float v5, float v6, 
	float r1, float r2, float r3, float r4, float r5, float r6, 
	float rMin, float rMax, float x )
{
	if( x < v1 )
		return( rMin );
	if( x > v6 )
		return( rMax );

	if( x < v2 )
		return( getLinear(v1, r1, v2, r2, x) );
	if( x < v3 )
		return( getLinear(v2, r2, v3, r3, x) );
	if( x < v4 )
		return( getLinear(v3, r3, v4, r4, x) );
	if( x < v5 )
		return( getLinear(v4, r4, v5, r5, x) );

	return( getLinear(v5, r5, v6, r6, x) );
}

/*#########################################################################*/
/*#########################################################################*/

float NNActivationFunction::getOutputFunction( float x )
{
	switch( functionType )
		{
			case FANN_LINEAR :
				return( x );
			case FANN_LINEAR_PIECE :
				if( x < 0 )
					return( 0 );
				if( x > 1 )
					return( 1 );
				return( x );
			case FANN_LINEAR_PIECE_SYMMETRIC :
				if( x < -1 )
					return( -1 );
				if( x > 1 )
					return( 1 );
				return( x );
			case FANN_SIGMOID :
				return( ( float )( 1/(1+exp(-2*x)) ) );
			case FANN_SIGMOID_SYMMETRIC :
				return( ( float )( -1+2/(1+exp(-2*x)) ) );
			case FANN_SIGMOID_STEPWISE :
				return( getStepwise(
					-2.64665246009826660156e+00, 
					-1.47221946716308593750e+00, 
					-5.49306154251098632812e-01, 
					5.49306154251098632812e-01, 
					1.47221934795379638672e+00, 
					2.64665293693542480469e+00, 
					4.99999988824129104614e-03, 
					5.00000007450580596924e-02, 
					2.50000000000000000000e-01, 
					7.50000000000000000000e-01, 
					9.49999988079071044922e-01, 
					9.95000004768371582031e-01, 
					0, 1, x ) );
			case FANN_SIGMOID_SYMMETRIC_STEPWISE :
				return( getStepwise(
					-2.64665293693542480469e+00, 
					-1.47221934795379638672e+00, 
					-5.49306154251098632812e-01, 
					5.49306154251098632812e-01, 
					1.47221934795379638672e+00, 
					2.64665293693542480469e+00, 
					-9.90000009536743164062e-01, 
					-8.99999976158142089844e-01, 
					-5.00000000000000000000e-01, 
					5.00000000000000000000e-01, 
					8.99999976158142089844e-01, 
					9.90000009536743164062e-01, 
					-1, 1, x ) );
			case FANN_THRESHOLD :
				return( ( x < 0 )? 0 : 1 );
			case FANN_THRESHOLD_SYMMETRIC :
				return( ( x < 0 )? -1 : 1 );
			case FANN_GAUSSIAN :
				return( ( float )( exp(-x*x) ) );
			case FANN_GAUSSIAN_SYMMETRIC :
				return( ( float )( 2*exp(-x*x)-1 ) );
			case FANN_ELLIOT :
				return( ( float )( 0.5+0.5*x/(1+fabs(x)) ) );
			case FANN_ELLIOT_SYMMETRIC :
				return( ( float )( x/(1+fabs(x)) ) );
			case FANN_SIN :
				return( ( float )( 0.5+0.5*sin(x) ) );
			case FANN_SIN_SYMMETRIC :
				return( ( float )( sin(x) ) );
			case FANN_COS :
				return( ( float )( 0.5+0.5*cos(x) ) );
			case FANN_COS_SYMMETRIC :
				return( ( float )( cos(x) ) );
		}

	throw RuntimeError( "Unknown function" );
}

float NNActivationFunction::getReverse( float x )
{
	// unscaled output
	float functionOutput = unscaleOutputValue( x );

	// input to function
	float functionInput = getReverseFunction( functionOutput );

	// discard steepness
	float inputScaled = functionInput / steepness;

	// raw input
	float input = unscaleInputValue( functionInput );

	return( input );
}

float NNActivationFunction::getReverseFunction( float x )
{
	switch( functionType )
		{
			case FANN_LINEAR :
				return( x );
			case FANN_LINEAR_PIECE :
				if( x < 0 )
					return( 0 );
				if( x > 1 )
					return( 1 );
				return( x );
			case FANN_LINEAR_PIECE_SYMMETRIC :
				if( x < -1 )
					return( -1 );
				if( x > 1 )
					return( 1 );
				return( x );
			case FANN_SIGMOID :
				return( ( float )( 0.5*log(x/(1-x)) ) );
			case FANN_SIGMOID_SYMMETRIC :
				return( ( float )( 0.5*log((1+x)/(1-x)) ) );

			case FANN_SIGMOID_STEPWISE :
				return( getStepwise(
					-2.64665246009826660156e+00, 
					-1.47221946716308593750e+00, 
					-5.49306154251098632812e-01, 
					5.49306154251098632812e-01, 
					1.47221934795379638672e+00, 
					2.64665293693542480469e+00, 
					4.99999988824129104614e-03, 
					5.00000007450580596924e-02, 
					2.50000000000000000000e-01, 
					7.50000000000000000000e-01, 
					9.49999988079071044922e-01, 
					9.95000004768371582031e-01, 
					0, 1, x ) );
			case FANN_SIGMOID_SYMMETRIC_STEPWISE :
				return( getStepwise(
					-2.64665293693542480469e+00, 
					-1.47221934795379638672e+00, 
					-5.49306154251098632812e-01, 
					5.49306154251098632812e-01, 
					1.47221934795379638672e+00, 
					2.64665293693542480469e+00, 
					-9.90000009536743164062e-01, 
					-8.99999976158142089844e-01, 
					-5.00000000000000000000e-01, 
					5.00000000000000000000e-01, 
					8.99999976158142089844e-01, 
					9.90000009536743164062e-01, 
					-1, 1, x ) );
			case FANN_THRESHOLD :
				return( ( x < 0 )? 0 : 1 );
			case FANN_THRESHOLD_SYMMETRIC :
				return( ( x < 0 )? -1 : 1 );
			case FANN_GAUSSIAN :
				return( ( float )( exp(-x*x) ) );
			case FANN_GAUSSIAN_SYMMETRIC :
				return( ( float )( 2*exp(-x*x)-1 ) );
			case FANN_ELLIOT :
				return( ( float )( 0.5+0.5*x/(1+fabs(x)) ) );
			case FANN_ELLIOT_SYMMETRIC :
				return( ( float )( x/(1+fabs(x)) ) );
			case FANN_SIN :
				return( ( float )( 0.5+0.5*sin(x) ) );
			case FANN_SIN_SYMMETRIC :
				return( ( float )( sin(x) ) );
			case FANN_COS :
				return( ( float )( 0.5+0.5*cos(x) ) );
			case FANN_COS_SYMMETRIC :
				return( ( float )( cos(x) ) );
		}

	throw RuntimeError( "Unknown function" );
}

float NNActivationFunction::getDerivativeFunction( float x , float y )
{
	switch( functionType )
		{
			case FANN_LINEAR :
			case FANN_LINEAR_PIECE :
				return( 1 );
			case FANN_LINEAR_PIECE_SYMMETRIC :
				return( 2 );
			case FANN_SIGMOID :
			case FANN_SIGMOID_STEPWISE :
				y = clip( y , 0.01f , 0.99f );
				return( 2*y*(1-y) );
			case FANN_SIGMOID_SYMMETRIC :
			case FANN_SIGMOID_SYMMETRIC_STEPWISE :
				y = clip( y , -0.98f , 0.98f );
				return( 1-y*y );
			case FANN_THRESHOLD :
				throw RuntimeError( "Inappropriate function" );
			case FANN_THRESHOLD_SYMMETRIC :
				return( 0 );
			case FANN_GAUSSIAN :
				return( -2 * x * y );
			case FANN_GAUSSIAN_SYMMETRIC :
				return( ( float )( -2*x*(y+1) ) );
			case FANN_ELLIOT :
				y = clip( y , 0.01f , 0.99f );
				return( ( float )( 1/(2*(1+fabs(x))*(1+fabs(x))) ) );
			case FANN_ELLIOT_SYMMETRIC :
				y = clip( y , -0.98f , 0.98f );
				return( ( float )( 1/((1+fabs(x))*(1+fabs(x))) ) );
			case FANN_SIN :
				return( ( float )( cos(x)/2 ) );
			case FANN_SIN_SYMMETRIC :
				return( ( float )( cos(x) ) );
			case FANN_COS :
				return( ( float )( -sin(x)/2 ) );
			case FANN_COS_SYMMETRIC :
				return( ( float )( -sin(x) ) );
		}

	throw RuntimeError( "Unknown function" );
}

float NNActivationFunction::clip( float v , float min , float max )
{
	if( v < min )
		return( min );
	if( v > max )
		return( max );
	return( v );
}

void NNActivationFunction::set( const NNActivationFunction *p_f )
{
	functionType = p_f -> functionType;
	symmetric = p_f -> symmetric;
	steepness = p_f -> steepness;

	// scale data
	inputScale.set( p_f -> inputScale );
	outputScale.set( p_f -> outputScale );
}

const char *NNActivationFunction::NAME = "NNActivationFunction";

void NNActivationFunction::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNActivationFunction::onCreate );

	so -> addFieldFloat( "inputRealMin" );
	so -> addFieldFloat( "inputRealMax" );
	so -> addFieldFloat( "inputFunctionMin" );
	so -> addFieldFloat( "inputFunctionMax" );
	so -> addFieldFloat( "outputFunctionMin" );
	so -> addFieldFloat( "outputFunctionMax" );
	so -> addFieldFloat( "outputDesiredMin" );
	so -> addFieldFloat( "outputDesiredMax" );

	so -> addFieldInt( "functionType" );
	so -> addFieldBool( "symmetric" );
	so -> addFieldFloat( "steepness" );
}

void NNActivationFunction::serialize( SerializeObject& so )
{
	so.setPropFloat( inputScale.getFromMin() , "inputRealMin" );
	so.setPropFloat( inputScale.getFromMax() , "inputRealMax" );
	so.setPropFloat( inputScale.getToMin() , "inputFunctionMin" );
	so.setPropFloat( inputScale.getToMax() , "inputFunctionMax" );
	so.setPropFloat( outputScale.getFromMin() , "outputFunctionMin" );
	so.setPropFloat( outputScale.getFromMax() , "outputFunctionMax" );
	so.setPropFloat( outputScale.getToMin() , "outputDesiredMin" );
	so.setPropFloat( outputScale.getToMax() , "outputDesiredMax" );

	so.setPropInt( functionType , "functionType" );
	so.setPropBool( symmetric , "symmetric" );
	so.setPropFloat( steepness , "steepness" );
}

void NNActivationFunction::deserialize( Object *parent , SerializeObject& so )
{
	float v1 , v2;
	v1 = so.getPropFloat( "inputRealMin" );
	v2 = so.getPropFloat( "inputRealMax" );
	inputScale.setRangeFrom( v1 , v2 );
	v1 = so.getPropFloat( "inputFunctionMin" );
	v2 = so.getPropFloat( "inputFunctionMax" );
	inputScale.setRangeTo( v1 , v2 );
	v1 = so.getPropFloat( "outputFunctionMin" );
	v2 = so.getPropFloat( "outputFunctionMax" );
	outputScale.setRangeFrom( v1 , v2 );
	v1 = so.getPropFloat( "outputDesiredMin" );
	v2 = so.getPropFloat( "outputDesiredMax" );
	outputScale.setRangeTo( v1 , v2 );

	functionType = ( ActivationFunction )so.getPropInt( "functionType" );
	symmetric = so.getPropBool( "symmetric" );
	steepness = so.getPropFloat( "steepness" );
}

