#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNErrorFunction *NNErrorFunction::newInit( NN *p_p )
{
	NNErrorFunction *o = new NNErrorFunction;
	o -> init( p_p );
	return( o );
}

void NNErrorFunction::init( NN *p_p )
{
	attach( p_p );
}

void NNErrorFunction::attach( NN *p_p )
{
	p = p_p;
}

NNErrorFunction::NNErrorFunction()
{
	p = NULL;
	errorFunction = FANN_ERRORFUNC_EMPTY;
	currentError = 0;
	packetMode = false;
}

NNErrorFunction::~NNErrorFunction()
{
}

void NNErrorFunction::set( const NNErrorFunction *p_p )
{
	errorFunction = p_p -> errorFunction;
	packetMode = p_p -> packetMode;
	currentError = 0;
}

/*#########################################################################*/
/*#########################################################################*/

// base algorithm - stddev
float NNErrorFunction::getInternal( NNSample *useSample , bool translate , bool updateOutputs )
{
	float e = 0;
	if( updateOutputs )
		p -> setSensors( useSample );

	// process targets
	p -> updateBackRepresentation( useSample -> getTargets() );

	// process outputs
	int n = p -> getNOutputs();
	const float * const *values = p -> getOutputs();
	float * const *valuesExpected = p -> getOutputsRestoredFromTargets();
	for( int m = 0; m < n; m++ )
		{
			float value = *( values[ m ] );
			float valueExpected = *( valuesExpected[ m ] );

			float diff = valueExpected - value;
			if( translate )
				diff = translateSignal( diff );
			e += diff * diff;
		}

	return( e );
}

float NNErrorFunction::getNormalized( NNSample *useSample , bool translate , bool updateOutputs )
{
	float e = getInternal( useSample , translate , updateOutputs );
	e /= p -> getNOutputs();
	return( e );
}

float NNErrorFunction::getSignalInternal( int p_output , bool translate )
{
	float valueExpected = *( p -> getOutputsRestoredFromTargets()[ p_output ] );
	float value = p -> getOutput( p_output );

	float diff = valueExpected - value;
	if( translate )
		diff = translateSignal( diff );
	return( diff );
}

float NNErrorFunction::getSignalNormalized( int p_output , bool translate )
{
	float valueExpected = *( p -> getOutputsRestoredFromTargets()[ p_output ] );
	float value = p -> getOutput( p_output );

	float diff = ( valueExpected - value ) / 2;
	if( translate )
		diff = translateSignal( diff );
	return( diff );
}

void NNErrorFunction::setTranslationTanh()
{
	errorFunction = FANN_ERRORFUNC_TANH;
}

void NNErrorFunction::setTranslationLinear()
{
	errorFunction = FANN_ERRORFUNC_LINEAR;
}

float NNErrorFunction::translateSignal( float primarySignal )
{
	switch( errorFunction )
		{
			// no change
			case FANN_ERRORFUNC_LINEAR :
				return( primarySignal );
			// reverse of tanh
			case FANN_ERRORFUNC_TANH :
				if( primarySignal < -0.9999999f )
					return( -17.0f );
				if( primarySignal > 0.9999999f )
					return( 17.0 );
				return( log((1+primarySignal)/(1-primarySignal)) );
		}

	throw RuntimeError( "Unknown function" );
}

float NNErrorFunction::getErrorSampleProgress( NNSample *sample )
{
	return( getNormalized( sample , false , true ) );
}

float NNErrorFunction::getErrorMSE( NNSample *sample )
{
	return( getNormalized( sample , true , true ) );
}

float NNErrorFunction::getErrorForBP( NNSample *sample )
{
	return( getInternal( sample , true , false ) / 2 );
}

float NNErrorFunction::getErrorSignalForBits( int p_output )
{
	return( getSignalNormalized( p_output , false ) );
}

float NNErrorFunction::getErrorSignalForBP( int p_output )
{
	return( getSignalNormalized( p_output , true ) );
}

const char *NNErrorFunction::NAME = "NNErrorFunction";

void NNErrorFunction::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNErrorFunction::onCreate );
	so -> addFieldInt( "errorFunction" );
	so -> addFieldBool( "packetMode" );
}

void NNErrorFunction::serialize( SerializeObject& so )
{
	so.setPropInt( errorFunction , "errorFunction" );
	so.setPropBool( packetMode , "packetMode" );
}

void NNErrorFunction::deserialize( Object *parent , SerializeObject& so )
{
	errorFunction = ( ErrorFunction )so.getPropInt( "errorFunction" );
	packetMode = so.getPropBool( "packetMode" );
}
