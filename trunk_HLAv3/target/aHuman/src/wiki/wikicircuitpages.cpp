#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiCircuitPages::WikiCircuitPages( WikiMaker *p_wm ) {
	attachLogger();
	wm = p_wm;
}

WikiCircuitPages::~WikiCircuitPages() {
}

void WikiCircuitPages::execute() {
	bool createCircuitPages = wm -> checkCreateCircuitPages();
	if( createCircuitPages == false ) {
		logger.logInfo( "skip creating circuit pages" );
		return;
	}

	String wikiDir = wm -> getWikiPath();

	// generate circuits
	MindService *ms = MindService::getService();
	MindMap *mm  = ms -> getMindMap();
	ClassList<MindGlobalCircuitDef>& circuitList = mm -> getMindGlobalCircuits();
	for( int k = 0; k < circuitList.count(); k++ ) {
		MindGlobalCircuitDef *cd = circuitList.get( k );

		String wikiPage = cd -> getId();
		createCircuitPage( wikiDir , wikiPage , cd );
	}
}

void WikiCircuitPages::createCircuitPage( String wikiDir , String wikiPage , MindGlobalCircuitDef *cd ) {
	StringList lines;

	StringList sections;
	sections.add( "= Components =" );
	sections.add( "= Connections =" );
	wm -> ensureFileExists( wikiDir , wikiPage , sections );

	// circuit heading
	createCircuitPage_getHeading( wikiPage , cd , lines );
	wm -> updateFileHeading( wikiDir , wikiPage , lines );
	lines.clear();

	// circuit nodes section
	MapStringToClass<MindRegion> nodes;
	createCircuitPage_getNodeList( cd , nodes );
	createCircuitPage_getNodeSection( cd , nodes , lines );
	String sectionName = "Components";
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
	lines.clear();

	// circuit graph section
	MapStringToClass<MindLocalCircuitConnectionDef> links;
	createCircuitPage_getLinkList( cd , links );
	createCircuitPage_getDiagram( cd , nodes , links , lines );
	createCircuitPage_getLinkSection( cd , links , lines );
	sectionName = "Connections";
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
	lines.clear();
}

void WikiCircuitPages::createCircuitPage_getHeading( String wikiPage , MindGlobalCircuitDef *cd , StringList& lines ) {
	lines.add( "#summary " + cd -> getName() );
	lines.add( "@@[Home] -> [BiologicalLifeResearch] -> [" + cd -> getId() + "]" );
	lines.add( "----" );
	lines.add( "" );
	lines.add( "This page covers components and connections of circuit " + cd -> getName() + "." );
	lines.add( "Circuit is part of aHuman target integrated biological model." );
	lines.add( "" );
}

void WikiCircuitPages::createCircuitPage_getLinkList( MindGlobalCircuitDef *cd , MapStringToClass<MindLocalCircuitConnectionDef>& links ) {
	// rows - sorted by component id
	ClassList<MindLocalCircuitConnectionDef>& linklist = cd -> getConnections();
	for( int k = 0; k < linklist.count(); k++ ) {
		MindLocalCircuitConnectionDef *link = linklist.get( k );
		String key = link -> getSrcRegion() + "-" + link -> getDstRegion();
		links.add( key , link );
	}
}

void WikiCircuitPages::createCircuitPage_getLinkSection( MindGlobalCircuitDef *cd , MapStringToClass<MindLocalCircuitConnectionDef>& links , StringList& lines ) {
	// heading
	createCircuitPage_getLinksRow( cd , NULL , lines );

	for( int k = 0; k < links.count(); k++ ) {
		MindLocalCircuitConnectionDef *link = links.getClassByIndex( k );
		createCircuitPage_getLinksRow( cd , link , lines );
	}
}

void WikiCircuitPages::createCircuitPage_getLinksRow( MindGlobalCircuitDef *cd , MindLocalCircuitConnectionDef *link , StringList& lines ) {
	String value1;
	if( link == NULL ) {
		// heading
		lines.add( "|| *Source Region* || *Target Region* || *Type* || *Reference* ||" );
		wm -> clearRepeats1( value1 );
		return;
	}

	// row
	String reference = wm -> findReference( link );
	value1 = wm -> getRegionReference( link -> getSrcRegion() );
	wm -> clearRepeats1( value1 );
	lines.add( "|| " + value1 + " || " + wm -> getRegionReference( link -> getDstRegion() ) + " || " + 
		link -> getTypeName() + " || " + reference + " ||" );
}

