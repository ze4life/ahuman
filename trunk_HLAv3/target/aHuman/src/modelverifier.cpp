#include "stdafx.h"

/*#########################################################################*/
/*#########################################################################*/

ModelVerifier::ModelVerifier() {
	attachLogger();
}

ModelVerifier::~ModelVerifier() {
}

void ModelVerifier::verify( Xml modelArea ) {
	logger.logInfo( "verify mind model ..." );
}
