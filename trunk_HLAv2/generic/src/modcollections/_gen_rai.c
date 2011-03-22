/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

static void
	_rfc_idx_int_insert( rfc_intarray *p_arr , int p_pos , int p_idx_pos );
static void
	_rfc_idx_int_remove( rfc_intarray *p_arr , int p_idx_pos );
static int
	_rfc_idx_int_find_near( rfc_intarray *p_arr , int p_data , short p_first );

/*#######################################################*/
/*#######################################################*/

/* construction */
rfc_intarray *
	rfc_arr_int_create( void )
{
	rfc_intarray *l_arr;

	l_arr = ( rfc_intarray * )calloc( 1 , sizeof( rfc_intarray ) );
	rfc_arr_int_allocate( l_arr , 1 );

	return( l_arr );
}

void
	rfc_arr_int_drop( rfc_intarray *p_arr )
{
	if( p_arr -> s_ref-- )
		return;

	rfc_arr_int_init( p_arr );
	free( p_arr );
}

void
	rfc_arr_int_ref( rfc_intarray *p_arr )
{
	p_arr -> s_ref++;
}

/* operations */
static int *	g_p;
static int
	_rfc_arr_qsort( const void *p_a1 , const void *p_a2 )
{
	return( g_p[ *( const int * )p_a1 ] - g_p[ *( const int * )p_a2 ] );
}

/* create index (avoid in MULTI-THREAD) */
void
	rfc_arr_int_setindex( rfc_intarray *p_arr )
{
	int k , n , a;

	if( p_arr -> s_idx != NULL )
		return;
	if( p_arr -> s_p == NULL )
		rfc_arr_int_allocate( p_arr , 1 );
	p_arr -> s_idx = ( int * )calloc( p_arr -> s_a , sizeof( int ) );

	/* add items to index */
	for( a = k = 0, n = p_arr -> s_n; k < n; a++ )
		if( p_arr -> s_p[ a ] )
			{
				p_arr -> s_idx[ k ] = k;
				k++;
			}
	
	/* make it with quick sort */
	g_p = p_arr -> s_p;
	qsort( p_arr -> s_idx , n , sizeof( int ) , _rfc_arr_qsort );
	g_p = NULL;
}

/* drop index */
void
	rfc_arr_int_clearindex( rfc_intarray *p_arr )
{
	if( p_arr -> s_idx == NULL )
		return;
	free( p_arr -> s_idx );
	p_arr -> s_idx = NULL;
}

/* add data to array */
int
	rfc_arr_int_add( rfc_intarray *p_arr , int p_data )
{
	int k;
	int l_pos;
	int l_idx_pos;

	/* check allocation */
	if( p_arr -> s_a == ( p_arr -> s_n + p_arr -> s_d ) )
		rfc_arr_int_allocate( p_arr , p_arr -> s_a + 1 );

	/* check deleted */
	if( p_arr -> s_d > 0 )
		{
			for( k = 0; k < p_arr -> s_n + p_arr -> s_d; k++ )
				if( !p_arr -> s_p[ k ] )
					break;
			p_arr -> s_d--;
			l_pos = k;
		}
	else
		l_pos = p_arr -> s_n;
	p_arr -> s_p[ l_pos ] = p_data;

	/* reindex */
	if( p_arr -> s_idx != NULL )
		{
			l_idx_pos = rfc_arr_int_find_first( p_arr , p_data );
			if( l_idx_pos < 0 )
				l_idx_pos = p_arr -> s_n;
			_rfc_idx_int_insert( p_arr , l_pos , l_idx_pos );
		}

	p_arr -> s_n++;

	return( l_pos );
}

