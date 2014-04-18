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

	createNeurons();
	createLayout();
	createNuclei();
	createTracts();
	createConnectivity();
}

void WikiSpinalCordPage::createNeurons() {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageSpinalCord" );
	String sectionName = wm -> wiki.getProperty( "wikiSpinalCordNeuronsSection" );

	// collect section lines
	StringList lines;
	XmlSpinalCord *cord = wm -> hmindxml.getSpinalCord();

	MapStringToClass<XmlSpinalEndingSet>& endings = cord -> getEndings();
	for( int k = 0; k < endings.count(); k++ ) {
		XmlSpinalEndingSet& set = endings.getClassRefByIndex( k );
		createNeurons_addEndings( set , lines );
	}

	lines.add( "*Fibers by thickness*:" );
	lines.add( "" );
	MapStringToClass<XmlSpinalFiber>& fibers = cord -> getFibers();
	createNeurons_addFibers( 0 , fibers , lines );

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiSpinalCordPage::createNeurons_addEndings( XmlSpinalEndingSet& set , StringList& lines ) {
	lines.add( "*" + set.name + "*:" );
	lines.add( "" );
	String s = wm -> getImageWikiLink( set.imgsrc , set.imgheight );
	lines.add( s );
	lines.add( "" );

	for( int k = 0; k < set.childs.count(); k++ )
		createNeurons_addEndingItem( 0 , set.childs.getClassRefByIndex( k ) , lines );
	
	lines.add( "" );
}

void WikiSpinalCordPage::createNeurons_addEndingItem( int level , XmlSpinalEnding& ending , StringList& lines ) {
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
			XmlSpinalTract& tract = ending.tracts.getClassRefByIndex( k );
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

void WikiSpinalCordPage::createNeurons_addFibers( int level , MapStringToClass<XmlSpinalFiber>& fibers , StringList& lines ) {
	for( int k = 0; k < fibers.count(); k++ ) {
		XmlSpinalFiber& fiber = fibers.getClassRefByIndex( k );
		createNeurons_addFiberInfo( level , fiber , lines );
	}
}

void WikiSpinalCordPage::createNeurons_addFiberInfo( int level , XmlSpinalFiber& fiber , StringList& lines ) {
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
			XmlSpinalTract& tract = fiber.tracts.getClassRefByIndex( k );
			if( k > 0 )
				ts += "; ";
			ts += tract.name;
		}

		s += "; TRACTS={" + ts + "}";
	}

	lines.add( s );

	createNeurons_addFibers( level + 1 , fiber.childs , lines );
}

