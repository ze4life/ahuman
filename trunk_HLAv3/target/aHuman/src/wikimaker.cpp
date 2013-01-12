#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiMaker::WikiMaker( Xml p_wiki ) {
	attachLogger();
	wiki = p_wiki;

}

WikiMaker::~WikiMaker() {
}

void WikiMaker::createPages() {
	logger.logInfo( "create mind model wiki pages..." );

	// create pages
	hmindxml.load();
	circuitsxml.load();

	updateHierarchyPage();
	createAreaPages();
	createComponentPages();
}

/*#########################################################################*/
/*#########################################################################*/
// heirarchy pages

void WikiMaker::updateHierarchyPage() {
	bool createPageHierarchy = wiki.getBooleanProperty( "createPageHierarchy" , true );
	if( createPageHierarchy == false ) {
		logger.logInfo( "skip creating hierarchy page" );
		return;
	}

	// get wiki file
	String wikiDir = wiki.getProperty( "wikiPath" );
	String wikiPage = wiki.getProperty( "wikiPageHierarchy" );

	// create hierarchy section
	StringList divisions;
	hmindxml.getDivisions( divisions );
	for( int k = 0; k < divisions.count(); k++ ) {
		String division = divisions.get( k );
		if( division.equals( "Neocortex" ) )
			updateHierarchyPage_walkNeocortex( division , wikiDir , wikiPage );
		else {
			StringList lines;
			updateHierarchyPage_walkTree( division , 0 , lines , NULL , NULL );
			updateFileSection( wikiDir , wikiPage , division , lines );
		}
	}
}

void WikiMaker::updateHierarchyPage_walkTree( String parentNode , int level , StringList& lines , MindArea *parentArea , MindRegion *parentRegion ) {
	StringList elements;
	hmindxml.getElements( parentNode , elements );

	for( int k = 0; k < elements.count(); k++ ) {
		String node = elements.get( k );

		// handle mapping
		MindArea *ownArea = NULL;
		MindRegion *ownRegion = NULL;

		if( parentArea == NULL )
			ownArea = updateHierarchyPage_getArea( node );
		if( parentRegion == NULL )
			ownRegion = updateHierarchyPage_getRegion( node );

		// add item string
		String itemString = updateHierarchyPage_getElementString( node , parentArea , parentRegion , ownArea , ownRegion );
		lines.add( String( " " ).replicate( 2 + level ) + "* " + itemString );

		// walk down
		if( ownArea == NULL )
			ownArea = parentArea;
		if( ownRegion == NULL )
			ownRegion = parentRegion;

		updateHierarchyPage_walkTree( node , level + 1 , lines , ownArea , ownRegion );
	}
}

MindArea *WikiMaker::updateHierarchyPage_getArea( String parentNode ) {
	MindService *ms = MindService::getService();

	XmlHMindElementInfo info;
	hmindxml.getElementInfo( parentNode , info );

	// check ignored
	if( info.ignore == true )
		return( NULL );

	// check direct
	if( info.mapped ) {
		MindRegion *region = ms -> getMindRegion( info.id );
		return( region -> getArea() );
	}

	// check all childs
	MindArea *area = NULL;
	StringList elements;
	hmindxml.getElements( parentNode , elements );

	for( int k = 0; k < elements.count(); k++ ) {
		String node = elements.get( k );

		// check ignored
		hmindxml.getElementInfo( node , info );
		if( info.ignore == true )
			continue;

		MindArea *one = updateHierarchyPage_getArea( node );
		if( area == NULL )
			area = one;
		else if( one != area )
			return( NULL );
	}

	return( area );
}

MindRegion *WikiMaker::updateHierarchyPage_getRegion( String parentNode ) {
	MindRegion *region = NULL;
	MindService *ms = MindService::getService();

	XmlHMindElementInfo info;
	hmindxml.getElementInfo( parentNode , info );

	// check ignored
	if( info.ignore == true )
		return( NULL );

	// check direct
	if( info.mapped ) {
		region = ms -> getMindRegion( info.id );
		return( region );
	}

	// check all childs
	StringList elements;
	hmindxml.getElements( parentNode , elements );

	for( int k = 0; k < elements.count(); k++ ) {
		String node = elements.get( k );

		// check ignored
		hmindxml.getElementInfo( node , info );
		if( info.ignore == true )
			continue;

		MindRegion *one = updateHierarchyPage_getRegion( node );
		if( region == NULL )
			region = one;
		else if( one != region )
			return( NULL );
	}

	return( region );
}

