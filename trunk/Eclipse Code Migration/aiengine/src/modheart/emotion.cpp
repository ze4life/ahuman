
#include "aiheart_impl.h"

/*#########################################################################*/
/*#########################################################################*/

// class AIEmotion()
AIEmotionImpl::AIEmotionImpl( AIEmotionType p_type , int p_val )
{
	type = p_type; 
	memset( &val , 0 , sizeof( int ) * AIEMOTION_COUNT );
	if( p_type != AIEMOTION_MIXED )
		val[ p_type ] = p_val;
}

AIEmotionImpl::AIEmotionImpl( const AIEmotionImpl& p_one , const AIEmotionImpl& p_two )
{
	// add 2 emotions
	if( p_one.type == p_two.type )
		type = p_one.type;
	else
		type = AIEMOTION_MIXED;

	// setup vals
	for( int k = 0; k < AIEMOTION_COUNT; k++ )
		val[ k ] = ( p_one.val[ k ] + p_two.val[ k ] ) / 2;
}

int AIEmotionImpl::size2() const
{
	int v = 0;
	for( int k = 0; k < AIEMOTION_COUNT; k++ )
		v += val[ k ] * val[ k ];
	return( v );
}

AIEmotionImpl operator +( const AIEmotionImpl& left , const AIEmotionImpl& right )
{
	return( AIEmotionImpl( left , right ) ); 
}

int operator *( const AIEmotionImpl& left , const AIEmotionImpl& right )
{
	int v = 0;
	for( int k = 0; k < AIEMOTION_COUNT; k++ )
		v += left.val[ k ] * right.val[ k ];

	return( v );
}

bool AIEmotionImpl::isApproved( const AIEmotionImpl& e ) const 
{
	int v2 = e.size2();

	// if no emotions then not approved
	if( v2 == 0 )
		return( false );

	// make e projection to "this" vector
	int v1 = *this * e;

	// if other direction then not approved
	if( v1 <= 0 )
		return( false );

	// calculate projection vector
	AIEmotionImpl res( AIEMOTION_MIXED , 0 );
	for( int k = 0; k < AIEMOTION_COUNT; k++ )
		res.val[ k ] = ( val[ k ] * v1 ) / v2;

	// compare with emotion vector
	int v3 = size2();
	if( ( v3 < v2 * APPROVED_SIZE_RATE_MIN ) ||
		( v2 < v3 * APPROVED_SIZE_RATE_MAX ) )
		return( false );

	return( true );
}


