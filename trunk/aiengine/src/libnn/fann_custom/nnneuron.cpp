#include "fann_custom.h"

/*#########################################################################*/
/*#########################################################################*/

NNNeuron::NNNeuron()
{
	layer = NULL;
	s = output = 0;
}

NNNeuron::NNNeuron( NNLayer *p_p )
{
	layer = NULL;
	s = output = 0;

	attach( p_p );
}

void NNNeuron::attach( NNLayer *p_p )
{
	layer = p_p;
	NN *p = layer -> getNN();

	// join connections
	NNConnection * const *ica = inputConnections.getAll();
	for( int k = 0; k < inputConnections.count(); k++ )
		{
			NNConnection *ic = ica[ k ];
			if( ic -> sourceLayerPos >= 0 )
				{
					NNLayer *pl = p -> getLayer( ic -> sourceLayerPos );
					ic -> sourceNeuron = pl -> getNeuron( ic -> sourceLayerNeuronPos );
					ic -> inputPtr = ic -> sourceNeuron -> getOutputPtr();
					ic -> bias = pl -> isBiasNeuron( ic -> sourceLayerNeuronPos );
				}
			else
				{
					ic -> inputPtr = p -> getInputs()[ ic -> sourceLayerNeuronPos ];
					ic -> bias = p -> isInputBias( ic -> sourceLayerNeuronPos );
				}
		}
}

NNLayer *NNNeuron::getLayer()
{
	return( layer );
}

NNNeuron::~NNNeuron()
{
}

void NNNeuron::createFinally()
{
}

void NNNeuron::clearValues()
{
	s = 0;
	output = 0;
}

// make connections
void NNNeuron::joinToPerceptronInputs()
{
	NN *p = layer -> getNN();

	int nInputs = p -> getNInputs();
	inputConnections.create( nInputs );

	const float * const *inputPtrGet = p -> getInputs();
	for( int k = 0; k < nInputs; k++ )
		{
			NNConnection *ic = inputConnections.getAt( k );
			ic -> sourceNeuron = NULL;
			ic -> sourceLayerPos = -1;
			ic -> sourceLayerNeuronPos = k;
			ic -> weight = 0;
			ic -> inputPtr = inputPtrGet[ k ];
			ic -> bias = p -> isInputBias( k );
		}
}

void NNNeuron::joinToLayer( NNLayer *pl )
{
	int nInputs = pl -> getNeuronCount();
	inputConnections.create( nInputs );

	for( int k = 0; k < nInputs; k++ )
		{
			NNConnection *ic = inputConnections.getAt( k );
			ic -> sourceNeuron = pl -> getNeuron( k );
			ic -> sourceLayerPos = pl -> getPos();
			ic -> sourceLayerNeuronPos = k;
			ic -> weight = 0;
			ic -> inputPtr = ic -> sourceNeuron -> getOutputPtr();
			ic -> bias = pl -> isBiasNeuron( k );
		}
}

int NNNeuron::getNConnections()
{
	return( inputConnections.count() );
}

void NNNeuron::getRangeS( float wMin , float wMax , float *ptrMinS , float *ptrMaxS )
{
	// calculate input limits
	float minS = 0;
	float maxS = 0;

	// iterate connections
	NN *p = layer -> getNN();
	for( int k = 0; k < inputConnections.count(); k++ )
		{
			NNConnection& c = inputConnections[ k ];
			
			float minLimitX;
			float maxLimitX;
			if( c.bias )
				minLimitX = maxLimitX = *c.inputPtr;
			else
			if( c.sourceNeuron != NULL )
				{
					Scale *scale = c.sourceNeuron -> getOutputScale();
					minLimitX = scale -> getToMin();
					maxLimitX = scale -> getToMax();
				}
			else
				{
					minLimitX = -1;
					maxLimitX = 1;
				}
					
			float minX = getMinMul( minLimitX , maxLimitX , wMin , wMax );
			float maxX = getMaxMul( minLimitX , maxLimitX , wMin , wMax );

			minS += minX;
			maxS += maxX;
		}

	// return
	*ptrMinS = minS;
	*ptrMaxS = maxS;
}

int NNNeuron::getNInputs()
{
	return( inputConnections.count() );
}

NNConnection *NNNeuron::getInputData( int pos )
{
	return( inputConnections.getAt( pos ) );
}

NNConnection * const *NNNeuron::getInputData()
{
	return( inputConnections.getAll() );
}

float *NNNeuron::getOutputPtr()
{
	return( &output );
}

void NNNeuron::execute()
{
	s = inductionFunction.calculate( inputConnections );
	output = activationFunction.getOutput( s );
}

void NNNeuron::executeSkipInduction()
{
	output = activationFunction.getOutput( s );
}

float NNNeuron::getInductionDerivative( int input )
{
	NNConnection *ic = inputConnections.getAt( input );
	return( inductionFunction.getDerivative( s , ic ) );
}

float NNNeuron::getActivationDerivative()
{
	return( activationFunction.getDerivative( s , output ) );
}

