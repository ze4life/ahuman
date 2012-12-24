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
	else
		logger.logError( "unknown cmd=" + cmdName );
}

void AHumanTarget::cmdPlayCircuit( Xml cmd ) {
	// find target connector
	MindService *ms = MindService::getService();

	String component = cmd.getProperty( "component" );
	String connector = cmd.getProperty( "connector" );

	MindRegion *region = ms -> getMindRegion( component );
	ASSERTMSG( region != NULL , "unknown region=" + component );

	NeuroLinkTarget *target = region -> getNeuroLinkTarget( connector );
	if( connector == NULL )
		return;

	NeuroSignal *signal = new NeuroSignal();
	static int z = 0;
	signal -> setId( String( "TM" ) + (++z) );
	logger.logInfo( "send message to component=" + component + ", connector=" + connector + ", signal id=" + signal -> getId() + " ..." );
	NeuroSignalSet *set = target -> execute( NULL , signal );
	if( set == NULL ) {
		logger.logDebug( signal -> getId() + ": there are no derived signals from signal id=" + signal -> getId() );
		return;
	}

	// define IDs
	ClassList<NeuroSignal>& signals = set -> getSignals();
	for( int k = 0; k < signals.count(); k++ ) {
		NeuroSignal *signalExecuted = signals.get( k );
		signalExecuted -> setId( signal -> getId() + ".S" + (k+1) );
	}

	// follow links
	MindArea *area = region -> getArea();
	area -> followLinks( signal -> getId() , region , set );
	set -> destroy();
}

void AHumanTarget::stopTarget() {
}

void AHumanTarget::exitTarget() {
}

void AHumanTarget::destroyTarget() {
}
