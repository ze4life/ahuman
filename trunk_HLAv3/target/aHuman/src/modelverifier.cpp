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

	MindModel::load();

	// collect mind regions
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();
	mm -> getMapRegions( regionMap );

	bool verifyHierarchy = modelArea.getBooleanProperty( "verifyHierarchy" , true );
	bool verifyCircuits = modelArea.getBooleanProperty( "verifyCircuits" , true );
	bool verifyNerves = modelArea.getBooleanProperty( "verifyNerves" , true );
	bool verifyMuscles = modelArea.getBooleanProperty( "verifyMuscles" , true );
	bool verifyMindModel = modelArea.getBooleanProperty( "verifyMindModel" , true );

	// verify
	if( verifyHierarchy )
		checkHierarchy();
	if( verifyCircuits )
		checkCircuits();
	if( verifyNerves )
		checkNerves();
	if( verifyMuscles )
		checkMuscles();
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
	const XmlHMindElementInfo& info = hmindxml.getElementInfo( parentNode );

	logger.logInfo( "check item=" + info.name );

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
			const XmlHMindElementInfo& childinfo = hmindxml.getElementInfo( node );

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
	XmlCircuitInfo& info = circuitsxml.getCircuitInfo( circuit );

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
	XmlCircuitInfo& info = circuitsxml.getCircuitInfo( circuit );

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
		bool check = checkLinkCoveredByModel( compSrc , compDst );
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

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkNerves() {
	// check nerves use correct components
	logger.logInfo( "checkNerves: CHECK NERVES ..." );

	bool checkAll = true;
	StringList nerves;
	nervesxml.getNerveList( nerves );

	for( int k = 0; k < nerves.count(); k++ ) {
		String id = nerves.get( k );

		// verify
		logger.logInfo( "checkNerves: verify nerve id=" + id );
		bool checkOne = checkNerves_verifyComponents( id );
		if( checkOne == false )
			checkAll = false;
	}

	if( checkAll )
		logger.logInfo( "checkNerves: NERVES ARE OK" );
	else
		logger.logInfo( "checkNerves: NERVES HAVE ERRORS" );
}

bool ModelVerifier::checkNerves_verifyComponents( String nerve ) {
	XmlNerveInfo& info = nervesxml.getNerveInfo( nerve );

	bool res = true;

	// check nerve modality
	String nm;
	for( int k = 0; k < info.mods.count(); k++ ) {
		nm = info.mods.get( k );
		if( !( nm.equals( "general sensory" ) || nm.equals( "cranial motor" ) || nm.equals( "visceral motor" ) || nm.equals( "sympahetic motor" ) || nm.equals( "parasympahetic motor" ) || 
			nm.equals( "autonomic sensory" ) || nm.equals( "special sensory" ) || nm.equals( "ganglion sensory" ) || nm.equals( "flexor motor" ) || nm.equals( "extensor motor" ) ) ) {
			logger.logError( "checkNerves_verifyLinks: nerve=" + info.name + ", unknown modality=" + nm );
			res = false;
		}
	}

	for( int k = 0; k < info.fibers.count(); k++ ) {
		XmlNerveFiberInfo& nf = info.fibers.getRef( k );

		logger.logInfo( "checkNerves: check fiber src=" + nf.src + ", dst=" + nf.dst );

		// check items
		if( !checkFiberComp( info , nf , nf.src ) )
			res = false;
		if( !checkFiberComp( info , nf , nf.dst ) )
			res = false;

		for( int m = 0; m < nf.mids.count(); m++ ) {
			String mid = nf.mids.get( m );
			if( !checkFiberComp( info , nf , mid ) )
				res = false;
		}

		// check type
		if( !checkFiberType( info , nf , nf.type ) )
			res = false;

		// check links
		if( res ) {
			if( !checkNerves_verifyLinks( info , nf ) )
				res = false;
		}
	}

	return( res );
}

bool ModelVerifier::checkFiberComp( XmlNerveInfo& info , XmlNerveFiberInfo& nf , String comp ) {
	if( hmindxml.isComponent( comp ) == false ) {
		logger.logError( "checkFiberComp: nerve=" + info.name + ", comp=" + comp + " - is not found in hierarchy" );
		return( false );
	}
	
	// find mapped regions
	String region = hmindxml.getMappedRegion( comp );
	if( region.isEmpty() ) {
		logger.logError( "checkFiberComp: nerve=" + info.name + ", comp=" + comp + " - is not mapped to region" );
		return( false );
	}

	return( true );
}

