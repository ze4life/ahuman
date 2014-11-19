#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiAreaPages::WikiAreaPages( WikiMaker *p_wm ) {
	attachLogger();
	wm = p_wm;
}

WikiAreaPages::~WikiAreaPages() {
}

void WikiAreaPages::execute() {
	bool createAreaPages = wm -> checkCreateAreaPages();
	if( createAreaPages == false ) {
		logger.logInfo( "skip creating area pages" );
		return;
	}

	// get wiki file
	String wikiDir = wm -> getWikiPath();
	String selectedArea = wm -> getSelectedArea();

	MindService *ms = MindService::getService();

	// by area
	MapStringToClass<MindArea>& areaMap = ms -> getMindAreas();
	for( int k = 0; k < areaMap.count(); k++ ) {
		MindArea *area = areaMap.getClassByIndex( k );

		if( !selectedArea.isEmpty() ) {
			if( !selectedArea.equals( area -> getAreaId() ) )
				continue;
		}

		createAreaPages_createArea( wikiDir , area );
	}
}

void WikiAreaPages::createAreaPages_createArea( String wikiDir , MindArea *area ) {
	MindAreaDef *def = area -> getMindAreaDef();
	MapStringToClass<MindLocalCircuitDef>& circuits = def -> getCircuits();
	
	StringList lines;
	createAreaPages_createAreaCircuitTable( circuits , lines );

	for( int k = 0; k < circuits.count(); k++ ) {
		MindLocalCircuitDef& circuit = circuits.getClassRefByIndex( k );
		createAreaPages_createAreaCircuit( area , circuit , lines );
	}

	String sectionName = "Local Circuits";
	String wikiPage = wm -> getAreaPage( area -> getAreaId() );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );

	createAreaPages_createCircuitsAndReferencesTableSection( wikiDir , area );

	bool createRegionPages = wm -> checkCreateRegionPages();
	if( createRegionPages )
		createAreaPages_createRegionPages( wikiDir , area );
}

void WikiAreaPages::createAreaPages_createAreaCircuitTable( MapStringToClass<MindLocalCircuitDef>& circuits , StringList& lines ) {
	createAreaPages_createAreaCircuitTableLine( NULL , lines );

	for( int k = 0; k < circuits.count(); k++ ) {
		MindLocalCircuitDef *circuit = circuits.getClassByIndex( k );
		createAreaPages_createAreaCircuitTableLine( circuit , lines );
	}
}

void WikiAreaPages::createAreaPages_createAreaCircuitTableLine( MindLocalCircuitDef *circuit , StringList& lines ) {
	String line;
	if( circuit == NULL ) {
		line = "|| *ID* || *Name* || *Regions* ||";
		lines.add( line );
		return;
	}

	line = "|| " + circuit -> getId() + " || " + circuit -> getName() + " || ";
	MapStringToClass<MindRegionDef>& regions = circuit -> getRegions();

	String id;
	String list;
	for( int k = 0; k < regions.count(); k++ ) {
		id = regions.getKeyByIndex( k );

		if( k > 0 )
			list += ", ";

		list += wm -> getRegionReference( id );
	}

	line += list + " ||";
	lines.add( line );
}

