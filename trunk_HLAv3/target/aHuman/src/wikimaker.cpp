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

	MindModel::load();

	// create pages
	createMainPage();
	createCircuitPages();
	updateHierarchyPage();
	createAreaPages();
	createComponentPages();
}

void WikiMaker::createMainPage() {
	WikiMainPage maker( this );
	maker.execute();
}

void WikiMaker::createCircuitPages() {
	WikiCircuitPages maker( this );
	maker.execute();
}

void WikiMaker::updateHierarchyPage() {
	WikiHierarchyPage maker( this );
	maker.execute();
}

void WikiMaker::createAreaPages() {
	WikiAreaPages maker( this );
	maker.execute();
}

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

void WikiMaker::updateFileHeading( String wikiDir , String wikiPage , StringList& lines ) {
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

	// write heading lines
	for( int k = 0; k < lines.count(); k++ )
		fputs( lines.get( k ) + "\n" , fw );

	fputs( "(generated)\n" , fw );

	// skip current heading content
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

	logger.logInfo( "page " + wikiPage + " - replaced heading, total nlines=" + lines.count() );
}

void WikiMaker::createFileContent( String fileName , StringList& lines ) {
	FILE *f = fopen( fileName , "wt" );
	ASSERTMSG( f != NULL , "Unable to open file=" + fileName );
	for( int k = 0; k < lines.count(); k++ ) {
		String s = lines.get( k ) + "\n";
		fputs( s , f );
	}
	fclose( f );
}

String WikiMaker::setSpecialCharacters( String data ) {
	String s = data.replace( "\\t" , "\t" );
	s = s.replace( "\\n" , "\n" );
	return( s );
}

String WikiMaker::findReference( MindCircuitConnectionDef *link ) {
	XmlCircuitInfo info;
	String circuitLink;

	// scan thirdparty circuits - check specific coverage
	StringList circuits;
	circuitsxml.getCircuitList( circuits );
	bool found = false;
	bool indirect = false;
	for( int k = 0; k < circuits.count(); k++ ) {
		circuitsxml.getCircuitInfo( circuits.get( k ) , info );
		if( findReferenceCircuitLink( link , info , circuitLink , true ) ) {
			found = true;
			break;
		}
	}

	// scan thirdparty circuits - check high-level coverage
	if( found == false ) {
		for( int k = 0; k < circuits.count(); k++ ) {
			circuitsxml.getCircuitInfo( circuits.get( k ) , info );
			if( findReferenceCircuitLink( link , info , circuitLink , false ) ) {
				found = true;
				break;
			}
		}
	}

	if( found == false )
		return( "(unknown reference)" );

	String reference = info.reference;
	if( reference.startsFrom( "article:" ) )
		reference = "http://ahuman.googlecode.com/svn/research/articles/" + reference.getMid( 8 );
			
	if( reference.equals( "UNKNOWN" ) ) {
		if( info.image.isEmpty() )
			return( "not linked reference, circuit=" + info.name + " (" + circuitLink + ")" );

		reference = info.image;
	}

	return( "[" + reference + " " + info.name + " (" + circuitLink + ")]" );
}

bool WikiMaker::findReferenceCircuitLink( MindCircuitConnectionDef *link , XmlCircuitInfo& info , String& circuitLink , bool directOnly ) {
	FlatList<Xml> links;
	XmlCircuitLinkInfo linkinfo;
	circuitsxml.getCircuitLinks( info.id , links );

	String checkSrcRegion = link -> getSrcRegion();
	String checkDstRegion = link -> getDstRegion();

	// find covering link
	for( int k = 0; k < links.count(); k++ ) {
		circuitsxml.getCircuitLinkInfo( links.get( k ) , linkinfo );
		String srcComponent = circuitsxml.mapComponent( info , linkinfo.compSrc );
		String dstComponent = circuitsxml.mapComponent( info , linkinfo.compDst );

		if( directOnly ) {
			String srcRegion = hmindxml.getMappedRegion( srcComponent );
			String dstRegion = hmindxml.getMappedRegion( dstComponent );
			if( srcRegion.equals( checkSrcRegion ) && dstRegion.equals( checkDstRegion ) ) {
				circuitLink = linkinfo.compSrc + " -> " + linkinfo.compDst;
				return( true );
			}
		}
		else {
			if( checkCircuitCoveredByModelLink( srcComponent , dstComponent , checkSrcRegion , checkDstRegion ) ) {
				circuitLink = linkinfo.compSrc + " -> " + linkinfo.compDst + ", abstract";
				return( true );
			}
		}
	}

	return( false );
}

String WikiMaker::getAreaPage( String area ) {
	return( "BrainArea" + area );
}

String WikiMaker::getRegionPage( String region ) {
	return( "BrainRegion" + region );
}
