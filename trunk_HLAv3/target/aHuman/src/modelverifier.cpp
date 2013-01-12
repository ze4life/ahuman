#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

ModelVerifier::ModelVerifier( Xml p_modelArea ) {
	attachLogger();
	modelArea = p_modelArea;
}

ModelVerifier::~ModelVerifier() {
}

void ModelVerifier::verify() {
	logger.logInfo( "verify: VERIFY MIND SETUP..." );
	
	// collect mind regions
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();
	mm -> getMapRegions( regionMap );

	// read definitions
	hmindxml.load();
	circuitsxml.load();

	bool verifyHierarchy = modelArea.getBooleanProperty( "verifyHierarchy" , true );
	bool verifyCircuits = modelArea.getBooleanProperty( "verifyCircuits" , true );
	bool verifyMindModel = modelArea.getBooleanProperty( "verifyMindModel" , true );

	// verify
	if( verifyHierarchy )
		checkHierarchy();
	if( verifyCircuits )
		checkCircuits();
	if( verifyMindModel )
		checkMindModel();
}

void ModelVerifier::checkHierarchy() {
	logger.logInfo( "checkHierarchy: CHECK HIERARCHY..." );

	hierarchyMap.clear();

	bool regionsMappedAll = true;
	StringList divisions;
	hmindxml.getDivisions( divisions );

	for( int k = 0; k < divisions.count(); k++ ) {
		String division = divisions.get( k );
		bool regionsMapped = checkHierarchy_verifyChild( division , true );
		if( regionsMapped == false )
			regionsMappedAll = false;
	}

	if( regionsMappedAll )
		logger.logInfo( "checkHierarchy: HIERARCHY IS OK" );
	else
		logger.logInfo( "checkHierarchy: HIERARCHY HAS ERRORS" );
}

bool ModelVerifier::checkHierarchy_verifyChild( String parentNode , bool checkMapping ) {
	XmlHMindElementInfo info;
	hmindxml.getElementInfo( parentNode , info );

	bool mappedOwn = false;
	if( checkMapping ) {
		// verify mind mapping
		if( info.mapped ) {
			MindRegionDef *rd = regionMap.get( info.id );

			if( rd == NULL ) {
				logger.logError( "checkHierarchy_verifyChild: " + info.name + " - hierarchy region with id=" + info.id + " is not mapped to mind model" );
				return( false );
			}

			hierarchyMap.add( info.id , rd );
		}

		// verify coverage
		mappedOwn = info.mapped;
	}

	bool mappedChildsAll = false;

	// check all childs
	StringList elements;
	hmindxml.getElements( parentNode , elements );

	if( elements.count() > 0 ) {
		mappedChildsAll = true;

		for( int k = 0; k < elements.count(); k++ ) {
			String node = elements.get( k );
			XmlHMindElementInfo childinfo;
			hmindxml.getElementInfo( node , childinfo );

			bool checkMappingChilds = ( checkMapping == false || mappedOwn == true )? false : true;

			if( childinfo.ignore )
				checkMappingChilds = false;

			bool regionsMappedChilds = checkHierarchy_verifyChild( node , checkMappingChilds );
			if( childinfo.ignore == false && regionsMappedChilds == false )
				mappedChildsAll = false;
		}
	}

	if( mappedOwn )
		return( true );

	if( mappedChildsAll )
		return( true );

	if( checkMapping )
		logger.logError( "checkHierarchy_verifyChild: id=" + info.id + ", name=" + info.name + " - region has no complete mapping to mind map" );
	return( false );
}

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkCircuits() {
	// check circuits use correct components
	logger.logInfo( "checkCircuits: CHECK CIRCUITS ..." );

	bool checkAll = true;
	StringList circuits;
	circuitsxml.getCircuitList( circuits );

	for( int k = 0; k < circuits.count(); k++ ) {
		String id = circuits.get( k );

		// verify
		logger.logInfo( "checkCircuits: verify circuit id=" + id );
		bool checkOne = checkCircuits_verifyComponents( id );
		if( checkOne == false )
			checkAll = false;

		checkOne = checkCircuits_verifyLinks( id );
		if( checkOne == false )
			checkAll = false;
	}

	if( checkAll )
		logger.logInfo( "checkCircuits: CIRCUITS ARE OK" );
	else
		logger.logInfo( "checkCircuits: CIRCUITS HAVE ERRORS" );
}

