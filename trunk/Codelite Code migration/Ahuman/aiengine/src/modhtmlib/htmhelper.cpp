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

void HtmHelper::showCortexInputs( HtmCortex *cortex )
{
	TwoIndexArray<int>& ci = cortex -> getInputs();

	String s = "cortex inputs = ";
	s += getIntArrayBySegments( ci.getData() , ci.getN1() , ci.getN2() );
	logger.logDebug( s );
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
	int size;
	s += getIntArrayBySegments( cs -> getData( &size ) , cs -> getHistoryCount() , cs -> getChildCount() );
	logger.logDebug( s );
}

String HtmHelper::getIntArrayBySegments( int *pv , int segCount , int segLen )
{
	String s;
	for( int k = 0; k < segCount; k++ )
		{
			if( k > 0 )
				s += "; ";
			s += k;
			s += "=";

			int px = -1;
			int nx = 0;
			bool ph = false;
			for( int m = 0; m <= segLen; m++ )
				{
					int wx = px;
					int nwx = nx;
					if( m < segLen )
						{
							int x = *pv++;
							if( x == px )
								{
									nx++;
									continue;
								}
							
							px = x;
							nx = 1;
							if( m == 0 )
								continue;
						}

					if( ph )
						s += ",";
					else
						ph = true;

					char l_buf[ 20 ];
					if( nwx > 1 )
						sprintf( l_buf , "%dx%8.8X" , nwx , wx );
					else
						sprintf( l_buf , "%8.8X" , wx );
					s += l_buf;
				}
		}

	return( s );
}

void HtmHelper::showAcceptWithoutPrediction( int layerPos , int h , int v , HtmSequence *cs , HtmSequence *csa , int action )
{
	Xml xml = logger.getLogSettings();
	String s = xml.getProperty( "showAcceptActions" , "" );
	char l_buf[ 10 ];
	sprintf( l_buf , "%d" , action );
	if( strstr( s , l_buf ) == NULL )
		return;

	int layer = xml.getIntProperty( "showLayer" , -1 );
	if( layer >= 0 && layer != layerPos )
		return;

	String area = String( "l" ) + layerPos + "-h" + h + "-v" + v;
	logger.logDebug( area + ": action=" + action );
	showSequence( "current" , cs );
	showSequence( "stored" , csa );
}

void HtmHelper::showTopLayer( HtmCortex *ctx )
{
	HtmLayer *layer = ctx -> getLayer( ctx -> getLayerCount() - 1 );
	showLayer( "Top layer" , layer );
}

void HtmHelper::showLayer( String title , HtmLayer *layer )
{
	Xml xml = logger.getLogSettings();
	int layerPos = xml.getIntProperty( "showLayer" , -1 );
	if( layerPos >= 0 && layer -> getLayerPos() != layerPos )
		return;

	logger.logDebug( title + " - sequences are:" );
	HtmLayerMemory *lm = layer -> getMemory();

	int n = lm -> getSequenceCount();
	for( int k = 0; k < n; k++ )
		{
			HtmSequence *seq = lm -> getSequenceByPos( k );
			showSequence( String( "s[" ) + k + "]" , seq );
		}
}