bool ModelVerifier::checkNerves_verifyLinks( XmlNerveInfo& info , XmlNerveFiberInfo& nf ) {
	String src = hmindxml.getMappedRegion( nf.src );
	String dst;

	bool res = true;

	ModelVerifierFiberChainPosEnum pos;
	int midleft;
	int midright;
	for( int k = 0; k <= nf.mids.count(); k++ ) {
		if( k == nf.mids.count() )
			dst = nf.dst;
		else
			dst = nf.mids.get( k );
		dst = hmindxml.getMappedRegion( dst );

		midleft = k;
		midright = nf.mids.count() - k;
		if( k == 0 )
			pos = FIBER_CHAIN_POS_BEGIN;
		else if( k == nf.mids.count() )
			pos = FIBER_CHAIN_POS_END;
		else
			pos = FIBER_CHAIN_POS_MID;

		if( !checkNerves_verifyFiberChain( info , nf , src , dst , pos , midleft , midright ) ) {
			logger.logError( "checkNerves_verifyLinks: nerve=" + info.name + ", src=" + src + ", dst=" + dst + " - is not covered by mind" );
			res = false;
		}

		src = dst;
	}

	return( res );
}

bool ModelVerifier::checkFiberType( XmlNerveInfo& info , XmlNerveFiberInfo& nf , String type ) {
	// comparent fiber type and nerve modality
	bool res = true;
	if( type.equals( "GSE" ) ) {
		if( !( info.mods.find( "cranial motor" ) >= 0 || info.mods.find( "flexor motor" ) >= 0 || info.mods.find( "extensor motor" ) >= 0 ) )
			res = false;
	}
	else if( type.equals( "GSA" ) ) {
		if( !( info.mods.find( "general sensory" ) >= 0 ) )
			res = false;
	}
	else if( type.equals( "GVA" ) ) {
		if( !( info.mods.find( "autonomic sensory" ) >= 0 ) )
			res = false;
	}
	else if( type.equals( "GVE" ) ) {
		if( !( info.mods.find( "sympathetic motor" ) >= 0 || info.mods.find( "parasympathetic motor" ) >= 0 ) )
			res = false;
	}
	else if( type.equals( "SSA" ) ) {
		if( !( info.mods.find( "special sensory" ) >= 0 ) )
			res = false;
	}
	else if( type.equals( "SVA" ) ) {
		if( !( info.mods.find( "ganglion sensory" ) >= 0 ) )
			res = false;
	}
	else if( type.equals( "SVE" ) ) {
		if( !( info.mods.find( "visceral motor" ) >= 0 ) )
			res = false;
	}
	else {
		logger.logError( "checkFiberType: nerve=" + info.name + ", type=" + type + " - is unknown type" );
		return( false );
	}

	if( res == false )
		logger.logError( "checkFiberType: nerve=" + info.name + ", type=" + type + " - is incompatible with modality=" + info.modality );

	return( res );
}