void WikiAreaPages::createAreaPages_createCircuitsAndReferencesTableSection( String wikiDir , MindArea *area ) {
	// skip circuits for target areas - will be in region pages
	if( area -> isTargetArea() )
		return;

	// collect circuits which reference any of area regions
	MindService *ms = MindService::getService();

	StringList circuits;
	wm -> circuitsxml.getCircuitList( circuits );

	MapStringToString circuitKeys;
	for( int k = 0; k < circuits.count(); k++ ) {
		String circuitId = circuits.get( k );
		XmlCircuitInfo& info = wm -> circuitsxml.getCircuitInfo( circuitId );

		String key = createAreaPages_getCircuitKey( area , info );
		if( key.isEmpty() )
			continue;

		circuitKeys.add( key , circuitId );
	}

	// add circuits section - sorted by relevance
	StringList lines;
	for( int k = circuitKeys.count() - 1; k >= 0; k-- ) {
		String circuitId = circuitKeys.getClassByIndex( k );
		XmlCircuitInfo& info = wm -> circuitsxml.getCircuitInfo( circuitId );
		createAreaPages_getCircuitLines( info , lines );
	}

	String sectionName = "Thirdparty Circuits";
	String wikiPage = wm -> getAreaPage( area -> getAreaId() );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
	lines.clear();

	// add unique and sorted references - sorted by relevance
	MapStringToClass<MindArea> refs;
	for( int k = circuitKeys.count() - 1; k >= 0; k-- ) {
		String circuitId = circuitKeys.getClassByIndex( k );
		XmlCircuitInfo& info = wm -> circuitsxml.getCircuitInfo( circuitId );

		if( !info.reference.equals( "UNKNOWN" ) )
			if( refs.get( info.reference ) == NULL ) {
				refs.add( info.reference , area );
				lines.add( String( "  * " ) + info.reference );
			}
	}

	sectionName = "References";
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

String WikiAreaPages::createAreaPages_getCircuitKey( MindArea *area , XmlCircuitInfo& info ) {
	// get circuit regions
	StringList comps;
	wm -> circuitsxml.getCircuitComponents( info , comps );

	// check circuit mentions area regions
	StringList compUsed;
	for( int k = 0; k < comps.count(); k++ ) {
		String comp = comps.get( k );
		String region = wm -> hmindxml.getMappedRegion( comp );
		if( !region.isEmpty() )
			if( area -> getMindAreaDef() -> findRegion( region ) != NULL )
				compUsed.add( region );
	}

	if( compUsed.count() == 0 )
		return( "" );

	// make key
	compUsed.sort();
	char l_buf[ 10 ];
	sprintf( l_buf , "%3.3d" , compUsed.count() );

	String key = l_buf;
	for( int k = 0; k < compUsed.count(); k++ )
		key += "." + compUsed.get( k );

	// ensure unique
	key += "." + info.id;
	return( key );
}

void WikiAreaPages::createAreaPages_getCircuitLines( XmlCircuitInfo& info , StringList& lines ) {
	String ref;
	if( info.reference.equals( "UNKNOWN" ) )
		ref = "(unknown reference)";
	else
		ref = "- see [" + info.reference + " Reference]";

	lines.add( "  * [" + info.image + " " + info.name + "] " + ref );
	lines.add( "" );

	lines.add( wm -> getImageWikiLink( info.image , info.imageHeight , info.imageWidth ) );
	lines.add( "" );
}

void WikiAreaPages::createAreaPages_createRegionPages( String wikiDir , MindArea *area ) {
	MapStringToClass<MindRegion>& regions = area -> getRegions();
	for( int k = 0; k < regions.count(); k++ ) {
		WikiRegionPage maker( wm , wikiDir , regions.getClassByIndex( k ) );
		maker.execute();
	}
}

void WikiAreaPages::createAreaPages_createAreaCircuit( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines ) {
	lines.add( "" );
	lines.add( "== " + circuit.getName() + " ==" );
	lines.add( "" );

	lines.add( "" );
	String line = wm -> getCircuitImageRef( circuit );
	lines.add( line );
	lines.add( "" );

	createAreaPages_createRegionTableSection( area , circuit , lines );
	createAreaPages_createConnectivityTableSection( area , circuit , lines );
}

void WikiAreaPages::createAreaPages_createRegionTableSection( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines ) {
	// heading
	String s = createAreaPages_getRegionTableRow( NULL );
	lines.add( s );

	// regions
	MindAreaDef *areaDef = area -> getMindAreaDef();
	MapStringToClass<MindRegionDef>& regionMap = circuit.getRegions();
	for( int k = 0; k < regionMap.count(); k++ ) {
		MindRegionDef *region = regionMap.getClassByIndex( k );
		s = createAreaPages_getRegionTableRow( region );
		lines.add( s );
	}
}

String WikiAreaPages::createAreaPages_getRegionTableRow( MindRegionDef *region ) {
	String value;

	// heading
	if( region == NULL ) {
		value = "|| *Component ID* || *Component Name* || *Type* || *Service* || *Function* || *Comments* ||";
		return( value );
	}

	// region row
	String regionId = region -> getId();
	const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( regionId );
	
	value = "|| " + wm -> getRegionReference( regionId ) + " || " + 
		wm -> getTableCellAttribute( info.id , "name" , info.name , true , 0 ) + " || " + 
		wm -> getTableCellAttribute( info.id , "type" , info.batype , true , 0 ) + " || " + 
		wm -> getTableCellAttribute( info.id , "service" , region -> getServiceName() , true , 0 ) + " || " + 
		wm -> getTableCellAttribute( info.id , "function" , info.function , true , 80 ) + " || " + 
		wm -> getTableCellAttribute( info.id , "notes" , info.notes , false , 50 ) + " ||";

	return( value );
}

void WikiAreaPages::createAreaPages_createConnectivityTableSection( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines ) {
	MapStringToClass<MindLocalCircuitConnectionDef> connections;

	if( !area -> isTargetArea() ) {
		// internal connections
		lines.add( "" );
		lines.add( "*Internal Region Connections:*" );
		createAreaPages_getInternalConnections( area , circuit , connections );
		createAreaPages_addInternalConnections( area , circuit , lines , connections );
	}

	// external connections - in
	lines.add( "" );
	lines.add( "*External Inbound Region Connections:*" );
	MapStringToClass<MindLocalCircuitConnectionDef> connectionsInputs;
	createAreaPages_getExternalConnections( area , circuit , connectionsInputs , true );
	createAreaPages_addExternalConnections( area , circuit , lines , connectionsInputs , true );

	// external connections - out
	lines.add( "" );
	lines.add( "*External Outbound Region Connections:*" );
	MapStringToClass<MindLocalCircuitConnectionDef> connectionsOutputs;
	createAreaPages_getExternalConnections( area , circuit , connectionsOutputs , false );
	createAreaPages_addExternalConnections( area , circuit , lines , connectionsOutputs , false );

	// create dot file
	createDotFile( area , circuit , connections , connectionsInputs , connectionsOutputs );
}

void WikiAreaPages::createAreaPages_addInternalConnections( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines , MapStringToClass<MindLocalCircuitConnectionDef>& connections ) {
	if( connections.count() == 0 ) {
		lines.add( "  * no connections" );
		return;
	}

	createAreaPages_addInternalConnectionTableLine( area , circuit , NULL , lines );
	for( int k = 0; k < connections.count(); k++ ) {
		MindLocalCircuitConnectionDef *c = connections.getClassByIndex( k );
		createAreaPages_addInternalConnectionTableLine( area , circuit , c , lines );
	}
}

void WikiAreaPages::createAreaPages_addExternalConnections( MindArea *area , MindLocalCircuitDef& circuit , StringList& lines , MapStringToClass<MindLocalCircuitConnectionDef>& connections , bool p_inputs ) {
	if( connections.count() == 0 ) {
		lines.add( "  * no connections" );
		return;
	}

	createAreaPages_getExternalConnectionTableLine( area , circuit , NULL , lines , p_inputs , NULL );

	// split connections by area types
	MindService *ms = MindService::getService();
	MapStringToClass<MapStringToClass<MindLocalCircuitConnectionDef>> groups;
	for( int k = 0; k < connections.count(); k++ ) {
		MindLocalCircuitConnectionDef *c = connections.getClassByIndex( k );
		String regionId = ( p_inputs )? c -> getSrcRegion() : c -> getDstRegion();
		MindRegion *region = ms -> getMindRegion( regionId );
		String areaType = region -> getArea() -> getMindAreaDef() -> getAreaType();

		MapStringToClass<MindLocalCircuitConnectionDef> *z = groups.get( areaType );
		if( z == NULL ) {
			z = new MapStringToClass<MindLocalCircuitConnectionDef>;
			groups.add( areaType , z );
		}

		String key = connections.getKeyByIndex( k );
		z -> add( key , c );
	}

	for( int k = 0; k < groups.count(); k++ ) {
		String areaType = groups.getKeyByIndex( k );
		MapStringToClass<MindLocalCircuitConnectionDef> *z = groups.getClassByIndex( k );
		createAreaPages_getExternalConnectionTableLine( area , circuit , NULL , lines , p_inputs , areaType );

		for( int m = 0; m < z -> count(); m++ ) {
			MindLocalCircuitConnectionDef *c = z -> getClassByIndex( m );
			createAreaPages_getExternalConnectionTableLine( area , circuit , c , lines , p_inputs , NULL );
		}
	}
}

void WikiAreaPages::createAreaPages_getInternalConnections( MindArea *area , MindLocalCircuitDef& circuit , MapStringToClass<MindLocalCircuitConnectionDef>& connections ) {
	ClassList<MindLocalCircuitConnectionDef> links;
	circuit.getInternalConnections( links );

	for( int k = 0; k < links.count(); k++ ) {
		MindLocalCircuitConnectionDef *c = links.get( k );

		// ignore secondary
		if( !c -> isPrimary() )
			continue;

		String key = c -> getSrcRegion() + "#" + c -> getDstRegion();
		if( connections.get( key ) == NULL )
			connections.add( key , c );
	}
}

void WikiAreaPages::createAreaPages_getExternalConnections( MindArea *area , MindLocalCircuitDef& circuit , MapStringToClass<MindLocalCircuitConnectionDef>& connections , bool isin ) {
	ClassList<MindLocalCircuitConnectionDef> links;
	circuit.getExternalConnections( links , isin );

	MindService *ms = MindService::getService();
	for( int k = 0; k < links.count(); k++ ) {
		MindLocalCircuitConnectionDef *c = links.get( k );

		// ignore secondary
		if( !c -> isPrimary() )
			continue;

		String key;
		if( isin == false ) {
			MindRegion *region = ms -> getMindRegion( c -> getDstRegion() );
			key = region -> getArea() -> getAreaId() + "#" + c -> getSrcRegion() + "#" + c -> getDstRegion() + "#1";
			if( connections.get( key ) == NULL )
				connections.add( key , c );
		}
		else {
			MindRegion *region = ms -> getMindRegion( c -> getSrcRegion() );
			key = region -> getArea() -> getAreaId() + "#" + c -> getDstRegion() + "#" + c -> getSrcRegion() + "#2";
			if( connections.get( key ) == NULL )
				connections.add( key , c );
		}
	}
}

void WikiAreaPages::createAreaPages_addInternalConnectionTableLine( MindArea *area , MindLocalCircuitDef& circuit , MindLocalCircuitConnectionDef *link , StringList& lines ) {
	String line;
	String value1;
	if( link == NULL ) {
		// add heading
		lines.add( "" );
		line = "|| *Source Region* || *Target Region* || *Type* || *Reference* ||";
		lines.add( line );
		wm -> clearRepeats1( value1 );
		return;
	}

	// table row
	String reference = wm -> findReference( link );
	value1 = wm -> getRegionReference( link -> getSrcRegion() );
	wm -> clearRepeats1( value1 );
	line = "|| " + value1 + " || " + wm -> getRegionReference( link -> getDstRegion() ) + " || " + 
		link -> getTypeName() + " || " + reference + " ||" ;
	lines.add( line );
}

void WikiAreaPages::createAreaPages_getExternalConnectionTableLine( MindArea *area , MindLocalCircuitDef& circuit , MindLocalCircuitConnectionDef *link , StringList& lines , bool isin , const char *p_areatype ) {
	String line;
	String value1;
	String value2;
	if( link == NULL ) {
		if( p_areatype == NULL ) {
			// add heading
			lines.add( "" );

			String colName = "Type";
			if( area -> isTargetArea() )
				colName = "Connector";

			if( isin )
				line = "|| *Source Area* || *Local Region* || *Source Region* || *Source Name* || *" + colName + "* || *Reference* ||";
			else
				line = "|| *Target Area* || *Local Region* || *Target Region* || *Target Name* || *" + colName + "* || *Reference* ||";
		}
		else {
			line = "|| <font color=\"red\">" + String( p_areatype ) + "</font> || || || || || ||";
		}

		lines.add( line );
		wm -> clearRepeats2( value1 , value2 );
		return;
	}

	// table row
	MindService *ms = MindService::getService();
	String srcRegionId = link -> getSrcRegion();
	String dstRegionId = link -> getDstRegion();

	String reference = wm -> findReference( link );
	String regionReference;
	String regionName;
	MindRegion *region;
	if( isin ) {
		const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( srcRegionId );
		regionName = info.name;
		region = ms -> getMindRegion( srcRegionId );
		value1 = wm -> getAreaReference( region -> getArea() -> getAreaId() );
		value2 = wm -> getRegionReference( dstRegionId );
		wm -> clearRepeats2( value1 , value2 );
		regionReference = wm -> getRegionReference( srcRegionId );
	}
	else {
		const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( dstRegionId );
		regionName = info.name;
		region = ms -> getMindRegion( dstRegionId );
		value1 = wm -> getAreaReference( region -> getArea() -> getAreaId() );
		value2 = wm -> getRegionReference( srcRegionId );
		wm -> clearRepeats2( value1 , value2 );
		regionReference = wm -> getRegionReference( dstRegionId );
	}

	if( area -> isTargetArea() ) {
		String targetRegionId = ( isin )? dstRegionId : srcRegionId;
		MindRegion *targetRegion = ms -> getMindRegion( targetRegionId );

		MapStringToString connectors;
		getTargetLinkConnectors( targetRegion , region , connectors );
		for( int k = 0; k < connectors.count(); k++ ) {
			String connector = connectors.getKeyByIndex( k );
			if( k == 0 )
				line = "|| " + value1 + " || " + value2 + " || " + regionReference + " || " + regionName + " || " + connector + " || " + reference + " ||";
			else
				line = "|| || || || || " + connector + " || ||";
			lines.add( line );
		}
	}
	else {
		line = "|| " + value1 + " || " + value2 + " || " + regionReference + " || " + regionName + " || " + link -> getTypeName() + " || " + reference + " ||";
		lines.add( line );
	}
}

void WikiAreaPages::getTargetLinkConnectors( MindRegion *targetRegion , MindRegion *linkRegion , MapStringToString& connectors ) {
	MindRegionTypeDef *type = targetRegion -> getRegionType();
	ClassList<MindRegionConnectorDef>& connectordefs = type -> getConnectors();

	String linkedRegion = linkRegion -> getRegionId();
	for( int k = 0; k < connectordefs.count(); k++ ) {
		TargetRegionConnectorDef *connectordef = ( TargetRegionConnectorDef * )connectordefs.get( k );
		if( linkedRegion.equals( connectordef -> getRegion() ) )
			connectors.add( connectordef -> getId() , linkedRegion );
	}
}

String WikiAreaPages::createDotFile_getRegionLabel( MindRegionDef *region ) {
	String subtype;
	if( region -> isTargetSensor() )
		subtype = "sensor";
	else if( region -> isTargetEffector() )
		subtype = "effector";
	else
		subtype = region -> getTypeName() + "/" + region -> getServiceName();

	String label = "<b>" + region -> getId() + "</b><br/>" + subtype;
	return( label );
}

void WikiAreaPages::createDotFile( MindArea *area , MindLocalCircuitDef& circuit , MapStringToClass<MindLocalCircuitConnectionDef>& internals , MapStringToClass<MindLocalCircuitConnectionDef>& inputs , MapStringToClass<MindLocalCircuitConnectionDef>& outputs ) {
	// create dot file
	String fileName = wm -> getCircuitDotPath( circuit );
	StringList text;

	// header
	text.add( "digraph \"" + area -> getAreaId() + "\" {" );
	text.add( "\tcompound=true;" );
	String defaultDotSetup = wm -> getDefaultDotSetup();
	text.add( wm -> setSpecialCharacters( defaultDotSetup ) );
	text.add( "" );

	// list nodes
	text.add( "\tsubgraph cluster_" + area -> getAreaId() + " {" );
	text.add( "\tlabel=<<b>" + area -> getMindAreaDef() -> getAreaName() + "</b>>;" );

	MapStringToClass<MindRegionDef>& regions = circuit.getRegions();
	for( int k = 0; k < regions.count(); k++ ) {
		MindRegionDef *region = regions.getClassByIndex( k );

		String dotdef = wm -> hmindxml.getDotDef( region -> getId() );
		String nodeline = "\t\"" + region -> getId() + "\"";
		if( !dotdef.isEmpty() ) {
			String s = wm -> setSpecialCharacters( dotdef );
			s += ", label=<" + createDotFile_getRegionLabel( region ) + ">";
			nodeline += " [" + s + "]";
		}
		nodeline += ";";

		text.add( nodeline );
	}
	text.add( "\t}" );

	// list connections
	text.add( "" );
	for( int k = 0; k < internals.count(); k++ ) {
		MindLocalCircuitConnectionDef *c = internals.getClassByIndex( k );
		MindConnectionLinkTypeDef *linkDef = c -> getPrimaryLinkType();
		String props = wm -> getLinkProps( linkDef );

		String linkline = "\t\"" + c -> getSrcRegion() + "\" -> \"" + c -> getDstRegion() + "\"" + props + ";";
		text.add( linkline );
	}

	// add subgraph
	String linkItem;
	createDotFile_subgraph( area , circuit , true , inputs , text , linkItem );
	createDotFile_subgraph( area , circuit , false , outputs , text , linkItem );

	// footer
	text.add( "}" );

	// out to file
	wm -> createFileContent( fileName , text );
}

String WikiAreaPages::getRegionColor( String regionId ) {
	const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( regionId );
	String ca;
	for( const XmlHMindElementInfo *xi = &info; xi != NULL; xi = xi -> getParent() ) {
		if( !xi -> dotdef.isEmpty() ) {
			ca = xi -> dotdef;
			break;
		}
	}

	int index = ca.find( "color=" );
	if( index < 0 )
		return( "springgreen" );

	int index2 = ca.find( index , "," );
	if( index2 < 0 )
		return( ca.getMid( index + 6 ) );

	return( ca.getMid( index + 6 , index2 - index ) );
}

void WikiAreaPages::createDotFile_subgraph( MindArea *area , MindLocalCircuitDef& circuit , bool p_inputs , MapStringToClass<MindLocalCircuitConnectionDef>& connections , StringList& text , String& linkItem ) {
	MindService *ms = MindService::getService();
	String postfix = ( p_inputs )? "IN" : "OUT";
	String postfixString = ( p_inputs )? "Inputs" : "Outputs";

	// inter-area links
	text.add( "" );
	if( p_inputs ) {
		text.add( "\tsubgraph cluster_ExtIn {" );
		text.add( "\tlabel=<<b>Inputs</b>>;" );
		text.add( "\t/* external inbound links */" );
	}
	else {
		text.add( "\tsubgraph cluster_ExtOut {" );
		text.add( "\tlabel=<<b>Outputs</b>>;" );
		text.add( "\t/* external outbound links */" );
	}

	MapStringToClass<MindRegion> areaTypes;
	MapStringToString areas;
	MapStringToClass<MapStringToClass<MindRegion>> areaTypeRegionMap;
	MapStringToClass<ClassList<MindLocalCircuitConnectionDef>> areaTypeConnectivityMap;
	for( int k = 0; k < connections.count(); k++ ) {
		MindLocalCircuitConnectionDef *c = connections.getClassByIndex( k );

		String regionId = ( p_inputs )? c -> getSrcRegion() : c -> getDstRegion();
		String regionLocalId = ( p_inputs )? c -> getDstRegion() : c -> getSrcRegion();
		MindRegion *region = ms -> getMindRegion( regionId );
		MindRegion *regionLocal = ms -> getMindRegion( regionLocalId );
		String areaId = region -> getArea() -> getAreaId();
		String areaType = region -> getArea() -> getMindAreaDef() -> getAreaType();

		String key = areaType;
		MapStringToClass<MindRegion> *typeRegions = areaTypeRegionMap.get( key );
		ClassList<MindLocalCircuitConnectionDef> *typeConnectivity = areaTypeConnectivityMap.get( key );
		if( typeRegions == NULL ) {
			typeRegions = new MapStringToClass<MindRegion>;
			typeConnectivity = new ClassList<MindLocalCircuitConnectionDef>;
			areaTypeRegionMap.add( key , typeRegions );
			areaTypeConnectivityMap.add( key , typeConnectivity );
		}

		if( typeRegions -> get( regionId ) == NULL )
			typeRegions -> add( regionId , region );

		areas.addnew( areaId , areaType );
		areaTypes.addnew( areaType , regionLocal );
		typeConnectivity -> add( c );
	}

	// add named lines
	String s;
	String localArea = area -> getAreaId();

	// header
	text.add( "" );

	for( int k = 0; k < areaTypes.count(); k++ ) {
		String areaType = areaTypes.getKeyByIndex( k );
		text.add( "\tsubgraph cluster_" + areaType + "_" + postfix + " {" );
		text.add( "\tlabel=\"" + areaType + " " + postfixString + "\";" );
		text.add( "\t\"" + areaType + "." + postfix + "\" [ shape=box, style=dotted , label = <" );
		text.add( "\t\t<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"4\" CELLPADDING=\"2\"><TR>" );

		// regions
		MapStringToClass<MindRegion> *typeRegions = areaTypeRegionMap.get( areaType );
		for( int a = 0; a < typeRegions -> count(); a++ ) {
			String regionId = typeRegions -> getKeyByIndex( a );
			MindRegion *region = typeRegions -> getClassByIndex( a );
			String color = getRegionColor( regionId );
			String label = createDotFile_getRegionLabel( region -> getRegionInfo() );
			text.add( "\t\t<TD PORT=\"" + regionId + "\" BGCOLOR=\"" + color + "\">" + label + "</TD>" );
		}

		text.add( "\t\t</TR></TABLE>> ];" );
		text.add( "\t}" );
		text.add( "" );

		// links
		ClassList<MindLocalCircuitConnectionDef> *typeConnectivity = areaTypeConnectivityMap.get( areaType );
		for( int a = 0; a < typeConnectivity -> count(); a++ ) {
			MindLocalCircuitConnectionDef *c = typeConnectivity -> get( a );
			MindConnectionLinkTypeDef *linkDef = c -> getPrimaryLinkType();
			String props = wm -> getLinkProps( linkDef );

			String srcId;
			String dstId;
			if( p_inputs ) {
				srcId = "\"" + areaType + "." + postfix + "\":\"" + c -> getSrcRegion() + "\"";
				dstId = "\"" + c -> getDstRegion() + "\"";
			}
			else {
				srcId = "\"" + c -> getSrcRegion() + "\"";
				dstId = "\"" + areaType + "." + postfix + "\":\"" + c -> getDstRegion() + "\"";
			}

			text.add( "\t" + srcId + " -> " + dstId + props + ";" );
		}

		text.add( "" );
	}

	text.add( "\t}" );
	areaTypeRegionMap.destroy();
	areaTypeConnectivityMap.destroy();
}

