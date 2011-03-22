class NN;
class NNLayer;
class NNNeuron;
class NNWeights;
class NNSample;
class NNSamples;
class NNVariable;

/*#########################################################################*/
/*#########################################################################*/

class NNVariables : public Object
{
public:
	NNVariables();
	~NNVariables();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NNVariables ); };

public:
	static int getRepresentationSize( ClassList<NNVariable>& vars );

	// ID range
	void create( int size );
	void createLocal();
	void clear();

	int getMinId();
	int getMaxId();

	// variables container
	NNVariable *getVarById( int p_id );
	NNVariable *add();
	NNVariable *addCommonBool();
	NNVariable *addCommonNumber( bool limitLeft , float valueLeft , bool limitRight , float valueRight );
	NNVariable *addCommonNumberDerivative();
	NNVariable *addCommonCategory( int count );

	// sensor scaling
	void setSensorRanges( float *minValue , float *maxValue );
	void setSensorRanges( float minValue , float maxValue );

	// outputs
	void setOutputRanges( float minValue , float maxValue );

private:
	void addVar( NNVariable *nv );

private:
	int minId;
	int maxId;
	int newId;
	bool local;
	MapIntToClass<NNVariable> data;
};

/*#########################################################################*/
/*#########################################################################*/

class NNVariablesContainer : public Object
{
private:
	NNVariablesContainer();
	~NNVariablesContainer();

public:
	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	// static Object *onCreate( const char *className ) { return( new NNVariablesContainer ); };

public:
	// instance handling
	static NNVariablesContainer *getInstance();
	static void destroy();

	// register
	void registerVariables( NNVariables *vars );
	void unregisterVariables( NNVariables *vars );

	NNVariable *getVarById( int id );
	void allocateVarRange( int size , int *minId , int *maxId );

private:
	static NNVariablesContainer *singlton;
	int lastVarId;
	MapIntToClass<NNVariables> varsMap;
};

/*#########################################################################*/
/*#########################################################################*/

class NNVariable : public Object
{
public:
	typedef struct {
		NNVariable *var;
		NN *p;
	} Mapping;

	typedef enum {
		VarUnknown = 0 ,
		VarSimple = 1 ,
		VarCategory = 2
	} VariableType;

public:
	NNVariable( VariableType p_type ) { type = p_type; domain = 0; id = 0; };
	virtual ~NNVariable() {};

	// Object interface
	static const char *NAME;
	// virtual const char *getClass() { return( NAME ); };
	// virtual void serialize( SerializeObject& so );
	// virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( Object::createObject( className ) ); };

public:
	// generic
	VariableType getType() { return( type ); };
	void setId( int p_id ) { id = p_id; };
	int getId() { return( id ); };

	// domain
	void setDomain( int v ) { domain = v; };
	int getDomain() { return( domain ); };

	// value
	virtual void clearValue() = 0;
	virtual float getValue() = 0;

	// attach to NN
	virtual NNVariable::Mapping *attachAsSensor( NN *nn , float * const *values ) = 0;
	virtual NNVariable::Mapping *attachAsTarget( NN *nn , float **values , float * const *valuesBack ) = 0;

	// representation
	virtual int getRepresentationSize() = 0; // count of corresponding inputs or outputs
	virtual void setValueAndCalculateRepresentation( float value , NNVariable::Mapping *vm ) = 0;
	virtual void calculateBackRepresentation( float value , NNVariable::Mapping *vm ) = 0;
	virtual void calculateValueFromRepresentation( NNVariable::Mapping *vm ) = 0;

protected:
	int id;
	int domain;
	VariableType type;
};

/*#########################################################################*/
/*#########################################################################*/

class NNVariableSimple : public NNVariable
{
public:
	typedef struct {
		NNVariable::Mapping objs;
		float *pv; // representation for simple variable
		float *pvBack; // restore representation for simple variable
	} Mapping;

public:
	NNVariableSimple();
	~NNVariableSimple();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NNVariableSimple ); };

public:
	// value
	virtual void clearValue();
	virtual float getValue();

	// attach to NN
	virtual NNVariable::Mapping *attachAsSensor( NN *nn , float * const *values );
	virtual NNVariable::Mapping *attachAsTarget( NN *nn , float **values , float * const *valuesBack );

	// representation
	virtual int getRepresentationSize(); // count of corresponding inputs or outputs
	virtual void setValueAndCalculateRepresentation( float value , NNVariable::Mapping *vm );
	virtual void calculateBackRepresentation( float value , NNVariable::Mapping *vm );
	virtual void calculateValueFromRepresentation( NNVariable::Mapping *vm );

	// simple-specific
	Scale& getScale();
	void setVariableRange( float minValue , float maxValue );
	void setRepresentationRange( float minValue , float maxValue );

