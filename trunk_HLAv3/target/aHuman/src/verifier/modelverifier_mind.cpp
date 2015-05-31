#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkMindModel() {
	logger.logInfo( "checkMindModel: CHECK MIND MODEL ..." );

	// check all regions
	bool verifyOkAll = true;
	for( int k = 0; k < regionMap.count(); k++ ) {
		MindRegionDef *regionDef = regionMap.getClassByIndex( k );
		bool regionOk = checkMindModel_verifyRegion( regionDef );
		if( regionOk == false )
			verifyOkAll = false;
	}

	// check region links
	if ( !checkMindModel_verifyLinkDuplicates() )
		verifyOkAll = false;

	if( verifyOkAll )
		logger.logInfo( "checkMindModel: MIND MODEL IS OK" );
	else
		logger.logInfo( "checkMindModel: MIND MODEL HAS ERRORS" );
}

bool ModelVerifier::checkMindModel_verifyRegion( MindRegionDef *regionDef ) {
	String regionId = regionDef -> getId();

	bool checkRegion = true;
	MindService *ms = MindService::getService();
	MindRegion *region = ms -> getMindRegion( regionId );

	// check mapped to hierarchy
	if( hierarchyMap.get( regionId ) == NULL ) {
		checkRegion = false;
		logger.logError( "checkMindModel_verifyRegion: " + regionId + " - region is not mapped to hierarchy" );
	}

	// check region in circuits
	if( !checkMindModel_verifyRegionCircuits( regionDef , region ) )
		checkRegion = false;

	// check region connectors are linked
	if( checkRegion )
		if( !checkMindModel_verifyLinkedConnectors( regionDef , region ) )
			checkRegion = false;

	if( checkRegion ) {
		// check region connections are covered by circuits
		ClassList<MindRegionLink>& links = region -> getSlaveRegionLinks();
		for( int k = 0; k < links.count(); k++ ) {
			MindRegionLink& link = links.getRef( k );
			String dstId = link.getDstRegion() -> getRegionId();

			XmlCircuitFind find;
			if( !circuitsxml.findReferenceLink( hmindxml , regionId , dstId , find ) ) {
				logger.logError( "checkMindModel_verifyRegion: model region=" + regionId + " link to region=" + dstId + " is not covered by circuit collection" );
				checkRegion = false;
			}
		}
	}

	return( checkRegion );
}

bool ModelVerifier::checkMindModel_verifyLinkedConnectors( MindRegionDef *regionDef , MindRegion *region ) {
	String regionId = regionDef -> getId();

	// check region has no connections at all
	ClassList<MindRegionLink>& masterLinks = region -> getMasterRegionLinks();
	if( masterLinks.count() == 0 ) {
		logger.logError( "checkMindModel_verifyLinkedConnectors: region=" + regionId + " has no input region" );
		return( false );
	}

	ClassList<MindRegionLink>& slaveLinks = region -> getSlaveRegionLinks();
	if( slaveLinks.count() == 0 ) {
		logger.logError( "checkMindModel_verifyLinkedConnectors: region=" + regionId + " has no output region" );
		return( false );
	}

	// check specific connectors
	bool checkRegion = true;
	MindRegionTypeDef *regionType = regionDef -> getType();
	ClassList<MindRegionConnectorDef>& connectors = regionType -> getConnectors();

	for( int k = 0; k < connectors.count(); k++ ) {
		MindRegionConnectorDef *connectorDef = connectors.get( k );

		// check whether exists in source or target
		bool present = false;
		String entity = connectorDef -> getId();
		NeuroLinkSource *source = region -> getNeuroLinkSource( entity );
		NeuroLinkTarget *target = region -> getNeuroLinkTarget( entity );
		if( source != NULL )
			if( source -> getLinks().count() > 0 )
				present = true;
		if( target != NULL )
			if( target -> getLinks().count() > 0 )
				present = true;

		if( present == false ) {
			checkRegion = false;
			logger.logError( "checkMindModel_verifyLinkedConnectors: region=" + regionId + " connector=" + entity + " - is not connected" );
		}
	}

	return( checkRegion );
}

bool ModelVerifier::checkMindModel_verifyRegionCircuits( MindRegionDef *regionDef , MindRegion *region ) {
	String regionId = regionDef -> getId();

	// ignore unknown region
	if( !hmindxml.isComponent( regionId ) )
		return( true );

	// find circuit which references given region
	StringList circuits;
	circuitsxml.getCircuitList( circuits );
	for( int k = 0; k < circuits.count(); k++ ) {
		String circuit = circuits.get( k );
		if( circuitsxml.checkRegionUsedByCircuit( regionId , circuit ) )
			return( true );
	}

	logger.logError( "checkMindModel_verifyRegionCircuits: region=" + regionId + " is not covered by circuit collection" );
	return( false );
}

bool ModelVerifier::checkMindModel_verifyLinkDuplicates() {
	bool ok = true;

	MindService *ms = MindService::getService();

	// collect links
	MapStringToClass<MindLocalCircuitConnectionDef> cm;
	MindMap *mm = ms -> getMindMap();
	ClassList<MindLocalCircuitDef>& ls = mm -> getMindLocalCircuits();
	for( int k = 0; k < ls.count(); k++ ) {
		MindLocalCircuitDef& ld = ls.getRef( k );
		MapStringToClass<MindLocalCircuitConnectionDef>& ldcs = ld.getConnections();

		for( int m = 0; m < ldcs.count(); m++ ) {
			MindLocalCircuitConnectionDef *cd = ldcs.getClassByIndex( m );
			String key = cd -> getSrcRegion() + "-" + cd -> getDstRegion();
			MindLocalCircuitConnectionDef *cdOther = cm.get( key );
			if( cdOther != NULL ) {
				MindRegion *rs = ms -> getMindRegion( cd -> getSrcRegion() );
				MindRegion *rd = ms -> getMindRegion( cd -> getDstRegion() );

				if( rs -> getRegionInfo() -> isTarget() == false && rd -> getRegionInfo() -> isTarget() == false ) {
					logger.logError( "checkMindModel_verifyRegionCircuits: region connection " + cd -> getSrcRegion() + " to " + cd -> getDstRegion() + " is duplicated (" +
						cd -> getCircuitDef() -> getId() + "/" + cdOther -> getCircuitDef() -> getId() + ")" );
					ok = false;
				}
			}
			else
				cm.add( key , cd );
		}
	}

	// verify duplicates
	for( int k = 0; k < cm.count(); k++ ) {
		MindLocalCircuitConnectionDef *cd = cm.getClassByIndex( k );
		String revKey = cd -> getDstRegion() + "-" + cd -> getSrcRegion();
		if( cm.get( revKey ) != NULL ) {
			ok = false;
			logger.logError( "checkMindModel_verifyLinkDuplicates: regions " + cd -> getSrcRegion() + " and " + cd -> getDstRegion() + " are connected in both directions" );
			cm.remove( revKey );
		}
	}

	return( ok );
}
