#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

HtmHelper::HtmHelper( Logger& p_logger )
:	logger( p_logger )
{
}

HtmHelper::~HtmHelper()
{
}

void HtmHelper::showCortex( HtmCortex *cortex )
{
	int n = cortex -> getLayerCount();
	logger.logDebug( String( "CORTEX: nLayers=" ) + n + 
		", sizeH=" + cortex -> getInputsSizeH() + 
		", sizeV=" + cortex -> getInputsSizeV() );
	for( int k = 0; k < n; k++ )
		{
			HtmLayer *layer = cortex -> getLayer( k );
			logger.logDebug( String( "LAYER " ) + k + 
				": sizeH=" + layer -> getSizeH() + 
				", sizeV=" + layer -> getSizeV() +
				", childSizeH=" + layer -> getChildSizeH() + 
				", childSizeV=" + layer -> getChildSizeV() );
		}
}

