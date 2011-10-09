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

private:
	// neurolink handlers
	void handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroVector *data );
	void handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroVector *data );

private:
// own data
	NeuroLinkSource sourceFeedForward;
	NeuroLinkSource sourceFeedBack;
	NeuroLinkTarget targetFeedForward;
	NeuroLinkTarget targetFeedBack;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createCortexRegion( MindArea *area ) { return( new CortexRegion( area ) ); };

/*#########################################################################*/
/*#########################################################################*/

CortexRegion::CortexRegion( MindArea *p_area )
:	MindRegion( p_area ) {
	attachLogger();
}

void CortexRegion::createRegion() {
	targetFeedForward.setHandler( this , ( MindRegion::NeuroLinkHandler )&CortexRegion::handleFeedForwardNeuroLinkMessage );
	targetFeedBack.setHandler( this , ( MindRegion::NeuroLinkHandler )&CortexRegion::handleFeedBackNeuroLinkMessage );
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
}

NeuroLinkSource *CortexRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "feed-forward" ) )
		return( &sourceFeedForward );
	if( entity.equals( "feed-back" ) )
		return( &sourceFeedBack );

	return( NULL );
}

NeuroLinkTarget *CortexRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	if( entity.equals( "feed-forward" ) )
		return( &targetFeedForward );
	if( entity.equals( "feed-back" ) )
		return( &targetFeedBack );

	return( NULL );
}

void CortexRegion::handleFeedForwardNeuroLinkMessage( NeuroLink *link , NeuroVector *data ) {
	logger.logError( "handleFeedForwardNeuroLinkMessage: not implemented, NeuroLink id=" + link -> getId() );
}

void CortexRegion::handleFeedBackNeuroLinkMessage( NeuroLink *link , NeuroVector *data ) {
	logger.logError( "handleFeedBackNeuroLinkMessage: not implemented, NeuroLink id=" + link -> getId() );
}
