#include "htm_custom.h"
#include <math.h>

const char *HtmCortex::NAME = "HtmCortex";

/*#########################################################################*/
/*#########################################################################*/

HtmCortex::HtmCortex()
{
	inputs = NULL;
	inputsPredicted = NULL;
	logger.attach( this );
}

HtmCortex::~HtmCortex()
{
	layers.destroy();

	if( inputs != NULL )
		delete inputs;
	if( inputsPredicted != NULL )
		delete inputsPredicted;
}

void HtmCortex::create( int d1 , int d2 )
{
	ASSERT( d1 > 0 && d2 > 0 );

	int l_d1 = d1;
	int l_d2 = d2;
	inputs = new TwoIndexArray<int>( l_d1 , l_d2 );
	inputsPredicted = new TwoIndexArray<int>( l_d1 , l_d2 );

	// number of layers
	int nLayers = calculateNumberOfLayers( l_d1 , l_d2 );

	HtmLayer *lowerLayer = NULL;
	for( int k = 0; k < nLayers; k++ )
		{
			int nd1 , nd2;
			calculateLayerDimensions( k , l_d1 , l_d2 , &nd1 , &nd2 );
			HtmLayer *layer = new HtmLayer( k , nd1 , nd2 , this , lowerLayer );

			l_d1 = nd1;
			l_d2 = nd2;

			// reduce
			layers.add( layer );
			lowerLayer = layer;
		}
}

int HtmCortex::calculateNumberOfLayers( int d1 , int d2 )
{
	int maxDim = ( d1 > d2 )? d1 : d2;
	ASSERT( maxDim > 0 );

	int nLayers = -2 + ( int )( log( ( double )maxDim ) / log( 2. ) );
	if( nLayers < 2 )
		nLayers = 2;
	return( nLayers );
}

void HtmCortex::calculateLayerDimensions( int pos , int d1 , int d2 , int *nd1 , int *nd2 )
{
	int l_d1 = d1;
	int l_d2 = d2;

	if( pos == 0 )
		{
			l_d1 = ( d1 % 8 )? (l_d1 / 8) + 1 : d1 / 8;
			l_d2 = ( d2 % 8 )? (l_d2 / 8) + 1 : d2 / 8;
		}
	else
		{
			if( l_d1 > 1 )
				l_d1 = l_d1 / 2 + l_d1 % 2;
			if( l_d2 > 1 )
				l_d2 = l_d2 / 2 + l_d2 % 2;
		}

	*nd1 = l_d1;
	*nd2 = l_d2;
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

TwoIndexArray<int>& HtmCortex::getInputs()
{
	return( *inputs );
}

TwoIndexArray<int>& HtmCortex::getInputsPredicted()
{
	return( *inputsPredicted );
}

void HtmCortex::recalculate( const HtmRect& rc )
{
	HtmHelper helper( logger );
	helper.showCortexInputs( this );

	// currently - all
	HtmRect rcChild = rc;
	for( int k = 0; k < layers.count(); k++ )
		{
			HtmLayer *layer = layers.get( k );
			HtmRect rc = layer -> getRectFromChild( rcChild );
			layer -> recalculate( rc );
			rcChild = rc;
		}
}

void HtmCortex::createSerializeObject()
{
}

void HtmCortex::serialize( SerializeObject& so )
{
}

void HtmCortex::deserialize( Object *parent , SerializeObject& so )
{
}