void WikiCircuitPages::createCircuitPage_getNodeList( MindGlobalCircuitDef *cd , MapStringToClass<MindRegion>& nodes ) {
	// get nodes
	MindService *ms = MindService::getService();
	ClassList<MindLocalCircuitConnectionDef>& links = cd -> getConnections();
	for( int k = 0; k < links.count(); k++ ) {
		MindLocalCircuitConnectionDef *link = links.get( k );
		String region = link -> getSrcRegion();
		if( nodes.get( region ) == NULL )
			nodes.add( region , ms -> getMindRegion( region ) );

		region = link -> getDstRegion();
		if( nodes.get( region ) == NULL )
			nodes.add( region , ms -> getMindRegion( region ) );
	}
}

void WikiCircuitPages::createCircuitPage_getNodeSection( MindGlobalCircuitDef *cd , MapStringToClass<MindRegion>& nodes , StringList& lines ) {
	// heading
	createCircuitPage_getNodesRow( cd , NULL , lines );

	for( int k = 0; k < nodes.count(); k++ ) {
		MindRegion *region = nodes.getClassByIndex( k );
		createCircuitPage_getNodesRow( cd , region , lines );
	}
}

void WikiCircuitPages::createCircuitPage_getNodesRow( MindGlobalCircuitDef *cd , MindRegion *region , StringList& lines ) {
	String value1;
	if( region == NULL ) {
		// heading
		lines.add( "|| *Mind Area* || *Component ID* || *Component Name* || *Type* || *Function* ||" );
		wm -> clearRepeats1( value1 );
		return;
	}

	// row
	MindArea *area = region -> getArea();
	const XmlHMindElementInfo& info = wm -> hmindxml.getElementInfo( region -> getRegionId() );
	value1 = wm -> getAreaReference( area -> getAreaId() );
	wm -> clearRepeats1( value1 );
	lines.add( "|| " + value1 + " || " + wm -> getRegionReference( region -> getRegionId() ) + " || " + 
		info.name + " || " + info.batype + " || " + info.function + " ||" );
}

void WikiCircuitPages::createCircuitPage_getDiagram( MindGlobalCircuitDef *cd , MapStringToClass<MindRegion>& nodes , MapStringToClass<MindLocalCircuitConnectionDef>& links , StringList& lines ) {
	String dotImageWikiPath = wm -> getWikiImagePath();
	String line = dotImageWikiPath + "/" + cd -> getId() + ".dot.jpg";
	lines.add( line );
	lines.add( "" );

	// create dot file
	String dotDir = wm -> getWikiDotPath();
	String fileName = dotDir + "/" + cd -> getId() + ".dot";
	StringList text;

	// header
	text.add( "digraph \"" + cd -> getId() + "\" {" );
	text.add( "\tconcentrate=true;" );
	String defaultDotSetup = wm -> getDefaultDotSetup();
	text.add( wm -> setSpecialCharacters( defaultDotSetup ) );
	text.add( "" );

	// list nodes
	for( int k = 0; k < nodes.count(); k++ ) {
		MindRegion *region = nodes.getClassByIndex( k );

		String dotdef = wm -> hmindxml.getDotDef( region -> getRegionId() );
		String nodeline = "\t\"" + region -> getRegionId() + "\"";
		if( !dotdef.isEmpty() ) {
			String s = wm -> setSpecialCharacters( dotdef );
			nodeline += " [" + s + "]";
		}
		nodeline += ";";

		text.add( nodeline );
	}

	// list connections
	text.add( "" );
	for( int k = 0; k < links.count(); k++ ) {
		MindLocalCircuitConnectionDef *link = links.getClassByIndex( k );
		String linkline = "\t\"" + link -> getSrcRegion() + "\" -> \"" + link -> getDstRegion() + "\";";
		text.add( linkline );
	}

	// footer
	text.add( "}" );

	// out to file
	wm -> createFileContent( fileName , text );
}

