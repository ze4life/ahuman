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

	// read hierarchy
	hmind.load();
	checkHierarchy();
	checkMindModel();
}

void ModelVerifier::checkHierarchy() {
	logger.logInfo( "checkHierarchy: CHECK HIERARCHY..." );

	hierarchyMap.clear();

	bool regionsMappedAll = true;
	StringList divisions;
	hmind.getDivisions( divisions );

	for( int k = 0; k < divisions.count(); k++ ) {
		String division = divisions.get( k );
		bool regionsMapped = checkHierarchy_verifyChild( division , true );
		if( regionsMapped == false )
			regionsMappedAll = false;
	}

	if( regionsMappedAll )
		logger.logInfo( "checkHierarchy: HIERARCHY IS OK" );
	else
		logger.logInfo( "checkHierarchy: HIERARCHY HAS MAPPING ERRORS" );
}

bool ModelVerifier::checkHierarchy_verifyChild( String parentNode , bool checkMapping ) {
	XmlHMindElementInfo info;
	hmind.getElementInfo( parentNode , info );

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
	hmind.getElements( parentNode , elements );

	if( elements.count() > 0 ) {
		mappedChildsAll = true;

		for( int k = 0; k < elements.count(); k++ ) {
			String node = elements.get( k );
			XmlHMindElementInfo childinfo;
			hmind.getElementInfo( node , childinfo );

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
		logger.logError( "checkHierarchy_verifyChild:" + info.name + " - region has no complete mapping to mind map" );
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

	// check region connectors are linked
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
