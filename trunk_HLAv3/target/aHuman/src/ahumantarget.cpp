#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

AHumanTarget::AHumanTarget() {
	attachLogger();
}

void AHumanTarget::configureTarget( Xml config ) {
}

void AHumanTarget::createTarget( SensorArea *sensorArea , EffectorArea *effectorArea ) {
}

void AHumanTarget::initSensorsTarget( SensorArea *sensorArea ) {
}

void AHumanTarget::initEffectorsTarget( EffectorArea *effectorArea ) {
}

void AHumanTarget::runTarget() {
	// subscribe command channel
	MessagingService *ms = MessagingService::getService();
	ms -> subscribe( NULL , "target.commands" , "target.commands.sub" , this );
}

void AHumanTarget::onXmlMessage( XmlMessage *msg ) {
	Xml xml = msg -> getXml();
	String cmdName = xml.getAttribute( "name" );

	logger.logInfo( "onXmlMessage: execute request=" + xml.getValue() );

	if( cmdName.equals( "PlayCircuit" ) )
		cmdPlayCircuit( xml );
	else if( cmdName.equals( "VerifyModel" ) )
		cmdVerifyModel( xml );
	else if( cmdName.equals( "CreateWikiPages" ) )
		cmdCreateWikiPages( xml );
	else
		logger.logError( "unknown cmd=" + cmdName );
}

void AHumanTarget::cmdPlayCircuit( Xml scenario ) {
	ScenarioPlayer player;
	player.play( scenario );
}

void AHumanTarget::cmdVerifyModel( Xml modelArea ) {
	ModelVerifier verifier;
	verifier.verify( modelArea );
}

void AHumanTarget::cmdCreateWikiPages( Xml wiki ) {
	WikiMaker maker;
	maker.createPages( wiki );
}

void AHumanTarget::stopTarget() {
}

void AHumanTarget::exitTarget() {
}

void AHumanTarget::destroyTarget() {
}
