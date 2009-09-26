#include "aihtmlib_impl.h"

/*#########################################################################*/
/*#########################################################################*/

HtmLayerMemory::HtmLayerMemory( int p_limitCount )
{
	lastId = 0;
	thresholdOne = 0.8f;
	thresholdMany = 0.8f;
	mostUsedCount = 0;
	limitCount = p_limitCount;
	limitLeastUsed = 1;
}

HtmLayerMemory::~HtmLayerMemory()
{
	sequences.destroy();
}

HtmSequence *HtmLayerMemory::findLike( HtmSequence *cs , int *precision , int *probability )
{
	// iterate sequences
	int n = sequences.count();
	float likelihood = 0;
	float likeMax = 0;
	HtmSequence *likeMaxSeq = NULL;
	int likeCount = 0;
	int csHistory = cs -> getHistoryCount();
	bool haveExactMatch = false;

	for( int k = 0; k < n; k++ )
		{
			HtmSequence *seq = sequences[ k ];
			float likeOne = compare( cs , seq );

			if( likeOne >= thresholdOne )
				{
					int seqHistory = seq -> getHistoryCount();

					if( seqHistory == csHistory )
						{
							// if exact sequence
							if( haveExactMatch )
								{
									// compare with another exaqct sequence
									if( likeOne > likeMax )
										{
											likeMax = likeOne;
											likeMaxSeq = seq;
										}
								}
							else
								{
									// replace any longer sequences if any
									likeMax = likeOne;
									likeMaxSeq = seq;
									haveExactMatch = true;
									likeCount = 1;
								}
						}
					else
						{
							// if longer sequence
							if( haveExactMatch == false )
								{
									// take into account how many longer sequences we have
									likelihood += likeOne;
									likeCount++;

									// compare with most likely longer sequence
									if( likeOne > likeMax )
										{
											likeMax = likeOne;
											likeMaxSeq = seq;
										}
								}
						}
				}
		}

	// no item found
	if( likeCount == 0 )
		return( NULL );

	// for exact match only one is used
	if( haveExactMatch )
		{
			*precision = ( int )( thresholdOne * 100 );
			*probability = ( int )( likeMax * 100 );
			return( likeMaxSeq );
		}
			
	// get average
	likelihood /= likeCount;

	// justify as many items found like given
	likelihood /= likeCount;

	// compare with threshold
	if( likelihood < thresholdMany )
		return( NULL );

	*precision = ( int )( thresholdMany * 100 );
	*probability = ( int )( likelihood * 100 );
	return( likeMaxSeq );
}

float HtmLayerMemory::compare( HtmSequence *cs1 , HtmSequence *cs2 )
{
	int sn1;
	int *sd1 = cs1 -> getData( &sn1 );
	int sn2;
	int *sd2 = cs2 -> getData( &sn2 );

	// do not compare with shorter sequences
	int sn = ( sn1 <= sn2 )? sn1 : 0;
	if( sn == 0 )
		return( 0 );

	int sne = 0;
	for( int k = 0; k < sn; k++ )
		if( *sd1++ == *sd2++ )
			sne++;

	float res = sne;
	res /= sn;
	return( res );
}

HtmSequence *HtmLayerMemory::store( int pos , HtmSequence *cs )
{
	HtmSequence *csn;
	if( pos < 0 )
		{
			csn = new HtmSequence( cs -> getHistoryCount() , cs -> getChildCount() );
			csn -> setId( ++lastId );

			pos = sequences.add( csn );
			csn -> setMemoryPos( pos );
		}
	else
		{
			csn = sequences[ pos ];
			csn -> clearUsage();
		}

	csn -> copyPatterns( cs );
	incrementUsage( csn );
	return( csn );
}

int HtmLayerMemory::selectLeastUsedPos()
{
	int n = sequences.count();

	// if can add more
	if( n < limitCount )
		return( -1 );

	// if all are most used
	if( mostUsedCount == n )
		return( -1 );

	// random select from least used
	int pos = Random::getRandomIntStatic( mostUsedCount , n - 1 );

	// shift it to the beginning of least used
	if( pos > mostUsedCount )
		{
			HtmSequence *cs1 = sequences[ pos ];
			HtmSequence *cs2 = sequences[ mostUsedCount ];
			sequences.set( pos , cs2 );
			cs2 -> setMemoryPos( pos );
			sequences.set( mostUsedCount , cs1 );
			cs1 -> setMemoryPos( mostUsedCount );
		}

	return( mostUsedCount );
}

bool HtmLayerMemory::hasSpace()
{
	return( mostUsedCount != limitCount );
}

void HtmLayerMemory::decrementUsageRandom()
{
	if( mostUsedCount == 0 )
		return;

	// decrement sequence usage
	int pos = Random::getRandomIntStatic( 0 , mostUsedCount - 1 );
	HtmSequence *cs1 = sequences[ pos ];
	cs1 -> decrementUsage();

	// return if still most used
	if( cs1 -> getUsage() >= limitLeastUsed )
		return;

	// increase least used group
	mostUsedCount--;
	ASSERT( mostUsedCount >= 0 );

	// exchange with last most used
	if( pos < mostUsedCount )
		{
			HtmSequence *cs2 = sequences[ mostUsedCount ];
			sequences.set( pos , cs2 );
			cs2 -> setMemoryPos( pos );
			sequences.set( mostUsedCount , cs1 );
			cs1 -> setMemoryPos( mostUsedCount );
		}
}

void HtmLayerMemory::decrementUsage( HtmSequence *cs1 )
{
	cs1 -> decrementUsage();

	// return if non-marginal
	if( cs1 -> getUsage() != ( limitLeastUsed - 1 ) )
		return;

	// increase least used group
	mostUsedCount--;
	ASSERT( mostUsedCount >= 0 );

	// exchange with last most used
	int pos = cs1 -> getMemoryPos();
	if( pos < mostUsedCount )
		{
			HtmSequence *cs2 = sequences[ mostUsedCount ];
			sequences.set( pos , cs2 );
			cs2 -> setMemoryPos( pos );
			sequences.set( mostUsedCount , cs1 );
			cs1 -> setMemoryPos( mostUsedCount );
		}
}

void HtmLayerMemory::incrementUsage( HtmSequence *cs1 )
{
	// increment sequence usage
	cs1 -> incrementUsage();

	// return if non-marginal
	if( cs1 -> getUsage() != limitLeastUsed )
		return;

	// exchange with first least used
	int pos = cs1 -> getMemoryPos();
	if( pos > mostUsedCount )
		{
			HtmSequence *cs2 = sequences[ mostUsedCount ];
			sequences.set( pos , cs2 );
			cs2 -> setMemoryPos( pos );
			sequences.set( mostUsedCount , cs1 );
			cs1 -> setMemoryPos( mostUsedCount );
		}
			
	// increase most used group
	mostUsedCount++;
}

int HtmLayerMemory::getSequenceCount()
{
	return( sequences.count() );
}

int HtmLayerMemory::getMaxSize()
{
	return( limitCount );
}
