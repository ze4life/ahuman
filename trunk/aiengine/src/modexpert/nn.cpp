#include "aiexpert_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class NN : public Object
NN::NN()
:	engine( AIEngine::getInstance() )
{
	id = 0;
	useInputsBias = false;
	executeStat = 0;
	biasValue = 0;

	validateFunction.attach( this );
}

NN *NN::newInit( const char *p_id , int nSensors , int nTargets , bool p_useInputsBias )
{
	NN *o = new NN;
	o -> init( p_id , nSensors , nTargets , p_useInputsBias );
	return( o );
}

void NN::init( const char *p_id , int nSensors , int nTargets , bool p_useInputsBias )
{
	id = p_id;

	sensors.create( nSensors , NULL );
	targets.create( nTargets , NULL );

	useInputsBias = p_useInputsBias;
}

NN::~NN()
{
	freeData();
}

void NN::createFinally()
{
	for( int k = 0; k < layers.count(); k++ )
		layers[ k ] -> createFinally();
}

void NN::freeData()
{
	layers.destroy();

	inputs.destroy();
	outputs.destroy();
	outputsRestoredFromTargets.destroy();

	executeStat = 0;
	id = 0;
}

void NN::setOutputRanges( float minValue , float maxValue )
{
	for( int k = 0; k < layers.count(); k++ )
		layers[ k ] -> setOutputRanges( minValue , maxValue );
}

NNSamples *NN::createSamples()
{
	return( new NNSamples( sensors.count() , targets.count() ) );
}

void NN::updateBackRepresentation( const float *targetValues )
{
	for( int k = 0; k < targets.count(); k++ )
		{
			NNVariable::Mapping *vm = targets[ k ];
			vm -> var -> calculateBackRepresentation( targetValues[ k ] , vm );
		}
}

int NN::addSensor( NNVariable *nv , bool createConnections , Random *random4weights )
{
	// add inputs
	int addInputs = nv -> getRepresentationSize();

	int pos = ( useInputsBias )? inputs.count() - 1 : inputs.count();
	inputs.insert( pos , addInputs , 0 );

	NNVariable::Mapping *vm = nv -> attachAsSensor( this , inputs.getAll() + pos ); 

	// add to sensor variables
	int posSensor = sensors.add( vm );

	// reflect connections
	for( int k = 0; k < layers.count(); k++ )
		layers[ k ] -> reflectInsertSensor( nv , posSensor , createConnections , random4weights );

	return( pos );
}

int NN::getNSensors() const
{
	return( sensors.count() );
}

int NN::getNInputs() const
{
	return( inputs.count() );
}

int NN::getExecuteStat() const
{
	return( executeStat );
}

void NN::clearExecuteStat()
{
	executeStat = 0;
}

void NN::clearValues()
{
	// clear inputs
	clearInputValues();

	// clear layers
	for( int k = 0; k < layers.count(); k++ )
		layers[ k ] -> clearValues();

	// clear targets
	clearTargetValues();
}

void NN::clearInputValues()
{
	inputs.set( 0 );
}

void NN::clearTargetValues()
{
	for( int k = 0; k < targets.count(); k++ )
		{
			NNVariable::Mapping *vm = targets[ k ];
			vm -> var -> clearValue();
		}
}

bool NN::getUseInputsBias() const
{
	return( useInputsBias );
}

bool NN::isInputBias( int p_input ) const
{
	// last input is bias if used
	if( useInputsBias )
		return( p_input == inputs.count() - 1 );

	return( false );
}

const float * const *NN::getInputs() const
{
	return( inputs.getAll() );
}

float *NN::getInputPtr( int p_input ) const
{
	return( inputs.getAt( p_input ) );
}

int NN::getNVars() const
{
	int nVars = 0;
	for( int k = 0; k < layers.count(); k++ )
		nVars += layers[ k ] -> getNVars();

	return( nVars );
}

void NN::execute()
{
	// execute by layers
	for( int k = 0; k < layers.count(); k++ )
		{
			NNLayer *layer = layers[ k ];
			layer -> execute();
		}

	// produce outputs
	calculateTargets();

	// statistics
	executeStat++;
}

float NN::getOutput( int p_output )
{
	return( *( layers.last() -> getOutputs()[ p_output ] ) );
}

const float * const *NN::getOutputs()
{
	return( outputs.getAll() );
}

