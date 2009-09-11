#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

HtmLayerMemory::HtmLayerMemory()
{
}

HtmLayerMemory::~HtmLayerMemory()
{
	sequences.destroy();
}

