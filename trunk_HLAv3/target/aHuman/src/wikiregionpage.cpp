#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiRegionPage::WikiRegionPage( WikiMaker *p_wm , String p_wikiDir , MindRegionDef *p_region ) {
	attachLogger();
	wm = p_wm;
	wikiDir = p_wikiDir;
	region = p_region;
	wm -> hmindxml.getElementInfo( region -> getName() , info );
}

WikiRegionPage::~WikiRegionPage() {
}

void WikiRegionPage::execute() {
	StringList sections;
	sections.add( "= Components =" );
	sections.add( "= Connectivity =" );
	sections.add( "= Thirdparty Circuits =" );
	sections.add( "= References =" );
	String wikiPage = wm -> getRegionPage( info.id );
	wm -> ensureFileExists( wikiDir , wikiPage , sections );

	createHeading();
	createChildTableSection();
	createConnectivitySection();
	createThirdpartyAndReferencesSection();
}

void WikiRegionPage::createHeading() {
	StringList lines;
	lines.add( "#summary " + info.name );
	String areaWikiPage = wm -> getAreaPage( region -> getArea() -> getAreaId() );
	lines.add( "@@[Home] -> [BiologicalLifeResearch] -> [" + areaWikiPage + "] -> [" + wm -> getRegionPage( info.id ) + "]" );
	lines.add( "----" );
	lines.add( "" );
	lines.add( "This page covers biological details of component " + info.name + "." );
	lines.add( "Region is part of aHuman target integrated biological model." );
	lines.add( "" );

	// add path
	StringList listItems;
	Xml node = wm -> hmindxml.getNodeXml( info.id );
	for( Xml nodePath = node; nodePath.exists(); nodePath = nodePath.getParentNode() ) {
		if( nodePath.getName().equals( "division" ) ) {
			String name = nodePath.getAttribute( "name" );
			listItems.add( name );
			break;
		}
		else {
			String id = nodePath.getAttribute( "id" , "" );
			String name = nodePath.getAttribute( "name" , "" );
			String value = name;
			if( !id.isEmpty() ) {
				if( value.isEmpty() )
					value = id;
				else
					value += " (" + id + ")";
			}
			listItems.add( value );
		}
	}
	String s;
	for( int k = listItems.count() - 1; k >= 0; k-- ) {
		s += listItems.get( k );
		if( k > 0 )
			s += " -> ";
	}
	lines.add( "  * *Top-down path to region*: " + s + " (see [OverallMindMaps Mind Maps])" );

	// mind area
	MindAreaDef *area = region -> getArea();
	lines.add( "  * *Brain area*: [BrainArea" + area -> getAreaId() + " " + area -> getAreaName() + "]" );

	// function
	if( !info.brodmannid.isEmpty() )
		lines.add( "  * *Brodmann ID*: " + info.brodmannid );
	lines.add( "  * *Function*: " + info.function );
	if( !info.comment.isEmpty() )
		lines.add( "  * *Notes to structure*: " + info.comment );
	if( !info.notes.isEmpty() )
		lines.add( "  * *Notes to function*: " + info.notes );

	String wikiPage = wm -> getRegionPage( info.id );
	wm -> updateFileHeading( wikiDir , wikiPage , lines );
}

void WikiRegionPage::createChildTableSection() {
	Xml node = wm -> hmindxml.getNodeXml( info.id );
	if( !node.exists() ) {
		logger.logInfo( "unable to find region=" + info.id );
		return;
	}

	// components section
	StringList lines;

	// lines hierarchy
	lines.add( "" );
	if( node.getChildNode( "element" ).exists() ) {
		lines.add( "*Component items*:" );
		createChildTableSection_addChilds( node , "  * " , lines );
	}
	else
		lines.add( "  * no child items defined" );

	String wikiPage = wm -> getRegionPage( info.id );
	String section = "Components";
	wm -> updateFileSection( wikiDir , wikiPage , section , lines );
}

void WikiRegionPage::createChildTableSection_addChilds( Xml node , String prefix , StringList& lines ) {
	String value;
	StringList refList;
	for( Xml nodeChild = node.getFirstChild( "element" ); nodeChild.exists(); nodeChild = nodeChild.getNextChild( "element" ) ) {
		String refs = nodeChild.getAttribute( "refs" , "" );

		if( refs.isEmpty() ) {
			String id = nodeChild.getAttribute( "id" , "" );
			String name = nodeChild.getAttribute( "name" , "" );
			value = name;
			if( !id.isEmpty() ) {
				if( value.isEmpty() )
					value = id;
				else
					value += " (" + id + ")";
			}
		}
		else {
			refs.split( refList , ";" );

			value.clear();
			for( int k = 0; k < refList.count(); k++ ) {
				String ref = refList.get( k );
				ref.trim();

				if( !value.isEmpty() )
					value += " = ";

				value += ref;
			}
			refList.clear();
		}

		lines.add( prefix + value );
		createChildTableSection_addChilds( nodeChild , " " + prefix , lines );
	}
}

