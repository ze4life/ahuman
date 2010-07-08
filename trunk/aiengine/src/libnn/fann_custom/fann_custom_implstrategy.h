// perceptron learn strategies

class NNStrategy;
class NNBPSHelper;
class NNStrategyBackPropagation;
class NNStrategyScan;
class NNStrategyScanIteration;
class NNStrategyScanItem;
class NNScanPoint;

class NNFinder;
class NNRegression;

/*#########################################################################*/
/*#########################################################################*/

// back propagation strategy show helper
class NNStrategyHelper
{
public:
	NNStrategyHelper( Logger& logger );
	void attach( NN *p_p );
	void attach( NNStrategy *st );
	void attach( NNFinder *ef );
	void attach( NNRegression *er );
	void attachSamples( NNSamples *samplesLearn , NNSamples *samplesValidate );

	// show events
	void onStartLearnSample( NNSample *sample );
	void onStartIterateOneSample( NNSample *sample , float startError );
	void onStopIterateOneSample( bool isChangeDone , NNSample *sample , float oldError , float newError );
	void onCheckGlobalMinBySubset( int point , MultiIndexIterator& mi , bool beyond , float error , float errorMin , int countChecked , bool final , int *axisIndex , int startIndexPos );
	void onDoLearnScan( NNSamples *samples , int iterationsDone , int timePassed , int numberOfIterations , ClassList<NNStrategyScanIteration>& runByPrecision , NNScanPoint *spBest , bool loopDetected );

	void showPerceptron( const char *preface );
	void showPerceptronClasses2();
	void showScanPoint( int id , NNScanPoint *ps , ClassList<NNStrategyScanItem>& randomValues );
	void showSamplesVariance( NNSamples *samples , NNWeights *pw );
	void showSamplesActual( const char *prefix , NNSamples *samples );
	void showSampleActual( NNSample *sample );
	void showValidateFailedSamples( NNSamples *samples );
	void showAxisError( int *axisIndex , float *axisErrorData , int nVars );

	void showIndexes( MultiIndexIterator& mi , float error );
	void showIndexesAround( MultiIndexIterator& mi , float error );
	void showWeights( NNWeights *pw );
	void showScanPoint( int id , NNScanPoint *ps );
	void showScanIteration( NNSamples *samples , NNWeights *sp , ClassList<NNScanPoint> *best , ClassList<NNStrategyScanItem>& axisValues , int countRuns , int minPoints , int bestChanges , float wChangeLimit );
	void showBestPoints( ClassList<NNScanPoint> *best );
	void showScanSlices( ClassList<NNStrategyScanItem>& axes , float *data , int axisItems , int pointsToCheck );
	void showSamplesVariance( NNSamples *samples );
	void showChanges( const char *preface , NNStrategyBackPropagation *bp );
	void showLayer( NNLayer *layer );
	void showLayerChanges( NNStrategyBackPropagation *bp , NNLayer *layer );
	void showNeuron( NNLayer *layer , int p_neuron );
	void showDelta();
	void showSamples( const char *prefix , NNSamples *samples );
	void showSensors();
	void showInputs();
	void showOutputs();
	void showTargets();

private:
	void showFunction( NNActivationFunction *f );
	void showSample( NNSample *sample );
	void showSGradient( NNLayer *layer , NNSample *sample , const float *inputs , int p_output , float range , int count , float expected );
	void showIGradient( NNLayer *layer , NNSample *sample , const float *inputs , int p_input , float range , int count );
	void showWGradient( NNLayer *layer , NNSample *sample , const float *inputs , int p_output , int p_input , float range , int count );
	void showWGradientBias( NNLayer *layer , NNSample *sample , const float *inputs , int p_output , float range , int count );
	void showWGradientHistory( NNSamples *samples , NNLayer *layer , const float *inputs );
	void showWGradientHistoryWeight( NNSamples *samples , NNLayer *layer , const float *inputs , int p_output , int p_input , int count , float delta );

	void investigateChangeFailureBP( NNSample *sample , NNLayer *layer , int p_output );
	void investigateBadHistory( NNSample *sample , NNLayer *layer , int p_output );
	void evaluateHistoryImpactBP( NNSamples *samples , NNLayer *layer , int p_output );
	void evaluateSampleImpactBP( NNSample *sample , NNLayer *layer , int p_output );
	float calculateSChangeBP( NNLayer *layer , const float *inputs , int p_output );
	void calculateVarianceAndDelta( NNLayer *layer , NNSample *sample , float *s , float *v , float *dVdS );

