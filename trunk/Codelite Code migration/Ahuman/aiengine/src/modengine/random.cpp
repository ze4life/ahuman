
#include "aiengine_impl.h"
#include <math.h>

// #############################################################################
// #############################################################################

int Random::instanceCount = 0;

// class Random
Random::Random()
{
	type = RND_UNKNOWN;

	// init randomizer if called first time
	if( instanceCount++ == 0 )
		srand( time( NULL ) );

	statCounts = NULL;
	statBuckets = 0;
	collect = false;
	bucketSize = 0;
}

Random::~Random()
{
	if( statCounts != NULL )
		free( statCounts );
}

void Random::createRangeRandomsFloat( float pmin , float pmax )
{
	type = RND_RANGEFLOAT;
	min1.u_r = pmin;
	max1.u_r = pmax;
	min2.u_r = 0;
	max2.u_r = 0;
}

void Random::createTwoRangeRandomsFloat( float pmin1 , float pmax1 , float pmin2 , float pmax2 )
{
	type = RND_TWORANGEFLOAT;
	min1.u_r = pmin1;
	max1.u_r = pmax1;
	min2.u_r = pmin2;
	max2.u_r = pmax2;
}

void Random::createRangeRandomsInt( int pmin , int pmax )
{
	type = RND_RANGEINT;
	min1.u_l = pmin;
	max1.u_l = pmax;
	min2.u_l = 0;
	max2.u_l = 0;
}

void Random::createTwoRangeRandomsInt( int pmin1 , int pmax1 , int pmin2 , int pmax2 )
{
	type = RND_TWORANGEINT;
	min1.u_l = pmin1;
	max1.u_l = pmax1;
	min2.u_l = pmin2;
	max2.u_l = pmax2;
}

int Random::getRandomInt()
{
	int r;
	int v;
	switch( type )
		{
			case RND_RANGEINT :
				r = rand();
				v = ( int )( ( ( float )r * ( max1.u_l - min1.u_l + 1 ) ) / ( RAND_MAX + 1 ) );

				// stat
				if( collect )
					statCounts[ v ]++;

				v = min1.u_l + v;
				if( v > max1.u_l )
					v = max1.u_l;
				return( v );
			case RND_TWORANGEINT :
				r = rand();
				v = ( int )( ( ( ( float )r ) * ( max1.u_l - min1.u_l + 1 + max2.u_l - min2.u_l + 1 ) ) / ( RAND_MAX + 1 ) );

				// stat
				if( collect )
					statCounts[ v ]++;

				if( v <= ( max1.u_l - min1.u_l ) )
					v = min1.u_l + v;
				else
					{
						v -= max1.u_l - min1.u_l + 1;
						v = min2.u_l + v;
						if( v > max2.u_l )
							v = max2.u_l;
					}

				return( v );
			case RND_TWORANGEFLOAT :
			case RND_RANGEFLOAT :
			case RND_UNKNOWN :
				break;
		}

	throw RuntimeError( "Random::getRandomInt: inappropriate type" );
}

float Random::randFloat()
{
	float r1 = rand();
	float r2 = rand();

	if( r1 < r2 )
		return( r1 / r2 );
	return( r2 / r1 );
}

float Random::getRandomFloat()
{
	float r;
	float v;
	switch( type )
		{
			case RND_RANGEFLOAT :
				r = randFloat();
				v = r * ( max1.u_r - min1.u_r );

				// stat
				if( collect )
					{
						int bucket = ( int )( v / bucketSize );
						statCounts[ bucket ]++;
					}

				v = min1.u_r + v;
				if( v > max1.u_r )
					v = max1.u_r;
				return( v );
			case RND_TWORANGEFLOAT :
				r = randFloat();
				v = r * ( max1.u_r - min1.u_r + max2.u_r - min2.u_r );

				// stat
				if( collect )
					{
						int bucket = ( int )( v / bucketSize );
						statCounts[ bucket ]++;
					}

				if( v <= ( max1.u_r - min1.u_r ) )
					v = min1.u_r + v;
				else
					{
						v -= max1.u_r - min1.u_r;
						v = min2.u_r + v;
						if( v > max2.u_r )
							v = max2.u_r;
					}

				return( v );
			case RND_UNKNOWN :
			case RND_TWORANGEINT :
			case RND_RANGEINT :
				break;
		}

	throw RuntimeError( "Random::getRandomFloat: inappropriate type" );
}

float Random::getRandomFloat( float min , float max )
{
	return( min + randFloat() * ( max - min ) );
}

void Random::collectStatisticsInt()
{
	if( statCounts != NULL )
		free( statCounts );

	switch( type )
		{
			case RND_RANGEINT :
				statBuckets = max1.u_l - min1.u_l + 1;
				break;
			case RND_TWORANGEINT :
				statBuckets = max1.u_l - min1.u_l + 1 + max2.u_l - min2.u_l + 1;
				break;
			case RND_RANGEFLOAT :
			case RND_TWORANGEFLOAT :
			case RND_UNKNOWN :
				break;
		}

	statCounts = ( int * )calloc( statBuckets , sizeof( int ) );
	collect = true;
}

