#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkSpinal() {
	bool checkAll = true;

	if( !checkSpinal_verifyEndings() )
		checkAll = false;
	if( !checkSpinal_verifyFibers() )
		checkAll = false;
	if( !checkSpinal_verifyTracts() )
		checkAll = false;

	if( checkAll )
		logger.logInfo( "checkSpinal: SPINAL CORD IS OK" );
	else
		logger.logInfo( "checkSpinal: SPINAL CORD HAS ERRORS" );
}

bool ModelVerifier::checkSpinal_verifyEndings() {
	XmlTracts *tm = hmindxml.getTracts();
	MapStringToClass<XmlBrainEnding>& endings = tm -> getEndingMap();

	bool checkAll = true;
	for( int k = 0; k < endings.count(); k++ ) {
		XmlBrainEnding& ending = endings.getClassRefByIndex( k );
		if( !checkSpinal_verifyEndingData( ending ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyEndingData( XmlBrainEnding& ending ) {
	// ignore non-leaf item
	if( ending.childs.count() > 0 )
		return( true );

	bool checkAll = true;

	if( ending.fibers.count() == 0 ) {
		logger.logError( "checkSpinal_verifyEndingData: no fibers assigned to ending=" + ending.id );
		checkAll = false;
	}

	if( ending.tracts.count() == 0 ) {
		logger.logError( "checkSpinal_verifyEndingData: no tracts assigned to ending=" + ending.id );
		checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyFibers() {
	XmlTracts *tm = hmindxml.getTracts();
	MapStringToClass<XmlBrainFiber>& fibers = tm -> getFibers();

	bool checkAll = true;
	for( int k = 0; k < fibers.count(); k++ ) {
		XmlBrainFiber& fiber = fibers.getClassRefByIndex( k );
		if( !checkSpinal_verifyFiberData( fiber ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyFiberData( XmlBrainFiber& fiber ) {
	bool checkAll = true;

	XmlTracts *tm = hmindxml.getTracts();

	// check leaf items
	if( fiber.childs.count() == 0 ) {
		if( fiber.endings.count() == 0 ) {
			logger.logError( "checkSpinal_verifyFiberData: no endings assigned to fiber=" + fiber.id );
			checkAll = false;
		}

		if( fiber.tracts.count() == 0 ) {
			logger.logError( "checkSpinal_verifyFiberData: no tracts assigned to fiber=" + fiber.id );
			checkAll = false;
		}
	}

	for( int k = 0; k < fiber.endings.count(); k++ ) {
		String item = fiber.endings.get( k );

		// find ending
		if( tm -> findEnding( item ) == NULL ) {
			logger.logError( "checkSpinal_verifyFiberData: unknown ending=" + item + " in fiber id=" + fiber.id );
			checkAll = false;
		}
	}

	// childs
	for( int k = 0; k < fiber.childs.count(); k++ ) {
		XmlBrainFiber& child = fiber.childs.getClassRefByIndex( k );
		if( !checkSpinal_verifyFiberData( child ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTracts() {
	XmlTracts *tm = hmindxml.getTracts();

	bool checkAll = true;
	MapStringToClass<XmlBrainTractSet>& tractsets = tm -> getTracts();
	for( int k = 0; k < tractsets.count(); k++ ) {
		XmlBrainTractSet& one = tractsets.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractSet( one ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTractSet( XmlBrainTractSet& ts ) {
	bool checkAll = true;
	for( int k = 0; k < ts.tracts.count(); k++ ) {
		XmlBrainTract& tract = ts.tracts.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractData( tract ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTractData( XmlBrainTract& tract ) {
	bool checkAll = true;

	for( int k = 0; k < tract.childs.count(); k++ ) {
		XmlBrainTract& child = tract.childs.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractData( child ) )
			checkAll = false;
	}

	for( int k = 0; k < tract.paths.count(); k++ ) {
		XmlBrainTractPath& child = tract.paths.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractPathData( tract , child ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTractPathData( XmlBrainTract& tract , XmlBrainTractPath& path ) {
	bool checkAll = true;

	// check leaf items
	if( path.childs.count() == 0 ) {
		if( path.endings.count() == 0 ) {
			logger.logError( "checkSpinal_verifyTractPathData: no endings assigned to fiber=" + path.id );
			checkAll = false;
		}

		if( path.fibers.count() == 0 ) {
			logger.logError( "checkSpinal_verifyTractPathData: no tracts assigned to fiber=" + path.id );
			checkAll = false;
		}
	}

	// chech fibers and endings
	XmlTracts *tm = hmindxml.getTracts();
	for( int k = 0; k < path.endings.count(); k++ ) {
		String ending = path.endings.get( k );
		if( tm -> findEnding( ending ) == NULL ) {
			logger.logError( "checkSpinal_verifyTractPathData: unknown ending=" + ending + " in tract name=" + tract.name );
			checkAll = false;
		}
	}

	for( int k = 0; k < path.fibers.count(); k++ ) {
		String fiber = path.fibers.get( k );
		if( tm -> findFiber( fiber ) == NULL ) {
			logger.logError( "checkSpinal_verifyTractPathData: unknown fiber=" + fiber + " in tract name=" + tract.name );
			checkAll = false;
		}
	}

	for( int k = 0; k < path.childs.count(); k++ ) {
		XmlBrainTractPath& child = path.childs.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractPathData( tract , child ) )
			checkAll = false;
	}

	return( checkAll );
}