	void calculateBestGradientFromCurrent( NNSamples *samples , NNLayer *layer , const float *inputs , TwoIndexArray<float>& range , int steps , bool p_show );
	void iterateWeights( NNSamples *samples , int var , TwoIndexArray<float>& range , int steps , NNLayer *layer , const float *inputs , bool p_show , TwoIndexArray<float>& layerWeightsBest , float& varianceBest );
	float getMaxHistoryVariance( NNSamples *samples );
	void showHistoryImpact( NNSamples *samples );
	void checkDeltaValue( NNLayer *layer , NNSample *sample , int p_output , float delta );
	String getChangeStringBP( NNLayer *layer , int p_neuron );
	bool checkPointSymbol2( NNSamples *samples , float s0 , float s1 , float stepXAxis , float stepYAxis , char& classSymbol );
	String getVariable( NNVariable::Mapping *vm , bool isSensor );
	String getCategoryVariableValues( NNVariableCategory::Mapping *vm );

private:
	AIEngine& engine;
	Logger& logger;

	NN *p;
	NNStrategy *st;
	NNFinder *ef;
	NNRegression *er;
	NNSamples *samplesLearn;
	NNSamples *samplesValidate;
};

/*#########################################################################*/
/*#########################################################################*/

class NNStrategy
{
public:
	NNStrategy( Logger& p_logger );

	// Object interface

	// generic functions
	virtual bool learn( NNSamples *samples , NNWeights *pwBest , float *pvar ) { throw RuntimeError( "NNStrategy::learn not implemented" ); };
	virtual bool learn( NNSample *sample , NNWeights *pwBest , float *pvar ) { throw RuntimeError( "NNStrategy::learn not implemented" ); };

public:
	~NNStrategy();
	void attach( NN *p_p );
	NN& getNN();
	NNStrategyHelper& getHelper();

	NNStopFunction *getStopFunction();
	NNErrorFunction *getErrorFunction();

protected:
	AIEngine& engine;
	NN *p;
	NNStrategyHelper helper;

protected:
	NNStopFunction stopFunction;
	NNErrorFunction errorFunction;
};

/*#########################################################################*/
/*#########################################################################*/

class NNStrategyBackPropagation : public NNStrategy , public Object
{
public:
	typedef struct {
		float delta;
		float errorSignal;
	} NeuronData;

	typedef struct {
		NeuronData *nd;
		float change;
		float slope;
		float slopePrev;
		float *weightPtr;
	} ConnectionData;

