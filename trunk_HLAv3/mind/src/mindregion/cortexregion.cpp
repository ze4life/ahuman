#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class CortexSpatialPooler;
class CortexTemporalPooler;

class CortexRegion : public MindRegion {
public:
	CortexRegion( MindArea *area );
	virtual const char *getClass() { return( "CortexRegion" ); };

public:
	// MindRegion lifecycle
	virtual void createRegion();
	virtual void exitRegion();
	virtual void destroyRegion();

	// NeuroLink support
	virtual String getRegionType();
	virtual void getSourceSizes( String entity , int *sizeX , int *sizeY );

public:
	void createCortexRegion( CortexRegionInfo *info , String p_id );

private:
	// neurolink handlers
	void handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );
	// void handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );
	// void handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );

private:
// own data
	NeuroLinkSource sourceFeedBack;
	NeuroLinkTarget targetFeedForward;

	// NeuroPool layerTemporalFeedback;	// layer 2
	// NeuroPool layerSpatial;				// layer 3
	// NeuroPool layerTemporal;			// layer 4
	// NeuroPool layerAttention;			// layer 5
	// NeuroPool layerSpatialFeedback;		// layer 6

	NeuroPool inputPool;
	NeuroPool feedbackPool;
	CortexSpatialPooler *spatialPooler;
	CortexTemporalPooler *temporalPooler;

// utilities
	int sizeX;
	int sizeY;
	bool useSpatialPooler;
	bool useTemporalPooler;
	int temporalDepth;
	int spatialPatternExpected;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createCortexRegion( MindArea *area , String id , CortexRegionInfo *info ) { 
	CortexRegion *region = new CortexRegion( area ); 
	region -> createCortexRegion( info , id );
	return( region );
}

/*#########################################################################*/
/*#########################################################################*/

CortexRegion::CortexRegion( MindArea *p_area )
:	MindRegion( p_area ) {
	attachLogger();

	sizeX = 0;
	sizeY = 0;
	useSpatialPooler = false;
	useTemporalPooler = false;
	temporalDepth = false;
	spatialPatternExpected = -1;

	spatialPooler = new CortexSpatialPooler();
	temporalPooler = new CortexTemporalPooler();
}

String CortexRegion::getRegionType() {
	return( "CortexRegion" );
}

void CortexRegion::createCortexRegion( CortexRegionInfo *info , String p_id ) {
	const int SPACIAL_MATCH_PATTERN_TOLERANCE = 10;
	const int SPACIAL_MATCH_NEURONSTATE_TOLERANCE = 30;
	const int SPATIAL_PROTECTED_PATTERN_USAGE = 100;
	const int TEMPORAL_MATCH_PATTERN_TOLERANCE = 20;
	const int TEMPORAL_PROTECTED_PATTERN_USAGE = 100;
	const int TEMPORAL_PREDICTION_PROBABILITY_TOLERANCE = 50;
	const int TEMPORAL_PREDICTION_MATCH_TOLERANCE = 75;

	// get parameters
	info -> getSizeInfo( &sizeX , &sizeY );
	useSpatialPooler = info -> isUsingSpatialPooler();
	useTemporalPooler = info -> isUsingTemporalPooler();
	temporalDepth = info -> getTemporalDepth();

	// create pools
	inputPool.setParent( this );
	inputPool.createNeurons( sizeX , sizeY );
	feedbackPool.setParent( this );
	feedbackPool.createNeurons( sizeX , sizeY );

	// create and setup spatial and temporal poolers
	spatialPooler -> create( info -> getSpatialPoolerSize() , sizeX , sizeY );
	spatialPooler -> setMatchTolerance( SPACIAL_MATCH_PATTERN_TOLERANCE , SPACIAL_MATCH_NEURONSTATE_TOLERANCE );
	spatialPooler -> setProtectedUsage( SPATIAL_PROTECTED_PATTERN_USAGE );

	temporalPooler -> create( info -> getTemporalPoolerSize() , temporalDepth );
	temporalPooler -> setMatchTolerance( TEMPORAL_MATCH_PATTERN_TOLERANCE );
	temporalPooler -> setProtectedUsage( TEMPORAL_PROTECTED_PATTERN_USAGE );
	temporalPooler -> setPredictionProbabilityTolerance( TEMPORAL_PREDICTION_PROBABILITY_TOLERANCE );
	temporalPooler -> setPredictionMatchTolerance( TEMPORAL_PREDICTION_MATCH_TOLERANCE );

	// set identity
	MindRegion::create( p_id );
	inputPool.setId( p_id + ".ff" );
	feedbackPool.setId( p_id + ".fb" );
}

void CortexRegion::getSourceSizes( String entity , int *p_sizeX , int *p_sizeY ) {
	*p_sizeX = sizeX;
	*p_sizeY = sizeY;
}

