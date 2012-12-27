#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

WikiMaker::WikiMaker() {
	attachLogger();
}

WikiMaker::~WikiMaker() {
}

void WikiMaker::createPages( Xml wiki ) {
	logger.logInfo( "create mind model wiki pages..." );

	// read hierarchy
	EnvService *es = EnvService::getService();
	Xml hmind = es -> loadXml( "hmind.xml" );
	ASSERTMSG( hmind.exists() , "unable to read file hmind.xml" );

	// create pages
	updateHierarchyPage( wiki , hmind );
	createAreaPages( wiki , hmind );
	createComponentPages( wiki , hmind );
}

/*#########################################################################*/
/*#########################################################################*/
// heirarchy pages

void WikiMaker::updateHierarchyPage( Xml wiki , Xml hmind ) {
	bool createPageHierarchy = wiki.getBooleanProperty( "createPageHierarchy" , true );
	if( createPageHierarchy == false ) {
		logger.logInfo( "skip creating hierarchy page" );
		return;
	}

	// get wiki file
	String wikiDir = wiki.getProperty( "wikiPath" );
	String wikiPage = wiki.getProperty( "wikiPageHierarchy" );

	// create hierarchy section
	for( Xml xmlChild = hmind.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		String sectionName = xmlChild.getAttribute( "name" );
		if( sectionName.equals( "Neocortex" ) )
			updateHierarchyPage_walkNeocortex( wiki , xmlChild , wikiDir , wikiPage );
		else {
			StringList lines;
			updateHierarchyPage_walkTree( wiki , xmlChild , 0 , lines , NULL , NULL );
			updateFileSection( wikiDir , wikiPage , sectionName , lines );
		}
	}
}

void WikiMaker::updateHierarchyPage_walkTree( Xml wiki , Xml hmind , int level , StringList& lines , MindArea *parentArea , MindRegion *parentRegion ) {
	for( Xml xmlChild = hmind.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		// handle mapping
		MindArea *ownArea = NULL;
		MindRegion *ownRegion = NULL;

		if( parentArea == NULL )
			ownArea = updateHierarchyPage_getArea( xmlChild );
		if( parentRegion == NULL )
			ownRegion = updateHierarchyPage_getRegion( xmlChild );

		// add item string
		String itemString = updateHierarchyPage_getElementString( wiki , xmlChild , parentArea , parentRegion , ownArea , ownRegion );
		lines.add( String( " " ).replicate( 2 + level ) + "* " + itemString );

		// walk down
		if( ownArea == NULL )
			ownArea = parentArea;
		if( ownRegion == NULL )
			ownRegion = parentRegion;

		updateHierarchyPage_walkTree( wiki , xmlChild , level + 1 , lines , ownArea , ownRegion );
	}
}

MindArea *WikiMaker::updateHierarchyPage_getArea( Xml item ) {
	MindService *ms = MindService::getService();

	// check ignored
	bool ignore = item.getBooleanAttribute( "ignore" , false );
	if( ignore == true )
		return( NULL );

	// check direct
	String id = item.getAttribute( "id" , "" );
	if( !id.isEmpty() ) {
		MindRegion *region = ms -> getMindRegion( id );
		return( region -> getArea() );
	}

	// check all childs
	MindArea *area = NULL;
	for( Xml xmlChild = item.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		// check ignored
		ignore = xmlChild.getBooleanAttribute( "ignore" , false );
		if( ignore == true )
			continue;

		MindArea *one = updateHierarchyPage_getArea( xmlChild );
		if( area == NULL )
			area = one;
		else if( one != area )
			return( NULL );
	}

	return( area );
}

