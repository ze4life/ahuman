#include "stdafx.h"
#include "xmlhuman.h"

/*#########################################################################*/
/*#########################################################################*/

XmlTracts::XmlTracts( XmlHMind *p_hmind ) {
	hmind = p_hmind;
}

XmlTracts::~XmlTracts() {
	tractsets.destroy();
}

void XmlTracts::load( Xml xml ) {
	loadFibers( xml );
	loadEndings( xml );
	loadTracts( xml );

	linkFibers();
	linkTracts();
}

void XmlTracts::loadFibers( Xml xml ) {
	Xml fiberset = xml.getFirstChild( "fibers" );
	ASSERTMSG( fiberset.exists() , "fibers is not found" );

	for( Xml xmlChild = fiberset.getFirstChild( "fiber" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "fiber" ) ) {
		XmlBrainFiber *f = new XmlBrainFiber( *this , NULL );
		f -> load( xmlChild );
		fibers.add( f -> id , f );
	}
}

void XmlTracts::loadEndings( Xml xml ) {
	Xml endingset = xml.getFirstChild( "endings" );
	ASSERTMSG( endingset.exists() , "endings is not found" );

	for( Xml xmlChild = endingset.getFirstChild( "endings" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "endings" ) ) {
		XmlBrainEndingSet *es = new XmlBrainEndingSet( *this );
		es -> load( xmlChild );
		endings.add( es -> type , es );
	}
}

void XmlTracts::loadTracts( Xml xml ) {
	Xml tractset = xml.getFirstChild( "tracts" );
	ASSERTMSG( tractset.exists() , "tracts is not found" );

	for( Xml xmlChild = tractset.getFirstChild( "tracts" ); xmlChild.exists(); xmlChild = xmlChild.getNextChild( "tracts" ) ) {
		XmlBrainTractSet *ts = new XmlBrainTractSet( *this );
		ts -> load( xmlChild );
		tractsets.add( ts -> name , ts );
	}
}

XmlBrainEnding& XmlTracts::getEnding( String id ) {
	XmlBrainEnding *ending = endingMap.get( id );
	ASSERTMSG( ending != NULL , "getEnding: unable to find ending id=" + id );
	return( *ending );
}

XmlBrainFiber& XmlTracts::getFiber( String id ) {
	XmlBrainFiber *fiber = fiberMap.get( id );
	ASSERTMSG( fiber != NULL , "getFiber: unable to find fiber id=" + id );
	return( *fiber );
}

XmlBrainEnding *XmlTracts::findEnding( String id ) {
	return( endingMap.get( id ) );
}

XmlBrainFiber *XmlTracts::findFiber( String id ) {
	return( fiberMap.get( id ) );
}

void XmlTracts::addEnding( XmlBrainEnding *ending ) {
	endingMap.add( ending -> id , ending );
}

void XmlTracts::addFiber( XmlBrainFiber *fiber ) {
	fiberMap.add( fiber -> id , fiber );
}

void XmlTracts::addTract( XmlBrainTract *tract ) {
	tractMap.add( tract -> name , tract );
}

void XmlTracts::addPath( XmlBrainTractPath *path ) {
	pathMap.add( path -> id , path );
}

void XmlTracts::linkFibers() {
	for( int k = 0; k < fiberMap.count(); k++ ) {
		XmlBrainFiber& fiber = fiberMap.getClassRefByIndex( k );
		for( int m = 0; m < fiber.endings.count(); m++ ) {
			String endingId = fiber.endings.get( m );
			XmlBrainEnding *ending = endingMap.get( endingId );
			if( ending != NULL )
				ending -> addFiber( &fiber );
		}
	}
}

void XmlTracts::linkTracts() {
	for( int k = 0; k < tractMap.count(); k++ ) {
		XmlBrainTract& tract = tractMap.getClassRefByIndex( k );
		linkTractPaths( tract , tract.paths );
	}
}

void XmlTracts::linkTractPaths( XmlBrainTract& tract , MapStringToClass<XmlBrainTractPath>& paths ) {
	for( int k = 0; k < paths.count(); k++ ) {
		XmlBrainTractPath& path = paths.getClassRefByIndex( k );

		for( int m = 0; m < path.endings.count(); m++ ) {
			String endingId = path.endings.get( m );
			XmlBrainEnding *ending = endingMap.get( endingId );
			if( ending != NULL )
				ending -> addTract( &tract );
		}
		for( int m = 0; m < path.fibers.count(); m++ ) {
			String fiberId = path.fibers.get( m );
			XmlBrainFiber *fiber = fiberMap.get( fiberId );
			if( fiber != NULL )
				fiber -> addTract( &tract );
		}

		linkTractPaths( tract , path.childs );
	}
}

void XmlTracts::getRegionTracts( String region , StringList& regionTracts ) {
	for( int k = 0; k < tractMap.count(); k++ ) {
		XmlBrainTract& tract = tractMap.getClassRefByIndex( k );
		if( tract.referencesRegion( region ) )
			regionTracts.add( tract.name );
	}
}

