#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class SpatialPooler;
class TemporalPooler;

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
	virtual void getSourceSizes( String entity , int *sizeX , int *sizeY );
	virtual NeuroLinkSource *getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

public:
	void createCortexRegion( CortexRegionInfo *info );

private:
	// neurolink handlers
	void handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );
	// void handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );
	// void handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );

private:
// own data
	// NeuroLinkSource *sourceFeedForward;
	NeuroLinkSource *sourceFeedBack;
	// NeuroLinkSource *sourceAttention;
	NeuroLinkTarget *targetFeedForward;
	// NeuroLinkTarget *targetFeedBack;
	// NeuroLinkTarget *targetAttention;

	// NeuroSignal vectorFeedForwardOutput;
	// NeuroSignal vectorFeedBackOutput;
	// NeuroSignal vectorAttentionOutput;

	// NeuroPool layerTemporalFeedback;	// layer 2
	// NeuroPool layerSpatial;				// layer 3
	// NeuroPool layerTemporal;			// layer 4
	// NeuroPool layerAttention;			// layer 5
	// NeuroPool layerSpatialFeedback;		// layer 6

	NeuroPool inputPool;
	NeuroPool feedbackPool;
	SpatialPooler *spatialPooler;
	TemporalPooler *temporalPooler;

// utilities
	int sizeX;
	int sizeY;
	bool useSpatialPooler;
	bool useTemporalPooler;
	int temporalDepth;
};

class SpatialPooler : public Object {
public:
	SpatialPooler();
	virtual const char *getClass() { return( "SpatialPooler" ); };
	
	void create( int poolSize , int sizeX , int sizeY );
	void setMatchTolerance( int matchTolerance );
	void setProtectedUsage( int usage );

	int matchPattern( NeuroPool *pool , int *patternForgotten );
	bool getPattern( int pattern , NeuroPool *feedbackPool );

private:
	int poolSize;
	int patternSizeX;
	int patternSizeY;
};

class TemporalPooler : public Object {
public:
	TemporalPooler();
	virtual const char *getClass() { return( "TemporalPooler" ); };

	void create( int poolSize , int depth );
	void forgetSpatialPattern( int spatialPattern );
	int matchPattern( int spatialPattern ,  int *temporalPatternForgotten , int *spatialPatternPredicted );
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createCortexRegion( MindArea *area , String id , CortexRegionInfo *info ) { 
	CortexRegion *region = new CortexRegion( area ); 
	region -> createCortexRegion( info );
	region -> create( id );
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

	// sourceFeedForward = NULL;
	sourceFeedBack = NULL;
	// sourceAttention = NULL;
	targetFeedForward = NULL;
	// targetFeedBack = NULL;
	// targetAttention = NULL;

	spatialPooler = new SpatialPooler();
	temporalPooler = new TemporalPooler();
}

void CortexRegion::createCortexRegion( CortexRegionInfo *info ) {
	const int SPACIAL_MATCH_TOLERANCE = 10;
	const int PROTECTED_SPATIAL_PATTERN_USAGE = 100;

	// get parameters
	info -> getSizeInfo( &sizeX , &sizeY );
	useSpatialPooler = info -> isUsingSpatialPooler();
	useTemporalPooler = info -> isUsingTemporalPooler();
	temporalDepth = info -> getTemporalDepth();

	// create pools
	inputPool.createNeurons( sizeX , sizeY );
	feedbackPool.createNeurons( sizeX , sizeY );

	// create and setup spatial and temporal poolers
	spatialPooler -> create( info -> getSpatialPoolerSize() , sizeX , sizeY );
	spatialPooler -> setMatchTolerance( SPACIAL_MATCH_TOLERANCE );
	spatialPooler -> setProtectedUsage( PROTECTED_SPATIAL_PATTERN_USAGE );
	temporalPooler -> create( info -> getTemporalPoolerSize() , temporalDepth );
}

void CortexRegion::getSourceSizes( String entity , int *p_sizeX , int *p_sizeY ) {
	*p_sizeX = sizeX;
	*p_sizeY = sizeY;
}

void CortexRegion::createRegion() {
	// sourceFeedForward = new NeuroLinkSource( this );
	sourceFeedBack = new NeuroLinkSource( this , "feed-back-output" );
	sourceFeedBack -> setSourcePool( &feedbackPool );
	// sourceAttention = new NeuroLinkSource( this );
	targetFeedForward = new NeuroLinkTarget( this );
	// targetFeedBack = new NeuroLinkTarget( this );
	// targetAttention = new NeuroLinkTarget( this );

	// create input/output vectors
	// vectorFeedForwardOutput.create( sideSize , sideSize );
	// sourceFeedForward -> setSourceSignal( &vectorFeedForwardOutput );

	// vectorFeedBackOutput.create( sideSize , sideSize );
	// sourceFeedBack -> setSourceSignal( &vectorFeedBackOutput );

	// vectorAttentionOutput.create( sideSize , sideSize );
	// sourceAttention -> setSourceSignal( &vectorAttentionOutput );

	targetFeedForward -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleFeedForwardNeuroLinkMessage );
	// targetFeedBack -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleFeedBackNeuroLinkMessage );
	// targetAttention -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleAttentionNeuroLinkMessage );
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
	// if( sourceFeedForward != NULL )
	// 	delete sourceFeedForward;
	if( sourceFeedBack != NULL )
		delete sourceFeedBack;
	// if( sourceAttention != NULL )
	// 	delete sourceAttention;
	if( targetFeedForward != NULL )
		delete targetFeedForward;
	// if( targetFeedBack != NULL )
	// 	delete targetFeedBack;
	// if( targetAttention != NULL )
	// 	delete targetAttention;

