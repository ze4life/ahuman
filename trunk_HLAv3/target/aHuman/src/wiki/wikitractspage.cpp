#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiTractsPage::WikiTractsPage( WikiMaker *p_wm ) {
	attachLogger();
	wm = p_wm;
}

WikiTractsPage::~WikiTractsPage() {
}

void WikiTractsPage::execute() {
	bool createMainPage = wm -> wiki.getBooleanProperty( "createMainPages" , false );
	if( createMainPage == false ) {
		logger.logInfo( "skip creating tracts page" );
		return;
	}

	createNeurons();
	createTracts();
}

void WikiTractsPage::createTracts() {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageTracts" );
	String sectionName = wm -> wiki.getProperty( "wikiTractsListSection" );

	// collect section lines
	StringList lines;
	XmlTracts *tm = wm -> hmindxml.getTracts();
	MapStringToClass<XmlBrainTractSet>& tractsets = tm -> getTracts();
	
	createTracts_addTractTableLines( tractsets , lines );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );

	lines.clear();
	for( int k = 0; k < tractsets.count(); k++ ) {
		XmlBrainTractSet& one = tractsets.getClassRefByIndex( k );
		createTracts_addTractSetLines( one , lines );
	}

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiTractsPage::createTracts_addTractTableLines( MapStringToClass<XmlBrainTractSet>& tractsets , StringList& lines ) {
	lines.add( "*Tracts overview*:" );
	lines.add( "|| *Tract* || *Name* || *Function* ||" );
	for( int k = 0; k < tractsets.count(); k++ ) {
		XmlBrainTractSet& one = tractsets.getClassRefByIndex( k );
		createTracts_addTractSetTableLines( one , lines );
	}
}

void WikiTractsPage::createTracts_addTractSetTableLines( XmlBrainTractSet& ts , StringList& lines ) {
	lines.add( "|| *" + ts.name + "* || || ||" );
	for( int k = 0; k < ts.tracts.count(); k++ ) {
		XmlBrainTract& tract = ts.tracts.getClassRefByIndex( k );
		createTracts_addTractTableLines( 0 , tract , lines );
	}
}

void WikiTractsPage::createTracts_addTractTableLines( int level , XmlBrainTract& tract , StringList& lines ) {
	String tname = tract.name;
	if( tract.childs.count() > 0 )
		tname = "*" + tname + "*";

	lines.add( "|| " + String( "----" ).replicate( level ) + " " + wm -> getWikiLink( tract.link , tract.index ) + " || " + 
		tname + " || " + tract.brief + " ||" );

	for( int k = 0; k < tract.childs.count(); k++ ) {
		XmlBrainTract& child = tract.childs.getClassRefByIndex( k );
		createTracts_addTractTableLines( level + 1 , child , lines );
	}
}

void WikiTractsPage::createTracts_addTractSetLines( XmlBrainTractSet& ts , StringList& lines ) {
	lines.add( "TRACT SET: *" + ts.name + "*" );
	lines.add( "" );
	String s = wm -> getImageWikiLink( ts.imgsrc , ts.imgheight );
	lines.add( s );
	lines.add( "" );

	for( int k = 0; k < ts.tracts.count(); k++ ) {
		XmlBrainTract& tract = ts.tracts.getClassRefByIndex( k );
		createTracts_addTractLines( 0 , tract , lines );
	}
}

void WikiTractsPage::createTracts_addTractLines( int level , XmlBrainTract& tract , StringList& lines ) {
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
	if( !tract.source.isEmpty() )
		s += "; path: {" + tract.source + "} -> {" + tract.target + "}";
	lines.add( s );

	if( !tract.imgsrc.isEmpty() ) {
		s = String( " " ).replicate( level + 2 ) + "* " + wm -> getImageWikiLink( tract.imgsrc , tract.imgheight );
		lines.add( s );
	}

	// tracts paths
	for( int k = 0; k < tract.paths.count(); k++ ) {
		XmlBrainTractPath& path = tract.paths.getClassRefByIndex( k );
		createTracts_addTractPathLines( level + 1 , path , lines );
	}

	// child tract
	for( int k = 0; k < tract.childs.count(); k++ ) {
		XmlBrainTract& child = tract.childs.getClassRefByIndex( k );
		createTracts_addTractLines( level + 1 , child , lines );
	}
}