private:
	// variable value
	float value;
	Scale scale; // target representation: from=inputs/outputs, to=sensors/targets

	// map value to sensor/target networks
	// NNVariable class owned by NNVariables
	FixedPtrList<Mapping> sensorMapping;
	FixedPtrList<Mapping> targetMapping;
};

/*#########################################################################*/
/*#########################################################################*/

class NNVariableCategory : public NNVariable
{
public:
	typedef struct {
		NNVariable::Mapping objs;
		FlatList<float *> *pv; // representation for category variable (categoryCount legnth) - copy for target/pointers for sensor
		FlatList<float *> *pvBack; // restore representation for category variable from variable value
	} Mapping;

public:
	NNVariableCategory();
	~NNVariableCategory();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NNVariableCategory ); };

public:
	// value
	virtual void clearValue();
	virtual float getValue();

	// attach to NN
	virtual NNVariable::Mapping *attachAsSensor( NN *nn , float * const *values );
	virtual NNVariable::Mapping *attachAsTarget( NN *nn , float **values , float * const *valuesBack );

	// representation
	virtual int getRepresentationSize(); // count of corresponding inputs or outputs
	virtual void setValueAndCalculateRepresentation( float value , NNVariable::Mapping *vm );
	virtual void calculateBackRepresentation( float value , NNVariable::Mapping *vm );
	virtual void calculateValueFromRepresentation( NNVariable::Mapping *vm );

	// category-specific
	int getCategoryCount() { return( categoryCount ); };
	void setCategoryCount( int count ) { categoryCount = count; };

private:
	int categoryCount; // will be included in domain class

	// variable value
	int value;

	// map value to sensor/target networks
	// NNVariable class owned by NNVariables
	FixedPtrList<Mapping> sensorMapping;
	FixedPtrList<Mapping> targetMapping;
};

/*#########################################################################*/
/*#########################################################################*/

class NN : public Object
{
public:
	NN();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NN ); };

public:
	static NN *newInit( const char *id , int nSensors , int nTargets , bool p_useInputsBias );
	void init( const char *id , int nSensors , int nTargets , bool p_useInputsBias );

	~NN();

	// generic
	const char *getId() const;
	int getNVars() const;
	int getNNeurons() const;
	int getNConnections() const;
	bool getUseInputsBias() const;

	// create internal data/set variables after all initial construction work is done
	// all subsequent direct structure operations are prohibited, except from constructive learn algorithms
	void createFinally();
	// init weights
	void initWeightsStatic( const float *pw , int count );
	void initWeightsRandom( float wMin , float wMax );
	void initWeightsRandom( float wMin1 , float wMax1 , float wMin2 , float wMax2 );
	void initWeightsRandom( Random& randoms );
	void initWeightsByWidrowNguyen();

	// samples
	NNSamples *createSamples();

	// sensors
	int getNSensors() const;
	void setSensors( const float *sensors );
	void setSensors( NNSample *sample );
	NNVariable::Mapping *getSensor( int p_sensor ) const;
	NNVariable *getSensorVariable( int p_sensor ) const;

	// inputs (each sensor is input with the same ID)
	int getNInputs() const; // differs from sensors if use bias and any other internally derived inputs
	const float * const *getInputs() const;
	float *getInputPtr( int p_input ) const;
	bool isInputBias( int p_input ) const;
	void setInputRanges( float minValue , float maxValue );
	void setLayerInputRangesUnlimited();
	void setSensorInputRanges( float minValue , float maxValue );
	void calculateLayerInputRanges( float wMin , float wMax , float ratio );
	void clearInputValues();

	// layers
	NNLayer *addLayer( int nNeurons , NNInductionFunction *p_fi , NNActivationFunction *p_fa , bool useBias );
	NNLayer *getLayer( int pos ) const;
	NNLayer *getFirstLayer() const;
	NNLayer *getLastLayer() const;
	int getNLayers() const;
	void scaleBySamplesSimple( NNSamples *samples );
	void scaleBySamplesStddev( NNSamples *samples );

	// join sensors, layers and targets
	void joinSensors( ClassList<NNVariable>& sensors );
	void joinTargets( ClassList<NNVariable>& targets );
	void joinLayersDirect();

	// targets
	int getNTargets() const;
	NNVariable::Mapping *getTarget( int p_target ) const;
	NNVariable *getTargetVariable( int p_target ) const;
	void clearTargetValues();
	void updateBackRepresentation( const float *targets );

	// outputs (each target is output with the same ID)
	int getNOutputs() const;
	void setBiasValues( float value );
	void setOutputRanges( float minValue , float maxValue );
	float getOutput( int p_output );
	const float * const *getOutputs();
	float * const *getOutputsRestoredFromTargets();

	// calculations
	void execute();
	void executeFromLayer( NNLayer *layer );
	void executeFromLayerWithoutS( NNLayer *layer );
	int getExecuteStat() const;
	void clearExecuteStat();
	void clearValues();

	// validation
	NNValidateFunction *getValidateFunction() const;
	bool validate( NNSample *sample , float *error );
	bool validate( NNSamples *samples , float *error );

	// live modifications
	int addSensor( NNVariable *nv , bool createConnections , Random *random4weights );

