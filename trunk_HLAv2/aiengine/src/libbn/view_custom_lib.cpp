#include "libbn_impl.h"
#include "view_custom/htm_custom.h"

ViewCustomLibBN::ViewCustomLibBN()
:	AILibBNVariant( "ViewCustom" )
{
	// register serialisable classes
	HtmCortex::createSerializeObject();
}

ViewCustomLibBN::~ViewCustomLibBN()
{
}

Object *ViewCustomLibBN::createBeliefNetwork()
{
	HtmCortex *libobj = new HtmCortex();
	return( libobj );
}

void ViewCustomLibBN::deleteObject( Object *object )
{
	HtmCortex *libobj = ( HtmCortex * )object;
	delete libobj;
}

/*#########################################################################*/
/*#########################################################################*/

AILibBNVariant *AILibBNImpl::createViewCustomLib() {
	return( new ViewCustomLibBN() );
}
