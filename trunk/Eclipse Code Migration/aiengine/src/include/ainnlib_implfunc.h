// perceptron functions

class NNInductionFunction;
class NNActivationFunction;
class NNValidationFunction;
class NNClusterFunction;
class NNErrorFunction;
class NNStopFunction;

class NN;
class NNSample;
class NNSamples;
class NNStrategy;
class NNNeuron;

/*#########################################################################*/
/*#########################################################################*/

typedef struct {
	NNNeuron *sourceNeuron;	// if NULL then connection to perceptron input
	int sourceLayerPos;					// -1 if perceptron input
	int sourceLayerNeuronPos;			// perceptron input position, if sourceNeuron=NULL
	float weight;
	const float *inputPtr;
	bool bias;
} NNConnection;

/*#########################################################################*/
/*#########################################################################*/

class NNInductionFunction : public Object
{
	typedef enum {
		FANN_EMPTY = 0 ,
		// f(x) = sum( Wk * Xx )
		FANN_WEIGHTEDSUM = 1 ,
	} InductionFunction;

public:
	NNInductionFunction();
	~NNInductionFunction();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new NNInductionFunction ); };
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	void setWeightedSum();

	float calculate( FixedPtrList<NNConnection>& inputs );
	void set( const NNInductionFunction *p_f );
	float getDerivative( float s , NNConnection *ic );

private:
	InductionFunction functionType;
};

/*#########################################################################*/
/*#########################################################################*/

class NNActivationFunction : public Object
{
	typedef enum {
		FANN_EMPTY = 0 ,
		// f(x) = x
		FANN_LINEAR = 1 ,
		// f(x) = { 0 (x<0), x (0<x<1), 1 (x>1) }
		FANN_LINEAR_PIECE = 2 ,
		// f(x) = { -1 (x<-1), x (-1<x<1), 1 (x>1) }
		FANN_LINEAR_PIECE_SYMMETRIC = 3 ,
		// f(x) = 1/(1+exp(-2x))
		FANN_SIGMOID = 4 ,
		// f(x) = -1+2/(1+exp(-2x))
		FANN_SIGMOID_SYMMETRIC = 5 ,
		// f(x) = {
		//		0 (x<-e),
		//		linear: (-e,0.005)-(-e/2,0.05)
		//		linear: (-e/2,0.05)-(-e/5,0.25)
		//		linear: (-e/5,0.25)-(e/5,0.75)
		//		linear: (e/5,0.75)-(e/2,0.95)
		//		linear: (e/2,0.95)-(e,0.99)
		//		1 (x>e)
		//	}
		FANN_SIGMOID_STEPWISE = 6 ,
		// f(x) = {
		//		-1 (x<-e),
		//		linear: (-e,-0.99)-(-e/2,-0.89)
		//		linear: (-e/2,-0.89)-(-e/5,-0.5)
		//		linear: (-e/5,-0.5)-(e/5,0.5)
		//		linear: (e/5,0.5)-(e/2,0.89)
		//		linear: (e/2,0.89)-(e,0.99)
		//		1 (x>e)
		//	}
		FANN_SIGMOID_SYMMETRIC_STEPWISE = 7 ,
		// f(x) = { 0 (x<0), 1 (x>=0) }
		FANN_THRESHOLD = 8 ,
		// f(x) = { -1 (x<0), 1 (x>=0) }
		FANN_THRESHOLD_SYMMETRIC = 9 ,
		// f(x) = exp(-x*x)
		FANN_GAUSSIAN = 10 ,
		// f(x) = 2exp(-x*x)-1
		FANN_GAUSSIAN_SYMMETRIC = 11 ,
		// f(x) = 0.5+0.5*x/(1+abs(x))
		FANN_ELLIOT = 12 ,
		// f(x) = x/(1+abs(x))
		FANN_ELLIOT_SYMMETRIC = 13 ,
		// f(x) = 0.5+0.5*sin(x)
		FANN_SIN = 14 ,
		// f(x) = sin(x) ,
		FANN_SIN_SYMMETRIC = 15 ,
		// f(x) = 0.5+0.5*cos(x)
		FANN_COS = 16 ,
		// f(x) = cos(x)
		FANN_COS_SYMMETRIC = 17
	} ActivationFunction;

public:
	NNActivationFunction();
	~NNActivationFunction();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new NNActivationFunction ); };
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	void initLinear();
	void initLinearPiece();
	void initLinearPieceSymmetric();
	void initSigmoid();
	void initSigmoidSymmetric();
	void initSigmoidStepwise();
	void initSigmoidSymmetricStepwise();
	void initThreshold();
	void initThresholdSymmetric();
	void initGaussian();
	void initGaussianSymmetric();
	void initElliot();
	void initElliotSymmetric();
	void initSin();
	void initSinSymmetric();
	void initCos();
	void initCosSymmetric();

	// init function
	void initFunction( ActivationFunction ft , bool symmetric , bool scaleOutputs );
	// get string function name representation
	const char *getName();
	void set( const NNActivationFunction *p_f );

	// get function value - non-scaled input, 
	float getOutput( float value );
	// get derivative by desired output
	float getDerivative( float input , float output );

	// steepness
	void setSteepness( float value );
	float getSteepness();

	// scale functions
	Scale *getInputScale();
	Scale *getOutputScale();
	void setInputRange( float minReal , float maxReal );
	void setOutputRange( float minDesired , float maxDesired );
	void setNoScaleInput( bool value );
	void setNoScaleOutput( bool value );
	bool getNoScaleInput();
	bool getNoScaleOutput();
	float getReverse( float value );

	float scaleInputValue( float value );
	float scaleOutputValue( float value );
	float unscaleInputValue( float value );
	float unscaleOutputValue( float value );