String WikiMaker::updateHierarchyPage_getElementString( String node , MindArea *parentArea , MindRegion *parentRegion , MindArea *ownArea , MindRegion *ownRegion ) {
	String value;

	XmlHMindElementInfo info;
	hmindxml.getElementInfo( node , info );

	// own name if any
	if( !info.name.isEmpty() ) {
		value += "*";
		value += info.name;

		if( !info.id.isEmpty() )
			value += " (" + info.id + ")";

		value += "*";
	}

	// ref section
	if( !info.refs.isEmpty() ) {
		StringList refList;
		info.refs.split( refList , ";" );
		for( int k = 0; k < refList.count(); k++ ) {
			String ref = refList.get( k );
			ref.trim();

			if( !value.isEmpty() )
				value += " = ";

			value += ref;
		}
	}

	// mapping section
	if( ownArea != NULL )
		value += " -> [BrainArea" + ownArea -> getId() + "]";

	// ignore section
	if( info.ignore == true ) {
		value += " (ignore";
		if( !info.comment.isEmpty() )
			value += ", " + info.comment;
		value += ")";
	}
	else if( !info.comment.isEmpty() )
		value += " (" + info.comment + ")";

	return( value );
}

void WikiMaker::updateHierarchyPage_walkNeocortex( String neocortexDivision , String wikiDir , String wikiPage ) {
	XmlHMindElementInfo info;
	StringList elements;
	hmindxml.getElements( neocortexDivision , elements );

	// group by major lobes
	for( int k = 0; k < elements.count(); k++ ) {
		String node = elements.get( k );
		hmindxml.getElementInfo( node , info );

		StringList lines;
		updateHierarchyPage_getNeocortexLobeLines( node , lines );
		updateFileSection( wikiDir , wikiPage , info.name , lines );
	}
}

void WikiMaker::updateHierarchyPage_getNeocortexLobeLines( String neocortexLobe , StringList& lines ) {
	String banum;
	banum.resize( 10 );

	// list by brodmann areas
	MapStringToString balines;
	for( int k = 1; k < 100; k++ ) {
		sprintf( banum.getBuffer() , "%2.2d" , k );

		String baline = updateHierarchyPage_getNeocortexBrodmannLine( neocortexLobe , banum );
		if( !baline.isEmpty() )
			balines.add( banum , baline );
	}

	// group the same if sequential
	String lastnumset;
	String lastline;
	for( int k = 1; k < 100; k++ ) {
		sprintf( banum.getBuffer() , "%2.2d" , k );
		String baline = balines.get( banum );

		if( baline.isEmpty() && k < 99 )
			continue;

		// first
		if( lastnumset.isEmpty() ) {
			if( baline.isEmpty() )
				continue;

			lastnumset = String( "BA " ) + k;
			lastline = baline;
			continue;
		}

		// next - check the same
		if( lastline.equals( baline ) ) {
			lastnumset += String( "," ) + k;
			continue;
		}

		// add line
		String value = "  * *" + lastnumset + "*: " + lastline;
		lines.add( value );

		// set next
		if( baline.isEmpty() ) {
			lastnumset.clear();
			lastline.clear();
		}
		else {
			lastnumset = String( "BA " ) + k;
			lastline = baline;
		}
	}
}

String WikiMaker::updateHierarchyPage_getNeocortexBrodmannLine( String neocortexDivision , String banum ) {
	// check all childs
	StringList items;
	updateHierarchyPage_walkNeocortexBrodmannLine( neocortexDivision , banum , items );

	// no items
	if( items.count() == 0 )
		return( "" );

	// make string
	String value;
	for( int k = 0; k < items.count(); k++ ) {
		if( !value.isEmpty() )
			value += ", ";
		value += items.get( k );
	}

	return( value );
}

void WikiMaker::updateHierarchyPage_walkNeocortexBrodmannLine( String node , String banum , StringList& items ) {
	XmlHMindElementInfo info;
	hmindxml.getElementInfo( node , info );

	if( info.brodmannid.isEmpty() ) {
		// check childs
		StringList elements;
		hmindxml.getElements( node , elements );

		// group by major lobes
		for( int k = 0; k < elements.count(); k++ ) {
			String nodeChild = elements.get( k );
			updateHierarchyPage_walkNeocortexBrodmannLine( nodeChild , banum , items );
		}
		return;
	}

	// check itself
	if( info.brodmannid.find( banum ) < 0 )
		return;

	// add string
	String value;
	if( info.ignore ) {
		value = "ignored";
		if( !info.comment.isEmpty() )
			value += ", " + info.comment;
	}
	else {
		MindService *ms = MindService::getService();
		MindRegion *region = ms -> getMindRegion( info.id );
		MindArea *area = region -> getArea();

		value = "[BrainArea" + area -> getId() + " " + info.name + " (" + info.id + ")]";
	}

	items.add( value );
}

