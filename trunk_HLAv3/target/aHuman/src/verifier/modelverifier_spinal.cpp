#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkSpinal() {
	bool checkAll = true;
	if( !checkSpinal_verifyFibers() )
		checkAll = false;
	if( !checkSpinal_verifyTracts() )
		checkAll = false;

	if( checkAll )
		logger.logInfo( "checkSpinal: SPINAL CORD IS OK" );
	else
		logger.logInfo( "checkSpinal: SPINAL CORD HAS ERRORS" );
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
	XmlSpinalCord *sc = hmindxml.getSpinalCord();

	bool checkAll = true;
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
	for( int k = 0; k < tract.tracts.count(); k++ ) {
		XmlSpinalTract& child = tract.tracts.getClassRefByIndex( k );
		if( !checkSpinal_verifyTractData( child ) )
			checkAll = false;
	}
	for( int k = 0; k < tract.paths.count(); k++ ) {
		XmlSpinalTractPath& child = tract.paths.getRef( k );
		if( !checkSpinal_verifyTractPathData( tract , child ) )
			checkAll = false;
	}

	return( checkAll );
}

bool ModelVerifier::checkSpinal_verifyTractPathData( XmlSpinalTract& tract , XmlSpinalTractPath& path ) {
	bool checkAll = true;

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
		XmlSpinalTractPath& child = path.childs.getRef( k );
		if( !checkSpinal_verifyTractPathData( tract , child ) )
			checkAll = false;
	}

	return( checkAll );
}

