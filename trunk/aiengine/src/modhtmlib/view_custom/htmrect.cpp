#include "htm_custom.h"

/*#########################################################################*/
/*#########################################################################*/

HtmRect::HtmRect( int p_fromH , int p_toH , int p_fromV , int p_toV )
{
	fromH = p_fromH;
	toH = p_toH;
	fromV = p_fromV;
	toV = p_toV;
}

int HtmRect::getSize() const
{
	return( ( toH - fromH + 1 ) * ( toV - fromV + 1 ) );
}

int HtmRect::getHeight() const
{
	return( toV - fromV + 1 );
}

int HtmRect::getWidth() const
{
	return( toH - fromH + 1 );
}

