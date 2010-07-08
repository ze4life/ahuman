#include "htm_custom.h"

/*#########################################################################*/
/*#########################################################################*/

AILibBNVariant *AILibBNVariant::createHtmCustom()
{
	LibHtmCustom *lib = new LibHtmCustom();
	lib -> init();
	return( lib );
}

/*#########################################################################*/
/*#########################################################################*/

void LibHtmCustom::init() {
	// register serialisable classes
	HtmCortex::createSerializeObject();
}