float * const *NN::getOutputsRestoredFromTargets()
{
	return( outputsRestoredFromTargets.getAll() );
}

void NN::calculateTargets()
{
	for( int k = 0; k < targets.count(); k++ )
		{
			NNVariable::Mapping *vm = targets[ k ];
			vm -> var -> calculateValueFromRepresentation( vm );
		}
}

void NN::setSensors( const float *p_sensorValues )
{
	// copy/trasform inputs
	convertSensorValues( p_sensorValues );

	// move forward
	execute();
}

void NN::setSensors( NNSample *sample )
{
	setSensors( sample -> getSensors() );
}

/*#########################################################################*/
/*#########################################################################*/

void NN::convertSensorValues( const float *values )
{
	// convert values
	for( int k = 0; k < sensors.count(); k++ )
		{
			NNVariable::Mapping *vm = sensors[ k ];
			vm -> var -> setValueAndCalculateRepresentation( values[ k ] , vm );
		}
}

NNVariable::Mapping *NN::getSensor( int p_sensor ) const
{
	return( sensors[ p_sensor ] );
}

NNVariable *NN::getSensorVariable( int p_sensor ) const
{
	return( sensors[ p_sensor ] -> var );
}

NNVariable::Mapping *NN::getTarget( int p_target ) const
{
	return( targets[ p_target ] );
}

NNVariable *NN::getTargetVariable( int p_target ) const
{
	return( targets[ p_target ] -> var );
}

int NN::getNLayers() const
{
	return( layers.count() );
}

NNLayer *NN::getLayer( int pos ) const
{
	return( layers[ pos ] );
}

NNLayer *NN::addLayer( int nNeurons , NNInductionFunction *p_fi , NNActivationFunction *p_fa , bool p_useBias )
{
	NNLayer *layer = NNLayer::newInit( this , layers.count() , nNeurons , p_useBias );
	layer -> setInductionFunction( p_fi );
	layer -> setActivationFunction( p_fa );

	layers.add( layer );
	return( layer );
}

void NN::setBiasValues( float value )
{
	biasValue = value;
	resetBiasValues();
}

void NN::resetBiasValues()
{
	for( int k = layers.count() - 1; k >= 0; k-- )
		{
			NNLayer *pl = layers[ k ];
			if( pl -> getUseBias() )
				pl -> setBiasValues( biasValue );
		}

	// set bias input
	if( useInputsBias )
		inputs[ inputs.count() - 1 ] = biasValue;
}

void NN::setInputRanges( float minValue , float maxValue )
{
	// setup layers
	for( int k = 0; k < layers.count(); k++ )
		{
			NNLayer *pl = layers[ k ];
			pl -> setInputRanges( minValue , maxValue );
		}
}

void NN::setLayerInputRangesUnlimited()
{
	// setup layers
	for( int k = 0; k < layers.count(); k++ )
		{
			NNLayer *pl = layers[ k ];
			pl -> setInputRangesUnlimited();
		}
}

void NN::calculateLayerInputRanges( float wMin , float wMax , float ratio )
{
	// setup layers
	for( int k = 0; k < getNLayers(); k++ )
		{
			NNLayer *pl = getLayer( k );
			pl -> calculateInputRanges( wMin , wMax , ratio );
		}
}

int NN::getNOutputs() const
{
	return( layers.last() -> getNeuronCount() );
}

int NN::getNTargets() const
{
	return( targets.count() );
}

int NN::getNNeurons() const
{
	int n = 0;
	for( int k = 0; k < layers.count(); k++ )
		n += layers[ k ] -> getNeuronCount();

	return( n );
}

int NN::getNConnections() const
{
	int n = 0;
	for( int k = 0; k < layers.count(); k++ )
		n += layers[ k ] -> getNConnections();

	return( n );
}

const char *NN::getId() const
{
	return( id );
}

void NN::joinLayersDirect()
{
	for( int k = 0; k < layers.count(); k++ )
		{
			NNLayer *pl = layers[ k ];
			if( k == 0 )
				pl -> joinToPerceptronInputs();
			else
				pl -> joinToLayer( layers[ k - 1 ] );
		}
}

void NN::executeFromLayer( NNLayer *layer )
{
	for( int k = layer -> getPos(); k < layers.count(); k++ )
		{
			NNLayer *layer = layers[ k ];
			layer -> execute();
		}

	// final scaling
	calculateTargets();

	executeStat++;
}

