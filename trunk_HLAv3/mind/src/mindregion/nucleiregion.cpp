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
	void createNucleiRegion( NucleiRegionInfo *info , String id );

private:
	// neurolink handler
	void handleTargetMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );

private:
// own data
	NeuroLinkSource *source;
	NeuroLinkTarget *target;
	NeuroPool neuroPool;
};

/*#########################################################################*/
/*#########################################################################*/

MindRegion *MindService::createNucleiRegion( MindArea *area , String id , NucleiRegionInfo *info ) { 
	NucleiRegion *region = new NucleiRegion( area ); 
	region -> createNucleiRegion( info , id );
	return( region );
}

/*#########################################################################*/
/*#########################################################################*/

NucleiRegion::NucleiRegion( MindArea *p_area )
:	MindRegion( p_area ) {
	attachLogger();

	source = NULL;
	target = NULL;
}

void NucleiRegion::createNucleiRegion( NucleiRegionInfo *info , String p_id ) {
	int totalSize = info -> getTotalSize();
	ASSERTMSG( totalSize > 0 , "invalid totalSize, positive value expected" );
	int sideSize = 2 * ( int )sqrt( ( double )totalSize );

	neuroPool.setParent( this );
	neuroPool.createNeurons( sideSize , sideSize );

	// set identity
	MindRegion::create( p_id );
	neuroPool.setId( p_id + ".ff" );
}

void NucleiRegion::createRegion() {
	source = new NeuroLinkSource( this , "input" );
	target = new NeuroLinkTarget( this );
	target -> setHandler( ( MindRegion::NeuroLinkTargetHandler )&NucleiRegion::handleTargetMessage );

	int nx , ny;
	neuroPool.getNeuronDimensions( &nx , &ny );
	logger.logDebug( String( "createRegion: create nuclei region: nx=" ) + nx + ", ny=" + ny );
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

	source = NULL;
	target = NULL;
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
	logger.logInfo( "handleTargetMessage: handle signal id=" + data -> getId() + " for NeuroLink id=" + link -> getId() );

	// execute default
	NeuroSignal *signal = link -> apply( data , &neuroPool );
	if( signal == NULL )
		return;

	// forward further
	signal -> setId( data -> getId() );
	LOGDEBUG( "handleTargetMessage: send data signal id=" + signal -> getId() + ", data=" + signal -> getNumberDataString() );
	source -> sendMessage( signal );
	delete signal;
}
