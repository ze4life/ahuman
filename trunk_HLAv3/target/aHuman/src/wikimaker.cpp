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
	// get wiki file
	String wikiDir = wiki.getProperty( "wikiPath" );
	String wikiPage = hmind.getProperty( "wikiPage" );
	String wikiFileName = wikiDir + "/" + wikiPage + ".wiki";

	// create hierarchy section
	for( Xml xmlChild = hmind.getFirstChild( "division" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "division" ) ) {
		StringList lines;
		updateHierarchyPage_WalkTree( wiki , xmlChild , 0 , lines , true );
		String sectionName = xmlChild.getAttribute( "name" );
		updateFileSection( wikiFileName , sectionName , lines );
	}
}

void WikiMaker::updateHierarchyPage_WalkTree( Xml wiki , Xml hmind , int level , StringList& lines , bool mapRegion ) {
	MindService *ms = MindService::getService();

	for( Xml xmlChild = hmind.getFirstChild( "element" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "element" ) ) {
		// handle mapping
		bool mapRegionNext = false;
		MindRegion *region = NULL;
		if( mapRegion ) {
			String id = xmlChild.getAttribute( "id" , "" );
			region = ms -> getMindRegion( id );
			if( region != NULL )
				mapRegionNext = false;
		}

		// add item string
		String itemString = updateHierarchyPage_getElementString( wiki , xmlChild , region );
		lines.add( String( " " ).replicate( 2 + level ) + "* " + itemString );

		// walk down
		updateHierarchyPage_WalkTree( wiki , xmlChild , level + 1 , lines , mapRegionNext );
	}
}

String WikiMaker::updateHierarchyPage_getElementString( Xml wiki , Xml item , MindRegion *region ) {
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
	String refs = item.getAttribute( "refs" );
	StringList refList;
	refs.split( refList , "," );
	for( int k = 0; k < refList.count(); k++ ) {
		String ref = refList.get( k );
		ref.trim();

		if( !value.isEmpty() )
			value += " = ";

		value += ref;
	}

	// mapping section
	if( region != NULL ) {
		MindArea *area = region -> getArea();
		value += " -> [BrainArea" + area -> getId() + "]";
	}

	return( value );
}

/*#########################################################################*/
/*#########################################################################*/
// create area pages

void WikiMaker::createAreaPages( Xml wiki , Xml hmind ) {
}

/*#########################################################################*/
/*#########################################################################*/
// create component pages

void WikiMaker::createComponentPages( Xml wiki , Xml hmind ) {
}

/*#########################################################################*/
/*#########################################################################*/
// common

void WikiMaker::updateFileSection( String fileName , String section , StringList& lines ) {
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
}