void NN::executeFromLayerWithoutS( NNLayer *p_layer )
{
	p_layer -> executeFunctionOnly();

	// calculate other layers
	for( int k = p_layer -> getPos() + 1; k < layers.count(); k++ )
		{
			NNLayer *layer = layers[ k ];
			layer -> execute();
		}

	// final scaling
	calculateTargets();

	executeStat++;
}

NNLayer *NN::getFirstLayer() const
{
	return( layers.first() );
}

NNLayer *NN::getLastLayer() const
{
	return( layers.last() );
}

void NN::initWeightsRandom( float wMin , float wMax )
{
	Random randoms4Weights;
	randoms4Weights.createRangeRandomsFloat( wMin , wMax );

	initWeightsRandom( randoms4Weights );
}

void NN::initWeightsRandom( float wMin1 , float wMax1 , float wMin2 , float wMax2 )
{
	Random randoms4Weights;
	randoms4Weights.createTwoRangeRandomsFloat( wMin1 , wMax1 , wMin2 , wMax2 );

	initWeightsRandom( randoms4Weights );
}

void NN::initWeightsRandom( Random& randoms )
{
	// setup layers
	NNWeights pw( this );
	pw.setRandom( randoms );
	pw.setToPerceptron();
}

void NN::initWeightsStatic( const float *pwData , int count )
{
	NNWeights pw( this );
	ASSERT( pw.getNVars() == count );

	int nLayers = getNLayers();

	float *pwd = pw.getData();
	const float *pws = pwData;

	memcpy( pwd , pws , count * sizeof( float ) );
	pw.setToPerceptron();
}

void NN::initWeightsByWidrowNguyen()
{
	// get max of internal input range
	float rangeMax = 2;

	// get count of hidden neurons
	int hiddenCount = 0;
	for( int m = 0; m < getNLayers() - 1; m++ )
		{
			NNLayer *pl = getLayer( m );
			hiddenCount += pl -> getNonBiasNeuronCount();
		}

	// scale factor
	float inputCount = inputs.count();
	float scaleFactor = ( float )( pow(0.7*hiddenCount,1/inputCount)/rangeMax );

	// calculate weights
	Random rw;
	for( int z = 0; z < getNLayers(); z++ )
		{
			NNLayer *pl = getLayer( z );
			for( int t = 0; t < pl -> getNeuronCount(); t++ )
				{
					NNNeuron *pn = pl -> getNeuron( t );
					for( int s = 0; s < pn -> getNInputs(); s++ )
						{
							NNConnection *ic = pn -> getInputData()[ s ];
							if( ic -> bias )
								ic -> weight = rw.getRandomFloat( -scaleFactor , scaleFactor );
							else
								ic -> weight = rw.getRandomFloat( 0 , scaleFactor );
						}
				}
		}
}

// validation
NNValidateFunction *NN::getValidateFunction() const
{
	return( const_cast<NNValidateFunction *>( &validateFunction ) );
}

bool NN::validate( NNSample *sample , float *error )
{
	return( validateFunction.validate( sample , error ) );
}

bool NN::validate( NNSamples *samples , float *error )
{
	return( validateFunction.validate( samples , error ) );
}

void NN::joinSensors( ClassList<NNVariable>& p_sensors )
{
	ASSERT( sensors.count() == p_sensors.count() );

	// fill placeholders with variables - join first layer to inputs
	NNLayer *pl = layers.first();

	int n = NNVariables::getRepresentationSize( p_sensors );
	int nWithBias = ( useInputsBias )? n + 1 : n;
	inputs.create( nWithBias );
	
	float * const *pi = inputs.getAll();
	int pos = 0;
	for( int k = 0; k < p_sensors.count(); k++ )
		{
			NNVariable *nv = p_sensors[ k ];
			sensors[ k ] = nv -> attachAsSensor( this , pi + pos );
			pos += nv -> getRepresentationSize();
		}
}

void NN::joinTargets( ClassList<NNVariable>& p_targets )
{
	ASSERT( targets.count() == p_targets.count() );

	// fill placeholders with variables - join last layer to outputs
	NNLayer *pl = layers.last();

	int n = NNVariables::getRepresentationSize( p_targets );
	outputs.create( n );
	outputsRestoredFromTargets.create( n );
	
	float **pi = outputs.getAll();
	float * const *piBack = outputsRestoredFromTargets.getAll();
	int pos = 0;
	for( int k = 0; k < p_targets.count(); k++ )
		{
			NNVariable *nv = p_targets[ k ];

			// set pointers
			int rSize = nv -> getRepresentationSize();
			for( int m = 0; m < rSize; m++ )
				pi[ m + pos ] = pl -> getNeuron( m + pos ) -> getOutputPtr();

			targets[ k ] = nv -> attachAsTarget( this , pi + pos , piBack + pos );
			pos += rSize;
		}
}