void Random::collectStatisticsFloat( int count )
{
	if( statCounts != NULL )
		free( statCounts );

	statBuckets = count;
	statCounts = ( int * )calloc( statBuckets , sizeof( int ) );
	switch( type )
		{
			case RND_RANGEFLOAT :
				bucketSize = ( max1.u_r - min1.u_r ) / count;
				break;
			case RND_TWORANGEFLOAT :
				bucketSize = ( max1.u_r - min1.u_r + max2.u_r - min2.u_r ) / count;
				break;
			default:
				throw RuntimeError( "Random::collectStatisticsFloat: invalid type" );
		}
	
	collect = true;
}

void Random::showStatistics()
{
	if( !collect )
		throw RuntimeError( "Random::showStatistics: collect turned off" );

	// calculate avg and variance
	float sum , var;
	// bool isInt = ( type == RND_RANGEINT || type == RND_TWORANGEINT )? true : false;
	sum = 0;
	var = 0;

	float avgBucket = 0;
	for( int k = 0; k < statBuckets; k++ )
		{
			sum += statCounts[ k ];
			avgBucket += statCounts[ k ] * ( k + 0.5f );
		}
	float avg = avgBucket / sum;

	for( int m = 0; m < statBuckets; m++ )
		var += ( statCounts[ m ] - avg ) * ( statCounts[ m ] - avg );
	// int varAvg = ( int )sqrt( var / statBuckets );

	logger.logInfo( String( "STAT: bucket count=" ) + statBuckets + 
		", avg bucket=" + avg );
	for( int z = 0; z < statBuckets; z++ )
		{
			// int diff = statCounts[ z ] - avg;
			// float var = ( int )sqrt( diff * diff );
			logger.logInfo( String( "BUCKET #" ) + z + 
				": count=" + statCounts[ z ] );
		}
}

int Random::getRandomIntStatic( int min , int max )
{
	float r = ( (( float )rand()) * ( max - min ) ) / RAND_MAX;
	int rm = ( int )r;
	if( rm < r )
		rm++;

	int v = min + rm;
	if( v > max )
		v = max;
	return( v );
}

int Random::getRandomFloatStatic( float min , float max )
{
	float v = min + randFloat() * ( max - min );
	if( v > max )
		v = max;
	return( ( int )v );
}

void Random::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( "Random" );
	so -> setFactoryMethod( Random::onCreate );

	// add own fields
	so -> addFieldInt( "type" );
	so -> addFieldInt( "min1.u_l" );
	so -> addFieldInt( "max1.u_l" );
	so -> addFieldInt( "min2.u_l" );
	so -> addFieldInt( "max2.u_l" );
	so -> addFieldFloat( "min1.u_r" );
	so -> addFieldFloat( "max1.u_r" );
	so -> addFieldFloat( "min2.u_r" );
	so -> addFieldFloat( "max2.u_r" );
}

void Random::serialize( SerializeObject& so )
{
	so.setPropInt( type , "type" );

	if( type == RND_RANGEFLOAT || type == RND_TWORANGEFLOAT )
		{
			so.setPropFloat( min1.u_r , "min1.u_r" );
			so.setPropFloat( max1.u_r , "max1.u_r" );
			so.setPropFloat( min2.u_r , "min2.u_r" );
			so.setPropFloat( max2.u_r , "max2.u_r" );
		}
	else
	if( type == RND_RANGEINT || type == RND_TWORANGEINT )
		{
			so.setPropInt( min1.u_l , "min1.u_l" );
			so.setPropInt( max1.u_l , "max1.u_l" );
			so.setPropInt( min2.u_l , "min2.u_l" );
			so.setPropInt( max2.u_l , "max2.u_l" );
		}
}

void Random::deserialize( Object *parent , SerializeObject& so )
{
	type = ( RandomType )so.getPropInt( "type" );
	if( type == RND_RANGEFLOAT || type == RND_TWORANGEFLOAT )
		{
			min1.u_r = so.getPropFloat( "min1.u_r" );
			max1.u_r = so.getPropFloat( "max1.u_r" );
			min2.u_r = so.getPropFloat( "min2.u_r" );
			max2.u_r = so.getPropFloat( "max2.u_r" );
		}
	else
	if( type == RND_RANGEINT || type == RND_TWORANGEINT )
		{
			min1.u_l = so.getPropInt( "min1.u_l" );
			max1.u_l = so.getPropInt( "max1.u_l" );
			min2.u_l = so.getPropInt( "min2.u_l" );
			max2.u_l = so.getPropInt( "max2.u_l" );
		}
}
