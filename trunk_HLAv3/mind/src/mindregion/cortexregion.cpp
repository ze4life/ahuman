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
	virtual NeuroLinkSource *getNeuroLinkSource( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

	// access to pools
	virtual NeuroPool *getFeedForwardInputPool();

private:
// parent
	MindArea *area;

// own data
	NeuroLinkSource sourceFeedForward;
	NeuroLinkSource sourceFeedback;
	NeuroLinkTarget targetFeedForward;
	NeuroLinkTarget targetFeedback;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createCortexRegion( MindArea *area ) { return( new CortexRegion( area ) ); };

/*#########################################################################*/
/*#########################################################################*/

CortexRegion::CortexRegion( MindArea *p_area ) {
	area = p_area;
	attachLogger();
}

void CortexRegion::createRegion() {
}

void CortexRegion::exitRegion() {
}

void CortexRegion::destroyRegion() {
}

NeuroPool *CortexRegion::getFeedForwardInputPool() {
	return( NULL );
}

NeuroLinkSource *CortexRegion::getNeuroLinkSource( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( NULL );
}

NeuroLinkTarget *CortexRegion::getNeuroLinkTarget( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( NULL );
}