	// sourceFeedForward = NULL;
	sourceFeedBack = NULL;
	// sourceAttention = NULL;
	targetFeedForward = NULL;
	// targetFeedBack = NULL;
	// targetAttention = NULL;

	delete spatialPooler;
	spatialPooler = NULL;

	delete temporalPooler;
	temporalPooler = NULL;
}

NeuroLinkSource *CortexRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	// if( entity.equals( "feed-forward-output" ) )
	// 	return( sourceFeedForward );
	if( entity.equals( "feed-back-output" ) )
		return( sourceFeedBack );
	// if( entity.equals( "attention-output" ) )
	// 	return( sourceAttention );

	return( NULL );
}

NeuroLinkTarget *CortexRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "feed-forward-input" ) )
		return( targetFeedForward );
	// if( entity.equals( "feed-back-input" ) )
	// 	return( targetFeedBack );
	// if( entity.equals( "attention-input" ) )
	// 	return( targetAttention );

	return( NULL );
}

void CortexRegion::handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
	// mock algorithm:
	//	1. project neurolink
	link -> apply( data , &inputPool );

	//	2. execute spacial pooler
	//		- max number of patterns, spatial pooler slots: MAX_SPACIAL_PATTERNS
	//		- size is defined by area, differs from neurolink width: nSideSize
	//		- add new patterns only if not matched for more than SPACIAL_MATCH_TOLERANCE=10
	//		- keep usage count for each pattern: usageCount
	//		- forget pattern only if usage is less than PROTECTED_SPATIAL_PATTERN_USAGE
	//		- forget least used stored pattern when adding new pattern and all spacial pooler slots are already filled in

	int spatialPatternForgotten = -1;
	int spatialPatternMatched = spatialPooler -> matchPattern( &inputPool , &spatialPatternForgotten );

	//	3. execute temporal pooler
	//		- max number of patterns, spatial pooler slots: MAX_TEMPORAL_PATTERNS
	//		- used length: temporalDepth
	//		- clear forgotten temporal pattern
	if( spatialPatternForgotten >= 0 )
		temporalPooler -> forgetSpatialPattern( spatialPatternForgotten );

	if( spatialPatternMatched < 0 )
		return;

	int temporalPatternForgotten = -1;
	int spatialPatternPredicted = -1;
	int temporalspatialPatternMatched = temporalPooler -> matchPattern( spatialPatternMatched , &temporalPatternForgotten , &spatialPatternPredicted );

	if( spatialPatternPredicted < 0 )
		return;

	// 4. generate feedback
	//		- get predicted pattern
	//		- generate feedback message
	spatialPooler -> getPattern( spatialPatternPredicted , &feedbackPool );
	sourceFeedBack -> sendMessage();
}

// void CortexRegion::handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
// 	sourceFeedBack -> sendMessage();
// }

// void CortexRegion::handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
// 	sourceAttention -> sendMessage();
// }

/*#########################################################################*/
/*#########################################################################*/

SpatialPooler::SpatialPooler() {
}

void SpatialPooler::create( int p_poolSize , int sizeX , int sizeY ) {
	poolSize = p_poolSize;
	patternSizeX = sizeX;
	patternSizeY = sizeY;
}

void SpatialPooler::setMatchTolerance( int matchTolerance ) {
}

void SpatialPooler::setProtectedUsage( int usage ) {
}

int SpatialPooler::matchPattern( NeuroPool *pool , int *patternForgotten ) {
	return( -1 );
}

bool SpatialPooler::getPattern( int pattern , NeuroPool *feedbackPool ) {
	return( false );
}

/*#########################################################################*/
/*#########################################################################*/

TemporalPooler::TemporalPooler() {
}

void TemporalPooler::create( int poolSize , int depth ) {
}

void TemporalPooler::forgetSpatialPattern( int spatialPattern ) {
}

int TemporalPooler::matchPattern( int spatialPattern ,  int *temporalPatternForgotten , int *spatialPatternPredicted ) {
	return( -1 );
}
