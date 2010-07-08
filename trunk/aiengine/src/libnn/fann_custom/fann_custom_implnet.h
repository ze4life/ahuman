
class NNSolution;
class NNFinder;
class NNFinderFactory;
class NNRegression;
class NNRegressionFactory;

/*#########################################################################*/
/*#########################################################################*/

class NNSolution : public Object
{
public:
	NNSolution() {};
};

/*#########################################################################*/
/*#########################################################################*/

class NNFinder : public NNSolution
{
public:
	typedef struct {
		int succeedRatio;
		int minEpochCount;
		int maxEpochCount;
		int avgEpochCount;
		int restartsTotal;
		int epochsTotal;
		int setSensorsTotal;
		int validationFailures;
	} StatResults;

	typedef struct {
		int statCount;
		int hiddenLayerSize;
		float stopBitsPrecision;
		int minIterations;
		int maxIterations;
		int algorithm;
		char initWeights;
		float gradientRate;
		float wMin;
		float wMax;
		float wRandomMin;
		float wRandomMax;
		bool calculateHiddenInputRanges;
		bool errorFunctionLinear;
		float momentum;
		float steepness;
		float increaseFactorRPROP;
		float decreaseFactorRPROP;
		float deltaMinRPROP;
		float deltaMaxRPROP;
		float deltaZeroRPROP;
		float deltaZeroMinRPROP;
		float quickPropDecay;
		float quickPropMu;
		float quickPropMinStep;
		int maxRestarts;
	} StatParams;

public:
	// Object interface
	NNFinder();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static Object *onCreate( const char *className ) { return( new NNFinder ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	~NNFinder();

	// creation
	void create( const char *name , ClassList<NNVariable>& sensors , NNVariable *target , int hiddenLayerSize );

	// generic
	NN *getNN();
	NNVariables	*getVariables();

	// clustering
	bool findClass( float *sensors , int *classID , float *probability );

	// stat learning
	void learnStat( NNSamples *samplesLearn , NNSamples *samplesValidate , StatParams *sp , StatResults& res );

private:
	void freeData();
	bool learnStatIteration( NNSamples *samplesLearn , NNSamples *samplesValidate , StatParams *sp , 
		int *epochCount , int *epochCountTotal , int *setSensorsStat , int *restartsDone , int *validationFailures );
	void learnStatInitWeights( NN *p , NNStrategyBackPropagation *ps , char type , float wRandomMin , float wRandomMax );

private:
	AIEngine& engine;
	NNFinderFactory *eff;

	int nClassCount;
	float bitTolerance;

	// primary perceptron
	NN *p;
	NNStrategyBackPropagation *psBP;
	NNSamples *trainSamples;

	Random randoms4Weights;
};

/*#########################################################################*/
/*#########################################################################*/

// wrapper class for finder factory sample
class NNFinderFactorySample
{
	typedef enum {
		SA_UNKNOWN = -1 ,
		SA_nSensors = 0 ,
		SA_nTargets = 1 ,
		SA_COUNT = 2 ,
		SC_errorLevel = 2
	} FieldSA;

	typedef enum {
		SB_UNKNOWN = -1 ,
		SB_algorithm = 0 ,
		SB_nHiddenNeurons1 = 1 ,
		SB_learnRate = 2 ,
		SB_COUNT = 3
	} FieldSB;

	typedef enum {
		ST_UNKNOWN = -1 ,
		ST_avgEpochs = 0 ,
		ST_avgRestarts = 1 ,
		ST_avgExecuteStat = 2 ,
		ST_avgValidateError = 3 ,
		ST_COUNT = 4
	} FieldST;

	typedef enum {
		SYS_UNKNOWN = -1 ,
		SYS_SA = 0 ,
		SYS_SB = 1 ,
		SYS_COUNT = 2
	} FieldSYS;

public:
	NNFinderFactorySample( NNSample *fs , NNSample *fe );

	// error level calculation
	static float p2TargetFunction( NN *p );
	static float p2TargetFunction( const float *targets );
	static void adjustDimensions( NNSamples *ss );

	// construct NN
	static int getTrainSampleSensors( NNVariables *vars , ClassList<NNVariable>& sensors );
	static int getTrainSampleTargets( NNVariables *vars , ClassList<NNVariable>& targets );
	static int getStatSampleTargets( NNVariables *vars , ClassList<NNVariable>& sensors );
	static int getStatSampleSensors( NNVariables *vars , ClassList<NNVariable>& targets );

	// set FE props
	void setSA( FieldSA field , float value );
	float getSA( FieldSA field );

	void setSB( FieldSB field , float value );
	float getSB( FieldSB field );

	void setST( FieldST field , float value );
	float getST( FieldST field );

	void setSysVar( FieldSYS field , float value );
	float getSysVar( FieldSYS field );

	// set all at once
	void setStat( NNSamples *samplesLearn , NNSamples *samplesValidate , NNFinder::StatParams *sp , NNFinder::StatResults& res );

	// calculate FS from FE
	void completeFS( NN *nfe );

public:
	NNSample *fs; // nn params + error level -> nn props
	NNSample *fe; // nn params + nn props + sysvars -> error details
};

/*#########################################################################*/
/*#########################################################################*/

class NNFinderFactory : public Object
{
public:
	// Object interface
	NNFinderFactory();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static Object *onCreate( const char *className ) { return( new NNFinderFactory ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	void init();
	~NNFinderFactory();

	// generic
	NNVariables *getVariables();

	// default perceptron and training strategy
	NN *createDefaultPerceptron( const char *name , ClassList<NNVariable>& sensors , NNVariable *target , int hiddenLayerSize );
	NNStrategyBackPropagation *createDefaultStrategy( const NN *p );

	NNSample *addFactoryTrainSample();
	NNSample *addFactoryStatSample();

	// train factory function
	void trainFactorySample( NNSample *fs );
	void trainFactorySamples();

	// do factory function based on previous training
	NNFinder *create( NNSamples *trainSet );

	// add sample for class - each class has ID from 1 to nClassCount, while 0 means no class assigned to sample
	NNSample *addSample( NNSamples *samples , float *sensors , int classID );
	NNSamples *createSamples( int nSensors , int nClasses );	

	// tests
	void testPlay();
	void testFactory();

private:
	String getNewId();
	void freeData();

	// create first version of perceptrons
	void createInitial();
	void createInitialP1( NN **pp , NNStrategyBackPropagation **ps );
	void createInitialP2( NN **pp , NNStrategyBackPropagation **ps );

	// save to file
	void save();

	// training
	void mixFactoryStatSamples( NNSamples *stat , NNSamples *mix );
	void convertStatToFactory( NNSamples *mix , NNSamples *fts );

private:
	AIEngine& engine;
	const float internalDiffForDerivative;
	const float internalMinValue;
	const float internalMaxValue;
	const float boolTrue;
	const float boolFalse;
	NNRegressionFactory *erf;
	NNVariables *vars;

	int nPerceptronIDLast;

	// NN 1: sensor metrics (Ps) to finder parameters (Pn)
	NN *p1;
	NNStrategyBackPropagation *p1s;
	// NN 2: finder parameters (Pn) to network training metrics
	NN *p2;
	NNStrategyBackPropagation *p2s;
	// stat samples
	NNSamples *factoryStatSamples;
};

/*#########################################################################*/
/*#########################################################################*/

class NNRegression : public NNSolution
{
public:
	typedef struct {
		int succeedRatio;
		int minEpochCount;
		int maxEpochCount;
		int avgEpochCount;
		int restartsTotal;
		int epochsTotal;
		int setSensorsTotal;
		int validationFailures;
	} StatResults;

	typedef struct {
		int statCount;
		int hiddenLayerSize;
		float stopBitsPrecision;
		int minIterations;
		int maxIterations;
		int algorithm;
		char initWeights;
		float gradientRate;
		float wMin;
		float wMax;
		float wRandomMin;
		float wRandomMax;
		bool calculateHiddenInputRanges;
		bool errorFunctionLinear;
		float momentum;
		float steepness;
		float increaseFactorRPROP;
		float decreaseFactorRPROP;
		float deltaMinRPROP;
		float deltaMaxRPROP;
		float deltaZeroRPROP;
		float deltaZeroMinRPROP;
		float quickPropDecay;
		float quickPropMu;
		float quickPropMinStep;
		int maxRestarts;
	} StatParams;

public:
	// Object interface
	NNRegression();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static Object *onCreate( const char *className ) { return( new NNRegression ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	~NNRegression();

	// init
	void create( const char *name , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets , int hiddenLayerSize );

	// find output
	bool getTargets( const float *sensors , FlatList<float>& targets );
	void learnStat( NNSamples *samplesLearn , NNSamples *samplesValidate , StatParams *sp , StatResults& res );

private:
	void freeData();

	bool learnStatIteration( NNSamples *samplesLearn , NNSamples *samplesValidate , StatParams *sp ,
		int *epochCount , int *epochCountTotal , int *setSensorsStat , int *restartsDone , int *validationFailures );
	void learnStatInitWeights( NN *p , NNStrategyBackPropagation *ps , char type , float wRandomMin , float wRandomMax );

private:
	AIEngine& engine;
	NNRegressionFactory *erf;

	// primary perceptron
	NN *p;
	NNStrategyBackPropagation *psBP;
	NNSamples *trainSamples;

	Random randoms4Weights;
	float bitTolerance;
};

/*#########################################################################*/
/*#########################################################################*/

class NNRegressionFactory : public Object
{
public:
	// Object interface
	NNRegressionFactory();

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static Object *onCreate( const char *className ) { return( new NNRegressionFactory ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	void init();
	~NNRegressionFactory();

	// default perceptron and training strategy
	NN *createDefaultPerceptron( const char *name , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets , int hiddenLayerSize );
	NNStrategyBackPropagation *createDefaultStrategy( const char *name , const NN *p );

	// samples
	NNSamples *createSamples( int nSensors , int nTargets );
	void scaleBySamplesSimple( NNSamples *samples , NNVariables *vars , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets );
	void scaleBySamplesStddev( NNSamples *samples , NNVariables *vars , ClassList<NNVariable>& sensors , ClassList<NNVariable>& targets );

private:
	void freeData();
	String getNewId();
	void createInitial();
	void save();

	// training
	NN *createDerivationPerceptron( NNVariables *vars , NN *p , NNSamples *pSamples , int sensorFrom , int sensorTo , float ( *targetFunction )( NN *p ) );
	void getDerivatives( NN *p , int sensorFrom , int sensorTo , NNSample *sample , float *targets , float ( *targetFunction )( NN *p ) );

private:
	AIEngine& engine;
	const float internalDiffForDerivative;
	const float internalMinValue;
	const float internalMaxValue;
	NNVariables *vars;

	int nPerceptronIDLast;
};
