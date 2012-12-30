#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

ModelVerifier::ModelVerifier() {
	attachLogger();

	// collect mind regions
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();
	mm -> getMapRegions( regionMap );
}

ModelVerifier::~ModelVerifier() {
}

void ModelVerifier::verify( Xml modelArea ) {
	logger.logInfo( "verify: VERIFY MIND SETUP..." );
	
	// read hierarchy
	EnvService *es = EnvService::getService();
	Xml hmind = es -> loadXml( "hmind.xml" );
	ASSERTMSG( hmind.exists() , "unable to read file hmind.xml" );

	checkHierarchy( modelArea , hmind );
	checkMindModel( modelArea , hmind );
}

void ModelVerifier::checkHierarchy( Xml modelArea , Xml hmind ) {
	logger.logInfo( "checkHierarchy: CHECK HIERARCHY..." );

	hierarchyMap.clear();

	bool regionsMappedAll = true;
	for( Xml xmlChild = hmind.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		bool regionsMapped = checkHierarchy_verifyChild( modelArea , xmlChild , true );
		if( regionsMapped == false )
			regionsMappedAll = false;
	}

	if( regionsMappedAll )
		logger.logInfo( "checkHierarchy: HIERARCHY IS OK" );
	else
		logger.logInfo( "checkHierarchy: HIERARCHY HAS MAPPING ERRORS" );
}

bool ModelVerifier::checkHierarchy_verifyChild( Xml modelArea , Xml element , bool checkMapping ) {
	String name = element.getAttribute( "name" , "" );

	bool mappedOwn = false;
	if( checkMapping ) {
		// verify mind mapping
		String id = element.getAttribute( "id" , "" );
		if( !id.isEmpty() ) {
			MindRegionDef *rd = regionMap.get( id );

			if( rd == NULL ) {
				logger.logError( "checkHierarchy_verifyChild: " + name + " - hierarchy region with id=" + id + " is not mapped to mind model" );
				return( false );
			}

			hierarchyMap.add( id , rd );
		}

		// verify coverage
		mappedOwn = ( id.isEmpty() )? false : true;
	}

	bool mappedChildsAll = false;
	if( element.getFirstChild( "element" ).exists() ) {
		mappedChildsAll = true;

		for( Xml xmlChild = element.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
			bool checkMappingChilds = ( checkMapping == false || mappedOwn == true )? false : true;
			bool ignore = xmlChild.getBooleanAttribute( "ignore" , false );

			if( ignore )
				checkMappingChilds = false;

			bool regionsMappedChilds = checkHierarchy_verifyChild( modelArea , xmlChild , checkMappingChilds );
			if( ignore == false && regionsMappedChilds == false )
				mappedChildsAll = false;
		}
	}

	if( mappedOwn )
		return( true );

	if( mappedChildsAll )
		return( true );

	if( checkMapping )
		logger.logError( "checkHierarchy_verifyChild:" + name + " - region has no complete mapping to mind map" );
	return( false );
}

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkMindModel( Xml modelArea , Xml hmind ) {
	logger.logInfo( "checkMindModel: CHECK MIND MODEL ..." );

	// check all regions
	bool regionsOkAll = true;
	for( int k = 0; k < regionMap.count(); k++ ) {
		MindRegionDef *regionDef = regionMap.getClassByIndex( k );
		bool regionOk = checkMindModel_verifyRegion( modelArea , hmind , regionDef );
		if( regionOk == false )
			regionsOkAll = false;
	}

	if( regionsOkAll )
		logger.logInfo( "checkMindModel: MIND MODEL IS OK" );
	else
		logger.logInfo( "checkMindModel: MIND MODEL HAS ERRORS" );
}

bool ModelVerifier::checkMindModel_verifyRegion( Xml modelArea , Xml hmind , MindRegionDef *regionDef ) {
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
	if( !checkMindModel_verifyLinkedConnectors( modelArea , hmind , regionDef , region ) )
		checkRegion = false;

	return( checkRegion );
}

bool ModelVerifier::checkMindModel_verifyLinkedConnectors( Xml modelArea , Xml hmind , MindRegionDef *regionDef , MindRegion *region ) {
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
