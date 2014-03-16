#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiSpinalCordPage::WikiSpinalCordPage( WikiMaker *p_wm ) {
	attachLogger();
	wm = p_wm;
}

WikiSpinalCordPage::~WikiSpinalCordPage() {
}

void WikiSpinalCordPage::execute() {
	bool createMainPage = wm -> wiki.getBooleanProperty( "createMainPages" , false );
	if( createMainPage == false ) {
		logger.logInfo( "skip creating spinal cord page" );
		return;
	}

	createLayout();
	createTracts();
}

void WikiSpinalCordPage::createLayout() {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageSpinalCord" );
	String sectionName = wm -> wiki.getProperty( "wikiSpinalCordLayoutSection" );

	// collect section lines
	StringList lines;
	XmlSpinalCord *cord = wm -> hmindxml.getSpinalCord();
	String s = wm -> getImageWikiLink( cord -> getImageSrc() , "" );
	lines.add( s );
	lines.add( "" );

	const char **levels = cord -> getLevels();
	const char **laminas = cord -> getLaminas();
	s = "|| *Level/Lamina* ||";
	for( int m = 0; laminas[ m ] != NULL; m++ )
		s += " *" + String( laminas[ m ] ) + "* ||";
	lines.add( s );

	for( int k = 0; levels[ k ] != NULL; k++ ) {
		String line = "|| " + String( levels[ k ] ) + " ||";
		for( int m = 0; laminas[ m ] != NULL; m++ ) {
			StringList& items = cord -> getCellItems( levels[ k ] , laminas[ m ] );
			if( items.count() > 0 )
				line += " " + items.combine( "," ) + " ||";
			else
				line += " ||";
		}
		lines.add( line );
	}

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiSpinalCordPage::createTracts() {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageSpinalCord" );
	String sectionName = wm -> wiki.getProperty( "wikiSpinalCordTractsSection" );

	// collect section lines
	StringList lines;
	XmlSpinalCord *cord = wm -> hmindxml.getSpinalCord();
	
	MapStringToClass<XmlSpinalTractSet>& tractsets = cord -> getTracts();
	for( int k = 0; k < tractsets.count(); k++ ) {
		XmlSpinalTractSet& one = tractsets.getClassRefByIndex( k );
		createTracts_addTractSetLines( one , lines );
	}

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiSpinalCordPage::createTracts_addTractSetLines( XmlSpinalTractSet& ts , StringList& lines ) {
	lines.add( "TRACT SET: *" + ts.name + "*" );
	lines.add( "" );
	String s = wm -> getImageWikiLink( ts.imgsrc , ts.imgheight );
	lines.add( s );
	lines.add( "" );

	for( int k = 0; k < ts.tracts.count(); k++ ) {
		XmlSpinalTract& tract = ts.tracts.getClassRefByIndex( k );
		createTracts_addTractLines( 0 , tract , lines );
	}
}

void WikiSpinalCordPage::createTracts_addTractLines( int level , XmlSpinalTract& tract , StringList& lines ) {
	// tract info
	String sname = "TRACT";
	if( !tract.index.isEmpty() )
		sname += " " + tract.index;

	String s = String( " " ).replicate( level + 1 ) + "* " + wm -> getWikiLink( tract.link , sname ) + ": " + wm -> getWikiBold( tract.name );
	if( !tract.synonyms.isEmpty() )
		s += " (" + tract.synonyms + ")";
	s += "; " + tract.function;
	if( !tract.notes.isEmpty() )
		s += " (" + tract.notes + ")";
	if( tract.final )
		s += "; path: {" + tract.source + "} -> {" + tract.target + "}";
	lines.add( s );

	// tracts paths
	for( int k = 0; k < tract.paths.count(); k++ ) {
		XmlSpinalTractPath& path = tract.paths.getRef( k );
		createTracts_addTractPathLines( level + 1 , path , lines );
	}

	// child tract
	for( int k = 0; k < tract.tracts.count(); k++ ) {
		XmlSpinalTract& child = tract.tracts.getClassRefByIndex( k );
		createTracts_addTractLines( level + 1 , child , lines );
	}
}

void WikiSpinalCordPage::createTracts_addTractPathLines( int level , XmlSpinalTractPath& path , StringList& lines ) {
	String s = String( " " ).replicate( level + 1 ) + "* " + path.function + " (" + path.pathway + "/" + path.fibers.combine(",") + "): ";

	for( int k = 0; k < path.items.count(); k++ ) {
		if( k > 0 )
			s += " -> ";
		s += wm -> getComponentReference( path.items.get( k ) );
	}

	lines.add( s );

	for( int k = 0; k < path.childs.count(); k++ ) {
		XmlSpinalTractPath& child = path.childs.getRef( k );
		createTracts_addTractPathLines( level + 1 , child , lines );
	}
}

