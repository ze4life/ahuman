
#include <aiexpert_impl.h>

/*#########################################################################*/
/*#########################################################################*/

NNWeights::NNWeights()
{
	p = NULL;
}

NNWeights::NNWeights( NN *p_p )
{
	attach( p_p );
}

NNWeights::~NNWeights()
{ 
}

void NNWeights::attach( NN *p_p )
{
	p = p_p;

	// get weight count
	int nVars = p -> getNVars();

	// allocate
	weights.create( nVars );
	weightsPtr.create( nVars );

	// fill ptrs
	float **pfPtr = weightsPtr.getAll();
	int index = 0;
	startIndex.createN1( p -> getNLayers() );
	for( int k = 0; k < p -> getNLayers(); k++ )
		{
			NNLayer *pl = p -> getLayer( k );

			float **wfNormal = pfPtr;
			startIndex.createN2( k , pl -> getNeuronCount() );
			for( int m = 0; m < pl -> getNeuronCount(); m++ )
				{
					NNNeuron *pn = pl -> getNeuron( m );
					
					// index counting
					startIndex[ k ][ m ] = index;

					// inputs
					for( int z = 0; z < pn -> getNInputs(); z++ )
						{
							NNConnection *ic = pn -> getInputData()[ z ];
							*wfNormal++ = &ic -> weight;
						}

					index += pn -> getNInputs();
				}

			pfPtr = wfNormal;
		}
}

NN *NNWeights::getNN()
{
	return( p );
}

float *NNWeights::getData()
{
	return( weights.getAll() );
}

float *NNWeights::getNeuronWeights( int layer , int neuron )
{
	return( weights.getAll() + startIndex[ layer ][ neuron ] );
}

void NNWeights::getFromPerceptron()
{
	float **pfPtr = weightsPtr.getAll();
	float *pf = weights.getAll();

	// copy
	pfPtr = weightsPtr.getAll();
	for( int z = 0; z < weights.count(); z++ )
		*pf++ = *( *pfPtr++ );
}

void NNWeights::setToPerceptron()
{
	float *pf = weights.getAll();
	float **pfPtr = weightsPtr.getAll();

	// fill
	for( int z = 0; z < weights.count(); z++ )
		*( *pfPtr++ ) = *pf++;
}

int NNWeights::getNVars()
{
	return( weights.count() );
}

float NNWeights::getVarValue( int index )
{
	return( weights[ index ] );
}

float *NNWeights::getVarPtrByIndex( int index )
{
	return( weightsPtr[ index ] );
}

void NNWeights::setToCenter()
{
	memset( weights.getAll() , 0 , weights.count() * sizeof( float ) );
}

void NNWeights::setRandomDefault()
{
	Random r;
	r.createTwoRangeRandomsFloat( -0.8f , -0.2f , 0.2f , 0.8f );
	setRandom( r );
}

void NNWeights::setRandom( Random& randoms )
{
	float *pw = weights.getAll();
	for( int k = 0; k < weights.count(); k++ )
		*pw++ = randoms.getRandomFloat();
}

void NNWeights::setIndexValue( int index , float value )
{
	weights[ index ] = value;
}

void NNWeights::setTo( const NNWeights *wp )
{
	// check the same weight count
	ASSERT( weights.count() == wp -> weights.count() );

	// copy all
	memcpy( weights.getAll() , wp -> weights.getAll() , weights.count() * sizeof( float ) );
}

bool NNWeights::equals( NNWeights *pw , float tolerance )
{
	ASSERT( weights.count() == pw -> weights.count() );

	float *pf1 = pw -> getData();
	float *pf2 = getData();
	for( int k = 0; k < weights.count(); k++ , pf1++ , pf2++ )
		if( compareFloats( *pf1 , *pf2 ) )
			return( false );

	return( true );
}

const char *NNWeights::NAME = "NNWeights";

void NNWeights::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNWeights::onCreate );

	// add fields
	so -> addFieldFloatList( "weights" );
}

void NNWeights::serialize( SerializeObject& so )
{
	so.setPropFloatList( weights.getAll() , weights.count() , "weights" , false );
}

void NNWeights::deserialize( Object *parent , SerializeObject& so )
{
	ASSERT( false );
}
