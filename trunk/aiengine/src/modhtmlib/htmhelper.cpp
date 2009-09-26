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
				", childSizeV=" + layer -> getChildSizeV() +
				", history=" + layer -> getMaxHistory() );
		}
}

void HtmHelper::showCortexMemorySize( HtmCortex *cortex )
{
	int n = cortex -> getLayerCount();
	String s = "Memory size by layer - ";
	for( int k = 0; k < n; k++ )
		{
			HtmLayer *layer = cortex -> getLayer( k );
			HtmLayerMemory *lm = layer -> getMemory();
			int v = lm -> getSequenceCount();
			if( k > 0 )
				s += ", ";

			s += k;
			s += "=";
			s += v;

			int maxSize = lm -> getMaxSize();
			s += "/";
			s += maxSize;
		}

	logger.logDebug( String( "CORTEX: " ) + s );
}

void HtmHelper::showSequence( const char *name , HtmSequence *cs )
{
	String s = name;
	s += ": ";

	if( cs == NULL )
		{
			logger.logDebug( s + "(null)" );
			return;
		}

	if( cs -> storedSequence() )
		{
			s += "id=";
			s += cs -> getId();
			s += ", usage=";
			s += cs -> getUsage();
			s += ", ";
		}
	else
	if( cs -> isEmpty() )
		{
			logger.logDebug( s + "(empty)" );
			return;
		}

	s += "data=";
	int cc = cs -> getChildCount();
	int size;
	int *pv = cs -> getData( &size );

	for( int k = 0; k < cs -> getHistoryCount(); k++ )
		{
			if( k > 0 )
				s += ";";
			s += k;
			s += "=";

			for( int m = 0; m < cc; m++ )
				{
					if( m > 0 )
						s += ", ";

					char l_buf[ 10 ];
					sprintf( l_buf , "%8.8X" , *pv++ );
					s += l_buf;
				}
		}
	logger.logDebug( s );
}

void HtmHelper::showAcceptWithoutPrediction( int layerPos , int h , int v , HtmSequence *cs , HtmSequence *csa , int action )
{
	Xml xml = logger.getLogSettings();
	String s = xml.getProperty( "showAcceptActions" , "" );
	char l_buf[ 10 ];
	sprintf( l_buf , "%d" , action );
	if( strstr( s , l_buf ) == NULL )
		return;

	String area = String( "l" ) + layerPos + "-h" + h + "-v" + v;
	logger.logDebug( area + ": action=" + action );
	showSequence( "current" , cs );
	showSequence( "stored" , csa );
}
