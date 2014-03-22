#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

void ModelVerifier::checkSpinal() {
	bool checkAll = true;
	if( !checkSpinal_verifyFibers() )
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