/* set data to array */
int
	rfc_arr_int_set( rfc_intarray *p_arr , int p_pos , int p_data )
{
	int l_idx_pos;

	if( p_pos >= p_arr -> s_a )
		rfc_arr_int_allocate( p_arr , p_pos + 1 );
	if( p_arr -> s_p[ p_pos ] )
		rfc_arr_int_remove( p_arr , p_pos );

	p_arr -> s_p[ p_pos ] = p_data;

	/* reindex */
	if( p_arr -> s_idx != NULL )
		{
			l_idx_pos = rfc_arr_int_find_first( p_arr , p_data );
			if( l_idx_pos < 0 )
				l_idx_pos = p_arr -> s_n;
			_rfc_idx_int_insert( p_arr , p_pos , l_idx_pos );
		}

	if( p_pos >= ( p_arr -> s_n + p_arr -> s_d ) )
		p_arr -> s_d += p_pos - p_arr -> s_n - p_arr -> s_d;
	else
		p_arr -> s_d--;
	p_arr -> s_n++;

	return( p_pos );
}

/* remove by position */
void
	rfc_arr_int_remove( rfc_intarray *p_arr , int p_pos )
{
	int l_idx_pos;
	int l_data;

	l_data = p_arr -> s_p[ p_pos ];
	if( !l_data )
		return;

	if( p_arr -> s_idx != NULL )
		{
			/* find index position */
			l_idx_pos = rfc_arr_int_find_first( p_arr , l_data );
			while( p_arr -> s_idx[ l_idx_pos ] != p_pos )
				l_idx_pos++;

			/* remove from index */
			_rfc_idx_int_remove( p_arr , l_idx_pos );
		}

	/* remove from array */
	p_arr -> s_p[ p_pos ] = 0;
	p_arr -> s_n--;
	if( p_pos < ( p_arr -> s_n + p_arr -> s_d ) )
		p_arr -> s_d++;
}

/* remove item by data */
int
	rfc_arr_int_remove_data( rfc_intarray *p_arr , int p_data )
{
	int l_idx_pos;
	int l_pos;

	if( !p_data )
		return( -1 );

	if( p_arr -> s_idx != NULL )
		{
			/* find index position */
			l_idx_pos = rfc_arr_int_find_first( p_arr , p_data );
			if( l_idx_pos < 0 )
				return( -1 );

			/* remove from index */
			l_pos = p_arr -> s_idx[ l_idx_pos ];
			_rfc_idx_int_remove( p_arr , l_idx_pos );
		}
	else
		{
			for( l_pos = p_arr -> s_n + p_arr -> s_d - 1; l_pos >= 0; l_pos-- )
				if( p_arr -> s_p[ l_pos ] == p_data )
					break;
			if( l_pos < 0 )
				return( -1 );
		}

	/* remove from array */
	p_arr -> s_p[ l_pos ] = 0;
	p_arr -> s_n--;
	if( l_pos < ( p_arr -> s_n + p_arr -> s_d ) )
		p_arr -> s_d++;

	return( l_pos );
}

/* remove item & shift positions */
void
	rfc_arr_int_remove_shift( rfc_intarray *p_arr , int p_pos )
{
	int *l_idx;
	int n;

	if( !p_arr -> s_p[ p_pos ] )
		return;

	/* remove item */
	rfc_arr_int_remove( p_arr , p_pos );

	/* shift */
	if( p_pos < ( p_arr -> s_n + p_arr -> s_d ) )
		{
			memmove( &p_arr -> s_p[ p_pos ] , &p_arr -> s_p[ p_pos + 1 ] , ( p_arr -> s_n + p_arr -> s_d - p_pos - 1 ) * sizeof( int ) );
			p_arr -> s_p[ p_arr -> s_n + p_arr -> s_d ] = 0;
		}

	/* adjust indexes */
	if( p_arr -> s_idx != NULL )
		{
			n = p_arr -> s_n;
			for( l_idx = p_arr -> s_idx; n--; l_idx++ )
				if( *l_idx > p_pos )
					(*l_idx)--;
		}
}

