#include "body_impl.h"

Physiology::Physiology()
:	engine( AIEngine::getInstance() )
{
	logger.attach( this );
}

void Physiology::onCreateArea()
{
	createPhysiology();
}

void Physiology::onLoadArea()
{
	// for body areas create and load are the same
	onCreateArea();
}

void Physiology::onBrainStart()
{
	// start controls
	for( int k = 0; k < controls.count(); k++ ) {
		PhysioControl *control = controls.getClassByIndex( k );
		String name = controls.getKeyByIndex( k );

		try {
			control -> start();
		}
		catch ( RuntimeException& e ) {
			logger.logError( "onBrainStart: cannot start control name=" + name );
			e.printStack( logger );
		}
		catch ( ... ) {
			logger.printStack();
			logger.logError( "onBrainStart: unexpected unknown exception, cannot start control name=" + name );
		}

		logger.logInfo( "onBrainStart: control started - name=" + control -> getName() );
	}
}

void Physiology::onBrainStop()
{
	// stop controls
	for( int k = 0; k < controls.count(); k++ ) {
		PhysioControl *control = controls.getClassByIndex( k );
		control -> stop();
	}
}

void Physiology::createPhysiology()
{
	AIBodyImpl *body = AIBodyImpl::getInstance();
	Xml config = body -> getConfigService();
	Xml configControls = config.getChildNode( "physiology" );

	addControl( configControls , PhysioControl::createRebeccaChat() );
}

void Physiology::addControl( Xml configControls , PhysioControl *att )
{
	String name = att -> getName();
	Xml config = configControls.getChildNamedNode( "control" , name );

	if( config.exists() && config.getBooleanAttribute( "run" ) ) {
		// add
		controls.add( name , att );
		logger.logInfo( "addControl: control added - name=" + name );

		// configure
		att -> create( config );
	}
	else {
		controlsOffline.add( name , att );
		logger.logInfo( "addControl: control is not configured to run - name=" + name );
	}
}

PhysioControl *Physiology::getControl( String name )
{
	return( controls.get( name ) );
}

MindArea *AIBodyImpl::createPhysiology()
{
	Physiology *area = new Physiology();
	return( area );
}

Physiology *Physiology::getPhysiology()
{
	AIBrain brain;
	MindArea *area = brain.getMindArea( "Physiology" );
	Physiology *physiology = static_cast<Physiology *>( area );
	return( physiology );
}

