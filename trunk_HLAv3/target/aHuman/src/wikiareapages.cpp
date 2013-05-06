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
	bool createAreaPages = wm -> wiki.getBooleanProperty( "createAreaPages" , true );
	if( createAreaPages == false ) {
		logger.logInfo( "skip creating area pages" );
		return;
	}

	// get wiki file
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String selectedArea = wm -> wiki.getProperty( "selectedArea" , "" );

	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();

	// by area
	bool createRegionPages = wm -> wiki.getBooleanProperty( "createRegionPages" , true );
	ClassList<MindAreaDef>& areaList = mm -> getMindAreas();
	for( int k = 0; k < areaList.count(); k++ ) {
		MindAreaDef *areaDef = areaList.get( k );

		if( !selectedArea.isEmpty() ) {
			if( !selectedArea.equals( areaDef -> getAreaId() ) )
				continue;
		}

		createAreaPages_createRegionTableSection( wikiDir , areaDef );
		createAreaPages_createConnectivityTableSection( wikiDir , areaDef );
		createAreaPages_createCircuitsAndReferencesTableSection( wikiDir , areaDef );

		if( createRegionPages )
			createAreaPages_createRegionPages( wikiDir , areaDef );
	}
}

void WikiAreaPages::createAreaPages_createRegionTableSection( String wikiDir , MindAreaDef *areaDef ) {
	StringList lines;

	// heading
	String wikiPage = wm -> getAreaPage( areaDef -> getAreaId() );
	String s = createAreaPages_getRegionTableRow( NULL );
	lines.add( s );

	// regions
	ClassList<MindRegionDef>& regionList = areaDef -> getRegions();
	MapStringToClass<MindRegionDef> regionMap;
	for( int k = 0; k < regionList.count(); k++ ) {
		MindRegionDef *regionDef = regionList.get( k );
		regionMap.add( regionDef -> getName() , regionDef );
	}

	for( int k = 0; k < regionMap.count(); k++ ) {
		MindRegionDef *regionDef = regionMap.getClassByIndex( k );
		s = createAreaPages_getRegionTableRow( regionDef );
		lines.add( s );
	}

	String sectionName = "Components";
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

String WikiAreaPages::createAreaPages_getRegionTableRow( MindRegionDef *regionDef ) {
	String value;

	// heading
	if( regionDef == NULL ) {
		value = "|| *Component ID* || *Component Name* || *Type* || *Function* || *Comments* ||";
		return( value );
	}

	// region row
	String regionId = regionDef -> getName();
	const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( regionId );
	
	value = "|| " + wm -> getRegionReference( regionId ) + " || " + 
		createAreaPages_getTableCellAttribute( info , "name" , info.name , true , 0 ) + " || " + 
		createAreaPages_getTableCellAttribute( info , "type" , info.batype , true , 0 ) + " || " + 
		createAreaPages_getTableCellAttribute( info , "function" , info.function , true , 80 ) + " || " + 
		createAreaPages_getTableCellAttribute( info , "notes" , info.notes , false , 50 ) + " ||";

	return( value );
}

String WikiAreaPages::createAreaPages_getTableCellAttribute( const XmlHMindElementInfo& info , String attribute , String value , bool required , int columnWidth ) {
	ASSERTMSG( ( required == false ) || ( value.isEmpty() == false ) , "attribute=" + attribute + " is empty for region=" + info.id );

	if( columnWidth == 0 )
		return( value );

	if( value.length() <= columnWidth )
		return( value );

	// format to column width
	StringList list;
	value.split( list , " " );
	value.clear();

	String valueline;
	for( int k = 0; k < list.count(); k++ ) {
		String item = list.get( k );
		if( valueline.length() + item.length() <= columnWidth || valueline.isEmpty() ) {
			if( !valueline.isEmpty() )
				valueline += " ";
			valueline += item;
			continue;
		}

		if( !value.isEmpty() )
			value += "<BR>";
		value += valueline;
		valueline = item;
	}

	if( !value.isEmpty() )
		value += "<BR>";
	value += valueline;

	return( value );
}

void WikiAreaPages::createAreaPages_createConnectivityTableSection( String wikiDir , MindAreaDef *areaDef ) {
	StringList lines;
	MapStringToClass<MindCircuitConnectionDef> connections;

	// internal connections
	createAreaPages_getInternalConnections( areaDef , connections );
	createAreaPages_getInternalConnectionTableLine( areaDef , NULL , lines );
	for( int k = 0; k < connections.count(); k++ ) {
		MindCircuitConnectionDef *c = connections.getClassByIndex( k );
		createAreaPages_getInternalConnectionTableLine( areaDef , c , lines );
	}

	// external connections - in
	lines.add( "" );
	MapStringToClass<MindCircuitConnectionDef> connectionsInputs;
	createAreaPages_getExternalConnections( areaDef , connectionsInputs , true );
	lines.add( "*External Inbound Region Connections:*" );
	if( connectionsInputs.count() == 0 ) {
		lines.add( "  * no connections" );
	}
	else {
		createAreaPages_getExternalConnectionTableLine( areaDef , NULL , lines , true );
		for( int k = 0; k < connectionsInputs.count(); k++ ) {
			MindCircuitConnectionDef *c = connectionsInputs.getClassByIndex( k );
			createAreaPages_getExternalConnectionTableLine( areaDef , c , lines , true );
		}
	}

	// external connections - out
	lines.add( "" );
	MapStringToClass<MindCircuitConnectionDef> connectionsOutputs;
	createAreaPages_getExternalConnections( areaDef , connectionsOutputs , false );
	lines.add( "*External Outbound Region Connections:*" );
	if( connectionsOutputs.count() == 0 ) {
		lines.add( "  * no connections" );
	}
	else {
		createAreaPages_getExternalConnectionTableLine( areaDef , NULL , lines , false );
		for( int k = 0; k < connectionsOutputs.count(); k++ ) {
			MindCircuitConnectionDef *c = connectionsOutputs.getClassByIndex( k );
			createAreaPages_getExternalConnectionTableLine( areaDef , c , lines , false );
		}
	}

	String sectionName = "Connectivity";
	String wikiPage = wm -> getAreaPage( areaDef -> getAreaId() );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );

	// create dot file
	createDotFile( areaDef , connections , connectionsInputs , connectionsOutputs );
}

