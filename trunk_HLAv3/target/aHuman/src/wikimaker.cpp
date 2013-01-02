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
	hmind.load();
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
	hmind.getDivisions( divisions );
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
	hmind.getElements( parentNode , elements );

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
	hmind.getElementInfo( parentNode , info );

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
	hmind.getElements( parentNode , elements );

	for( int k = 0; k < elements.count(); k++ ) {
		String node = elements.get( k );

		// check ignored
		hmind.getElementInfo( node , info );
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
	hmind.getElementInfo( parentNode , info );

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
	hmind.getElements( parentNode , elements );

	for( int k = 0; k < elements.count(); k++ ) {
		String node = elements.get( k );

		// check ignored
		hmind.getElementInfo( node , info );
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
	hmind.getElementInfo( node , info );

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
	hmind.getElements( neocortexDivision , elements );

	// group by major lobes
	for( int k = 0; k < elements.count(); k++ ) {
		String node = elements.get( k );
		hmind.getElementInfo( node , info );

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
	hmind.getElementInfo( node , info );

	if( info.brodmannid.isEmpty() ) {
		// check childs
		StringList elements;
		hmind.getElements( node , elements );

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
	bool createPageHierarchy = wiki.getBooleanProperty( "createAreaPages" , true );
	if( createPageHierarchy == false ) {
		logger.logInfo( "skip creating area pages" );
		return;
	}

	// get wiki file
	String wikiDir = wiki.getProperty( "wikiPath" );

	MindService *ms = MindService::getService();
	MindMap *mm = ms -> getMindMap();

	// by area
	ClassList<MindAreaDef>& areaList = mm -> getMindAreas();
	for( int k = 0; k < areaList.count(); k++ ) {
		MindAreaDef *areaDef = areaList.get( k );

		String wikiPage = "BrainArea" + areaDef -> getAreaId();
		createAreaPages_createRegionTableSection( wikiDir , wikiPage , areaDef );
	}
}

void WikiMaker::createAreaPages_createRegionTableSection( String wikiDir , String wikiPage , MindAreaDef *areaDef ) {
	String selectedArea = wiki.getProperty( "selectedArea" , "" );
	if( !selectedArea.isEmpty() ) {
		if( !selectedArea.equals( areaDef -> getAreaId() ) )
			return;
	}

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
	hmind.getElementInfo( regionId , info );
	
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

void WikiMaker::createAreaPages_createCircuitsSection( String wikiDir , String wikiPage , MindAreaDef *areaDef ) {
}

void WikiMaker::createAreaPages_createReferencesSection( String wikiDir , String wikiPage , MindAreaDef *areaDef ) {
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
		ASSERTFAILED( "unable to find section=" + section );
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