void WikiRegionPage::createConnectivitySection() {
	StringList lines;
	MapStringToClass<MindCircuitConnectionDef> connections;
	MapStringToClass<MindRegionDef> regions;
	MapStringToClass<MindCircuitConnectionDef> connectionsTotal;

	// image
	lines.add( "" );
	String dotImageWikiPath = wm -> wiki.getProperty( "imageWikiPath" );
	String line = dotImageWikiPath + "/" + info.id + ".dot.jpg";
	lines.add( line );

	// external connections - in
	lines.add( "" );
	connections.clear();
	createConnectivitySection_getExternalConnections( connections , true );
	connectionsTotal.add( connections );
	lines.add( "*Inbound Region Connections:*" );
	if( connections.count() == 0 ) {
		lines.add( "  * no connections" );
	}
	else {
		createConnectivitySection_getExternalConnectionTableLine( NULL , lines , true );
		for( int k = 0; k < connections.count(); k++ ) {
			MindCircuitConnectionDef *c = connections.getClassByIndex( k );
			createConnectivitySection_getExternalConnectionTableLine( c , lines , true );
			regions.addnew( c -> getSrcRegion() , NULL );
		}
	}

	// external connections - out
	lines.add( "" );
	connections.clear();
	createConnectivitySection_getExternalConnections( connections , false );
	connectionsTotal.add( connections );
	lines.add( "*Outbound Region Connections:*" );
	if( connections.count() == 0 ) {
		lines.add( "  * no connections" );
	}
	else {
		createConnectivitySection_getExternalConnectionTableLine( NULL , lines , false );
		for( int k = 0; k < connections.count(); k++ ) {
			MindCircuitConnectionDef *c = connections.getClassByIndex( k );
			createConnectivitySection_getExternalConnectionTableLine( c , lines , false );
			regions.addnew( c -> getDstRegion() , NULL );
		}
	}

	String wikiPage = wm -> getRegionPage( info.id );
	String section = "Connectivity";
	wm -> updateFileSection( wikiDir , wikiPage , section , lines );

	// create dot file
	String dotDir = wm -> wiki.getProperty( "dotPath" );
	String fileName = dotDir + "/" + info.id + ".dot";
	StringList text;

	// header
	text.add( "digraph \"" + info.id.replace( "." , "_" ) + "\" {" );
	String defaultDotSetup = wm -> wiki.getProperty( "defaultDotSetup" );
	text.add( wm -> setSpecialCharacters( defaultDotSetup ) );
	text.add( "" );

	// list nodes
	XmlHMindElementInfo infoPair;
	for( int k = 0; k < regions.count(); k++ ) {
		String regionPaired = regions.getKeyByIndex( k );

		String dotdef = wm -> hmindxml.getDotDef( regionPaired );
		String nodeline = "\t\"" + regionPaired + "\"";
		if( !dotdef.isEmpty() ) {
			String s = wm -> setSpecialCharacters( dotdef );
			nodeline += " [" + s + "]";
		}
		nodeline += ";";

		text.add( nodeline );
	}

	// list connections
	text.add( "" );
	for( int k = 0; k < connectionsTotal.count(); k++ ) {
		MindCircuitConnectionDef *c = connectionsTotal.getClassByIndex( k );
		String linkline = "\t\"" + c -> getSrcRegion() + "\" -> \"" + c -> getDstRegion() + "\";";
		text.add( linkline );
	}

	// footer
	text.add( "}" );

	// out to file
	wm -> createFileContent( fileName , text );
}

void WikiRegionPage::createConnectivitySection_getExternalConnections( MapStringToClass<MindCircuitConnectionDef>& connections , bool isin ) {
	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();
	ClassList<MindCircuitDef>& circuits = mm -> getMindCircuits();

	String key;
	for( int k1 = 0; k1 < circuits.count(); k1++ ) {
		MindCircuitDef *circuit = circuits.get( k1 );
		ClassList<MindCircuitConnectionDef>& links = circuit -> getConnections();
		for( int k2 = 0; k2 < links.count(); k2++ ) {
			MindCircuitConnectionDef *c = links.get( k2 );
			if( isin == false && info.id.equals( c -> getSrcRegion() ) ) {
				MindArea *dstArea = ms -> getMindRegion( c -> getDstRegion() ) -> getArea();
				key = dstArea -> getId() + "#" + c -> getSrcRegion() + "#" + c -> getDstRegion() + "#1";
				if( connections.get( key ) == NULL )
					connections.add( key , c );
			}
			else 
			if( isin == true && info.id.equals( c -> getDstRegion() ) ) {
				MindArea *srcArea = ms -> getMindRegion( c -> getSrcRegion() ) -> getArea();
				key = srcArea -> getId() + "#" + c -> getDstRegion() + "#" + c -> getSrcRegion() + "#2";
				if( connections.get( key ) == NULL )
					connections.add( key , c );
			}
		}
	}
}