/*#########################################################################*/
/*#########################################################################*/
// create area pages

void WikiMaker::createAreaPages() {
	bool createAreaPages = wiki.getBooleanProperty( "createAreaPages" , true );
	if( createAreaPages == false ) {
		logger.logInfo( "skip creating area pages" );
		return;
	}

	// get wiki file
	String wikiDir = wiki.getProperty( "wikiPath" );
	String selectedArea = wiki.getProperty( "selectedArea" , "" );

	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();

	// by area
	ClassList<MindAreaDef>& areaList = mm -> getMindAreas();
	for( int k = 0; k < areaList.count(); k++ ) {
		MindAreaDef *areaDef = areaList.get( k );

		String wikiPage = "BrainArea" + areaDef -> getAreaId();
		if( !selectedArea.isEmpty() ) {
			if( !selectedArea.equals( areaDef -> getAreaId() ) )
				continue;
		}

		createAreaPages_createRegionTableSection( wikiDir , wikiPage , areaDef );
		createAreaPages_createConnectivityTableSection( wikiDir , wikiPage , areaDef );
		createAreaPages_createCircuitsAndReferencesTableSection( wikiDir , wikiPage , areaDef );
	}
}

void WikiMaker::createAreaPages_createRegionTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef ) {
	StringList lines;

	// heading
	String s = createAreaPages_getRegionTableRow( NULL );
	lines.add( s );

	// regions
	ClassList<MindRegionDef>& regionList = areaDef -> getRegions();
	for( int k = 0; k < regionList.count(); k++ ) {
		MindRegionDef *regionDef = regionList.get( k );
		s = createAreaPages_getRegionTableRow( regionDef );
		lines.add( s );
	}

	String sectionName = "Components";
	updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

String WikiMaker::createAreaPages_getRegionTableRow( MindRegionDef *regionDef ) {
	String value;

	// heading
	if( regionDef == NULL ) {
		value = "|| *Component ID* || *Component Name* || *Type* || *Function* || *Comments* ||";
		return( value );
	}

	// region row
	String regionId = regionDef -> getName();
	XmlHMindElementInfo info;
	hmindxml.getElementInfo( regionId , info );
	
	value = "|| *" + regionId + "* || " + 
		createAreaPages_getTableCellAttribute( info , "name" , info.name , true , 0 ) + " || " + 
		createAreaPages_getTableCellAttribute( info , "type" , info.type , true , 0 ) + " || " + 
		createAreaPages_getTableCellAttribute( info , "function" , info.function , true , 80 ) + " || " + 
		createAreaPages_getTableCellAttribute( info , "notes" , info.notes , false , 50 ) + " ||";

	return( value );
}

String WikiMaker::createAreaPages_getTableCellAttribute( XmlHMindElementInfo& info , String attribute , String value , bool required , int columnWidth ) {
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

void WikiMaker::createAreaPages_createConnectivityTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef ) {
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
	connections.clear();
	createAreaPages_getExternalConnections( areaDef , connections , true );
	createAreaPages_getExternalConnectionTableLine( areaDef , NULL , lines , true );
	for( int k = 0; k < connections.count(); k++ ) {
		MindCircuitConnectionDef *c = connections.getClassByIndex( k );
		createAreaPages_getExternalConnectionTableLine( areaDef , c , lines , true );
	}

	// external connections - out
	lines.add( "" );
	connections.clear();
	createAreaPages_getExternalConnections( areaDef , connections , false );
	createAreaPages_getExternalConnectionTableLine( areaDef , NULL , lines , false );
	for( int k = 0; k < connections.count(); k++ ) {
		MindCircuitConnectionDef *c = connections.getClassByIndex( k );
		createAreaPages_getExternalConnectionTableLine( areaDef , c , lines , false );
	}

	String sectionName = "Connectivity";
	updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiMaker::createAreaPages_getInternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections ) {
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

	// create dot file
	String dotDir = wiki.getProperty( "dotPath" );
	String fileName = dotDir + "/" + areaDef -> getAreaId() + ".dot";
	StringList text;

	// header
	text.add( "digraph \"" + areaDef -> getAreaId() + "\" {" );
	String defaultDotSetup = wiki.getProperty( "defaultDotSetup" );
	text.add( defaultDotSetup );
	text.add( "" );

	// list nodes
	ClassList<MindRegionDef>& regions = areaDef -> getRegions();
	for( int k = 0; k < regions.count(); k++ ) {
		MindRegionDef *regionDef = regions.get( k );

		// find region in htree
		XmlHMindElementInfo info;
		hmindxml.getElementInfo( regionDef -> getName() , info );

		String nodeline = "\t\"" + info.id + "\"";
		if( !info.dotdef.isEmpty() )
			nodeline += "[" + info.dotdef + "]";
		nodeline += ";";
		text.add( nodeline );
	}

	// list connections
	text.add( "" );
	for( int k = 0; k < connections.count(); k++ ) {
		MindCircuitConnectionDef *c = connections.getClassByIndex( k );
		String linkline = "\t\"" + c -> getSrcRegion() + "\" -> \"" + c -> getDstRegion() + "\";";
		text.add( linkline );
	}

	// footer
	text.add( "}" );

	// out to file
	FILE *f = fopen( fileName , "wt" );
	ASSERTMSG( f != NULL , "Unable to open file=" + fileName );
	for( int k = 0; k < text.count(); k++ ) {
		String s = text.get( k ) + "\n";
		s = s.replace( "\\t" , "\t" );
		s = s.replace( "\\n" , "\n" );
		fputs( s , f );
	}
	fclose( f );
}

void WikiMaker::createAreaPages_getExternalConnections( MindAreaDef *areaDef , MapStringToClass<MindCircuitConnectionDef>& connections , bool isin ) {
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

void WikiMaker::createAreaPages_getInternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines ) {
	String line;
	if( link == NULL ) {
		// add heading
		line = "*Internal Region Connections:*";
		lines.add( line );
		lines.add( "" );
		String dotImageWikiPath = wiki.getProperty( "imageWikiPath" );
		line = dotImageWikiPath + "/" + areaDef -> getAreaId() + ".dot.jpg";
		lines.add( line );
		lines.add( "" );
		line = "|| *Source Region* || *Target Region* || *Type* ||";
		lines.add( line );
		return;
	}

	// table row
	line = "|| " + link -> getSrcRegion() + " || " + link -> getDstRegion() + " || " + link -> getTypeName() + " ||";
	lines.add( line );
}

void WikiMaker::createAreaPages_getExternalConnectionTableLine( MindAreaDef *areaDef , MindCircuitConnectionDef *link , StringList& lines , bool isin ) {
	String line;
	if( link == NULL ) {
		// add heading
		if( isin )
			line = "*External Inbound Region Connections:*";
		else
			line = "*External Outbound Region Connections:*";
		lines.add( line );

		if( isin )
			line = "|| *Source Area* || *Local Region* || *Source Region* || *Source Name* || *Type* ||";
		else
			line = "|| *Target Area* || *Local Region* || *Target Region* || *Target Name* || *Type* ||";
		lines.add( line );
		return;
	}

	// table row
	MindService *ms = MindService::getService();
	MindRegion *srcRegion = ms -> getMindRegion( link -> getSrcRegion() );
	MindRegion *dstRegion = ms -> getMindRegion( link -> getDstRegion() );
	String area = areaDef -> getAreaId();

	XmlHMindElementInfo info;
	if( area.equals( srcRegion -> getArea() -> getId() ) ) {
		hmindxml.getElementInfo( link -> getDstRegion() , info );
		line = "|| " + dstRegion -> getArea() -> getId() + " || " + 
			link -> getSrcRegion() + " || " + link -> getDstRegion() + " || " + info.name + " || " + link -> getTypeName() + " || ";
	}
	else {
		hmindxml.getElementInfo( link -> getSrcRegion() , info );
		line = "|| " + srcRegion -> getArea() -> getId() + " || " + 
			link -> getDstRegion() + " || " + link -> getSrcRegion() + " || " + info.name + " || " + link -> getTypeName() + " || ";
	}
	lines.add( line );
}

void WikiMaker::createAreaPages_createCircuitsAndReferencesTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef ) {
	// collect circuits which reference any of area regions
	MindService *ms = MindService::getService();

	StringList circuits;
	circuitsxml.getCircuitList( circuits );

	MindArea *area = ms -> getMindArea( areaDef -> getAreaId() );
	MapStringToString circuitKeys;
	for( int k = 0; k < circuits.count(); k++ ) {
		String circuitId = circuits.get( k );
		XmlCircuitInfo info;
		circuitsxml.getCircuitInfo( circuitId , info );

		String key = createAreaPages_getCircuitKey( areaDef , info );
		if( key.isEmpty() )
			continue;

		circuitKeys.add( key , circuitId );
	}

	// add circuits section
	StringList lines;
	for( int k = 0; k < circuitKeys.count(); k++ ) {
		String circuitId = circuitKeys.getClassByIndex( k );
		XmlCircuitInfo info;
		circuitsxml.getCircuitInfo( circuitId , info );
		createAreaPages_getCircuitLines( info , lines );
	}

	String sectionName = "Circuits";
	updateFileSection( wikiDir , wikiPage , sectionName , lines );
	lines.clear();

	// add unique and sorted references
	MapStringToClass<MindArea> refs;
	for( int k = 0; k < circuitKeys.count(); k++ ) {
		String circuitId = circuitKeys.getClassByIndex( k );
		XmlCircuitInfo info;
		circuitsxml.getCircuitInfo( circuitId , info );

		if( refs.get( info.reference ) == NULL )
			refs.add( info.reference , area );
	}

	for( int k = 0; k < refs.count(); k++ )
		lines.add( String( "  * " ) + refs.getKeyByIndex( k ) );

	sectionName = "References";
	updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

String WikiMaker::createAreaPages_getCircuitKey( MindAreaDef *areaDef , XmlCircuitInfo& info ) {
	// get circuit regions
	StringList comps;
	circuitsxml.getCircuitComponents( info , comps );

	// check circuit mentions area regions
	StringList compUsed;
	for( int k = 0; k < comps.count(); k++ ) {
		String comp = comps.get( k );
		String region = hmindxml.getMappedRegion( comp );
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

void WikiMaker::createAreaPages_getCircuitLines( XmlCircuitInfo& info , StringList& lines ) {
	lines.add( "  * [" + info.image + " " + info.name + "] - see [" + info.reference + " Reference]" );
	lines.add( "" );
	lines.add( info.image );
	lines.add( "" );
}

/*#########################################################################*/
/*#########################################################################*/
// create component pages

void WikiMaker::createComponentPages() {
}

/*#########################################################################*/
/*#########################################################################*/
// common

void WikiMaker::updateFileSection( String wikiDir , String wikiPage , String section , StringList& lines ) {
	String fileName = wikiDir + "/" + wikiPage + ".wiki";

	// scan file until section
	FILE *fr = fopen( fileName , "rt" );
	ASSERTMSG( fr != NULL , "unable to read from file " + fileName );

	String fileNameNew = fileName + ".new";
	remove( fileNameNew );
	FILE *fw = fopen( fileNameNew , "wt" );
	ASSERTMSG( fw != NULL , "unable to write to file " + fileNameNew );
	String s;

	int maxSize = 10000;
	s.resize( maxSize );

	// find start of section
	bool found = false;
	while( !feof( fr ) ) {
		fgets( s.getBuffer() , maxSize , fr );
		fputs( s , fw );

		s.trim();
		s.trim( '=' );
		s.trim();
		if( s.equals( section ) ) {
			found = true;
			break;
		}
	}

	if( !found ) {
		fclose( fr );
		fclose( fw );
		ASSERTFAILED( "unable to find section=" + section + " in page=" + wikiPage );
	}

	// write section lines
	fputs( "(generated)\n" , fw );
	fputs( "\n" , fw );
	for( int k = 0; k < lines.count(); k++ )
		fputs( lines.get( k ) + "\n" , fw );

	fputs( "\n" , fw );

	// skip current section content
	while( !feof( fr ) ) {
		fgets( s.getBuffer() , maxSize , fr );
		if( s.startsFrom( "= " ) || s.startsFrom( "== " ) || s.startsFrom( "=== " ) ) {
			fputs( s , fw );
			break;
		}
	}

	// write remaining file content
	while( !feof( fr ) ) {
		fgets( s.getBuffer() , maxSize , fr );
		fputs( s , fw );
	}

	// close files
	fclose( fr );
	fclose( fw );

	// rename file
	remove( fileName );
	rename( fileNameNew , fileName );

	logger.logInfo( "page " + wikiPage + " - replaced section " + section + " total nlines=" + lines.count() );
}