	typedef enum {
		FANN_TRAIN_UNKNOWN = 0 ,
		// standard backpropagation algorithm, update weights after each sample
		FANN_TRAIN_INCREMENTAL = 1 ,
		// weights are updated once during epoch
		FANN_TRAIN_BATCH = 2 ,
		// advanced batch training algorithm, adaptive - not use the learning_rate (iRPROP)
		FANN_TRAIN_RPROP = 3 ,
		// advanced batch training algorithm, uses the learning_rate parameter
		FANN_TRAIN_QUICKPROP = 4
	} TrainingAlgorithm;

public:
	// Object interface
	NNStrategyBackPropagation();
	void attach( NN *p );

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static Object *onCreate( const char *className ) { return( new NNStrategyBackPropagation ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

	// learn functions
	virtual bool learn( NNSamples *vm , NNWeights *pwBest , float *pvar );
	virtual bool learn( NNSample *sample , NNWeights *pwBest , float *pvar );

public:
	static NNStrategyBackPropagation *newInit( NN *p_p );
	~NNStrategyBackPropagation();
	void init( NN *p_p );

	int getEpochCount();
	NeuronData *getNeuronData( NNNeuron *pn );
	ConnectionData *getConnectionData( NNConnection *ic );
	void applyChanges();
	void rollbackChanges();

	// set training algorithm
	void setTrainingIncremental();
	void setTrainingBatchSimple();
	void setTrainingBatchRProp();
	void setTrainingBatchQuickProp();
	bool isTrainingBatchRProp();

	// set strategy properties
	void setSmoothLearning( bool p_smooth );
	void setGradientRate( float p_value );
	void setSmoothRate( float p_value );
	void setWeightRange( float p_valueMin , float p_valueMax );

	// rprop specific
	void setRPropFactor( float increaseFactor , float decreaseFactor );
	void setRPropDelta( float deltaMin , float deltaMax , float deltaZero , float deltaZeroMin );

	// quickprop specific
	void setQuickPropDecay( float decay );
	void setQuickPropMu( float mu );
	void setQuickPropMinStep( float minStep );

	// get strategy properties
	bool getSmooth();
	float getGradientRate();
	float getSmoothRate();
	NNSamples *getSamples();

private:
	void initialize( NN *p_p );
	void initBatch();

	bool doEpoch( NNSamples *samples , float *variance );
	bool iterateSamplesOneByOne( NNSamples *samples , float *variance );
	bool iterateOneSample( NNSample *sample , float *precision );
	void clearDataBeforeLearn();

	void updateSlopesBatch( NNSample *sample , bool init );
	bool updateWeightsSimpleBatch( NNSamples *samples , float *learnMaxVariance );
	bool updateWeightsIRPropM( NNSamples *samples , float *learnMaxVariance );
	bool updateWeightsQuickProp( NNSamples *samples , float *learnMaxVariance );
	void doChangeWeightIRPropM( float *pw , float *pChange , float *pSlopePrev , float *pSlope );
	void doChangeWeightQuickProp( int numData , float *pw , float *pChange , float *pSlopePrev , float *pSlope );

	bool iterateSamplesSimpleBatch( NNSamples *samples , float *variance );
	bool iterateSamplesRProp( NNSamples *samples , float *variance );
	bool iterateSamplesQuickProp( NNSamples *samples , float *variance );

	void updateDelta( NNSample *sample );
	bool adjustWeights( NNSample *sample );

	float updateFromLayer( NNSample *sample , NNLayer *layer );
	bool checkDeltaApplicable( NNLayer *layer , const float *inputs , int p_output , float delta );

private:
	int epochCount;

	float nuFixed; // fixed rate of gradient method
	float wLimitMin; // weight limits
	float wLimitMax;

	TrainingAlgorithm trainingAlgorithm;
	bool smooth;
	float mu; // slow down rate of weight changing, used if smooth = true

	float rpropIncreaseFactor;
	float rpropDecreaseFactor;
	float rpropDeltaMin;
	float rpropDeltaMax;
	float rpropDeltaZero;
	float rpropDeltaZeroMin;

	float quickPropDecay;
	float quickPropMu;
	float quickPropMinStep;

	// perceptron learn data
	NNSamples *execSamples;

	MapPtrToClass<NNNeuron, NeuronData> neuronData;
	MapPtrToClass<NNConnection, ConnectionData> connectionData;
};

/*#########################################################################*/
/*#########################################################################*/

class NNStrategyScanItem
{
public:
	float getPointValue( int point )
		{
			return( fromValue + ( point * ( toValue - fromValue ) ) / ( totalPoints - 1 ) );
		};

public:
	int index;
	float *ptrValue;
	float centerValue;

	float wValueLimitMin;
	float wValueLimitMax;

	float fromValue;
	float toValue;
	int totalPoints;
};

/*#########################################################################*/
/*#########################################################################*/

class NNScanPoint
{
public:
	NNScanPoint( NN *p_p );
	NNScanPoint( NN *p_p , int p_id );
	NNScanPoint( NNScanPoint *src );

	void setFromPoint( NNScanPoint *src );

	int getId();
	void setVariance( float value );
	float getVariance();

	NNScanPoint *getSourcePoint();
	NNWeights *getWeights();

	bool isStatusUnknown();
	bool isMinimum();
	void setMinimum( bool isMinimum );
	void reuse( int p_id );
	bool isSearchDirectionUsed( const char *sd );
	void addSearchDirection( const char *searchDirection );

private:
	int id;
	NNScanPoint *src;
	NNWeights pw;
	bool statusUnknown;
	bool minimum;
	float variance;
	MapStringToClass<NNScanPoint> searchDirectionsUsed;
};

/*#########################################################################*/
/*#########################################################################*/

class NNStrategyScanIteration : public Object
{
	typedef enum {
		PACKET_ERRFUNC_MAX = 1 ,
		PACKET_ERRFUNC_VAR = 2
	} PacketErrFunc;

public:
	NNStrategyScanIteration( NNStrategyScan *strategy , NN *p_p , int p_bestMax , 
		int p_axisItems , int p_pointsToCheck );
	~NNStrategyScanIteration();

	NNScanPoint *createBestPoint( NNWeights *point );
	ClassList<NNScanPoint>& getBestPoints();

	int addMinPoint( NNScanPoint *ps );
	bool scanBestPoints( NNSamples *samples , NNSample *p_sample , NNStrategyScanIteration *runNext );

	int getIterationCount();
	void clearIterationCount();

	void setSearchArea( float value );
	float getSearchArea();

private:
	bool find( NNScanPoint *p_spStartPoint , float *error );
	void copyBestPoints( ClassList<NNScanPoint> *dst );

	bool selectSearchDirection( NNScanPoint *p_spStartPoint );
	bool chooseRandomAxisItems( NNScanPoint *p_spStartPoint );
	bool chooseBestAxisItems( NNScanPoint *p_spStartPoint );
	String getDirection( int *axes );
	
	void findWalk( int axisItem , float*& pe );
	
	NNStrategyScanItem *addAxis( int axisIndex , float *ptr = NULL );
	int onSortAxis( const int& v1 , const int& v2 );
	int onSortAxisFirst( const int& v1 , const int& v2 );
	float calculateErrorByAxis( int axis );
	float calculateCurrentError();

	// find minimums
	void findMinPoints();
	int addMinItem( MultiIndexIterator& mp , float errorValue );
	void setWeightsFromMultiIndexIterator( NNWeights *pw , MultiIndexIterator& mp );

	bool checkGlobalMin( int id , float searchArea , NNScanPoint *ps );
	bool checkGlobalMinBySubset( int id , int startIndexPos , int count , float errorMin , NNWeights *pw );
	bool checkTheSamePoint( NNWeights *pw , int pos );

private:
	AIEngine& engine;
	Logger logger;

	NNStrategyScan *strategy;
	NNStrategyHelper helper;
	NN *p;
	NNSamples *samples;
	NNSample *sample;

	ClassList<NNScanPoint> best;
	NNWeights *pwStartPoint;
	int axisItems;
	int pointsToCheck;
	int nVars;
	float searchArea;
	String searchDirection;
	int uniqueID;
	PacketErrFunc errFunc;

	float *axisErrorData; // [nVars] in sort only
	int *axisIndex; // [nVars]
	float *errorValues; // for all: [pointsToCheck][pointsToCheck]...[pointsToCheck] - axisItems times

	int countRuns;
	int bestChanges;
	int bestMax;
	bool axisSelection;
	int minPoints;

	float findBest;
	float findLast;
	int findCount;
	
	Random randoms4Axes;
	ClassList<NNStrategyScanItem> axisValues;

	NNWeights pwc; // for copy purposes
};

/*#########################################################################*/
/*#########################################################################*/

class NNStrategyScan : public NNStrategy , public Object
{
public:
	// Object interface
	NNStrategyScan();
	void attach( NN *p );

	static const char *NAME;
	virtual const char *getClass() { return( NAME ); };
	virtual void serialize( SerializeObject& so );
	virtual void deserialize( Object *parent , SerializeObject& so );

	static Object *onCreate( const char *className ) { return( new NNStrategyScan ); };
	static void createSerializeObject();
	static SerializeObject *getSerializeObject()
		{ return( AIEngine::getInstance().getSerializeObject( NAME ) ); };

public:
	static NNStrategyScan *newInit( NN *p_p );
	~NNStrategyScan();
	void init( NN *p_p );

	void setMaxTime( int ms );
	void setWeightRange( float p_valueMin , float p_valueMax );
	void getWeightRange( float& p_valueMin , float& p_valueMax );
	void setTolerance( float p_value );

	// learn functions
	virtual bool learn( NNSamples *samples , NNWeights *pwBest , float *pvar );
	virtual bool learnSample( NNSamples *samples , int id , NNWeights *pwBest , float *pvar );

private:
	bool doLearn( NNSamples *samples , NNSample *sample , NNScanPoint *spBest );
	int getIterationsPerSec( NNSample *sample );
	int getVariableCount();
	void mergeBest( ClassList<NNScanPoint>& best , ClassList<NNScanPoint>& bestIteration );

	NNWeights *getFixedStartPoint();
	NNWeights *getRandomStartPoint();

	NNScanPoint *createRunsAndStartPoint( ClassList<NNStrategyScanIteration>& runByPrecision );
	bool runFindByPrecisions( NNSamples *samples , NNSample *sample , Timer& t , ClassList<NNStrategyScanIteration>& runByPrecision , NNScanPoint *& bestPoint , int& iterationsDone );
	bool runFindByOnePrecision( NNSamples *samples , NNSample *sample , NNStrategyScanIteration *run , NNStrategyScanIteration *runNext , NNScanPoint *& bestPoint , int& iterationsDone );

private:
	NN *p;
	int bestMax;
	int maxTime;
	float wLimitMin; // weight limits
	float wLimitMax;
	float tolerance;
};

/*#########################################################################*/
/*#########################################################################*/