void WikiAreaPages::createDotFile( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& internals , MapStringToClass<MindCircuitConnectionDef>& inputs , MapStringToClass<MindCircuitConnectionDef>& outputs ) {
	// create dot file
	String dotDir = wm -> wiki.getProperty( "dotPath" );
	String fileName = dotDir + "/" + areaDef -> getAreaId() + ".dot";
	StringList text;

	// header
	text.add( "digraph \"" + areaDef -> getAreaId() + "\" {" );
	text.add( "\tconcentrate=true;" );
	text.add( "\tcompound=true;" );
	String defaultDotSetup = wm -> wiki.getProperty( "defaultDotSetup" );
	text.add( wm -> setSpecialCharacters( defaultDotSetup ) );
	text.add( "" );

	// list nodes
	text.add( "\tsubgraph cluster_" + areaDef -> getAreaId() + " {" );
	text.add( "\tlabel=<<b>" + areaDef -> getAreaName() + "</b>>;" );
	ClassList<MindRegionDef>& regions = areaDef -> getRegions();
	for( int k = 0; k < regions.count(); k++ ) {
		MindRegionDef *regionDef = regions.get( k );

		String dotdef = wm -> hmindxml.getDotDef( regionDef -> getName() );
		String nodeline = "\t\"" + regionDef -> getName() + "\"";
		if( !dotdef.isEmpty() ) {
			String s = wm -> setSpecialCharacters( dotdef );
			s += ", label=<" + createDotFile_getRegionLabel( regionDef , inputs , outputs ) + ">";
			nodeline += " [" + s + "]";
		}
		nodeline += ";";

		text.add( nodeline );
	}
	text.add( "\t}" );

	// list connections
	text.add( "" );
	for( int k = 0; k < internals.count(); k++ ) {
		MindCircuitConnectionDef *c = internals.getClassByIndex( k );
		String linkline = "\t\"" + c -> getSrcRegion() + "\" -> \"" + c -> getDstRegion() + "\";";
		text.add( linkline );
	}

	// add subgraph
	String linkItem;
	createDotFile_subgraph( areaDef , true , inputs , text , linkItem );
	createDotFile_subgraph( areaDef , false , outputs , text , linkItem );

	// footer
	text.add( "}" );

	// out to file
	wm -> createFileContent( fileName , text );
}

