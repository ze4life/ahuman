#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

WikiNerveMainPage::WikiNerveMainPage( WikiMaker *p_wm ) {
	attachLogger();
	wm = p_wm;
}

WikiNerveMainPage::~WikiNerveMainPage() {
}

void WikiNerveMainPage::execute() {
	bool createMainPage = wm -> wiki.getBooleanProperty( "createNervePages" , true );
	if( createMainPage == false ) {
		logger.logInfo( "skip creating nerve main page" );
		return;
	}

	String wikiDir = wm -> wiki.getProperty( "wikiPath" );
	String wikiPage = wm -> wiki.getProperty( "wikiPageNerveMain" );
	String sectionName = wm -> wiki.getProperty( "wikiPageNerveMainSection" );

	// get nerves from pns
	ClassList<XmlNerveInfo>& divs = wm -> nervesxml.getDivisions();

	// collect model circuit section lines
	StringList lines;
	for( int k = 0; k < divs.count(); k++ ) {
		XmlNerveInfo& div = divs.getRef( k );
		if( !div.tree )
			continue;

		String divPage = div.origin;
		addNerve( 0 , divPage , div , lines );
	}

	wm -> updateFileSection( wikiDir , wikiPage , sectionName , lines );
}

void WikiNerveMainPage::addNerve( int level , String divPage , XmlNerveInfo& nerve , StringList& lines ) {
	String prefix = "  * ";
	if( level > 0 )
		prefix = String( " " ).replicate( level ) + prefix;

	String ns = "[" + divPage + " " + nerve.name + "]";
	if( !nerve.modality.isEmpty() )
		ns += " - " + nerve.modality;

	lines.add( prefix + ns );

	for( int k = 0; k < nerve.childs.count(); k++ ) {
		XmlNerveInfo *nc = nerve.childs.getClassByIndex( k );
		addNerve( level + 1 , divPage , *nc , lines );
	}
}

