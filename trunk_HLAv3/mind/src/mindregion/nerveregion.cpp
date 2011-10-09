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
	virtual NeuroLinkSource *getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createNerveRegion( MindArea *area ) { return( new NerveRegion( area ) ); };

/*#########################################################################*/
/*#########################################################################*/

NerveRegion::NerveRegion( MindArea *p_area )
:	MindRegion( p_area ) {
	attachLogger();
}

void NerveRegion::createRegion() {
}

void NerveRegion::exitRegion() {
}

void NerveRegion::destroyRegion() {
}

NeuroLinkSource *NerveRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( NULL );
}

NeuroLinkTarget *NerveRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( NULL );
}

