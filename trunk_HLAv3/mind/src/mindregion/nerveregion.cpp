#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class NerveRegion : public MindRegion {
public:
	NerveRegion( MindArea *area );
	virtual const char *getClass() { return( "NerveRegion" ); };

public:
	// MindRegion lifecycle
	virtual void createRegion();
	virtual void exitRegion();
	virtual void destroyRegion();

	// NeuroLink support
	virtual NeuroLinkSource *getNeuroLinkSource( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

private:
// parent
	MindArea *area;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createNerveRegion( MindArea *area ) { return( new NerveRegion( area ) ); };

/*#########################################################################*/
/*#########################################################################*/

NerveRegion::NerveRegion( MindArea *p_area ) {
	area = p_area;
	attachLogger();
}

void NerveRegion::createRegion() {
}

void NerveRegion::exitRegion() {
}

void NerveRegion::destroyRegion() {
}