void WikiSpinalCordPage::createLayout() {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageSpinalCord" );
	String sectionName = wm -> wiki.getProperty( "wikiSpinalCordLayoutSection" );

	// collect section lines
	StringList lines;
	XmlSpinalCord *cord = wm -> hmindxml.getSpinalCord();
	String s = wm -> getImageWikiLink( cord -> getImageSrc() , cord -> getImageHeight() );
	lines.add( s );
	lines.add( "" );

	const char **levels = cord -> getLayoutLevels();
	const char **laminas = cord -> getLayoutLaminas();
	s = "|| *Level/Lamina* ||";
	for( int m = 0; laminas[ m ] != NULL; m++ )
		s += " *" + String( laminas[ m ] ) + "* ||";
	lines.add( s );

	for( int k = 0; levels[ k ] != NULL; k++ ) {
		String line = "|| " + String( levels[ k ] ) + " ||";
		for( int m = 0; laminas[ m ] != NULL; m++ ) {
			StringList& items = cord -> getLayoutCellItems( levels[ k ] , laminas[ m ] );
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
	
	createTracts_addTractTableLines( tractsets , lines );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );

	lines.clear();
	wikiPage = wm -> wiki.getProperty( "wikiPageSpinalCordTracts" );
	for( int k = 0; k < tractsets.count(); k++ ) {
		XmlSpinalTractSet& one = tractsets.getClassRefByIndex( k );
		createTracts_addTractSetLines( one , lines );
	}

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiSpinalCordPage::createTracts_addTractTableLines( MapStringToClass<XmlSpinalTractSet>& tractsets , StringList& lines ) {
	lines.add( "*Tracts overview*:" );
	lines.add( "|| *Tract* || *Name* || *Function* ||" );
	for( int k = 0; k < tractsets.count(); k++ ) {
		XmlSpinalTractSet& one = tractsets.getClassRefByIndex( k );
		createTracts_addTractSetTableLines( one , lines );
	}
}

void WikiSpinalCordPage::createTracts_addTractSetTableLines( XmlSpinalTractSet& ts , StringList& lines ) {
	lines.add( "|| *" + ts.name + "* || || ||" );
	for( int k = 0; k < ts.tracts.count(); k++ ) {
		XmlSpinalTract& tract = ts.tracts.getClassRefByIndex( k );
		createTracts_addTractTableLines( 0 , tract , lines );
	}
}

void WikiSpinalCordPage::createTracts_addTractTableLines( int level , XmlSpinalTract& tract , StringList& lines ) {
	String tname = tract.name;
	if( tract.childs.count() > 0 )
		tname = "*" + tname + "*";

	lines.add( "|| " + String( "----" ).replicate( level ) + " " + wm -> getWikiLink( tract.link , tract.index ) + " || " + 
		tname + " || " + tract.brief + " ||" );

	for( int k = 0; k < tract.childs.count(); k++ ) {
		XmlSpinalTract& child = tract.childs.getClassRefByIndex( k );
		createTracts_addTractTableLines( level + 1 , child , lines );
	}
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
	if( !tract.source.isEmpty() )
		s += "; path: {" + tract.source + "} -> {" + tract.target + "}";
	lines.add( s );

	if( !tract.imgsrc.isEmpty() ) {
		s = String( " " ).replicate( level + 2 ) + "* " + wm -> getImageWikiLink( tract.imgsrc , tract.imgheight );
		lines.add( s );
	}

	// tracts paths
	for( int k = 0; k < tract.paths.count(); k++ ) {
		XmlSpinalTractPath& path = tract.paths.getClassRefByIndex( k );
		createTracts_addTractPathLines( level + 1 , path , lines );
	}

	// child tract
	for( int k = 0; k < tract.childs.count(); k++ ) {
		XmlSpinalTract& child = tract.childs.getClassRefByIndex( k );
		createTracts_addTractLines( level + 1 , child , lines );
	}
}

void WikiSpinalCordPage::createTracts_addTractPathLines( int level , XmlSpinalTractPath& path , StringList& lines ) {
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
		XmlSpinalTractPath& child = path.childs.getClassRefByIndex( k );
		createTracts_addTractPathLines( level + 1 , child , lines );
	}
}

void WikiSpinalCordPage::createNuclei() {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageSpinalCord" );
	String sectionName = wm -> wiki.getProperty( "wikiSpinalCordNucleiSection" );

	// collect section lines
	StringList lines;
	String s;

	StringList items;
	XmlSpinalCord *cord = wm -> hmindxml.getSpinalCord();
	cord -> getLayoutItems( items );
	items.sort();

	// group items by type and fgroup
	MapStringToClass<MapStringToClass<MapStringToClass<XmlHMindElementInfo> > > groups;
	for( int k = 0; k < items.count(); k++ ) {
		String item = items.get( k );
		XmlHMindElementInfo *comp = wm -> hmindxml.getIndexedElement( item );
		MapStringToClass<MapStringToClass<XmlHMindElementInfo> > *tgroup = groups.get( comp -> eltypename );
		if( tgroup == NULL ) {
			tgroup = new MapStringToClass<MapStringToClass<XmlHMindElementInfo> >;
			groups.add( comp -> eltypename , tgroup );
		}

		String fgrouptext = comp -> fgroup;
		if( fgrouptext.isEmpty() )
			fgrouptext = "none";

		MapStringToClass<XmlHMindElementInfo> *fgroup = tgroup -> get( fgrouptext );
		if( fgroup == NULL ) {
			fgroup = new MapStringToClass<XmlHMindElementInfo>;
			tgroup -> add( fgrouptext , fgroup );
		}

		fgroup -> addnew( item , comp );
	}

	// create page content
	for( int k = 0; k < groups.count(); k++ ) {
		MapStringToClass<MapStringToClass<XmlHMindElementInfo> >& tgroup = groups.getClassRefByIndex( k );
		s = String( "*" ) + groups.getKeyByIndex( k ) + "*:";
		lines.add( s );

		for( int m = 0; m < tgroup.count(); m++ ) {
			MapStringToClass<XmlHMindElementInfo>& fgroup = tgroup.getClassRefByIndex( m );

			String fgtext = tgroup.getKeyByIndex( m );
			String prefix;
			if( fgtext.equals( "none" ) )
				prefix = "  * ";
			else {
				s = "  * " + fgtext;
				lines.add( s );
				prefix = "   * ";
			}

			for( int t = 0; t < fgroup.count(); t++ ) {
				XmlHMindElementInfo& comp = fgroup.getClassRefByIndex( t );

				// add comp info
				s = prefix + "*" + comp.index + "*: ";
				s += wm -> getComponentReference( comp.id );
				s += " - " + comp.function;
				if( !comp.notes.isEmpty() )
					s += " (" + comp.notes + ")";

				// layers
				StringList laminas;
				cord -> getLayoutItemLaminas( comp.index , laminas );
				s += "; LAMINA={" + laminas.combine( "," ) + "}";

				// tracts
				StringList tracts;
				cord -> getRegionTracts( comp.id , tracts );
				s += "; TRACTS={" + tracts.combine( "; " ) + "}";

				lines.add( s );
			}
		}
	}

	for( int k = 0; k < groups.count(); k++ )
		groups.getClassRefByIndex( k ).destroy();
	groups.destroy();

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiSpinalCordPage::createConnectivity() {
	// get spinal items
	MapStringToClass<XmlHMindElementInfo> spinalitems;
	StringList layoutitems;
	XmlSpinalCord *cord = wm -> hmindxml.getSpinalCord();
	cord -> getLayoutItems( layoutitems );
	for( int k = 0; k < layoutitems.count(); k++ ) {
		String item = layoutitems.get( k );
		XmlHMindElementInfo *comp = wm -> hmindxml.getIndexedElement( item );
		spinalitems.add( comp -> id , comp );
	}

	MapStringToClass<XmlSpinalTractPath>& paths = cord -> getTractPathMap();

	// collect nuclei
	MapStringToClass<StringList> sensoryNuclei;
	MapStringToClass<StringList> motorNuclei;
	MapStringToClass<StringList> reciprocalNuclei;
	MapStringToClass<StringList> ganglia;
	for( int k = 0; k < paths.count(); k++ ) {
		XmlSpinalTractPath& path = paths.getClassRefByIndex( k );
		createConnectivity_extractNuclei( spinalitems , path , sensoryNuclei , motorNuclei , ganglia );
	}

	for( int k = 0; k < sensoryNuclei.count(); k++ ) {
		String key = sensoryNuclei.getKeyByIndex( k );
		if( motorNuclei.get( key ) != NULL ) {
			StringList *tracts = new StringList;
			tracts -> add( sensoryNuclei.getClassByIndex( k ) );
			tracts -> addnew( motorNuclei.get( key ) );
			reciprocalNuclei.add( key , tracts );
		}
	}

	// output to sections
	createConnectivity_fillSection( "wikiSpinalCordSensoryLinkSection" , sensoryNuclei );
	createConnectivity_fillSection( "wikiSpinalCordMotorLinkSection" , motorNuclei );
	createConnectivity_fillSection( "wikiSpinalCordReciprocalLinkSection" , reciprocalNuclei );
	createConnectivity_fillSection( "wikiSpinalCordGangliaLinkSection" , ganglia );

	sensoryNuclei.destroy();
	motorNuclei.destroy();
	reciprocalNuclei.destroy();
	ganglia.destroy();
}

void WikiSpinalCordPage::createConnectivity_fillSection( String section , MapStringToClass<StringList>& nuclei ) {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageSpinalCord" );
	
	// extract subtree
	MapStringToClass<XmlHMindElementInfo> subtree;
	for( int k = 0; k < nuclei.count(); k++ ) {
		String id = nuclei.getKeyByIndex( k );
		XmlHMindElementInfo& item = wm -> hmindxml.getElementInfo( id );
		subtree.add( item.id , &item );
		for( XmlHMindElementInfo *parent = item.getParent(); parent != NULL; parent = parent -> getParent() )
			subtree.addnew( parent -> id , parent );
	}

	// walk subtree
	StringList lines;
	StringList divs;
	wm -> hmindxml.getDivisions( divs );
	for( int k = 0; k < divs.count(); k++ ) {
		String div = divs.get( k );
		XmlHMindElementInfo& divitem = wm -> hmindxml.getElementInfo( div );
		if( subtree.get( divitem.id ) != NULL )
			createConnectivity_fillSectionTree( nuclei , 0 , divitem , subtree , lines );
	}

	String sectionName = wm -> wiki.getProperty( section );
	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiSpinalCordPage::createConnectivity_fillSectionTree( MapStringToClass<StringList>& nuclei , int level , XmlHMindElementInfo& item , MapStringToClass<XmlHMindElementInfo>& subtree , StringList& lines ) {
	String s = String( " " ).replicate( level + 2 ) + "* " + wm -> getAvailableReference( item.id );
	if( !item.function.isEmpty() )
		s += ": " + item.function;

	// extract tracts
	StringList *tracts = nuclei.get( item.id );
	if( tracts != NULL ) {
		tracts -> sort();
		s += "; TRACTS={" + tracts -> combine( "; " ) + "}";
	}

	lines.add( s );

	StringList elements;
	wm -> hmindxml.getElements( item.id , elements );
	for( int k = 0; k < elements.count(); k++ ) {
		String element = elements.get( k );
		XmlHMindElementInfo *child = subtree.get( element );
		if( child != NULL )
			createConnectivity_fillSectionTree( nuclei , level + 1 , *child , subtree , lines );
	}
}

void WikiSpinalCordPage::createConnectivity_extractNuclei( MapStringToClass<XmlHMindElementInfo>& spinalitems , XmlSpinalTractPath& path , MapStringToClass<StringList>& sensoryNuclei , MapStringToClass<StringList>& motorNuclei , MapStringToClass<StringList>& ganglia ) {
	if( path.type.equals( "sensory" ) ) {
		for( int k = 0; k < path.items.count(); k++ ) {
			String item = path.items.get( k );
			XmlHMindElementInfo& el = wm -> hmindxml.getElementInfo( item );
			if( el.isTarget() || spinalitems.get( item ) != NULL )
				continue;

			if( el.isGanglion() ) {
				createConnectivity_addTract( ganglia , el , path );
				continue;
			}

			// add to sensory if not target/ganglia/spinal
			createConnectivity_addTract( sensoryNuclei , el , path );
			return;
		}
	}
	else
	if( path.type.equals( "motor" ) ) {
		for( int k = path.items.count() - 1; k >= 0; k-- ) {
			String item = path.items.get( k );
			XmlHMindElementInfo& el = wm -> hmindxml.getElementInfo( item );
			if( el.isTarget() || spinalitems.get( item ) != NULL )
				continue;

			if( el.isGanglion() ) {
				createConnectivity_addTract( ganglia , el , path );
				continue;
			}

			// add to motor if not target/ganglia/spinal
			createConnectivity_addTract( motorNuclei , el , path );
			return;
		}
	}
}

void WikiSpinalCordPage::createConnectivity_addTract( MapStringToClass<StringList>& map , XmlHMindElementInfo& comp , XmlSpinalTractPath& path ) {
	StringList *tracts = map.get( comp.id );
	if( tracts == NULL ) {
		tracts = new StringList;
		map.add( comp.id , tracts );
	}

	tracts -> addnew( path.tract.name );
}