private:
	// called by function implementation
	void setInputFunction( float minFunction , float maxFunction );
	void setOutputFunction( float minFunction , float maxFunction );

	// various implementation - w/o scaling
	float getOutputFunction( float internalInput );
	float getDerivativeFunction( float internalInput , float internalOutput );
	float getReverseFunction( float value );

	// helpers
	float clip( float v , float min , float max );
	float getLinear( float v1, float r1, float v2, float r2, float x );
	float getStepwise( float v1, float v2, float v3, float v4, float v5, float v6, 
		float r1, float r2, float r3, float r4, float r5, float r6, 
		float min, float max, float x );

private:
	// type: NeuronFunction
	ActivationFunction functionType;
	bool symmetric;
	float steepness;

	// scale data
	Scale inputScale;
	Scale outputScale;

	// function names
	static const char *functionNames[ 20 ];
};

/*#########################################################################*/
/*#########################################################################*/

class NNErrorFunction : public Object
{
	typedef enum {
		FANN_ERRORFUNC_EMPTY = 0 ,
		// standard function
		FANN_ERRORFUNC_LINEAR = 1 ,
		// agressively targets outputs that
		// differ much from the desired, while not targetting outputs that only differ a little that much.
		// This activation function is not recommended for cascade training and incremental training
		FANN_ERRORFUNC_TANH = 2
	} ErrorFunction;

public:
	NNErrorFunction();
	~NNErrorFunction();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new NNErrorFunction ); };
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

	static NNErrorFunction *newInit( NN *p_p );

public:
	void init( NN *p_p );
	void attach( NN *p_p );
	void set( const NNErrorFunction *p_p );

	float getErrorSampleProgress( NNSample *sample );
	float getErrorSignalForBP( int p_output );
	float getErrorMSE( NNSample *sample );
	float getErrorSignalForBits( int p_output );
	float getErrorForBP( NNSample *sample );

	float getCurrentErrorValue();
	void setCurrentErrorValue( float error );

	void setTranslationTanh();
	void setTranslationLinear();

