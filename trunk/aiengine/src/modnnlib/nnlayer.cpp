#include "ainnlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class NNLayer : public AIObject

NNLayer::NNLayer()
:	engine( AIEngine::getInstance() )
{
	p = NULL;

	nPos = 0;
	outputs = NULL;
	useBias = false;
}

NNLayer *NNLayer::newInit( NN *p_perceptron , int nPos , int p_nOutputs , bool p_usebias )
{
	NNLayer *o = new NNLayer;
	o -> init( p_perceptron , nPos , p_nOutputs , p_usebias );
	return( o );
}

void NNLayer::init( NN *p_perceptron , int p_nPos , int p_nNeurons , bool p_usebias )
{
	p = p_perceptron;
	nPos = p_nPos;
	useBias = p_usebias;

	// create neurons
	int nNeurons = ( useBias )? p_nNeurons + 1 : p_nNeurons;
	neurons.allocate( nNeurons );
	for( int k = 0; k < nNeurons; k++ )
		neurons.add( new NNNeuron( this ) );
}

NNLayer::~NNLayer()
{
	clearData();
}

void NNLayer::createFinally()
{
	outputs.create( neurons.count() );

	// for neurons
	for( int k = 0; k < neurons.count(); k++ )
		{
			neurons[ k ] -> createFinally();
			outputs[ k ] = neurons[ k ] -> getOutputPtr();
		}
}

void NNLayer::clearData()
{
	neurons.destroy();

	p = NULL;

	nPos = 0;
	outputs = NULL;
	useBias = false;
}

void NNLayer::clearValues()
{
	for( int k = 0; k < getNonBiasNeuronCount(); k++ )
		neurons[ k ] -> clearValues();
}

void NNLayer::attach( NN *p_p , int pPos )
{
	p = p_p;
	nPos = pPos;

	// attach neurons
	for( int k = 0; k < neurons.count(); k++ )
		{
			NNNeuron *pn = neurons[ k ];
			outputs[ k ] = pn -> getOutputPtr();

			pn -> attach( this );
		}
}

void NNLayer::execute()
{
	// calculate outputs
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			pn -> execute();
		}
}

void NNLayer::executeFunctionOnly()
{
	// update output from S values
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			pn -> executeSkipInduction();
		}
}

void NNLayer::setInductionFunction( const NNInductionFunction *p_f )
{
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			NNInductionFunction *f = pn -> getInductionFunction();
			f -> set( p_f );
		}
}

void NNLayer::setActivationFunction( const NNActivationFunction *p_f )
{
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			NNActivationFunction *f = pn -> getActivationFunction();
			f -> set( p_f );
		}
}

int NNLayer::getNeuronCount()
{
	return( neurons.count() );
}

NNNeuron *NNLayer::getNeuron( int pos )
{
	return( neurons[ pos ] );
}

int NNLayer::getNVars()
{
	int nVars = 0;
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		nVars += neurons[ k ] -> getNInputs();

	return( nVars );
}

int NNLayer::getNConnections()
{
	int n = 0;
	for( int k = 0; k < neurons.count(); k++ )
		n += neurons[ k ] -> getNConnections();

	return( n );
}

int NNLayer::getNonBiasNeuronCount()
{
	if( useBias )
		return( neurons.count() - 1 );

	return( neurons.count() );
}

const float **NNLayer::getOutputs()
{
	return( outputs.getAll() );
}

int NNLayer::getPos()
{
	return( nPos );
}

NN *NNLayer::getNN()
{
	return( p );
}

void NNLayer::setBiasValues( float value )
{
	ASSERT( useBias );
	NNNeuron *pn = neurons.last();
	pn -> setInitialOutput( value );
}

bool NNLayer::isBiasNeuron( int p_neuron )
{
	// last neuron is bias if used
	if( useBias )
		return( p_neuron == neurons.count() - 1 );

	return( false );
}

void NNLayer::setInputRanges( float minValue , float maxValue )
{
	// do for all neurons
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			NNActivationFunction *af = pn -> getActivationFunction();
			af -> setInputRange( minValue , maxValue );
		}
}

void NNLayer::setOutputRanges( float minValue , float maxValue )
{
	// do for all neurons
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			NNActivationFunction *af = pn -> getActivationFunction();
			af -> setOutputRange( minValue , maxValue );
		}
}

void NNLayer::setInputRangesUnlimited()
{
	// do for all neurons
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			NNActivationFunction *af = pn -> getActivationFunction();

			Scale *scale = af -> getInputScale();
			scale -> setDoScale( false );
		}
}

void NNLayer::joinToPerceptronInputs()
{
	// create connections from all neurons to all inputs
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			pn -> joinToPerceptronInputs();
		}
}

void NNLayer::joinToLayer( NNLayer *pl )
{
	// create connections from all neurons to all inputs
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];
			pn -> joinToLayer( pl );
		}
}

bool NNLayer::getUseBias()
{
	return( useBias );
}

float *NNLayer::getS( int p_neuron )
{
	NNNeuron *pn = getNeuron( p_neuron );
	return( pn -> getS() );
}

void NNLayer::calculateInputRanges( float wMin , float wMax , float ratio )
{
	// do for all neurons
	int n = getNonBiasNeuronCount();
	for( int k = 0; k < n; k++ )
		{
			NNNeuron *pn = neurons[ k ];

			float minS , maxS;
			pn -> getRangeS( wMin , wMax , &minS , &maxS );

			NNActivationFunction *af = pn -> getActivationFunction();
			af -> setInputRange( minS * ratio , maxS * ratio );
		}
}

void NNLayer::reflectInsertNeuron( NNLayer *layer , int pos , bool createConnections , Random *randoms4Weights )
{
	for( int k = 0; k < neurons.count(); k++ )
		neurons[ k ] -> reflectInsertNeuron( layer , pos , createConnections , randoms4Weights );
}

void NNLayer::reflectInsertSensor( NNVariable *nv , int pos , bool createConnections , Random *random4weights )
{
	for( int k = 0; k < neurons.count(); k++ )
		neurons[ k ] -> reflectInsertSensor( nv , pos , createConnections , random4weights );
}

/*#########################################################################*/
/*#########################################################################*/

const char *NNLayer::NAME = "NNLayer";

void NNLayer::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNLayer::onCreate );

	so -> addFieldInt( "nPos" );
	so -> addFieldBool( "useBias" );
	so -> addFieldObjectList( "neurons" , NNNeuron::getSerializeObject() );
}

void NNLayer::serialize( SerializeObject& so )
{
	so.setPropInt( nPos , "nPos" );
	so.setPropBool( useBias , "useBias" );
	so.setPropObjectList( ( ClassList<Object>& )neurons , "neurons" , false );
}

void NNLayer::deserialize( Object *parent , SerializeObject& so )
{
	clearData();

	nPos = so.getPropInt( "nPos" );
	useBias = so.getPropBool( "useBias" );
	so.getPropObjectList( ( ClassList<Object>& )neurons , "neurons" , true );

	outputs.create( neurons.count() );
}
