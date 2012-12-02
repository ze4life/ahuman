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
	virtual String getRegionType();
	virtual void getSourceSizes( String entity , int *sizeX , int *sizeY );

public:
	void createNucleiRegion( NucleiRegionInfo *info , String id );

private:
	// neurolink handler
	void handleSubTargetMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );
	void handleInterNeuronsTargetMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data );

private:
// own data
	NeuroLinkSource source;
	NeuroLinkTarget targetSub;
	NeuroLinkTarget targetInterNeurons;
	NeuroLink *linkInterNeuronsToSub;

	NeuroPool neuroPoolSub;
	NeuroPool neuroPoolInterNeurons;
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
	linkInterNeuronsToSub = NULL;
}

String NucleiRegion::getRegionType() {
	return( "NucleiRegion" );
}

void NucleiRegion::createNucleiRegion( NucleiRegionInfo *info , String p_id ) {
	int totalSize = info -> getTotalSize();
	ASSERTMSG( totalSize > 0 , "invalid totalSize, positive value expected" );
	int sideSize = 2 * ( int )sqrt( ( double )totalSize );

	neuroPoolSub.setParent( this );
	neuroPoolSub.createNeurons( sideSize , sideSize );
	neuroPoolInterNeurons.setParent( this );
	neuroPoolInterNeurons.createNeurons( sideSize , sideSize );

	// set identity
	MindRegion::create( p_id );
	neuroPoolSub.setId( p_id + ".ff" );
	neuroPoolInterNeurons.setId( p_id + ".in" );

	// create internal link
}

void NucleiRegion::createRegion() {
	source.create( this , "nucleus.output" );

	targetSub.create( this , "nucleus.input" );
	targetSub.setHandler( ( MindRegion::NeuroLinkTargetHandler )&NucleiRegion::handleSubTargetMessage );
	targetInterNeurons.create( this , "nucleus.interneurons-input" );
	targetInterNeurons.setHandler( ( MindRegion::NeuroLinkTargetHandler )&NucleiRegion::handleInterNeuronsTargetMessage );

	int nx , ny;
	neuroPoolSub.getNeuronDimensions( &nx , &ny );
	logger.logDebug( String( "createRegion: create nuclei region: nx=" ) + nx + ", ny=" + ny );
}

void NucleiRegion::getSourceSizes( String entity , int *sizeX , int *sizeY ) {
	neuroPoolSub.getNeuronDimensions( sizeX , sizeY );
}

void NucleiRegion::exitRegion() {
}

void NucleiRegion::destroyRegion() {
	if( linkInterNeuronsToSub != NULL )
		delete linkInterNeuronsToSub;

	linkInterNeuronsToSub = NULL;
}

void NucleiRegion::handleSubTargetMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
	logger.logInfo( "handleSubTargetMessage: handle signal id=" + data -> getId() + " for NeuroLink id=" + link -> getId() );

	// execute default
	NeuroSignal *signal = link -> apply( data , &neuroPoolSub );
	if( signal == NULL )
		return;

	// forward further
	signal -> setId( data -> getId() );
	LOGDEBUG( "handleInputTargetMessage: send data signal id=" + signal -> getId() + ", data=" + signal -> getNumberDataString() );
	source.sendMessage( signal );
	delete signal;
}

void NucleiRegion::handleInterNeuronsTargetMessage( NeuroLink *link , NeuroLinkTarget *point , NeuroSignal *data ) {
	logger.logInfo( "handleInterNeuronsTargetMessage: handle signal id=" + data -> getId() + " for NeuroLink id=" + link -> getId() );

	// execute default
	NeuroSignal *signalInterNeurons = link -> apply( data , &neuroPoolInterNeurons );
	if( signalInterNeurons == NULL )
		return;

	// apply signal to Sub neuropool
	signalInterNeurons -> setId( data -> getId() );
	LOGDEBUG( "handleInterNeuronsTargetMessage: send data signal id=" + signalInterNeurons -> getId() + ", data=" + signalInterNeurons -> getNumberDataString() );

	// apply inhibitory signal
	NeuroSignal *signalUnexpected = linkInterNeuronsToSub -> apply( signalInterNeurons , &neuroPoolSub );
	ASSERTMSG( signalUnexpected == NULL , "unexpected signal" );
}