void WikiTractsPage::createTracts_addTractPathLines( int level , XmlBrainTractPath& path , StringList& lines ) {
	String s = String( " " ).replicate( level + 1 ) + "* path *" + path.id + "*: " + path.function + " (" + path.pathway + ")" + 
		"; FIBERS={" + path.fibers.combine("; ") + "}" + 
		", ENDINGS={" + path.endings.combine(",") + "}: ";

	for( int k = 0; k < path.items.count(); k++ ) {
		if( k > 0 )
			s += " -> ";
		s += wm -> getComponentReference( path.items.get( k ) );
	}

	lines.add( s );

	for( int k = 0; k < path.childs.count(); k++ ) {
		XmlBrainTractPath& child = path.childs.getClassRefByIndex( k );
		createTracts_addTractPathLines( level + 1 , child , lines );
	}
}

void WikiTractsPage::createNeurons() {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageTracts" );
	String sectionName = wm -> wiki.getProperty( "wikiTractsNeuronsSection" );

	// collect section lines
	StringList lines;
	XmlTracts *tm = wm -> hmindxml.getTracts();

	MapStringToClass<XmlBrainEndingSet>& endings = tm -> getEndings();
	for( int k = 0; k < endings.count(); k++ ) {
		XmlBrainEndingSet& set = endings.getClassRefByIndex( k );
		createNeurons_addEndings( set , lines );
	}

	lines.add( "*Fibers by thickness*:" );
	lines.add( "" );
	MapStringToClass<XmlBrainFiber>& fibers = tm -> getFibers();
	createNeurons_addFibers( 0 , fibers , lines );

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiTractsPage::createNeurons_addEndings( XmlBrainEndingSet& set , StringList& lines ) {
	lines.add( "*" + set.name + "*:" );
	lines.add( "" );
	String s = wm -> getImageWikiLink( set.imgsrc , set.imgheight );
	lines.add( s );
	lines.add( "" );

	for( int k = 0; k < set.childs.count(); k++ )
		createNeurons_addEndingItem( 0 , set.childs.getClassRefByIndex( k ) , lines );
	
	lines.add( "" );
}

void WikiTractsPage::createNeurons_addEndingItem( int level , XmlBrainEnding& ending , StringList& lines ) {
	String s = String( " " ).replicate( level + 1 ) + "* *" + ending.name + "*";
	if( !ending.id.isEmpty() )
		s += " (" + ending.id + ")";
	if( !ending.function.isEmpty() ) {
		s += ": " + ending.function;
		if( !ending.notes.isEmpty() )
			s += " (" + ending.notes + ")";
	}

	if( ending.fibers.count() > 0 )
		s += "; FIBERS={" + ending.fibers.combine( "; " ) + "}";

	if( ending.tracts.count() > 0 ) {
		String ts;
		for( int k = 0; k < ending.tracts.count(); k++ ) {
			XmlBrainTract& tract = ending.tracts.getClassRefByIndex( k );
			if( k > 0 )
				ts += "; ";
			ts += tract.name;
		}

		s += "; TRACTS={" + ts + "}";
	}

	lines.add( s );

	for( int k = 0; k < ending.childs.count(); k++ )
		createNeurons_addEndingItem( level + 1 , ending.childs.getClassRefByIndex( k ) , lines );
}

void WikiTractsPage::createNeurons_addFibers( int level , MapStringToClass<XmlBrainFiber>& fibers , StringList& lines ) {
	for( int k = 0; k < fibers.count(); k++ ) {
		XmlBrainFiber& fiber = fibers.getClassRefByIndex( k );
		createNeurons_addFiberInfo( level , fiber , lines );
	}
}

void WikiTractsPage::createNeurons_addFiberInfo( int level , XmlBrainFiber& fiber , StringList& lines ) {
	String s = String( " " ).replicate( level + 1 ) + "* *" + fiber.id + "*";
	if( !fiber.name.isEmpty() )
		s += " - " + fiber.name;
	if( !fiber.type.isEmpty() ) {
		s += " (" + fiber.type;
		if( !fiber.mcm.isEmpty() )
			s += ", " + fiber.mcm;
		if( !fiber.msec.isEmpty() )
			s += ", " + fiber.msec;
		s += ")";
	}

	if( !fiber.function.isEmpty() ) {
		s += ": " + fiber.function;
		if( !fiber.notes.isEmpty() )
			s += " (" + fiber.notes + ")";
	}

	if( fiber.endings.count() > 0 )
		s += "; ENDINGS={" + fiber.endings.combine( "," ) + "}";

	if( fiber.tracts.count() > 0 ) {
		String ts;
		for( int k = 0; k < fiber.tracts.count(); k++ ) {
			XmlBrainTract& tract = fiber.tracts.getClassRefByIndex( k );
			if( k > 0 )
				ts += "; ";
			ts += tract.name;
		}

		s += "; TRACTS={" + ts + "}";
	}

	lines.add( s );

	createNeurons_addFibers( level + 1 , fiber.childs , lines );
}
