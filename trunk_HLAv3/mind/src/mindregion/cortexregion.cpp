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
	void handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroVector *data );
	void handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroVector *data );
	void handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroVector *data );

private:
// own data
	NeuroLinkSource sourceFeedForward;
	NeuroLinkSource sourceFeedBack;
	NeuroLinkSource sourceAttention;
	NeuroLinkTarget targetFeedForward;
	NeuroLinkTarget targetFeedBack;
	NeuroLinkTarget targetAttention;

	NeuroVector vectorFeedForwardOutput;
	NeuroVector vectorFeedBackOutput;
	NeuroVector vectorAttentionOutput;

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
}

void CortexRegion::createCortexRegion( CortexRegionInfo *info ) {
	nSideSize = info -> getRegionSideSize();
	nCols = nSideSize * nSideSize;
	useSpatialPooler = info -> isUsingSpatialPooler();
	useTemporalPooler = info -> isUsingTemporalPooler();
	nTemporalDepth = info -> getTemporalDepth();

	// create input/output vectors
	vectorFeedForwardOutput.create( nSideSize , nSideSize );
	sourceFeedForward.setSourceVector( &vectorFeedForwardOutput );

	vectorFeedBackOutput.create( nSideSize , nSideSize );
	sourceFeedBack.setSourceVector( &vectorFeedBackOutput );

	vectorAttentionOutput.create( nSideSize , nSideSize );
	sourceAttention.setSourceVector( &vectorAttentionOutput );

	// create pools
}

void CortexRegion::createRegion() {
	targetFeedForward.setHandler( this , ( MindRegion::NeuroLinkHandler )&CortexRegion::handleFeedForwardNeuroLinkMessage );
	targetFeedBack.setHandler( this , ( MindRegion::NeuroLinkHandler )&CortexRegion::handleFeedBackNeuroLinkMessage );
	targetAttention.setHandler( this , ( MindRegion::NeuroLinkHandler )&CortexRegion::handleAttentionNeuroLinkMessage );
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
}

NeuroLinkSource *CortexRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "feed-forward-output" ) )
		return( &sourceFeedForward );
	if( entity.equals( "feed-back-output" ) )
		return( &sourceFeedBack );
	if( entity.equals( "attention-output" ) )
		return( &sourceAttention );

	return( NULL );
}

NeuroLinkTarget *CortexRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "feed-forward-input" ) )
		return( &targetFeedForward );
	if( entity.equals( "feed-back-input" ) )
		return( &targetFeedBack );
	if( entity.equals( "attention-input" ) )
		return( &targetAttention );

	return( NULL );
}

void CortexRegion::handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroVector *data ) {
	sourceFeedForward.sendMessage( this );
}

void CortexRegion::handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroVector *data ) {
	sourceFeedBack.sendMessage( this );
}

void CortexRegion::handleAttentionNeuroLinkMessage( NeuroLink *link , NeuroVector *data ) {
	sourceAttention.sendMessage( this );
}