/* insert item & shift positions */
void
	rfc_arr_int_add_shift( rfc_intarray *p_arr , int p_pos , int p_data )
{
	int n;
	int *l_idx;

	/* check allocate */
	if( p_pos >= p_arr -> s_a )
		rfc_arr_int_allocate( p_arr , p_pos + 1 );
	else
	if( ( p_arr -> s_n + p_arr -> s_d ) == p_arr -> s_a )
		rfc_arr_int_allocate( p_arr , p_arr -> s_a + 1 );

	/* shift data */
	if( p_arr -> s_p[ p_pos ] )
		{
			if( p_pos < ( p_arr -> s_n + p_arr -> s_d ) )
				memmove( &p_arr -> s_p[ p_pos + 1 ] , &p_arr -> s_p[ p_pos ] , ( p_arr -> s_n + p_arr -> s_d - p_pos ) * sizeof( int ) );
			p_arr -> s_p[ p_pos ] = 0;

			if( p_arr -> s_idx != NULL )
				{
					/* shift indexes */
					n = p_arr -> s_n;
					for( l_idx = p_arr -> s_idx; n--; l_idx++ )
						if( *l_idx >= p_pos )
							(*l_idx)++;
				}
		}

	/* set to pos */
	rfc_arr_int_set( p_arr , p_pos , p_data );
}

/* clear array with init memory */
void
	rfc_arr_int_remove_all( rfc_intarray *p_arr )
{
	rfc_arr_int_init( p_arr );
	rfc_arr_int_allocate( p_arr , 1 );
}

/* clear array without reallocate memory */
void
	rfc_arr_int_clear( rfc_intarray *p_arr )
{
	p_arr -> s_n = p_arr -> s_d = 0;
	if( p_arr -> s_a > 0 )
		{
			memset( p_arr -> s_p , 0 , p_arr -> s_a * sizeof( int ) );
			if( p_arr -> s_idx != NULL )
				memset( p_arr -> s_idx , 0 , p_arr -> s_a * sizeof( int ) );
		}
}

/* clear array with free intenal memory without destroy struct */
void
	rfc_arr_int_init( rfc_intarray *p_arr )
{
	if( p_arr -> s_p != NULL )
		free( p_arr -> s_p );
	if( p_arr -> s_idx != NULL )
		free( p_arr -> s_idx );
	p_arr -> s_n = p_arr -> s_d = p_arr -> s_a = 0;
	p_arr -> s_p = p_arr -> s_idx = NULL;
}

/* allocate array memory to given count */
void
	rfc_arr_int_allocate( rfc_intarray *p_arr , int p_count )
{
	int l_a;

	if( p_arr -> s_a >= p_count )
		return;
	l_a = p_count;
	if( l_a % RFC_ARRAY_BLOCK )
		l_a += RFC_ARRAY_BLOCK - ( l_a % RFC_ARRAY_BLOCK );
	if( !p_arr -> s_a )
		{
			p_arr -> s_a = l_a;
			p_arr -> s_p = ( int * )calloc( l_a , sizeof( int ) );
		}
	else
		{
			p_arr -> s_p = ( int * )realloc( p_arr -> s_p , l_a * sizeof( int ) );
			memset( &p_arr -> s_p[ p_arr -> s_a ] , 0 , ( l_a - p_arr -> s_a ) * sizeof( int ) );
			if( p_arr -> s_idx != NULL )
				{
					p_arr -> s_idx = ( int * )realloc( p_arr -> s_idx , l_a * sizeof( int ) );
					memset( &p_arr -> s_idx[ p_arr -> s_a ] , 0 , ( l_a - p_arr -> s_a ) * sizeof( int ) );
				}
			p_arr -> s_a = l_a;
		}
}

/* find position by index */
int
	rfc_arr_int_find_id( rfc_intarray *p_arr , int p_data )
{
	int l_idx_pos;

	if( !p_data )
		return( -1 );
	l_idx_pos = rfc_arr_int_find_first( p_arr , p_data );
	if( l_idx_pos < 0 )
		return( -1 );
	return( p_arr -> s_idx[ l_idx_pos ] );
}

/* find index position */
int
	rfc_arr_int_find_index( rfc_intarray *p_arr , int p_data )
{
	int l_idx_pos;

	if( !p_data )
		return( -1 );
	l_idx_pos = rfc_arr_int_find_first( p_arr , p_data );
	return( l_idx_pos );
}

