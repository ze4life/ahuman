#include "aihtmlib_impl.h"
#include "math.h"

/*#########################################################################*/
/*#########################################################################*/

HtmCortex::HtmCortex()
{
	inputs = NULL;
}

HtmCortex::~HtmCortex()
{
	layers.destroy();
}

void HtmCortex::create( int d1 , int d2 )
{
	ASSERT( d1 > 0 && d2 > 0 );

	int l_d1 = d1;
	int l_d2 = d2;
	inputs = new TwoIndexArray<int>( l_d1 , l_d2 );

	if( l_d1 > 1 )
		l_d1 = l_d1 / 2 + l_d1 % 2;
	if( l_d2 > 1 )
		l_d2 = l_d2 / 2 + l_d2 % 2;

	// number of layers
	int maxDim = ( l_d1 > l_d2 )? l_d1 : l_d2;
	ASSERT( maxDim > 0 );

	int nLayers = 1 + ( int )( log( maxDim ) / log( 2 ) );

	HtmLayer *lowerLayer = NULL;
	for( int k = 0; k < nLayers; k++ )
		{
			HtmLayer *layer = new HtmLayer( l_d1 , l_d2 , this , lowerLayer );

			// reduce
			if( l_d1 > 1 )
				l_d1 = l_d1 / 2 + l_d1 % 2;
			if( l_d2 > 1 )
				l_d2 = l_d2 / 2 + l_d2 % 2;
			layers.add( layer );
			lowerLayer = layer;
		}
}

int HtmCortex::getLayerCount()
{
	return( layers.count() );
}

HtmLayer *HtmCortex::getLayer( int pos )
{
	return( layers.get( pos ) );
}

HtmRect HtmCortex::getRect()
{
	return( HtmRect( 0 , inputs -> getN1() - 1 , 0 , inputs -> getN2() - 1 ) );
}

int HtmCortex::getInputsSizeH()
{
	ASSERT( inputs != NULL );
	return( inputs -> getN1() );
}

int HtmCortex::getInputsSizeV()
{
	ASSERT( inputs != NULL );
	return( inputs -> getN2() );
}

void HtmCortex::recalculate( const HtmRect& rc )
{
	// currently - all
	HtmRect rcChild = rc;
	for( int k = 0; k < layers.count(); k++ )
		{
			HtmLayer *layer = layers.get( k );
			HtmRect rc = layer -> getRectFromChild( rcChild );
			layer -> recalculate( rc );
		}
}