/*#########################################################################*/
/*#########################################################################*/

const char *NN::NAME = "NN";

void NN::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NN::onCreate );

	// add own fields
	so -> addFieldString( "id" );
	so -> addFieldBool( "useInputsBias" );
	so -> addFieldFloat( "biasValue" );

	so -> addFieldIntList( "sensorVars" );
	so -> addFieldIntList( "targetVars" );

	so -> addFieldObjectList( "layers" , NNLayer::getSerializeObject() );
	so -> addFieldObject( "validateFunction" , NNValidateFunction::getSerializeObject() );
}

void NN::serialize( SerializeObject& so )
{
	so.setPropString( id , "id" , false );
	so.setPropBool( useInputsBias , "useInputsBias" );
	so.setPropFloat( biasValue , "biasValue" );

	int *sensorVars = ( int * )malloc( sizeof( int ) * sensors.count() );
	for( int k = 0; k < sensors.count(); k++ )
		sensorVars[ k ] = sensors[ k ] -> var -> getId();
	so.setPropIntList( sensorVars , sensors.count() , "sensorVars" , true );

	int *targetVars = ( int * )malloc( sizeof( int ) * targets.count() );
	for( k = 0; k < targets.count(); k++ )
		targetVars[ k ] = targets[ k ] -> var -> getId();
	so.setPropIntList( targetVars , targets.count() , "targetVars" , true );

	so.setPropObjectList( ( ClassList<Object>& )layers , "layers" , false );
	so.setPropObject( validateFunction , "validateFunction" );
}

void NN::deserialize( Object *parent , SerializeObject& so )
{
	// delete old
	freeData();

	id = so.getPropString( "id" , false );
	useInputsBias = so.getPropBool( "useInputsBias" );
	biasValue = so.getPropFloat( "biasValue" );

	// sensors/inputs
	inputs.clear();
	int nSensors;
	int *sensorVars = so.getPropIntList( "sensorVars" , &nSensors , false );

	// request variables from service
	NNVariablesContainer *vc = NNVariablesContainer::getInstance();

	int inputsCount = 0;
	for( int k = 0; k < nSensors; k++ )
		{
			NNVariable *nv = vc -> getVarById( sensorVars[ k ] );

			inputs.add( nv -> getRepresentationSize() , 0 );
			float * const *inputPtr = inputs.getAll() + inputsCount;

			nv -> attachAsSensor( this , inputPtr );
			inputsCount += nv -> getRepresentationSize();
		}

	so.getPropObjectList( ( ClassList<Object>& )layers , "layers" , true );

	NNValidateFunction *pf = ( NNValidateFunction * )so.getPropObject( "validateFunction" , false );
	validateFunction.set( pf );

	// attach layers
	int n = layers.count();
	for( k = 0; k < n; k++ )
		{
			NNLayer *pl = layers[ k ];
			pl -> attach( this , k );
		}

	// attach outputs to last layer
	NNLayer *lastLayer = layers.last();
	outputs.clear();
	outputs.create( lastLayer -> getNeuronCount() );
	for( k = 0; k < lastLayer -> getNeuronCount(); k++ )
		outputs[ k ] = lastLayer -> getNeuron( k ) -> getOutputPtr();

	// attach outputs to variables
	int nTargets;
	int *targetVars = so.getPropIntList( "targetVars" , &nTargets , false );

	int outputsCount = 0;
	outputsRestoredFromTargets.clear();
	outputsRestoredFromTargets.create( outputs.count() );
	for( k = 0; k < nTargets; k++ )
		{
			NNVariable *nv = vc -> getVarById( targetVars[ k ] );

			nv -> attachAsTarget( this , outputs.getAll() + outputsCount , outputsRestoredFromTargets.getAll() + outputsCount );
			outputsCount += nv -> getRepresentationSize();
		}
	ASSERT( outputsCount == outputs.count() );

	// bias
	resetBiasValues();
}
