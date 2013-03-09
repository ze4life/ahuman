#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiRegionPage::WikiRegionPage( WikiMaker *p_wm , String p_wikiDir , MindRegionDef *p_region ) {
	attachLogger();
	wm = p_wm;
	wikiDir = p_wikiDir;
	region = p_region;
	wm -> hmindxml.getElementInfo( region -> getName() , info );
}

WikiRegionPage::~WikiRegionPage() {
}

void WikiRegionPage::execute() {
	createHeading();
	createChildTableSection();
	createConnectivitySection();
	createThirdpartyAndReferencesSection();
}

void WikiRegionPage::createHeading() {
	StringList lines;
	lines.add( "#summary " + info.name );
	String areaWikiPage = wm -> getAreaPage( region -> getArea() -> getAreaId() );
	lines.add( "@@[Home] -> [BiologicalLifeResearch] -> [" + areaWikiPage + "] -> [" + info.id + "]" );
	lines.add( "----" );
	lines.add( "" );
	lines.add( "This page covers biological details of component " + info.name + "." );
	lines.add( "Region is part of aHuman target integrated biological model." );
	lines.add( "" );

	String wikiPage = wm -> getRegionPage( info.id );
	wm -> updateFileHeading( wikiDir , wikiPage , lines );
}

void WikiRegionPage::createChildTableSection() {
}

void WikiRegionPage::createConnectivitySection() {
}

void WikiRegionPage::createThirdpartyAndReferencesSection() {
}