NNInductionFunction *NNNeuron::getInductionFunction()
{
	return( &inductionFunction );
}

NNActivationFunction *NNNeuron::getActivationFunction()
{
	return( &activationFunction );
}

void NNNeuron::setInitialOutput( float value )
{
	output = value;
}

float *NNNeuron::getS()
{
	return( &s );
}

Scale* NNNeuron::getInputScale()
{
	return( activationFunction.getInputScale() );
}

Scale *NNNeuron::getOutputScale()
{
	return( activationFunction.getOutputScale() );
}

float NNNeuron::getOutput()
{
	return( output );
}

void NNNeuron::reflectInsertNeuron( NNLayer *p_layer , int pos , bool createConnections , Random *randoms4Weights )
{
	NNNeuron *pn = ( p_layer == NULL )? NULL : p_layer -> getNeuron( pos );

	// create connection if requested
	if( createConnections )
		{
			NNConnection ic;
			ic.sourceLayerPos = ( p_layer == NULL )? -1 : p_layer -> getPos();
			ic.sourceLayerPos = pos;
			ic.sourceNeuron = ( p_layer == NULL )? NULL : p_layer -> getNeuron( pos );
			ic.weight = randoms4Weights -> getRandomFloat();
			ic.inputPtr = NULL;
			ic.bias = 0;

			inputConnections.add( ic );
		}

	// shift indexes in connections
	const float * const *inputs1 = ( p_layer == NULL )? layer -> getNN() -> getInputs() : NULL;
	const float **inputs2 = ( p_layer != NULL )? p_layer -> getOutputs() : NULL;
	for( int k = 0; k < inputConnections.count(); k++ )
		{
			NNConnection *ic = inputConnections.getAt( k );
			NNLayer *pl = ( ic -> sourceNeuron == NULL )? NULL : ic -> sourceNeuron -> getLayer();

			// check uses this layer
			if( pl == p_layer )
				{
					if( ic -> sourceLayerNeuronPos >= pos )
						ic -> sourceLayerNeuronPos++;

					// rebuild pointer (memory could be relocated)
					ic -> inputPtr = ( pl == NULL )? inputs1[ ic -> sourceLayerNeuronPos ] : inputs2[ ic -> sourceLayerNeuronPos ];
				}
		}
}

void NNNeuron::reflectInsertSensor( NNVariable *nv , int pos , bool createConnections , Random *random4weights )
{
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNNeuron::NAME = "NNNeuron";

void NNNeuron::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNNeuron::onCreate );

	so -> addFieldObject( "inductionFunction" , NNInductionFunction::getSerializeObject() );
	so -> addFieldObject( "activationFunction" , NNActivationFunction::getSerializeObject() );

	// implement connections as several arrays
	so -> addFieldIntList( "connectionSourceLayer" );
	so -> addFieldIntList( "connectionSourceInput" );
	so -> addFieldFloatList( "connectionWeight" );
}

void NNNeuron::serialize( SerializeObject& so )
{
	so.setPropObject( inductionFunction , "inductionFunction" );
	so.setPropObject( activationFunction , "activationFunction" );

	// connection data
	int n = inputConnections.count();
	if( n > 0 )
		{
			int *layerPos = ( int * )malloc( n * sizeof( int ) );
			int *ptr = layerPos;
			for( int k = 0; k < n; k++ )
				{
					NNConnection& ic = inputConnections[ k ];
					*ptr++ = ( ic.sourceNeuron == NULL )? -1 : ic.sourceNeuron -> getLayer() -> getPos();
				}
			so.setPropIntList( layerPos , n , "connectionSourceLayer" , true );
		}

	so.setPropIntListFromStructPtrList( ( void ** )inputConnections.getAll() , inputConnections.count() , sizeof( NNConnection ) , offsetof( NNConnection , sourceLayerNeuronPos ) , "connectionSourceInput" );
	so.setPropFloatListFromStructPtrList( ( void ** )inputConnections.getAll() , inputConnections.count() , sizeof( NNConnection ) , offsetof( NNConnection , weight ) , "connectionWeight" );
}

void NNNeuron::deserialize( Object *parent , SerializeObject& so )
{
	inductionFunction.set( ( const NNInductionFunction * )so.getPropObject( "inductionFunction" , false ) );
	activationFunction.set( ( const NNActivationFunction * )so.getPropObject( "activationFunction" , false ) );

	int n = 0;
	int *connectionSourceLayer = so.getPropIntList( "connectionSourceLayer" , &n , false );
	int *connectionSourceInput = so.getPropIntList( "connectionSourceInput" , &n , false );
	float *connectionWeight = so.getPropFloatList( "connectionWeight" , &n , false );

	// rebuild new ones
	inputConnections.create( n );
	for( int k = 0; k < n; k++ )
		{
			NNConnection *ic = inputConnections.getAt( k );
			int layer = *connectionSourceLayer++;
			int neuron = *connectionSourceInput++;
			float weight = *connectionWeight++;

			ic -> sourceLayerPos = layer;
			ic -> sourceLayerNeuronPos = neuron;
			ic -> weight = weight;
		}
}