private:
	void freeData();
	void convertSensorValues( const float *values );
	void calculateTargets();
	void resetBiasValues();

private:
	AIEngine& engine;

	// perceptron unique ID and dimensions
	String id;
	bool useInputsBias;
	float biasValue;

	// network variables
	FlatList<NNVariable::Mapping *> sensors;
	FlatList<NNVariable::Mapping *> targets;

	// internal processing
	ClassList<NNLayer> layers;
	NNValidateFunction validateFunction;

	// input (including bias - last)/output data 
	FixedPtrList<float> inputs;
	FlatList<float *> outputs;
	FixedPtrList<float> outputsRestoredFromTargets;

	// stat metrics
	int executeStat;
};

/*#########################################################################*/
/*#########################################################################*/

class NNLayer : public Object
{
public:
	NNLayer();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static Object *onCreate( const char *className ) { return( new NNLayer ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	static NNLayer *newInit( NN *p , int nPos , int nNeurons , bool usebias );
	void init( NN *p , int nPos , int nNeurons , bool usebias );
	~NNLayer();
	void createFinally();

	void attach( NN *p , int pPos );
	NN *getNN();
	int getPos();
	void clearValues();
	int getNConnections();

	// forward run
	void execute();
	void executeFunctionOnly();

	// input data
	void setInputRanges( float minValue , float maxValue );
	void setInputRangesUnlimited();
	void calculateInputRanges( float wMin , float wMax , float ratio );
	void joinToPerceptronInputs();
	void joinToLayer( NNLayer *pl );
	bool isBiasNeuron( int p_neuron );

	// neurons
	int getNeuronCount();
	int getNonBiasNeuronCount();
	NNNeuron *getNeuron( int pos );
	int getNVars();
	void setInductionFunction( const NNInductionFunction *p_f );
	float *getS( int p_neuron );
	void setActivationFunction( const NNActivationFunction *p_f );

	// bias neuron - output only
	bool getUseBias();
	void setBiasValues( float value );

	// outputs
	const float **getOutputs();
	void setOutputRanges( float minValue , float maxValue );

	// live modifications
	void reflectInsertSensor( NNVariable *nv , int pos , bool createConnections , Random *random4weights );
	void reflectInsertNeuron( NNLayer *layer , int pos , bool createConnections , Random *random4weights );

private:
	void clearData();

private:
	AIEngine& engine;
	NN *p;
	int nPos;

	ClassList<NNNeuron> neurons;		// neurons
	bool useBias;								// if true then last neuron in list is bias
	FlatList<const float *> outputs;			// outputs (ptrs to neuron outputs)
};

/*#########################################################################*/
/*#########################################################################*/

class NNNeuron : public Object
{
public:
	NNNeuron();
	NNNeuron( NNLayer *p_p );
	~NNNeuron();
	void createFinally();
	void attach( NNLayer *p_p );

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NNNeuron ); };

public:
	NNLayer *getLayer();
	void clearValues();

	// execution
	void execute();
	void executeSkipInduction();

	// inputs
	int getNInputs();
	NNConnection *getInputData( int pos );
	NNConnection * const *getInputData();
	Scale *getInputScale();

	// induction
	NNInductionFunction *getInductionFunction();
	float getInductionDerivative( int input );
	float *getS();
	void getRangeS( float wMin , float wMax , float *ptrMinS , float *ptrMaxS );

	// activation and outputs
	NNActivationFunction *getActivationFunction();
	Scale *getOutputScale();
	float getOutput();
	float getActivationDerivative();
	float *getOutputPtr();
	void setInitialOutput( float value );

	// connections
	void joinToPerceptronInputs();
	void joinToLayer( NNLayer *pl );
	int getNConnections();