bool ModelVerifier::checkCircuits_verifyComponents( String circuit ) {
	XmlCircuitInfo info;
	circuitsxml.getCircuitInfo( circuit , info );

	// check components
	bool checkAll = true;
	for( int k = 0; k < info.componentMapping.count(); k++ ) {
		String originalComponentId = info.componentMapping.getKeyByIndex( k );
		String modelComponentId = info.componentMapping.getClassByIndex( k );

		// check region in hierarchy
		if( !hmindxml.isComponent( modelComponentId ) ) {
			checkAll = false;
			logger.logError( "checkCircuits_verifyComponents: unknown region=" + modelComponentId + " mapped from component=" + originalComponentId );
		}
	}

	return( checkAll );
}

bool ModelVerifier::checkCircuits_verifyLinks( String circuit ) {
	XmlCircuitInfo info;
	circuitsxml.getCircuitInfo( circuit , info );

	// check links
	bool checkAll = true;
	FlatList<Xml> links;
	circuitsxml.getCircuitLinks( circuit , links );

	for( int k = 0; k < links.count(); k++ ) {
		Xml link = links.get( k );

		XmlCircuitLinkInfo linkinfo;
		circuitsxml.getCircuitLinkInfo( link , linkinfo );

		bool checkOne = checkCircuits_verifyCircuitLink( info , linkinfo );
		if( checkOne == false )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkCircuits_verifyCircuitLink( XmlCircuitInfo& circuit , XmlCircuitLinkInfo& link ) {
	// use mapping
	String compSrc = circuitsxml.mapComponent( circuit , link.compSrc );
	String compDst = circuitsxml.mapComponent( circuit , link.compDst );

	// ignore mapping errors
	if( hmindxml.isComponent( compSrc ) == false || hmindxml.isComponent( compDst ) == false )
		return( true );
	
	// ignore if it is connection from one component part to another, not listed in mind tree
	if( compSrc.equals( compDst ) )
		return( true );

	// find mapped regions
	String regionSrcId = hmindxml.getMappedRegion( compSrc );
	String regionDstId = hmindxml.getMappedRegion( compDst );

	// specific check if mapped to upper items
	if( regionSrcId.isEmpty() || regionDstId.isEmpty() ) {
		bool check = checkCircuits_verifyCircuitChildLinks( compSrc , compDst , regionSrcId , regionDstId );
		if( check == false )
			logger.logError( "checkCircuits_verifyCircuitLink: not found covering child link element=" + compSrc + " to element=" + compDst + ", from circuit component=" + link.compSrc + " to component=" + link.compDst );
		return( check );
	}

	MindService *ms = MindService::getService();

	// ignore check if no correct mapping
	if( ms -> isMindRegion( regionSrcId ) == false || ms -> isMindRegion( regionDstId ) == false )
		return( true );

	MindRegion *regionSrc = ms -> getMindRegion( regionSrcId );
	MindRegion *regionDst = ms -> getMindRegion( regionDstId );

	// check link exists from src to dst
	if( regionSrc -> checkLinkedTo( regionDst ) )
		return( true );

	// this link does not exist in mind model
	logger.logError( "checkCircuits_verifyCircuitLink: not found link from region=" + regionSrcId + " to region=" + regionDstId + ", from circuit component=" + link.compSrc + " to component=" + link.compDst );
	return( false );
}

bool ModelVerifier::checkCircuits_verifyCircuitChildLinks( String compSrc , String compDst , String regionSrcId , String regionDstId ) {
	// collect sets of child regions
	StringList srcRegions;
	if( regionSrcId.isEmpty() )
		hmindxml.getChildRegions( compSrc , srcRegions );
	else
		srcRegions.add( regionSrcId );

	StringList dstRegions;
	if( regionDstId.isEmpty() )
		hmindxml.getChildRegions( compDst , dstRegions );
	else
		dstRegions.add( regionDstId );

	// check mapping
	MindService *ms = MindService::getService();
	for( int k1 = 0; k1 < srcRegions.count(); k1++ ) {
		String srcRegionId = srcRegions.get( k1 );
		if( !ms -> isMindRegion( srcRegionId ) )
			continue;

		MindRegion *srcRegion = ms -> getMindRegion( srcRegionId );
		for( int k2 = 0; k2 < dstRegions.count(); k2++ ) {
			String dstRegionId = dstRegions.get( k2 );
			if( !ms -> isMindRegion( dstRegionId ) )
				continue;

			MindRegion *dstRegion = ms -> getMindRegion( dstRegionId );
			if( srcRegion -> checkLinkedTo( dstRegion ) )
				return( true );
		}
	}

	return( false );
}

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkMindModel() {
	logger.logInfo( "checkMindModel: CHECK MIND MODEL ..." );

	// check all regions
	bool regionsOkAll = true;
	for( int k = 0; k < regionMap.count(); k++ ) {
		MindRegionDef *regionDef = regionMap.getClassByIndex( k );
		bool regionOk = checkMindModel_verifyRegion( regionDef );
		if( regionOk == false )
			regionsOkAll = false;
	}

	if( regionsOkAll )
		logger.logInfo( "checkMindModel: MIND MODEL IS OK" );
	else
		logger.logInfo( "checkMindModel: MIND MODEL HAS ERRORS" );
}

bool ModelVerifier::checkMindModel_verifyRegion( MindRegionDef *regionDef ) {
	String name = regionDef -> getName();

	bool checkRegion = true;
	MindService *ms = MindService::getService();
	MindRegion *region = ms -> getMindRegion( name );

	// check mapped to hierarchy
	if( hierarchyMap.get( name ) == NULL ) {
		checkRegion = false;
		logger.logError( "checkMindModel_verifyRegion: " + name + " - region is not mapped to hierarchy" );
	}

	// check region in circuits
	if( !checkMindModel_verifyRegionCircuits( regionDef , region ) )
		checkRegion = false;

	// check region connectors are linked
	if( checkRegion )
		if( !checkMindModel_verifyLinkedConnectors( regionDef , region ) )
			checkRegion = false;

	return( checkRegion );
}

bool ModelVerifier::checkMindModel_verifyLinkedConnectors( MindRegionDef *regionDef , MindRegion *region ) {
	String name = regionDef -> getName();

	// check region has no connections at all
	MindRegionLinkSet *set = region -> getRegionLinkSet();
	if( set == NULL || set -> getCount() == 0 ) {
		logger.logError( "checkMindModel_verifyLinkedConnectors: region=" + name + " is not connected to any other region" );
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
			logger.logError( "checkMindModel_verifyLinkedConnectors: region=" + name + " connector=" + entity + " - is not connected" );
		}
	}

	return( checkRegion );
}

bool ModelVerifier::checkMindModel_verifyRegionCircuits( MindRegionDef *regionDef , MindRegion *region ) {
	String name = regionDef -> getName();

	// ignore unknown region
	if( !hmindxml.isComponent( name ) )
		return( true );

	// find circuit which references given region
	StringList circuits;
	circuitsxml.getCircuitList( circuits );
	for( int k = 0; k < circuits.count(); k++ ) {
		String circuit = circuits.get( k );
		if( circuitsxml.checkRegionUsedByCircuit( name , circuit ) )
			return( true );
	}

	logger.logError( "checkMindModel_verifyRegionCircuits: region=" + name + " is not covered by circuit collection" );
	return( false );
}

