#include "stdafx.h"
#include "ahumantarget.h"

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

	logger.logInfo( "onXmlMessage: execute request=" + cmdName );

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
	logger.logInfo( "cmdPlayCircuit: SUCCESSFULLY FINISHED" );
}

void AHumanTarget::cmdVerifyModel( Xml modelArea ) {
	ModelVerifier verifier( modelArea );
	verifier.verify();
	logger.logInfo( "cmdVerifyModel: SUCCESSFULLY FINISHED" );
}

void AHumanTarget::cmdCreateWikiPages( Xml wiki ) {
	WikiMaker maker( wiki );
	maker.createPages();
	logger.logInfo( "cmdCreateWikiPages: SUCCESSFULLY FINISHED" );
}

void AHumanTarget::stopTarget() {
}

void AHumanTarget::exitTarget() {
}

void AHumanTarget::destroyTarget() {
}