private:
	// get function value
	float getInternal( NNSample *useSample , bool translate , bool updateOutputs );
	float getNormalized( NNSample *useSample , bool translate , bool updateOutputs );

	float getSignalInternal( int p_output , bool translate );
	float getSignalNormalized( int p_output , bool translate );

	float translateSignal( float primarySignal );

private:
	NN *p;

	ErrorFunction errorFunction;

	float currentError;
	bool packetMode;
};

/*#########################################################################*/
/*#########################################################################*/

class NNStopFunction : public Object
{
	typedef enum {
		FANN_STOPFUNC_EMPTY = 0 ,
		// output deviation
		FANN_STOPFUNC_OUTPUTMSE = 1 ,
		// number of neurons with major deviation
		FANN_STOPFUNC_OUTPUTBIT = 2
	} StopFunction;

public:
	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new NNStopFunction ); };
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	NNStopFunction();
	~NNStopFunction();

	static NNStopFunction *newInit( NN *p , NNErrorFunction *ef );

public:
	void attach( NN *p );
	void setErrorFunction( NNErrorFunction *ef );
	NNErrorFunction *getErrorFunction();
	void set( const NNStopFunction *p_p );

	void setMinIterations( int v );
	void setMaxIterations( int v );
	int getMinIterations();
	int getMaxIterations();

	// stop modes
	void setModeMSEOne( NNSample *sample , float desiredError );
	void setModeMSEMany( NNSamples *samples , float desiredError );
	void setModeBitsOne( NNSample *sample , float bitFailLimit , int maxFailedNeurons );
	void setModeBitsMany( NNSamples *samples , float bitFailLimit , int maxFailedNeurons );
	void setModeMSE( float p_desiredError );
	void setModeBits( float p_bitFailLimit , int p_maxFailedNeurons );
	void setModeOne( NNSample *sample );
	void setModeMany( NNSamples *samples );

	// get function value
	bool stopConditionFound( int epoch , bool *psuccess );
	float getCurrentErrorValue();
	float calculateErrorValue();
	float calculateErrorValueMSE();
	float calculateErrorValueBits();

private:
	bool stopConditionFoundMSE();
	bool stopConditionFoundBits();

	int calculateBits( NNSamples *samples );
	int calculateBits( NNSample *sample );

private:
	AIEngine& engine;

	NN *p;
	NNErrorFunction *ef;

	// mode
	StopFunction functionType;
	NNSamples *execSamples;
	NNSample *execSample;
	bool modeOne;

	// MSE
	float currentError;
	float desiredError;

	// bit count
	float bitFailLimit;
	int maxFailedNeurons;

	int minIterations;
	int maxIterations;
};

/*#########################################################################*/
/*#########################################################################*/

class NNValidateFunction : public Object
{
	typedef enum {
		FANN_VALIDATEFUNC_EMPTY = 0 ,
		// internal (output) deviation per one sample
		FANN_VALIDATEFUNC_AVGOUTPUTMSE = 1 ,
		// number of neurons with major internal deviation per one sample
		FANN_VALIDATEFUNC_AVGOUTPUTBIT = 2
	} ValidateFunction;

public:
	NNValidateFunction();
	~NNValidateFunction();

	// Object interface
	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static void createSerializeObject();
	static Object *onCreate( const char *className ) { return( new NNValidateFunction ); };
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	void attach( NN *p );
	void set( NNValidateFunction *pf );

	void setValidateAvgOutputMSE( float error );
	void setValidateAvgOutputBits( float bitFailLimit , float avgFailedNeurons );

	bool validate( NNSample *sample , float *error );
	bool validate( NNSamples *samples , float *error );

private:
	bool validateAvgOutputMSE( NNSample *sample , float *error );
	bool validateAvgOutputBit( NNSample *sample , float *error );

private:
	AIEngine& engine;
	NN *p;

	ValidateFunction functionType;

	// MSE
	float desiredError;

	// bit count
	float bitFailLimit;
	float avgFailedNeurons;
};
