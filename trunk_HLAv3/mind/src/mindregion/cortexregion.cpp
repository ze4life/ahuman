#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

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
	virtual NeuroLinkSource *getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

public:
	void createCortexRegion( CortexRegionInfo *info );

private:
	// neurolink handlers
	void handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );
	void handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );
	void handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );

private:
// own data
	NeuroLinkSource *sourceFeedForward;
	NeuroLinkSource *sourceFeedBack;
	NeuroLinkSource *sourceAttention;
	NeuroLinkTarget *targetFeedForward;
	NeuroLinkTarget *targetFeedBack;
	NeuroLinkTarget *targetAttention;

	NeuroSignal vectorFeedForwardOutput;
	NeuroSignal vectorFeedBackOutput;
	NeuroSignal vectorAttentionOutput;

	NeuroPool layerTemporalFeedback;	// layer 2
	NeuroPool layerSpatial;				// layer 3
	NeuroPool layerTemporal;			// layer 4
	NeuroPool layerAttention;			// layer 5
	NeuroPool layerSpatialFeedback;		// layer 6

// utilities
	int nCols;
	int nSideSize;
	bool useSpatialPooler;
	bool useTemporalPooler;
	int nTemporalDepth;
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

	nCols = 0;
	useSpatialPooler = false;
	useTemporalPooler = false;
	nTemporalDepth = false;

	sourceFeedForward = NULL;
	sourceFeedBack = NULL;
	sourceAttention = NULL;
	targetFeedForward = NULL;
	targetFeedBack = NULL;
	targetAttention = NULL;
}

void CortexRegion::createCortexRegion( CortexRegionInfo *info ) {
	nSideSize = info -> getRegionSideSize();
	nCols = nSideSize * nSideSize;
	useSpatialPooler = info -> isUsingSpatialPooler();
	useTemporalPooler = info -> isUsingTemporalPooler();
	nTemporalDepth = info -> getTemporalDepth();
}

void CortexRegion::createRegion() {
	sourceFeedForward = new NeuroLinkSource( this );
	sourceFeedBack = new NeuroLinkSource( this );
	sourceAttention = new NeuroLinkSource( this );
	targetFeedForward = new NeuroLinkTarget( this );
	targetFeedBack = new NeuroLinkTarget( this );
	targetAttention = new NeuroLinkTarget( this );

	// create input/output vectors
	vectorFeedForwardOutput.create( nSideSize , nSideSize );
	sourceFeedForward -> setSourceSignal( &vectorFeedForwardOutput );

	vectorFeedBackOutput.create( nSideSize , nSideSize );
	sourceFeedBack -> setSourceSignal( &vectorFeedBackOutput );

	vectorAttentionOutput.create( nSideSize , nSideSize );
	sourceAttention -> setSourceSignal( &vectorAttentionOutput );

	targetFeedForward -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleFeedForwardNeuroLinkMessage );
	targetFeedBack -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleFeedBackNeuroLinkMessage );
	targetAttention -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&CortexRegion::handleAttentionNeuroLinkMessage );
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
	if( sourceFeedForward != NULL )
		delete sourceFeedForward;
	if( sourceFeedBack != NULL )
		delete sourceFeedBack;
	if( sourceAttention != NULL )
		delete sourceAttention;
	if( targetFeedForward != NULL )
		delete targetFeedForward;
	if( targetFeedBack != NULL )
		delete targetFeedBack;
	if( targetAttention != NULL )
		delete targetAttention;

	sourceFeedForward = NULL;
	sourceFeedBack = NULL;
	sourceAttention = NULL;
	targetFeedForward = NULL;
	targetFeedBack = NULL;
	targetAttention = NULL;
}

NeuroLinkSource *CortexRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "feed-forward-output" ) )
		return( sourceFeedForward );
	if( entity.equals( "feed-back-output" ) )
		return( sourceFeedBack );
	if( entity.equals( "attention-output" ) )
		return( sourceAttention );

	return( NULL );
}

NeuroLinkTarget *CortexRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "feed-forward-input" ) )
		return( targetFeedForward );
	if( entity.equals( "feed-back-input" ) )
		return( targetFeedBack );
	if( entity.equals( "attention-input" ) )
		return( targetAttention );

	return( NULL );
}

void CortexRegion::handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
	sourceFeedForward -> sendMessage();
}

void CortexRegion::handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
	sourceFeedBack -> sendMessage();
}

void CortexRegion::handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
	sourceAttention -> sendMessage();
}

