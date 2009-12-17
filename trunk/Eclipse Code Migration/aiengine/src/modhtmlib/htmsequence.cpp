#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

HtmSequence::HtmSequence()
{
	memset( dummy , 0 , sizeof( dummy ) );
	historyCount = 0;
	childCount = 0;
	isStored = false;
}

HtmSequence::HtmSequence( int nTemporalCount , int nChilds )
{
	create( nTemporalCount , nChilds );
}

HtmSequence::~HtmSequence()
{
}

void HtmSequence::create( int nTemporalCount  , int nChilds )
{
	memset( dummy , 0 , sizeof( dummy ) );
	historyCount = 0;
	childCount = nChilds;

	data.allocate( nTemporalCount * nChilds );
}

void HtmSequence::setId( int id )
{
	stored.ID = id;
	isStored = true;
}

int HtmSequence::getId()
{
	return( stored.ID );
}

void HtmSequence::incrementUsage()
{
	stored.usage++;
}

void HtmSequence::decrementUsage()
{
	stored.usage--;
}

int HtmSequence::getUsage()
{
	return( stored.usage );
}

void HtmSequence::clearUsage()
{
	stored.usage = 0;
}

bool HtmSequence::addPattern( TwoIndexArray<int>& inputs , const HtmRect& rc )
{
	int sizeAdd = rc.getSize();
	if( sizeAdd > ( data.size() - data.count() ) )
		return( false );

	for( int k = rc.fromV; k <= rc.toV; k++ )
		{
			int *pc = inputs[ k ];
			data.add( pc + rc.fromH , rc.toH - rc.fromH + 1 );
		}

	historyCount++;
	return( true );
}

bool HtmSequence::isNewPattern( TwoIndexArray<int>& inputs , const HtmRect& rc )
{
	if( historyCount == 0 )
		return( true );

	int *lc = data.getAt( data.count() - childCount );
	// int height = rc.getHeight();
	int width = rc.getWidth();
	for( int k = rc.fromV; k <= rc.toV; k++ )
		{
			int *pc = inputs[ k ] + rc.fromH;
			int *pz = lc + width * ( k - rc.fromV );

			for( int x = 0; x < width; x++ )
				if( *pc++ != *pz++ )
					return( true );
		}

	return( false );
}

void HtmSequence::clear()
{
	data.clear();
	historyCount = 0;
}

void HtmSequence::clearCurrent()
{
	data.clear();
	historyCount = 0;

	current.lastReturned = NULL;
	current.lastProbability = 0;
}

int *HtmSequence::getData( int *psize )
{
	*psize = data.count();
	return( data.getAll() );
}

void HtmSequence::copyPatterns( HtmSequence *cs )
{
	data.allocate( cs -> data.count() );
	data.clear();
	data.add( cs -> data.getAll() , cs -> data.count() );
	historyCount = cs -> historyCount;
}

void HtmSequence::setMemoryPos( int pos )
{
	stored.memoryPos = pos;
}

int HtmSequence::getMemoryPos()
{
	return( stored.memoryPos );
}

int HtmSequence::getHistoryCount()
{
	return( historyCount );
}

bool HtmSequence::isEmpty()
{
	return( historyCount == 0 );
}

int HtmSequence::getChildCount()
{
	return( childCount );
}

void HtmSequence::setLastReturned( HtmSequence *cs , int probability )
{
	current.lastReturned = cs;
	current.lastProbability = probability;
}

HtmSequence *HtmSequence::getLastReturned( int *probability )
{
	*probability = current.lastProbability;
	return( current.lastReturned );
}

void HtmSequence::clearCurrentKeepLast()
{
	memcpy( data.getAll() , data.getAt( ( historyCount - 1 ) * childCount ) , sizeof( int ) * childCount );
	data.cut( childCount );
	historyCount = 1;
	current.lastReturned = NULL;
	current.lastProbability = 0;
}

bool HtmSequence::storedSequence()
{
	return( isStored );
}

