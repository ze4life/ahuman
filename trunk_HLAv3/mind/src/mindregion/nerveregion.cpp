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
	virtual void getSourceSizes( String entity , int *sizeX , int *sizeY );
	virtual NeuroLinkSource *getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

public:
	void createNerveRegion( NerveRegionInfo *info );
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createNerveRegion( MindArea *area , String id , NerveRegionInfo *info ) { 
	NerveRegion *region = new NerveRegion( area ); 
	region -> createNerveRegion( info );
	region -> create( id );
	return( region );
}

/*#########################################################################*/
/*#########################################################################*/

NerveRegion::NerveRegion( MindArea *p_area )
:	MindRegion( p_area ) {
	attachLogger();
}

void NerveRegion::createNerveRegion( NerveRegionInfo *info ) {
	ASSERTFAILED( "createNerveRegion: not implemented" );
}

void NerveRegion::createRegion()  {
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

