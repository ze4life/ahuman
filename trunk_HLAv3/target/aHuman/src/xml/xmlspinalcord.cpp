#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

static const char *levels[] = {
	"C1" , "C2" , "C3" , "C4" , "C5" , "C6" , "C7" , "C8" ,
	"T1" , "T2" , "T3" , "T4" , "T5" , "T6" , "T7" , "T8" , "T9" , "T10" , "T11" , "T12" ,
	"L1" , "L2" , "L3" , "L4" , "L5" , 
	"S1" , "S2" , "S3" , "S4" , "S5" , 
	"CX" ,
	NULL
};

static const char *laminas[] = {
	"LO" ,
	"LI" , "LII" , "LIII-IV" , "LV-VI" , "LVIIS" , "LVIIM" , "LVIII" , "LIX" , "LX" ,
	NULL
};

XmlSpinalCord::XmlSpinalCord( XmlHMind *p_hmind ) {
	hmind = p_hmind;

	for( int k = 0; levels[ k ] != NULL; k++ ) {
		MapStringToClass<StringList> *levelData = new MapStringToClass<StringList>;
		data.add( levels[ k ] , levelData );

		for( int m = 0; laminas[ m ] != NULL; m++ )
			levelData -> add( laminas[ m ] , new StringList );
	}
}

XmlSpinalCord::~XmlSpinalCord() {
	for( int k = 0; k < data.count(); k++ ) {
		MapStringToClass<StringList>& item = data.getClassRefByIndex( k );
		item.destroy();
	}
	data.destroy();
	tractsets.destroy();
}

void XmlSpinalCord::load( Xml xmlDiv ) {
	loadFibers( xmlDiv );
	loadEndings( xmlDiv );
	loadLayout( xmlDiv );
	loadTracts( xmlDiv );

	linkFibers();
	linkTracts();
}

void XmlSpinalCord::loadFibers( Xml xmlDiv ) {
	Xml fiberset = xmlDiv.getFirstChild( "fibers" );
	ASSERTMSG( fiberset.exists() , "fibers is not found" );

	for( Xml xmlChild = fiberset.getFirstChild( "fiber" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "fiber" ) ) {
		XmlSpinalFiber *f = new XmlSpinalFiber();
		f -> load( *this , xmlChild );
		fibers.add( f -> id , f );
	}
}

void XmlSpinalCord::loadEndings( Xml xmlDiv ) {
	for( Xml xmlChild = xmlDiv.getFirstChild( "endings" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "endings" ) ) {
		XmlSpinalEndingSet *es = new XmlSpinalEndingSet();
		es -> load( *this , xmlChild );
		endings.add( es -> type , es );
	}
}

void XmlSpinalCord::loadLayout( Xml xmlDiv ) {
	Xml layout = xmlDiv.getFirstChild( "layout" );
	ASSERTMSG( layout.exists() , "layout is not found" );

	imgSrc = layout.getAttribute( "imgsrc" , "" );
	imgHeight = layout.getAttribute( "imgheight" , "" );

	for( Xml xmlChild = layout.getFirstChild( "level" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "level" ) ) {
		String id = xmlChild.getAttribute( "id" );
		MapStringToClass<StringList>& levelData = data.getRef( id );

		loadLayoutLevel( xmlChild , levelData );
	}
}

void XmlSpinalCord::loadLayoutLevel( Xml xmlLevel , MapStringToClass<StringList>& levelData ) {
	for( Xml xmlChild = xmlLevel.getFirstChild( "lamina" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "lamina" ) ) {
		String id = xmlChild.getAttribute( "id" );
		String elements = xmlChild.getAttribute( "elements" );

		StringList& items = levelData.getRef( id );
		StringList parts;
		elements.split( parts , "," );
		for( int k = 0; k < parts.count(); k++ ) {
			String element = parts.get( k );
			ASSERTMSG( hmind -> getIndexedElement( element ) != NULL , "unknown element index=" + element );

			if( items.find( element ) < 0 )
				items.add( element );
		}
	}
}

const char **XmlSpinalCord::getLevels() {
	return( levels );
}

const char **XmlSpinalCord::getLaminas() {
	return( laminas );
}

StringList& XmlSpinalCord::getCellItems( String level , String lamina ) {
	MapStringToClass<StringList>& levelData = data.getRef( level );
	return( levelData.getRef( lamina ) );
}

void XmlSpinalCord::loadTracts( Xml xmlDiv ) {
	for( Xml xmlChild = xmlDiv.getFirstChild( "tracts" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tracts" ) ) {
		XmlSpinalTractSet *ts = new XmlSpinalTractSet();
		ts -> load( *this , xmlChild );
		tractsets.add( ts -> name , ts );
	}
}

XmlSpinalEnding& XmlSpinalCord::getEnding( String id ) {
	XmlSpinalEnding *ending = endingMap.get( id );
	ASSERTMSG( ending != NULL , "getEnding: unable to find ending id=" + id );
	return( *ending );
}

XmlSpinalFiber& XmlSpinalCord::getFiber( String id ) {
	XmlSpinalFiber *fiber = fiberMap.get( id );
	ASSERTMSG( fiber != NULL , "getFiber: unable to find fiber id=" + id );
	return( *fiber );
}

XmlSpinalEnding *XmlSpinalCord::findEnding( String id ) {
	return( endingMap.get( id ) );
}

XmlSpinalFiber *XmlSpinalCord::findFiber( String id ) {
	return( fiberMap.get( id ) );
}

void XmlSpinalCord::addEnding( XmlSpinalEnding *ending ) {
	endingMap.add( ending -> id , ending );
}

void XmlSpinalCord::addFiber( XmlSpinalFiber *fiber ) {
	fiberMap.add( fiber -> id , fiber );
}

void XmlSpinalCord::addTract( XmlSpinalTract *tract ) {
	tractMap.add( tract -> name , tract );
}

void XmlSpinalCord::linkFibers() {
	for( int k = 0; k < fiberMap.count(); k++ ) {
		XmlSpinalFiber& fiber = fiberMap.getClassRefByIndex( k );
		for( int m = 0; m < fiber.endings.count(); m++ ) {
			String endingId = fiber.endings.get( m );
			XmlSpinalEnding *ending = endingMap.get( endingId );
			if( ending != NULL )
				ending -> addFiber( &fiber );
		}
	}
}

void XmlSpinalCord::linkTracts() {
	for( int k = 0; k < tractMap.count(); k++ ) {
		XmlSpinalTract& tract = tractMap.getClassRefByIndex( k );
		linkTractPaths( tract , tract.paths );
	}
}

void XmlSpinalCord::linkTractPaths( XmlSpinalTract& tract , ClassList<XmlSpinalTractPath>& paths ) {
	for( int k = 0; k < paths.count(); k++ ) {
		XmlSpinalTractPath& path = paths.getRef( k );

		for( int m = 0; m < path.endings.count(); m++ ) {
			String endingId = path.endings.get( m );
			XmlSpinalEnding *ending = endingMap.get( endingId );
			if( ending != NULL )
				ending -> addTract( &tract );
		}
		for( int m = 0; m < path.fibers.count(); m++ ) {
			String fiberId = path.fibers.get( m );
			XmlSpinalFiber *fiber = fiberMap.get( fiberId );
			if( fiber != NULL )
				fiber -> addTract( &tract );
		}

		linkTractPaths( tract , path.childs );
	}
}

