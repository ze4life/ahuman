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
	createNervePages();
	createMusclePages();
	createSpinalCordPage();
	createTractsPages();
	createPeripheralPage();
}

void WikiMaker::createSpinalCordPage() {
	WikiSpinalCordPage maker( this );
	maker.execute();
}

void WikiMaker::createTractsPages() {
	WikiTractsPages maker( this );
	maker.execute();
}

void WikiMaker::createPeripheralPage() {
	WikiCategoryPage maker( this );
	maker.execute( "peripheral" , getPeripheralPage() );
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

void WikiMaker::createNervePages() {
	WikiNerveMainPage maker1( this );
	maker1.execute();

	WikiNerveSpecPages maker2( this );
	maker2.execute();
}

void WikiMaker::createMusclePages() {
	WikiMuscleMainPage maker1( this );
	maker1.execute();

	WikiMuscleSpecPages maker2( this );
	maker2.execute();
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
	String sectionHeading;
	while( !feof( fr ) ) {
		s.clear();
		fgets( s.getBuffer() , maxSize , fr );
		fputs( s , fw );

		if( s.startsFrom( "=" ) ) {
			int index = s.find( " " );
			if( index < 0 ) {
				fclose( fr );
				fclose( fw );
				ASSERTFAILED( "invalid section name=" + s + " in page=" + wikiPage );
			}

			sectionHeading = s.getMid( 0 , index ) + "=";
			s.trim();
			s.trim( '=' );
			s.trim();
			if( s.equals( section ) ) {
				found = true;
				break;
			}
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
		s.clear();
		fgets( s.getBuffer() , maxSize , fr );
		if( s.startsFrom( "=" ) && !s.startsFrom( sectionHeading ) ) {
			fputs( s , fw );
			break;
		}
	}

	// write remaining file content
	while( !feof( fr ) ) {
		s.clear();
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

String WikiMaker::findReference( MindRegionLink *link ) {
	return( findReference( link -> getSrcRegion() -> getRegionId() , link -> getDstRegion() -> getRegionId() ) );
}

String WikiMaker::findReference( MindLocalCircuitConnectionDef *link ) {
	return( findReference( link -> getSrcRegion() , link -> getDstRegion() ) );
}

String WikiMaker::findReference( String srcRegion , String dstRegion ) {
	// check by map
	String key = srcRegion + "." + dstRegion;
	String reference = referenceMap.get( key );
	if( !reference.isEmpty() )
		return( reference );

	XmlCircuitFind find;
	if( circuitsxml.findReferenceLink( hmindxml , srcRegion , dstRegion , find ) ) {
		String circuitLink = find.link.compSrc + " -> " + find.link.compDst;
		if( find.isAbstractLink )
			circuitLink += ", abstract";

		reference = find.circuit -> reference;
		if( reference.startsFrom( "article:" ) )
			reference = "http://ahuman.googlecode.com/svn/research/articles/" + reference.getMid( 8 );
		else
		if( reference.equals( "UNKNOWN" ) ) {
			if( find.circuit -> image.isEmpty() )
				reference = "not linked reference, circuit=" + find.circuit -> name + " (" + circuitLink + ")";
			else
				reference = find.circuit -> image;
		}

		reference = "[" + reference + " " + find.circuit -> name + " (" + circuitLink + ")]";
	}
	else
		reference = "(unknown reference)";

	// add to map and return
	referenceMap.add( key , reference );
	return( reference );
}

String WikiMaker::getAreaPage( String area ) {
	return( "BrainArea" + area );
}

String WikiMaker::getRegionPage( String region ) {
	return( "BrainRegion" + region.replace( "." , "_" ) );
}

void WikiMaker::ensureFileExists( String wikiDir , String wikiPage , StringList& sections ) {
	String fileName = wikiDir + "/" + wikiPage + ".wiki";

	// scan file until section
	FILE *fr = fopen( fileName , "rt" );
	if( fr != NULL ) {
		fclose( fr );
		return;
	}

	// create sections
	FILE *fw = fopen( fileName , "wt" );
	for( int k = 0; k < sections.count(); k++ ) {
		fputs( sections.get( k ) + "\n" , fw );
		fputs( "\n" , fw );
	}
	fclose( fw );
}

String WikiMaker::getRegionReference( String region ) {
	return( "[" + getRegionPage( region ) + " " + region + "]" );
}

const XmlHMindElementInfo& WikiMaker::getComponentReferenceInfo( String comp ) {
	String region = hmindxml.getMappedRegion( comp );
	if( !region.isEmpty() )
		return( hmindxml.getElementInfo( region ) );

	return( hmindxml.getElementInfo( comp ) );
}

String WikiMaker::getAvailableReference( String comp ) {
	String s;
	const XmlHMindElementInfo& info = hmindxml.getElementInfo( comp );

	if( info.mapped ) {
		s = "[" + getRegionPage( comp ) + " " + info.name + "," + comp + "]";
	}
	else if( info.parent == NULL ) {
		s = "*" + info.name + "*";
	}
	else
		s = info.name + "," + comp;

	return( s );
}

String WikiMaker::getComponentReference( String comp ) {
	String s;
	String region = hmindxml.getMappedRegion( comp );
	if( !region.isEmpty() ) {
		const XmlHMindElementInfo& info = hmindxml.getElementInfo( region );
		s = "[" + getRegionPage( region ) + " " + info.name + "," + comp + "]";
	}
	else {
		StringList regions;
		hmindxml.getChildRegions( comp , regions );
		StringList regionRef;
		for( int k = 0; k < regions.count(); k++ ) {
			String child = regions.get( k );
			const XmlHMindElementInfo& info = hmindxml.getElementInfo( child );
			String ref = "[" + getRegionPage( child ) + " " + info.name + "," + child + "]";
			regionRef.add( ref );
		}

		const XmlHMindElementInfo& info = hmindxml.getElementInfo( comp );
		s = info.name + "," + comp + " (" + regionRef.combine( ", " ) + ")";
	}

	return( s );
}

String WikiMaker::getMuscleReference( String name , String text ) {
	XmlMuscleInfo *muscle = musclesxml.findByConnector( name );
	if( muscle == NULL )
		return( text );

	String link = "[" + muscle -> division -> page + " " + text + "]";
	return( link );
}

String WikiMaker::getAreaReference( String area ) {
	return( "[" + getAreaPage( area ) + " " + area + "]" );
}

String WikiMaker::getDotColor( String dotdef ) {
	int index = dotdef.find( "color=" );
	if( index < 0 )
		return( "" );

	int stop = dotdef.find( index , "." );

	String color;
	if( stop < 0 )
		color = dotdef.getMid( index + 6 );
	else
		color = dotdef.getMid( index + 6 , stop - index - 6 );

	color.trim();
	return( color );
}

void WikiMaker::clearRepeats1( String& value1 ) {
	if( saveRepeats1.equals( value1 ) )
		value1.clear();
	else
		saveRepeats1 = value1;
}

void WikiMaker::clearRepeats2( String& value1 , String& value2 ) {
	if( saveRepeats1.equals( value1 ) ) {
		value1.clear();
		if( saveRepeats2.equals( value2 ) )
			value2.clear();
		else
			saveRepeats2 = value2;
	}
	else {
		saveRepeats1 = value1;
		saveRepeats2 = value2;
	}
}

String WikiMaker::getNerveWikiPage( String nerve ) {
	// load nerves
	nervesxml.load();
	XmlNerveInfo& div = nervesxml.getNerveDivision( nerve );
	return( div.origin );
}

String WikiMaker::getTractPageLink( String location ) {
	return( "MindTracts" + location );
}

String WikiMaker::getImageWikiLink( String imgsrc , String height ) {
	String s = "<img src=\"" + imgsrc + "\"";
	if( !height.isEmpty() )
		s += " height=" + height;
	s += ">";
	return( s );
}

String WikiMaker::getWikiLink( String link , String text ) {
	if( link.isEmpty() )
		return( text );

	return( "[" + link + " " + text + "]" );
}

String WikiMaker::getWikiBold( String text ) {
	return( "*" + text + "*" );
}

bool WikiMaker::checkCreateMainPages() {
	return( wiki.getBooleanProperty( "createMainPages" , false ) );
}

bool WikiMaker::checkCreateNervePages() {
	return( wiki.getBooleanProperty( "createNervePages" , true ) );
}

bool WikiMaker::checkCreateMusclePages() {
	return( wiki.getBooleanProperty( "createMusclePages" , true ) );
}

bool WikiMaker::checkCreateOverallHierarchyPage() {
	return( wiki.getBooleanProperty( "createPageHierarchy" , true ) );
}

bool WikiMaker::checkCreateCircuitPages() {
	return( wiki.getBooleanProperty( "createCircuitPages" , true ) );
}

bool WikiMaker::checkCreateRegionPages() {
	return( wiki.getBooleanProperty( "createRegionPages" , true ) );
}

bool WikiMaker::checkCreateAreaPages() {
	return( wiki.getBooleanProperty( "createAreaPages" , true ) );
}

String WikiMaker::getWikiPath() {
	return( wiki.getProperty( "wikiPath" ) );
}

String WikiMaker::getWikiImagePath() {
	return( "http://ahuman.googlecode.com/svn/images/dot/aHuman" );
}

String WikiMaker::getWikiDotPath() {
	return( wiki.getProperty( "dotPath" ) );
}

String WikiMaker::getDefaultDotSetup() {
	return( "\\tnode [shape=box, style=filled, color=springgreen, fontsize=10];" );
}

String WikiMaker::getDefaultDotRegionSetup() {
	return( "shape=box, style=bold, fontsize=10" );
}

String WikiMaker::getMainPage() {
	return( "BiologicalLifeResearch" );
}

String WikiMaker::getOverallHierarchyPage() {
	return( "OverallMindMaps" );
}

String WikiMaker::getSpinalCordPage() {
	return( "SpinalCord" );
}

String WikiMaker::getSpinalCordPageLayoutSection() {
	return( "SPINAL CORD LAMINAE AND LEVELS" );
}

String WikiMaker::getMainTractPage() {
	return( "MindTracts" );
}

String WikiMaker::getMainTractPageListSection() {
	return( "Tracts Hierarchy" );
}

String WikiMaker::getMainTractPageNeuronsSection() {
	return( "Sensory and Motor Root Neurons" );
}

String WikiMaker::getMainNervePage() {
	return( "HumanNerves" );
}

String WikiMaker::getMainNervePageListSection() {
	return( "NERVES HIERARCHY" );
}

String WikiMaker::getMainMusclePage() {
	return( "HumanMuscles" );
}

String WikiMaker::getMainMusclePageListSection() {
	return( "MUSCLES HIERARCHY" );
}

String WikiMaker::getCategoryPageRegionSection() {
	return( "INNER REGIONS" );
}

String WikiMaker::getCategoryPageSensoryLinkSection() {
	return( "LINKED SENSORY REGIONS" );
}

String WikiMaker::getCategoryPageMotorLinkSection() {
	return( "LINKED MOTOR REGIONS" );
}

String WikiMaker::getCategoryPageReciprocalLinkSection() {
	return( "LINKED RECIPROCAL REGIONS" );
}

String WikiMaker::getCategoryPageGangliaLinkSection() {
	return( "LINKED GANGLIA" );
}

String WikiMaker::getSelectedArea() {
	return( wiki.getProperty( "selectedArea" , "" ) );
}

String WikiMaker::getPeripheralPage() {
	return( "PeripheralBrain" );
}

String WikiMaker::getCircuitDotPath( MindLocalCircuitDef& circuit ) {
	String line = getWikiDotPath() + "/" + circuit.getAreaDef() -> getAreaId() + "_" + circuit.getId() + ".dot";
	return( line );
}

String WikiMaker::getCircuitImageRef( MindLocalCircuitDef& circuit ) {
	String line = getWikiImagePath() + "/" + circuit.getAreaDef() -> getAreaId() + "_" + circuit.getId() + ".dot.png";
	return( line );
}

String WikiMaker::getTableCellAttribute( const char *id , const char *attribute , String value , bool required , int columnWidth ) {
	ASSERTMSG( ( required == false ) || ( value.isEmpty() == false ) , String( "attribute=" ) + attribute + " is empty for region=" + id );

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

