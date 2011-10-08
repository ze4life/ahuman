#include <ah_mind.h>
#include <ah_mind_impl.h>

/*#########################################################################*/
/*#########################################################################*/

class NucleiRegion : public MindRegion {
public:
	NucleiRegion( MindArea *area );
	virtual const char *getClass() { return( "NucleiRegion" ); };

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
	NeuroLinkSource source;
	NeuroLinkTarget target;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createNucleiRegion( MindArea *area ) { return( new NucleiRegion( area ) ); };

/*#########################################################################*/
/*#########################################################################*/

NucleiRegion::NucleiRegion( MindArea *p_area ) {
	area = p_area;
	attachLogger();
}

void NucleiRegion::createRegion() {
}

void NucleiRegion::exitRegion() {
}

void NucleiRegion::destroyRegion() {
}

// NeuroLink support
NeuroLinkSource *NucleiRegion::getNeuroLinkSource( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	// allow any
	return( &source );
}

NeuroLinkTarget *NucleiRegion::getNeuroLinkTarget( MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( &target );
}

