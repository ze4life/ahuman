#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

HtmLayer::HtmLayer( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
:	ctx( p_ctx ) ,
	outputs( p_d1 , p_d2 ) ,
	childLayer( p_source ) ,
	maxHistoryLength( calcMaxHistoryLength( p_d1 , p_d2 , p_ctx , p_source ) ) ,
	childCountH( calcChildCountH( p_d1 , p_d2 , p_ctx , p_source ) ) ,
	childCountV( calcChildCountV( p_d1 , p_d2 , p_ctx , p_source ) ) ,
	currentSequence( maxHistoryLength , childCountH * childCountV )
{
}

HtmLayer::~HtmLayer()
{
}

int HtmLayer::getSizeH()
{
	return( outputs.getN1() );
}

int HtmLayer::getSizeV()
{
	return( outputs.getN2() );
}

int HtmLayer::calcMaxHistoryLength( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
{
	return( 10 );
}

int HtmLayer::calcChildCountH( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
{
	int cd1 = ( p_source != NULL )? p_source -> getSizeH() : p_ctx -> getInputsSizeH();
	int rate = cd1 / p_d1;
	if( rate * p_d1 < cd1 )
		rate++;
	return( rate );
}

int HtmLayer::calcChildCountV( int p_d1 , int p_d2 , HtmCortex *p_ctx , HtmLayer *p_source )
{
	int cd2 = ( p_source != NULL )? p_source -> getSizeV() : p_ctx -> getInputsSizeV();
	int rate = cd2 / p_d2;
	if( rate * p_d2 < cd2 )
		rate++;
	return( rate );
}

int HtmLayer::getChildSizeH()
{
	return( childCountH );
}

int HtmLayer::getChildSizeV()
{
	return( childCountV );
}

HtmRect HtmLayer::getRect()
{
	return( HtmRect( 0 , outputs.getN1() - 1 , 0 , outputs.getN2() - 1 ) );
}

HtmRect HtmLayer::getRectFromChild( const HtmRect& rcChild )
{
	int cd1 = ( childLayer != NULL )? childLayer -> getSizeH() : ctx -> getInputsSizeH();
	int cd2 = ( childLayer != NULL )? childLayer -> getSizeV() : ctx -> getInputsSizeV();

	int d1 = outputs.getN1();
	int d2 = outputs.getN2();

	int fromH = ( rcChild.fromH * d1 ) / cd1;
	int toH = ( rcChild.toH * d1 ) / cd1;
	int fromV = ( rcChild.fromV * d2 ) / cd2;
	int toV = ( rcChild.toV * d2 ) / cd2;

	return( HtmRect( fromH , toH , fromV , toV ) );
}

void HtmLayer::recalculate( const HtmRect& rc )
{
}