String WikiAreaPages::createDotFile_getRegionLabel( MindRegionDef *region , MapStringToClass<MindCircuitConnectionDef>& inputs , MapStringToClass<MindCircuitConnectionDef>& outputs ) {
	MindService *ms = MindService::getService();
	String label = "<b>" + region -> getName() + "</b>";

	MapStringToClass<MindCircuitConnectionDef> inputAreas;
	for( int k = 0; k < inputs.count(); k++ ) {
		MindCircuitConnectionDef *c = inputs.getClassByIndex( k );
		if( !region -> getName().equals( c -> getDstRegion() ) )
			continue;

		String regionId = c -> getSrcRegion();
		MindRegion *regionExt = ms -> getMindRegion( regionId );
		inputAreas.addnew( regionExt -> getArea() -> getId() , c );
	}

	String in;
	for( int k = 0; k < inputAreas.count(); k++ ) {
		String area = inputAreas.getKeyByIndex( k );
		if( !in.isEmpty() )
			in += ",";
		in += area;
	}

	MapStringToClass<MindCircuitConnectionDef> outputAreas;
	for( int k = 0; k < outputs.count(); k++ ) {
		MindCircuitConnectionDef *c = outputs.getClassByIndex( k );
		if( !region -> getName().equals( c -> getSrcRegion() ) )
			continue;

		String regionId = c -> getDstRegion();
		MindRegion *regionExt = ms -> getMindRegion( regionId );
		outputAreas.addnew( regionExt -> getArea() -> getId() , c );
	}

	String out;
	for( int k = 0; k < outputAreas.count(); k++ ) {
		String area = outputAreas.getKeyByIndex( k );
		if( !out.isEmpty() )
			out += ",";
		out += area;
	}

	if( !in.isEmpty() )
		label += "<br/>IN: " + in;
	if( !out.isEmpty() )
		label += "<br/>OUT: " + out;

	return( label );
}

void WikiAreaPages::createDotFile_subgraph( MindAreaDef *areaDef , bool p_inputs , MapStringToClass<MindCircuitConnectionDef>& connections , StringList& text , String& linkItem ) {
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

	MapStringToString areaTypes;
	MapStringToString areas;
	MapStringToClass<MapStringToPtr> areaTypeRegionMap;
	for( int k = 0; k < connections.count(); k++ ) {
		MindCircuitConnectionDef *c = connections.getClassByIndex( k );
		String regionId = ( p_inputs )? c -> getSrcRegion() : c -> getDstRegion();
		String regionLocalId = ( p_inputs )? c -> getDstRegion() : c -> getSrcRegion();
		MindRegion *region = ms -> getMindRegion( regionId );
		String area = region -> getArea() -> getId();
		String areaType = region -> getArea() -> getMindAreaDef() -> getAreaType();

		String key = areaType + ":" + regionLocalId;
		MapStringToPtr *lineAreas = areaTypeRegionMap.get( key );
		if( lineAreas == NULL ) {
			lineAreas = new MapStringToPtr;
			areaTypeRegionMap.add( key , lineAreas );
		}

		if( lineAreas -> get( area ) == NULL )
			lineAreas -> add( area , c );

		areas.addnew( area , areaType );
		areaTypes.addnew( areaType , regionLocalId );
	}

	// add named lines
	String s;
	String localArea = areaDef -> getAreaId();
	for( int k = 1; k < areaTypes.count(); k++ ) {
		String areaType = areaTypes.getKeyByIndex( k );

		if( k == 1 )
			s = String( "\"" ) + areaTypes.getKeyByIndex( 0 ) + "." + postfix + "\"";
		s += String( " -> " ) + "\"" + areaType + "." + postfix + "\"";
	}

	if( !s.isEmpty() ) {
		s += " [ style=invis ];";
		text.add( "\t" + s );
	}

	// header
	text.add( "" );

	for( int k = 0; k < areaTypes.count(); k++ ) {
		String areaType = areaTypes.getKeyByIndex( k );
		text.add( "\tsubgraph cluster_" + areaType + "_" + postfix + " {" );
		text.add( "\tlabel=\"" + areaType + " " + postfixString + "\";" );
		text.add( "\t\"" + areaType + "." + postfix + "\" [ shape=box, style=dotted , label = <" );
		text.add( "\t\t<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\"><TR>" );

		for( int a = 0; a < areas.count(); a++ ) {
			if( !areaType.equals( areas.getClassByIndex( a ) ) )
				continue;

			String area = areas.getKeyByIndex( a );
			text.add( "\t\t<TD PORT=\"" + area + "\" BGCOLOR=\"springgreen\">" + area + "</TD>" );
		}

		text.add( "\t\t</TR></TABLE>> ];" );
		text.add( "\t}" );
	}

	text.add( "\t}" );
	areaTypeRegionMap.destroy();

	// input-output link
	if( areaTypes.count() > 0 ) {
		if( p_inputs == true )
			linkItem = areaTypes.getKeyByIndex( areaTypes.count() - 1 ) + String( "." ) + postfix;
		else 
		if( !linkItem.isEmpty() ) {
			String linkTo = areaTypes.getKeyByIndex( 0 ) + String( "." ) + postfix;
			text.add( "\t\"" + linkItem + "\" -> \"" + linkTo + "\" [ style=invis ];" );
		}
	}
}