void WikiRegionPage::createConnectivitySection_getExternalConnectionTableLine( MindCircuitConnectionDef *link , StringList& lines , bool isin ) {
	String line;
	if( link == NULL ) {
		// add heading
		lines.add( "" );

		if( isin )
			line = "|| *Source Area* || *Source Region* || *Source Name* || *Type* || *Reference* ||";
		else
			line = "|| *Target Area* || *Target Region* || *Target Name* || *Type* || *Reference* ||";
		lines.add( line );
		return;
	}

	// table row
	MindService *ms = MindService::getService();
	MindRegion *srcRegion = ms -> getMindRegion( link -> getSrcRegion() );
	MindRegion *dstRegion = ms -> getMindRegion( link -> getDstRegion() );
	String area = region -> getArea() -> getAreaId();

	XmlHMindElementInfo info;
	String reference = wm -> findReference( link );
	if( isin == true ) {
		wm -> hmindxml.getElementInfo( link -> getSrcRegion() , info );
		line = "|| " + wm -> getAreaReference( srcRegion -> getArea() -> getId() ) + " || " + 
			wm -> getRegionReference( link -> getSrcRegion() ) + " || " + info.name + " || " + link -> getTypeName() + " || " + reference + " ||";
	}
	else {
		wm -> hmindxml.getElementInfo( link -> getDstRegion() , info );
		line = "|| " + wm -> getAreaReference( dstRegion -> getArea() -> getId() ) + " || " + 
			wm -> getRegionReference( link -> getDstRegion() ) + " || " + info.name + " || " + link -> getTypeName() + " || " + reference + " ||";
	}
	lines.add( line );
}

void WikiRegionPage::createThirdpartyAndReferencesSection() {
	// collect circuits which reference any of area regions
	MindService *ms = MindService::getService();

	StringList circuits;
	wm -> circuitsxml.getCircuitList( circuits );

	MindAreaDef *areaDef = region -> getArea();
	MindArea *area = ms -> getMindArea( areaDef -> getAreaId() );
	MapStringToString circuitKeys;
	for( int k = 0; k < circuits.count(); k++ ) {
		String circuitId = circuits.get( k );
		XmlCircuitInfo infoPaired;
		wm -> circuitsxml.getCircuitInfo( circuitId , infoPaired );

		String key = createThirdpartyAndReferencesSection_getCircuitKey( areaDef , infoPaired );
		if( key.isEmpty() )
			continue;

		circuitKeys.add( key , circuitId );
	}

	// add circuits section - sorted by relevance
	StringList lines;
	if( circuitKeys.count() > 0 ) {
		for( int k = circuitKeys.count() - 1; k >= 0; k-- ) {
			String circuitId = circuitKeys.getClassByIndex( k );
			XmlCircuitInfo infoPaired;
			wm -> circuitsxml.getCircuitInfo( circuitId , infoPaired );
			createThirdpartyAndReferencesSection_getCircuitLines( infoPaired , lines );
		}
	}
	else {
		lines.add( "  * no circuits defined" );
	}

	String sectionName = "Thirdparty Circuits";
	String wikiPage = wm -> getRegionPage( info.id );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
	lines.clear();

	// add unique and sorted references - sorted by relevance
	if( circuitKeys.count() > 0 ) {
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
	}
	else {
		lines.add( "  * no references defined" );
	}

	sectionName = "References";
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

String WikiRegionPage::createThirdpartyAndReferencesSection_getCircuitKey( MindAreaDef *areaDef , XmlCircuitInfo& cinfo ) {
	// get circuit regions
	StringList comps;
	wm -> circuitsxml.getCircuitComponents( cinfo , comps );

	// check circuit mentions area regions
	for( int k = 0; k < comps.count(); k++ ) {
		String comp = comps.get( k );
		if( comp.equals( info.id ) )
			return( cinfo.id );
	}

	return( "" );
}

void WikiRegionPage::createThirdpartyAndReferencesSection_getCircuitLines( XmlCircuitInfo& cinfo , StringList& lines ) {
	String ref;
	if( cinfo.reference.equals( "UNKNOWN" ) )
		ref = "(unknown reference)";
	else
		ref = "- see [" + cinfo.reference + " Reference]";

	lines.add( "  * [" + cinfo.image + " " + cinfo.name + "] " + ref );
	lines.add( "" );
	String sizeInfo;
	if( cinfo.imageHeight > 0 )
		sizeInfo += String( "height=" ) + cinfo.imageHeight;
	if( cinfo.imageWidth > 0 )
		sizeInfo += String( "width=" ) + cinfo.imageWidth;

	lines.add( "<img src=\"" + cinfo.image + "\" alt=\"unavailable\"" + sizeInfo + ">" );
	lines.add( "" );
}
