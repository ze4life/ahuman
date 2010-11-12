#include "body_impl.h"

Physiology::Physiology()
:	engine( AIEngine::getInstance() )
{
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
		control -> start();
		logger.logInfo( "Physiology::onBrainStart: control started - name=" + control -> getName() );
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
		controls.add( name , att );
		logger.logInfo( "Physiology::addControl: control added - name=" + name );
	}
	else {
		controlsOffline.add( name , att );
		logger.logInfo( "Physiology::addControl: control is not configured to run - name=" + name );
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

