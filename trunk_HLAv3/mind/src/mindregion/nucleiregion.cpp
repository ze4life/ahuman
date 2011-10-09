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
	virtual NeuroLinkSource *getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

private:
	// neurolink handler
	void handleNeuroLinkMessage( NeuroLink *link , NeuroVector *data );

private:
// own data
	NeuroLinkSource source;
	NeuroLinkTarget target;
	NeuroPool neuroPool;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createNucleiRegion( MindArea *area ) { return( new NucleiRegion( area ) ); };

/*#########################################################################*/
/*#########################################################################*/

NucleiRegion::NucleiRegion( MindArea *p_area )
:	MindRegion( p_area ) {
	attachLogger();
}

void NucleiRegion::createRegion() {
	target.setHandler( this , ( MindRegion::NeuroLinkHandler )&NucleiRegion::handleNeuroLinkMessage );
}

void NucleiRegion::exitRegion() {
}

void NucleiRegion::destroyRegion() {
}

// NeuroLink support
NeuroLinkSource *NucleiRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	// allow any
	return( &source );
}

NeuroLinkTarget *NucleiRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( &target );
}

void NucleiRegion::handleNeuroLinkMessage( NeuroLink *link , NeuroVector *data ) {
	// execute default
	link -> apply( data , &neuroPool );

	// forward further
	source.sendMessage( this );
}
