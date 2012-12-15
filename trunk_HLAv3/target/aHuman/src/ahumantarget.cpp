#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

AHumanTarget::AHumanTarget( String p_component , String p_connector ) {
	attachLogger();
	component = p_component;
	connector = p_connector;
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
	// find target connector
	MindService *ms = MindService::getService();
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
	if( set == NULL )
		return;

	// define IDs
	ClassList<NeuroSignal>& signals = set -> getSignals();
	for( int k = 0; k < signals.count(); k++ ) {
		NeuroSignal *signalExecuted = signals.get( k );
		signalExecuted -> setId( signal ->getId() + "." + (k+1) );
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