bool ModelVerifier::checkNerves_verifyFiberChain( XmlNerveInfo& info , XmlNerveFiberInfo& nf , String regionSrcId , String regionDstId , ModelVerifierFiberChainPosEnum pos , int midleft , int midright ) {
	MindService *ms = MindService::getService();

	// ignore check if no correct mapping
	if( ms -> isMindRegion( regionSrcId ) == false || ms -> isMindRegion( regionDstId ) == false )
		return( true );

	MindRegion *regionSrc = ms -> getMindRegion( regionSrcId );
	MindRegion *regionDst = ms -> getMindRegion( regionDstId );

	bool res = true;

	// check link exists from src to dst
	if( !regionSrc -> checkLinkedTo( regionDst ) ) {
		res = false;
		logger.logError( "checkNerves_verifyFiberChain: not found link from region=" + regionSrcId + " to region=" + regionDstId + ", from nerve=" + info.name );
	}

	// check fiber type is valid
	ModelFiberValidator fv;
	if( nf.type.equals( "GSE" ) || nf.type.equals( "SVE" ) ) {
		if( pos == FIBER_CHAIN_POS_END )
			if( !fv.isValid_GSE_end( info , regionSrc , regionDst ) )
				res = false;
	}
	else if( nf.type.equals( "GSA" ) || nf.type.equals( "GVA" ) ) {
		if( pos == FIBER_CHAIN_POS_BEGIN )
			if( !fv.isValid_GSA_begin( info , regionSrc , regionDst ) )
				res = false;
		if( midleft == 1 )
			if( !fv.isValid_GSA_afterbegin( info , regionSrc , regionDst ) )
				res = false;
	}
	else if( nf.type.equals( "GVE" ) ) {
		if( pos == FIBER_CHAIN_POS_END )
			if( !fv.isValid_GVE_end( info , regionSrc , regionDst ) )
				res = false;
		if( midright == 1 )
			if( !fv.isValid_GVE_beforeend( info , regionSrc , regionDst ) )
				res = false;
	}
	else if( nf.type.equals( "SSA" ) ) {
		if( pos == FIBER_CHAIN_POS_BEGIN )
			if( !fv.isValid_SSA_begin( info , regionSrc , regionDst ) )
				res = false;
	}
	else if( nf.type.equals( "SVA" ) ) {
		if( pos == FIBER_CHAIN_POS_BEGIN )
			if( !fv.isValid_SVA_begin( info , regionSrc , regionDst ) )
				res = false;
		if( midleft == 1 )
			if( !fv.isValid_SVA_afterbegin( info , regionSrc , regionDst ) )
				res = false;
	}

	return( res );
}

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkMuscles() {
	// check muscles use correct nerves
	logger.logInfo( "checkNerves: CHECK MUSCLES ..." );

	bool checkAll = true;
	StringList muscles;
	musclesxml.getMuscleList( muscles );

	for( int k = 0; k < muscles.count(); k++ ) {
		String id = muscles.get( k );

		// verify
		logger.logInfo( "checkMuscles: verify muscle id=" + id );
		bool checkOne = checkMuscles_verifyNerves( id );
		if( checkOne == false )
			checkAll = false;
	}

	if( checkAll )
		logger.logInfo( "checkMuscles: MUSCLES ARE OK" );
	else
		logger.logInfo( "checkMuscles: MUSCLES HAVE ERRORS" );
}

bool ModelVerifier::checkMuscles_verifyNerves( String muscle ) {
	XmlMuscleInfo& info = musclesxml.getMuscleInfo( muscle );

	if( info.nerve.isEmpty() )
		return( true );

	bool res = true;

	String mtype = info.type;
	if( mtype.isEmpty() ) {
		logger.logError( "checkMuscles_verifyNerves: muscle=" + info.name + ", type is not set" );
		res = false;
	}
	else if( ! ( mtype.equals( "flexor" ) || mtype.equals( "extensor" ) || mtype.equals( "cranial" ) || mtype.equals( "gland" ) ) ) {
		logger.logError( "checkMuscles_verifyNerves: muscle=" + info.name + ", invalid type=" + mtype );
		res = false;
	}

	if( !nervesxml.checkNerve( info.nerve ) ) {
		logger.logError( "checkMuscles_verifyNerves: muscle=" + info.name + ", nerve=" + info.nerve + " - is unknown nerve" );
		res = false;
	}

	XmlNerveInfo& nerve = nervesxml.getNerveInfo( info.nerve );

	// compare muscle type with nerve modality
	bool xres = true;
	if( mtype.equals( "flexor" ) ) {
		if( nerve.mods.find( "flexor motor" ) < 0 && nerve.mods.find( "sympathetic motor" ) < 0 )
			xres = false;
	}
	else if( mtype.equals( "extensor" ) ) {
		if( nerve.mods.find( "extensor motor" ) < 0 && nerve.mods.find( "parasympathetic motor" ) < 0 )
			xres = false;
	}
	else if( mtype.equals( "cranial" ) ) {
		if( nerve.mods.find( "cranial motor" ) < 0 && nerve.mods.find( "visceral motor" ) < 0 && nerve.mods.find( "sympathetic motor" ) < 0 && nerve.mods.find( "parasympathetic motor" ) < 0 )
			xres = false;
	}
	else if( mtype.equals( "gland" ) ) {
		if( nerve.mods.find( "sympathetic motor" ) < 0 && nerve.mods.find( "parasympathetic motor" ) < 0 )
			xres = false;
	}

	if( xres == false ) {
		res = false;
		logger.logError( "checkMuscles_verifyNerves: muscle=" + info.name + ", nerve=" + info.nerve + " - muscle type=" + mtype + " does not correspond to nerve modality=" + nerve.modality );
	}

	return( res );
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