void WikiAreaPages::createAreaPages_getInternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections ) {
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();
	ClassList<MindCircuitDef>& circuits = mm -> getMindCircuits();

	MindArea *area = ms -> getMindArea( areaDef -> getAreaId() );
	for( int k1 = 0; k1 < circuits.count(); k1++ ) {
		MindCircuitDef *circuit = circuits.get( k1 );
		ClassList<MindCircuitConnectionDef>& links = circuit -> getConnections();
		for( int k2 = 0; k2 < links.count(); k2++ ) {
			MindCircuitConnectionDef *c = links.get( k2 );
			MindArea *srcArea = ms -> getMindRegion( c -> getSrcRegion() ) -> getArea();
			MindArea *dstArea = ms -> getMindRegion( c -> getDstRegion() ) -> getArea();

			if( srcArea == area && dstArea == area ) {
				String key = c -> getSrcRegion() + "#" + c -> getDstRegion();
				if( connections.get( key ) == NULL )
					connections.add( key , c );
			}
		}
	}
}

void WikiAreaPages::createAreaPages_getExternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections , bool isin ) {
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();
	ClassList<MindCircuitDef>& circuits = mm -> getMindCircuits();

	MindArea *area = ms -> getMindArea( areaDef -> getAreaId() );
	for( int k1 = 0; k1 < circuits.count(); k1++ ) {
		MindCircuitDef *circuit = circuits.get( k1 );
		ClassList<MindCircuitConnectionDef>& links = circuit -> getConnections();
		for( int k2 = 0; k2 < links.count(); k2++ ) {
			MindCircuitConnectionDef *c = links.get( k2 );
			MindArea *srcArea = ms -> getMindRegion( c -> getSrcRegion() ) -> getArea();
			MindArea *dstArea = ms -> getMindRegion( c -> getDstRegion() ) -> getArea();

			if( srcArea != dstArea && ( srcArea == area || dstArea == area ) ) {
				String key;
				if( area == srcArea ) {
					if( isin == false ) {
						key = dstArea -> getId() + "#" + c -> getSrcRegion() + "#" + c -> getDstRegion() + "#1";
						if( connections.get( key ) == NULL )
							connections.add( key , c );
					}
				}
				else {
					if( isin == true ) {
						key = srcArea -> getId() + "#" + c -> getDstRegion() + "#" + c -> getSrcRegion() + "#2";
						if( connections.get( key ) == NULL )
							connections.add( key , c );
					}
				}
			}
		}
	}
}

void WikiAreaPages::createAreaPages_getInternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines ) {
	String line;
	if( link == NULL ) {
		// add heading
		line = "*Internal Region Connections:*";
		lines.add( line );
		lines.add( "" );
		String dotImageWikiPath = wm -> wiki.getProperty( "imageWikiPath" );
		line = dotImageWikiPath + "/" + areaDef -> getAreaId() + ".dot.jpg";
		lines.add( line );
		lines.add( "" );
		line = "|| *Source Region* || *Target Region* || *Type* || *Reference* ||";
		lines.add( line );
		return;
	}

	// table row
	String reference = wm -> findReference( link );
	line = "|| " + wm -> getRegionReference( link -> getSrcRegion() ) + " || " + wm -> getRegionReference( link -> getDstRegion() ) + " || " + 
		link -> getTypeName() + " || " + reference + " ||" ;
	lines.add( line );
}