void CortexRegion::createRegion() {
	targetFeedForward.create( this , "cortex.ff-input" );
	targetFeedForward.setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleFeedForwardNeuroLinkMessage );
	sourceFeedBack.create( this , "cortex.fb-output" );
	sourceFeedBack.setSourcePool( &feedbackPool );

	// sourceFeedForward = new NeuroLinkSource( this );
	// sourceAttention = new NeuroLinkSource( this );
	// targetFeedBack = new NeuroLinkTarget( this );
	// targetAttention = new NeuroLinkTarget( this );
	// create input/output vectors
	// sourceFeedForward -> setSourceSignal( &vectorFeedForwardOutput );
	// sourceFeedBack -> setSourceSignal( &vectorFeedBackOutput );
	// sourceAttention -> setSourceSignal( &vectorAttentionOutput );
	// targetFeedBack -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleFeedBackNeuroLinkMessage );
	// targetAttention -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleAttentionNeuroLinkMessage );

	logger.logDebug( String( "createRegion: created cortex region: sizeX=" ) + sizeX + ", sizeY=" + sizeY );
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
	delete spatialPooler;
	spatialPooler = NULL;

	delete temporalPooler;
	temporalPooler = NULL;
}

void CortexRegion::handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *inputSignal ) {
	// mock algorithm:
	//	1. project neurolink
	NeuroSignal *forwardSignal = link -> apply( inputSignal , &inputPool );
	if( forwardSignal == NULL )
		return;

	//	2. execute spacial pooler
	//		- max number of patterns, spatial pooler slots: MAX_SPACIAL_PATTERNS
	//		- size is defined by area, differs from neurolink width
	//		- add new patterns only if not matched for more than SPACIAL_MATCH_TOLERANCE=10
	//		- keep usage count for each pattern: usageCount
	//		- forget pattern only if usage is less than PROTECTED_SPATIAL_PATTERN_USAGE
	//		- forget least used stored pattern when adding new pattern and all spacial pooler slots are already filled in
	int spatialPatternForgotten = -1;
	int matchProbability = 0;
	int spatialPatternMatched = spatialPooler -> matchPattern( forwardSignal , &matchProbability , &spatialPatternForgotten );

	StatService *ss = StatService::getService();
	ss -> addMetricValue( "cortex.spatialmatch.rate" , matchProbability );

	// ignore excited signal for now
	delete forwardSignal;

	//	3. execute temporal pooler
	//		- max number of patterns, spatial pooler slots: MAX_TEMPORAL_PATTERNS
	//		- use length: temporalDepth
	//		- use complete (max depth) and incomplete (less than depth) patterns
	//		- clear forgotten spatial pattern if any from temporal patterns
	//		- clear forgotten temporal pattern
	if( spatialPatternForgotten >= 0 )
		temporalPooler -> forgetSpatialPattern( spatialPatternForgotten );

	if( spatialPatternMatched < 0 ) {
		logger.logInfo( String( "handleFeedForwardNeuroLinkMessage: id=" ) + inputSignal -> getId() + " - not matched, ignored" );

		if( logger.isLogAll() ) {
			spatialPooler -> logItems();
			temporalPooler -> logItems();
		}
		return;
	}

	int spatialPatternPredicted = -1;
	int predictionProbability = 0;
	int temporalPatternForgotten;
	int temporalspatialPatternMatched = temporalPooler -> matchPattern( spatialPatternMatched , &spatialPatternPredicted , &predictionProbability , &temporalPatternForgotten );
	
	ss -> addMetricValue( "cortex.temporalmatch.rate" , predictionProbability );
	int predictionRate = ( spatialPatternPredicted >= 0 && spatialPatternPredicted == spatialPatternExpected )? 100 : 0;
	ss -> addMetricValue( "cortex.prediction.rate" , predictionRate );

	if( spatialPatternPredicted < 0 ) {
		logger.logInfo( String( "handleFeedForwardNeuroLinkMessage: id=" ) + inputSignal -> getId() + ", spatialMatched=" + spatialPatternMatched + ", spatialExpected=" + spatialPatternExpected + ", temporalMatched=" + temporalspatialPatternMatched + ", spatialPredicted=-1, probability=" + matchProbability + "/-1" );

		if( logger.isLogAll() ) {
			spatialPooler -> logItems();
			temporalPooler -> logItems();
		}
		return;
	}

	if( logger.isLogAll() ) {
		spatialPooler -> logItems();
		temporalPooler -> logItems();
	}

	// 4. generate feedback
	//		- get predicted pattern
	logger.logInfo( String( "handleFeedForwardNeuroLinkMessage: id=" ) + inputSignal -> getId() + ", spatialMatched=" + spatialPatternMatched + ", spatialExpected=" + spatialPatternExpected + ", temporalMatched=" + temporalspatialPatternMatched + ", spatialPredicted=" + spatialPatternPredicted + ", probability=" + matchProbability + "/" + predictionProbability );
	spatialPatternExpected = spatialPatternPredicted;

	//		- generate feedback message
	int fnx , fny;
	feedbackPool.getNeuronDimensions( &fnx , &fny );
	NeuroSignal *feedbackSignal = new NeuroSignal( fnx , fny );
	spatialPooler -> getPattern( spatialPatternPredicted , feedbackSignal );
	feedbackSignal -> setId( inputSignal -> getId() );
	feedbackSignal -> setTs( Timer::getCurrentTimeMillis() );

	sourceFeedBack.sendMessage( feedbackSignal );
}

// void CortexRegion::handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
// 	sourceFeedBack -> sendMessage();
// }

// void CortexRegion::handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
// 	sourceAttention -> sendMessage();
// }

