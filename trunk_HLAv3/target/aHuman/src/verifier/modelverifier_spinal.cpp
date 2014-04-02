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
	XmlSpinalCord *sc = hmindxml.getSpinalCord();
	MapStringToClass<XmlSpinalEnding>& endings = sc -> getEndingMap();

	bool checkAll = true;
	for( int k = 0; k < endings.count(); k++ ) {
		XmlSpinalEnding& ending = endings.getClassRefByIndex( k );
		if( !checkSpinal_verifyEndingData( ending ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyEndingData( XmlSpinalEnding& ending ) {
	XmlSpinalCord *sc = hmindxml.getSpinalCord();

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
	XmlSpinalCord *sc = hmindxml.getSpinalCord();
	MapStringToClass<XmlSpinalFiber>& fibers = sc -> getFibers();

	bool checkAll = true;
	for( int k = 0; k < fibers.count(); k++ ) {
		XmlSpinalFiber& fiber = fibers.getClassRefByIndex( k );
		if( !checkSpinal_verifyFiberData( fiber ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyFiberData( XmlSpinalFiber& fiber ) {
	bool checkAll = true;

	XmlSpinalCord *sc = hmindxml.getSpinalCord();

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
		if( sc -> findEnding( item ) == NULL ) {
			logger.logError( "checkSpinal_verifyFiberData: unknown ending=" + item + " in fiber id=" + fiber.id );
			checkAll = false;
		}
	}

	// childs
	for( int k = 0; k < fiber.childs.count(); k++ ) {
		XmlSpinalFiber& child = fiber.childs.getClassRefByIndex( k );
		if( !checkSpinal_verifyFiberData( child ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTracts() {
	XmlSpinalCord *sc = hmindxml.getSpinalCord();

	bool checkAll = true;
	MapStringToClass<XmlSpinalTractSet>& tractsets = sc -> getTracts();
	for( int k = 0; k < tractsets.count(); k++ ) {
		XmlSpinalTractSet& one = tractsets.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractSet( one ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTractSet( XmlSpinalTractSet& ts ) {
	bool checkAll = true;
	for( int k = 0; k < ts.tracts.count(); k++ ) {
		XmlSpinalTract& tract = ts.tracts.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractData( tract ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTractData( XmlSpinalTract& tract ) {
	bool checkAll = true;

	for( int k = 0; k < tract.childs.count(); k++ ) {
		XmlSpinalTract& child = tract.childs.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractData( child ) )
			checkAll = false;
	}

	for( int k = 0; k < tract.paths.count(); k++ ) {
		XmlSpinalTractPath& child = tract.paths.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractPathData( tract , child ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTractPathData( XmlSpinalTract& tract , XmlSpinalTractPath& path ) {
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
	XmlSpinalCord *sc = hmindxml.getSpinalCord();
	for( int k = 0; k < path.endings.count(); k++ ) {
		String ending = path.endings.get( k );
		if( sc -> findEnding( ending ) == NULL ) {
			logger.logError( "checkSpinal_verifyTractPathData: unknown ending=" + ending + " in tract name=" + tract.name );
			checkAll = false;
		}
	}

	for( int k = 0; k < path.fibers.count(); k++ ) {
		String fiber = path.fibers.get( k );
		if( sc -> findFiber( fiber ) == NULL ) {
			logger.logError( "checkSpinal_verifyTractPathData: unknown fiber=" + fiber + " in tract name=" + tract.name );
			checkAll = false;
		}
	}

	for( int k = 0; k < path.childs.count(); k++ ) {
		XmlSpinalTractPath& child = path.childs.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractPathData( tract , child ) )
			checkAll = false;
	}

	return( checkAll );
}