void WikiAreaPages::createAreaPages_getExternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines , bool isin ) {
	String line;
	if( link == NULL ) {
		// add heading
		lines.add( "" );

		if( isin )
			line = "|| *Source Area* || *Local Region* || *Source Region* || *Source Name* || *Type* || *Reference* ||";
		else
			line = "|| *Target Area* || *Local Region* || *Target Region* || *Target Name* || *Type* || *Reference* ||";
		lines.add( line );
		return;
	}

	// table row
	MindService *ms = MindService::getService();
	MindRegion *srcRegion = ms -> getMindRegion( link -> getSrcRegion() );
	MindRegion *dstRegion = ms -> getMindRegion( link -> getDstRegion() );
	String area = areaDef -> getAreaId();

	String reference = wm -> findReference( link );
	if( area.equals( srcRegion -> getArea() -> getId() ) ) {
		const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( link -> getDstRegion() );
		line = "|| " + wm -> getAreaReference( dstRegion -> getArea() -> getId() ) + " || " + 
			wm -> getRegionReference( link -> getSrcRegion() ) + " || " + wm -> getRegionReference( link -> getDstRegion() ) + " || " + 
			info.name + " || " + link -> getTypeName() + " || " + reference + " ||";
	}
	else {
		const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( link -> getSrcRegion() );
		line = "|| " + wm -> getAreaReference( srcRegion -> getArea() -> getId() ) + " || " + 
			wm -> getRegionReference( link -> getDstRegion() ) + " || " + wm -> getRegionReference( link -> getSrcRegion() ) + " || " + 
			info.name + " || " + link -> getTypeName() + " || " + reference + " ||";
	}
	lines.add( line );
}

void WikiAreaPages::createAreaPages_createCircuitsAndReferencesTableSection( String wikiDir , MindAreaDef *areaDef ) {
	// collect circuits which reference any of area regions
	MindService *ms = MindService::getService();

	StringList circuits;
	wm -> circuitsxml.getCircuitList( circuits );

	MindArea *area = ms -> getMindArea( areaDef -> getAreaId() );
	MapStringToString circuitKeys;
	for( int k = 0; k < circuits.count(); k++ ) {
		String circuitId = circuits.get( k );
		XmlCircuitInfo info;
		wm -> circuitsxml.getCircuitInfo( circuitId , info );

		String key = createAreaPages_getCircuitKey( areaDef , info );
		if( key.isEmpty() )
			continue;

		circuitKeys.add( key , circuitId );
	}

	// add circuits section - sorted by relevance
	StringList lines;
	for( int k = circuitKeys.count() - 1; k >= 0; k-- ) {
		String circuitId = circuitKeys.getClassByIndex( k );
		XmlCircuitInfo info;
		wm -> circuitsxml.getCircuitInfo( circuitId , info );
		createAreaPages_getCircuitLines( info , lines );
	}

	String sectionName = "Thirdparty Circuits";
	String wikiPage = wm -> getAreaPage( areaDef -> getAreaId() );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
	lines.clear();

	// add unique and sorted references - sorted by relevance
	MapStringToClass<MindArea> refs;
	for( int k = circuitKeys.count() - 1; k >= 0; k-- ) {
		String circuitId = circuitKeys.getClassByIndex( k );
		XmlCircuitInfo info;
		wm -> circuitsxml.getCircuitInfo( circuitId , info );

		if( !info.reference.equals( "UNKNOWN" ) )
			if( refs.get( info.reference ) == NULL ) {
				refs.add( info.reference , area );
				lines.add( String( "  * " ) + info.reference );
			}
	}

	sectionName = "References";
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

String WikiAreaPages::createAreaPages_getCircuitKey( MindAreaDef *areaDef , XmlCircuitInfo& info ) {
	// get circuit regions
	StringList comps;
	wm -> circuitsxml.getCircuitComponents( info , comps );

	// check circuit mentions area regions
	StringList compUsed;
	for( int k = 0; k < comps.count(); k++ ) {
		String comp = comps.get( k );
		String region = wm -> hmindxml.getMappedRegion( comp );
		if( areaDef -> findRegion( region ) != NULL )
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
	String sizeInfo;
	if( info.imageHeight > 0 )
		sizeInfo += String( "height=" ) + info.imageHeight;
	if( info.imageWidth > 0 )
		sizeInfo += String( "width=" ) + info.imageWidth;

	lines.add( "<img src=\"" + info.image + "\" alt=\"unavailable\"" + sizeInfo + ">" );
	lines.add( "" );
}

void WikiAreaPages::createAreaPages_createRegionPages( String wikiDir , MindAreaDef *areaDef ) {
	ClassList<MindRegionDef>& regions = areaDef -> getRegions();
	for( int k = 0; k < regions.count(); k++ ) {
		WikiRegionPage maker( wm , wikiDir , regions.get( k ) );
		maker.execute();
	}
}