/* find index position range - return match count */
int
	rfc_arr_int_find_range( rfc_intarray *p_arr , int p_data , int *p_idx_start , int *p_idx_stop )
{
	int l_k;
	int l_idx_from;
	int l_idx_to;

	l_idx_from = _rfc_idx_int_find_near( p_arr , p_data , 1 );
	l_idx_to = _rfc_idx_int_find_near( p_arr , p_data , 0 );
	if( l_idx_from < 0 || 
		l_idx_to < 0 )
		{
			l_idx_from = l_idx_to = -1;
			l_k = 0;
		}
	else
		l_k = l_idx_to - l_idx_from + 1;

	if( p_idx_start )
		*p_idx_start = l_idx_from;
	if( p_idx_stop )
		*p_idx_stop = l_idx_to;

	return( l_k );
}

/* find first index position for item data >= p_data by sort order */
int
	rfc_arr_int_find_first( rfc_intarray *p_arr , int p_data )
{
	return( _rfc_idx_int_find_near( p_arr , p_data , 1 ) );
}

/* find last index position for item data <= p_data by sort order */
int
	rfc_arr_int_find_last( rfc_intarray *p_arr , int p_data )
{
	return( _rfc_idx_int_find_near( p_arr , p_data , 0 ) );
}

/* return number of non-deleted items */
int
	rfc_arr_int_count( rfc_intarray *p_arr )
{
	return( p_arr -> s_n );
}

/* return max number of items */
int
	rfc_arr_int_margin( rfc_intarray *p_arr )
{
	return( p_arr -> s_n + p_arr -> s_d );
}

/* get item by position */
int
	rfc_arr_int_get( rfc_intarray *p_arr , int p_pos )
{
	return( p_arr -> s_p[ p_pos ] );
}

/* get array position by index position */
int
	rfc_arr_int_get_index( rfc_intarray *p_arr , int p_pos )
{
	if( p_arr -> s_idx == NULL )
		return( -1 );
	return( p_arr -> s_idx[ p_pos ] );
}

/*#######################################################*/
/*#######################################################*/

static void
	_rfc_idx_int_insert( rfc_intarray *p_arr , int p_pos , int p_idx_pos )
{
	memmove( &p_arr -> s_idx[ p_idx_pos + 1 ] , &p_arr -> s_idx[ p_idx_pos ] , ( p_arr -> s_n - p_idx_pos ) * sizeof( int ) );
	p_arr -> s_idx[ p_idx_pos ] = p_pos;
}

static void
	_rfc_idx_int_remove( rfc_intarray *p_arr , int p_idx_pos )
{
	memmove( &p_arr -> s_idx[ p_idx_pos ] , &p_arr -> s_idx[ p_idx_pos + 1 ] , ( p_arr -> s_n - p_idx_pos - 1 ) * sizeof( int ) );
	p_arr -> s_idx[ p_arr -> s_n - 1 ] = 0;
}

static int
	_rfc_idx_int_find_near( rfc_intarray *p_arr , int p_data , short p_first )
{
	int *l_all;
	int *l_idx;
	int l_from;
	int l_to;
	int l_res;
	int l_k;

	l_all = p_arr -> s_p;
	l_idx = p_arr -> s_idx;

	l_from = 0;
	l_to = p_arr -> s_n - 1;

	/* check margins */
	if( l_to < 0 )
		return( -1 );

	l_res = p_data - l_all[ l_idx[ l_to ] ];
	if( p_first )
		{
			if( l_res > 0 )
				return( -1 );
			if( l_to == 0 )
				return( 0 );
		}
	else
		{
			if( l_res >= 0 )
				return( l_to );
			if( l_to == 0 )
				return( -1 );
		}

	l_res = p_data - l_all[ l_idx[ 0 ] ];
	if( l_res <= 0 && p_first )
		return( 0 );
	if( l_res < 0 && !p_first )
		return( -1 );

	while( l_to > l_from + 1 )
		{
			l_k = ( l_to + l_from ) / 2;

			l_res = p_data - l_all[ l_idx[ l_k ] ];
			if( p_first )
				{
					if( l_res <= 0 )
						l_to = l_k;
					else
						l_from = l_k;
				}
			else
				{
					if( l_res >= 0 )
						l_from = l_k;
					else
						l_to = l_k;
				}
		}

	return( ( p_first )? l_to : l_from );
}