MindRegion *WikiMaker::updateHierarchyPage_getRegion( Xml item ) {
	MindRegion *region = NULL;
	MindService *ms = MindService::getService();

	// check ignored
	bool ignore = item.getBooleanAttribute( "ignore" , false );
	if( ignore == true )
		return( NULL );

	// check direct
	String id = item.getAttribute( "id" , "" );
	if( !id.isEmpty() ) {
		region = ms -> getMindRegion( id );
		return( region );
	}

	// check all childs
	for( Xml xmlChild = item.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		// check ignored
		ignore = xmlChild.getBooleanAttribute( "ignore" , false );
		if( ignore == true )
			continue;

		MindRegion *one = updateHierarchyPage_getRegion( xmlChild );
		if( region == NULL )
			region = one;
		else if( one != region )
			return( NULL );
	}

	return( region );
}

String WikiMaker::updateHierarchyPage_getElementString( Xml wiki , Xml item , MindArea *parentArea , MindRegion *parentRegion , MindArea *ownArea , MindRegion *ownRegion ) {
	String value;

	// own name if any
	String id = item.getAttribute( "id" , "" );
	String name = item.getAttribute( "name" , "" );
	if( name.isEmpty() ) {
		ASSERTMSG( id.isEmpty() , "unexpected not empty id=" + id );
	}
	else {
		value += "*";
		value += name;

		if( !id.isEmpty() )
			value += " (" + id + ")";

		value += "*";
	}

	// ref section
	String refs = item.getAttribute( "refs" , "" );
	if( !refs.isEmpty() ) {
		StringList refList;
		refs.split( refList , ";" );
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
	bool ignore = item.getBooleanAttribute( "ignore" , false );
	String comment = item.getAttribute( "comment" , "" );

	if( ignore == true ) {
		value += " (ignore";
		if( !comment.isEmpty() )
			value += ", " + comment;
		value += ")";
	}
	else if( !comment.isEmpty() )
		value += " (" + comment + ")";

	return( value );
}

void WikiMaker::updateHierarchyPage_walkNeocortex( Xml wiki , Xml neocortexDivision , String wikiDir , String wikiPage ) {
	// group by major lobes
	for( Xml xmlChild = neocortexDivision.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		String wikiNeoCortexSection = xmlChild.getAttribute( "name" );
		StringList lines;

		updateHierarchyPage_getNeocortexLobeLines( wiki , xmlChild , lines );
		updateFileSection( wikiDir , wikiPage , wikiNeoCortexSection , lines );
	}
}

void WikiMaker::updateHierarchyPage_getNeocortexLobeLines( Xml wiki , Xml neocortexLobe , StringList& lines ) {
	String banum;
	banum.resize( 10 );

	// list by brodmann areas
	MapStringToString balines;
	for( int k = 1; k < 100; k++ ) {
		sprintf( banum.getBuffer() , "%2.2d" , k );

		String baline = updateHierarchyPage_getNeocortexBrodmannLine( wiki , neocortexLobe , banum );
		if( !baline.isEmpty() )
			balines.add( banum , baline );
	}

	// group the same if sequential
	String lastnumset;
	String lastline;
	for( int k = 1; k < 100; k++ ) {
		sprintf( banum.getBuffer() , "%2.2d" , k );
		String baline = balines.get( banum );

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

String WikiMaker::updateHierarchyPage_getNeocortexBrodmannLine( Xml wiki , Xml neocortexDivision , String banum ) {
	// check all childs
	StringList items;
	updateHierarchyPage_walkNeocortexBrodmannLine( wiki , neocortexDivision , banum , items );

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

void WikiMaker::updateHierarchyPage_walkNeocortexBrodmannLine( Xml wiki , Xml item , String banum , StringList& items ) {
	String brodmannid = item.getAttribute( "brodmannid" , "" );
	if( brodmannid.isEmpty() ) {
		// check childs
		for( Xml xmlChild = item.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) )
			updateHierarchyPage_walkNeocortexBrodmannLine( wiki , xmlChild , banum , items );
		return;
	}

	// check itself
	if( brodmannid.find( banum ) < 0 )
		return;

	// add string
	String value;
	bool ignore = item.getBooleanAttribute( "ignore" , false );
	String comment = item.getAttribute( "comment" , "" );

	if( ignore ) {
		value = "ignored";
		if( !comment.isEmpty() )
			value += ", " + comment;
	}
	else {
		String id = item.getAttribute( "id" );
		String name = item.getAttribute( "name" );

		MindService *ms = MindService::getService();
		MindRegion *region = ms -> getMindRegion( id );
		MindArea *area = region -> getArea();

		value = "[BrainArea" + area -> getId() + " " + name + " (" + id + ")]";
	}

	items.add( value );
}

/*#########################################################################*/
/*#########################################################################*/
// create area pages

void WikiMaker::createAreaPages( Xml wiki , Xml hmind ) {
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
		createAreaPages_makeAreaPageFile( wiki , hmind , wikiDir , wikiPage , areaDef );
	}
}

void WikiMaker::createAreaPages_makeAreaPageFile( Xml wiki , Xml hmind , String wikiDir , String wikiPage , MindAreaDef *areaDef ) {
	String selectedArea = wiki.getProperty( "selectedArea" , "" );
	if( !selectedArea.isEmpty() ) {
		if( !selectedArea.equals( areaDef -> getAreaId() ) )
			return;
	}

	StringList lines;

	// heading
	String s = createAreaPages_getRegionTableRow( wiki , hmind , NULL );
	lines.add( s );

	// regions
	ClassList<MindRegionDef>& regionList = areaDef -> getRegions();
	for( int k = 0; k < regionList.count(); k++ ) {
		MindRegionDef *regionDef = regionList.get( k );
		s = createAreaPages_getRegionTableRow( wiki , hmind , regionDef );
		lines.add( s );
	}

	String sectionName = "Components";
	updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

String WikiMaker::createAreaPages_getRegionTableRow( Xml wiki , Xml hmind , MindRegionDef *regionDef ) {
	String value;

	// heading
	if( regionDef == NULL ) {
		value = "|| *Component ID* || *Component Name* || *Type* || *Function* || *Comments* ||";
		return( value );
	}

	// region row
	String regionId = regionDef -> getName();
	Xml regionXml = findHMindRegion( hmind , regionId );
	ASSERTMSG( regionXml.exists() , "unable to find region id=" + regionId + " in hierarchy" );
	
	value = "|| *" + regionId + "* || " + 
		createAreaPages_getTableCellAttribute( wiki , regionXml , "name" , true , 0 ) + " || " + 
		createAreaPages_getTableCellAttribute( wiki , regionXml , "type" , true , 0 ) + " || " + 
		createAreaPages_getTableCellAttribute( wiki , regionXml , "function" , true , 80 ) + " || " + 
		createAreaPages_getTableCellAttribute( wiki , regionXml , "notes" , false , 50 ) + " ||";

	return( value );
}

String WikiMaker::createAreaPages_getTableCellAttribute( Xml wiki , Xml regionXml , String attribute , bool required , int columnWidth ) {
	String value = regionXml.getAttribute( attribute , "" );
	ASSERTMSG( ( required == false ) || ( value.isEmpty() == false ) , "attribute=" + attribute + " is empty for region=" + regionXml.getAttribute( "id" , "" ) );

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

/*#########################################################################*/
/*#########################################################################*/
// create component pages

void WikiMaker::createComponentPages( Xml wiki , Xml hmind ) {
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

Xml WikiMaker::findHMindRegion( Xml hmind , String regionId ) {
	// walk childs
	for( Xml xmlChild = hmind.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		Xml item = findHMindRegionElement( xmlChild , regionId );
		if( item.exists() )
			return( item );
	}

	Xml itemEmpty;
	return( itemEmpty );
}

Xml WikiMaker::findHMindRegionElement( Xml element , String regionId ) {
	// walk childs
	for( Xml xmlChild = element.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		// check this
		if( regionId.equals( xmlChild.getAttribute( "id" , "" ) ) )
			return( xmlChild );

		// check childs
		Xml item = findHMindRegionElement( xmlChild , regionId );
		if( item.exists() )
			return( item );
	}

	Xml itemEmpty;
	return( itemEmpty );
}
