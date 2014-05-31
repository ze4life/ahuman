#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiCategoryPage::WikiCategoryPage( WikiMaker *p_wm ) {
	attachLogger();
	wm = p_wm;
}

WikiCategoryPage::~WikiCategoryPage() {
}

void WikiCategoryPage::execute( String category , String settingPage ) {
	bool createMainPage = wm -> wiki.getBooleanProperty( "createMainPages" , false );
	if( createMainPage == false ) {
		logger.logInfo( "skip creating category page" );
		return;
	}

	String wikiPage = wm -> wiki.getProperty( settingPage );
	XmlBrainCategory *braincategory = wm -> hmindxml.getCategory( category );

	createRegions( braincategory , wikiPage );
	createConnectivity( braincategory , wikiPage );
}

void WikiCategoryPage::createRegions( XmlBrainCategory *braincategory , String wikiPage ) {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String sectionName = wm -> wiki.getProperty( "wikiCategoryRegionSection" );

	// collect section lines
	StringList lines;
	String s;

	XmlTracts *tm = wm -> hmindxml.getTracts();
	StringList items;
	braincategory -> getMappedItems( items );
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

				// tracts
				StringList tracts;
				tm -> getRegionTracts( comp.id , tracts );
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

void WikiCategoryPage::createConnectivity( XmlBrainCategory *braincategory , String wikiPage ) {
	// get spinal items
	MapStringToClass<XmlHMindElementInfo> spinalitems;
	StringList items;
	braincategory -> getMappedItems( items );
	for( int k = 0; k < items.count(); k++ ) {
		String item = items.get( k );
		XmlHMindElementInfo *comp = wm -> hmindxml.getIndexedElement( item );
		spinalitems.add( comp -> id , comp );
	}

	XmlTracts *tm = wm -> hmindxml.getTracts();
	MapStringToClass<XmlBrainTractPath>& paths = tm -> getTractPathMap();

	// collect nuclei
	MapStringToClass<StringList> sensoryNuclei;
	MapStringToClass<StringList> motorNuclei;
	MapStringToClass<StringList> reciprocalNuclei;
	MapStringToClass<StringList> ganglia;
	for( int k = 0; k < paths.count(); k++ ) {
		XmlBrainTractPath& path = paths.getClassRefByIndex( k );
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
	createConnectivity_fillSection( wikiPage , "wikiCategorySensoryLinkSection" , sensoryNuclei );
	createConnectivity_fillSection( wikiPage , "wikiCategoryMotorLinkSection" , motorNuclei );
	createConnectivity_fillSection( wikiPage , "wikiCategoryReciprocalLinkSection" , reciprocalNuclei );
	createConnectivity_fillSection( wikiPage , "wikiCategoryGangliaLinkSection" , ganglia );

	sensoryNuclei.destroy();
	motorNuclei.destroy();
	reciprocalNuclei.destroy();
	ganglia.destroy();
}

void WikiCategoryPage::createConnectivity_fillSection( String wikiPage , String section , MapStringToClass<StringList>& nuclei ) {
	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	
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

void WikiCategoryPage::createConnectivity_fillSectionTree( MapStringToClass<StringList>& nuclei , int level , XmlHMindElementInfo& item , MapStringToClass<XmlHMindElementInfo>& subtree , StringList& lines ) {
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

void WikiCategoryPage::createConnectivity_extractNuclei( MapStringToClass<XmlHMindElementInfo>& spinalitems , XmlBrainTractPath& path , MapStringToClass<StringList>& sensoryNuclei , MapStringToClass<StringList>& motorNuclei , MapStringToClass<StringList>& ganglia ) {
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

void WikiCategoryPage::createConnectivity_addTract( MapStringToClass<StringList>& map , XmlHMindElementInfo& comp , XmlBrainTractPath& path ) {
	StringList *tracts = map.get( comp.id );
	if( tracts == NULL ) {
		tracts = new StringList;
		map.add( comp.id , tracts );
	}

	tracts -> addnew( path.tract.name );
}
