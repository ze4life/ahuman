#include "stdafx.h"
#include "ahumantarget.h"

/*#########################################################################*/
/*#########################################################################*/

ModelFiberValidator::ModelFiberValidator() {
	attachLogger();
}

ModelFiberValidator::~ModelFiberValidator() {
}

bool ModelFiberValidator::isValid_GSE_end( XmlNerveInfo& info , MindRegion *src , MindRegion *dst ) {
	bool res = true;

	// src=somatic motor, dst=target
	MindRegionRoleEnum role = src -> getRegionInfo() -> getRole();
	if( role != MIND_REGION_ROLE_FLEXOR && role != MIND_REGION_ROLE_EXTENSOR ) {
		res = false;
		logger.logError( "isValid_GSE_end: invalid source role in link from region=" + src -> getRegionId() + " to region=" + dst -> getRegionId() + ", from nerve=" + info.name );
	}

	role = dst -> getRegionInfo() -> getRole();
	if( role != MIND_REGION_ROLE_TARGET ) {
		res = false;
		logger.logError( "isValid_GSE_end: invalid destination role in link from region=" + src -> getRegionId() + " to region=" + dst -> getRegionId() + ", from nerve=" + info.name );
	}

	return( res );
}

bool ModelFiberValidator::isValid_GSA_begin( XmlNerveInfo& info , MindRegion *src , MindRegion *dst ) {
	bool res = true;

	// src=target, dst=sensory
	MindRegionRoleEnum role = src -> getRegionInfo() -> getRole();
	if( role != MIND_REGION_ROLE_TARGET ) {
		res = false;
		logger.logError( "isValid_GSA_begin: invalid source role in link from region=" + src -> getRegionId() + " to region=" + dst -> getRegionId() + ", from nerve=" + info.name );
	}

	role = dst -> getRegionInfo() -> getRole();
	if( role != MIND_REGION_ROLE_SENSORY ) {
		res = false;
		logger.logError( "isValid_GSA_begin: invalid destination role in link from region=" + src -> getRegionId() + " to region=" + dst -> getRegionId() + ", from nerve=" + info.name );
	}

	return( res );
}

bool ModelFiberValidator::isValid_GSA_end( XmlNerveInfo& info , MindRegion *src , MindRegion *dst ) {
	bool res = true;

	// src=sensory ganglion, dst=not sensory/target
	MindRegionRoleEnum role = src -> getRegionInfo() -> getRole();
	if( role != MIND_REGION_ROLE_SENSORY ) {
		res = false;
		logger.logError( "isValid_GSA_end: invalid source role in link from region=" + src -> getRegionId() + " to region=" + dst -> getRegionId() + ", from nerve=" + info.name );
	}

	role = dst -> getRegionInfo() -> getRole();
	if( role == MIND_REGION_ROLE_TARGET || role == MIND_REGION_ROLE_SENSORY ) {
		res = false;
		logger.logError( "isValid_GSA_end: invalid destination role in link from region=" + src -> getRegionId() + " to region=" + dst -> getRegionId() + ", from nerve=" + info.name );
	}

	return( res );
}