	// live modifications
	void reflectInsertNeuron( NNLayer *layer , int pos , bool createConnections , Random *random4weights );
	void reflectInsertSensor( NNVariable *layer , int pos , bool createConnections , Random *random4weights );

private:
	// data
	NNLayer *layer;
	NNInductionFunction inductionFunction;
	NNActivationFunction activationFunction;

	FixedPtrList<NNConnection> inputConnections;	// connections to input neurons/perceptron input
	float s;											// induction outcome
	float output;										// final neuron output
};

/*#########################################################################*/
/*#########################################################################*/

class NNWeights : public Object
{
public:
	NNWeights();
	NNWeights( NN *p_p );
	~NNWeights();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NNWeights ); };

public:
	void attach( NN *p_p );

	NN *getNN();

	void getFromPerceptron();
	void setToPerceptron();
	void setRandomDefault(); // random in range [-0.8, -0.2] U [0.2, 0.8]
	void setRandom( Random& randoms );
	void setTo( const NNWeights *wp );
	void setIndexValue( int index , float value );

	void setToCenter();
	int getNVars();
	float *getVarPtrByIndex( int index );
	float getVarValue( int index );

	float *getData();
	bool equals( NNWeights *pw , float tolerance );

	float *getNeuronWeights( int layer , int neuron );

private:
	// data
	NN *p;
	TwoIndexVarArray<int> startIndex; // start index in [weights] for given layer/neuron
	FlatList<float> weights; // layer by layer: [neuron non-bias/bias],,,[non-bias/bias]
	FlatList<float *> weightsPtr;
};

/*#########################################################################*/
/*#########################################################################*/

class NNSample : public Object
{
public:
	NNSample();
	NNSample( int nSizeIn , int nSizeOut , bool createID );
	NNSample( int nSizeIn , int nSizeOut , float *sensors , float *targets );
	~NNSample();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NNSample ); };

public:
	NNSample *duplicate() const;

	// parameters
	int getId() const;
	int getNSensors() const;
	int getNTargets() const;

	// data
	float *getSensors() const;
	float *getTargets() const;
	int getClusterID() const;
	void setClusterID( int cluster );
	void setSensors( const float *values );
	void setTargets( const float *values );

	// learn data
	void setError( float v );
	float getError() const;
	void clearLearnData();
	void clearValidateData();
	void setValidateFailed( float error );
	bool isValidateFailed() const;
	float getValidateError() const;

	// live modifications
	void addSensor( float defaultValue );
	void addSensors( int count , float defaultValue );

private:
	FlatList<float> sensors;
	FlatList<float> targets;

	static int nIDLast;
	int id;
	int clusterID;

	// learn data
	float lastError;
	bool lastValidateFailed;
	float lastValidateError;
};

/*#########################################################################*/
/*#########################################################################*/

class NNSamples : public Object
{
	typedef enum {
		// unlimited set
		LIMITTYPE_EMPTY	= 0 ,
		// first in first out method
		LIMITTYPE_FIFO = 1 ,
		// wipe out any random
		LIMITTYPE_RANDOM = 2
	} LimitType;

public:
	NNSamples();
	NNSamples( int nIn , int nOut );
	NNSamples( NN *p );
	~NNSamples();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };
	static Object *onCreate( const char *className ) { return( new NNSamples ); };

public:
	int sizeIn() const;
	int sizeOut() const;

	// items
	int count() const;
	NNSample *getByPos( int pos ) const;
	NNSample *getById( int id ) const;
	int add( const NNSample *sample );
	void add( const NNSamples *samples );
	NNSample *add();
	NNSample *add( float *sensors , float *targets );
	
	void clear();
	void clearLearnData();
	void clearValidateData();

	// self-limiting
	void setLimitFIFO( int count );
	void setLimitRandom( int count );

	// scaling
	void getSensorRange( int pos , float *vMin , float *vMax ) const;
	void getTargetRange( int pos , float *vMin , float *vMax ) const;
	void getValueRange( int pos , float *vMin , float *vMax , bool sensors ) const;

	void getSensorStat( int pos , float *vMean , float *vStddev ) const;
	void getTargetStat( int pos , float *vMean , float *vStddev ) const;
	void getValueStat( int pos , float *vMean , float *vStddev , bool sensors ) const;

	// set operations
	NNSamples *duplicate() const;
	NNSamples *copy( int posFrom , int posUpTo ) const;
	void merge( NNSamples *src );

	// live modifications
	void addSensor( float defaultValue );
	void addSensors( int count , float defaultValue );

private:
	void wipeOut();

private:
	int nSizeIn;
	int nSizeOut;
	MapIntToClass<NNSample> data;

	// limiting
	LimitType limitType;
	int maxSize;
};

