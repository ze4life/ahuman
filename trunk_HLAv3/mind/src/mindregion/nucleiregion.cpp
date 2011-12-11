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
	virtual void getSourceSizes( String entity , int *sizeX , int *sizeY );
	virtual NeuroLinkSource *getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );
	virtual NeuroLinkTarget *getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo );

public:
	void createNucleiRegion( NucleiRegionInfo *info );

private:
	// neurolink handler
	void handleTargetMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );

private:
// own data
	NeuroLinkSource *source;
	NeuroLinkTarget *target;
	NeuroSignal *sourceSignal;
	NeuroPool neuroPool;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createNucleiRegion( MindArea *area , String id , NucleiRegionInfo *info ) { 
	NucleiRegion *region = new NucleiRegion( area ); 
	region -> createNucleiRegion( info );
	region -> create( id );
	return( region );
}

/*#########################################################################*/
/*#########################################################################*/

NucleiRegion::NucleiRegion( MindArea *p_area )
:	MindRegion( p_area ) {
	attachLogger();

	source = NULL;
	target = NULL;
	sourceSignal = NULL;
}

void NucleiRegion::createNucleiRegion( NucleiRegionInfo *info ) {
	int sideSize = info -> getSideSize();
	ASSERTMSG( sideSize > 0 , "invalid sideSize, positive value expected" );
	neuroPool.createNeurons( sideSize , sideSize );
}

void NucleiRegion::createRegion() {
	source = new NeuroLinkSource( this , "input" );
	target = new NeuroLinkTarget( this );
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&NucleiRegion::handleTargetMessage );

	int nx , ny;
	neuroPool.getNeuronDimensions( &nx , &ny );
	sourceSignal = new NeuroSignal();
	sourceSignal -> create( nx , ny );
	source -> setSourceSignal( sourceSignal );
}

void NucleiRegion::getSourceSizes( String entity , int *sizeX , int *sizeY ) {
	neuroPool.getNeuronDimensions( sizeX , sizeY );
}

void NucleiRegion::exitRegion() {
}

void NucleiRegion::destroyRegion() {
	if( source != NULL )
		delete source;
	if( target != NULL )
		delete target;
	if( sourceSignal != NULL )
		delete sourceSignal;

	source = NULL;
	target = NULL;
	sourceSignal = NULL;
}

// NeuroLink support
NeuroLinkSource *NucleiRegion::getNeuroLinkSource( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	// allow any
	return( source );
}

NeuroLinkTarget *NucleiRegion::getNeuroLinkTarget( String entity , MindNetInfo *netInfo , NeuroLinkInfo *linkInfo ) {
	return( target );
}

void NucleiRegion::handleTargetMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
	// execute default
	link -> apply( data , &neuroPool );

	// update neurosignal
	sourceSignal -> createFromPool( &neuroPool );

	// forward further
	source -> sendMessage();
}
