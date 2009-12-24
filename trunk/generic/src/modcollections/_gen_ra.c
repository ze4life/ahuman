/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/
/* dynamic array */

/*#######################################################*/
/*#######################################################*/
/* index for rfc_array */

/* index functions */
/* construction */
static rfc_index *
	_rfc_idx_create( int p_offset , int p_size , char p_type );
static void
	_rfc_idx_destroy( rfc_index *p_idx );

/* operations */
/* append item to index */
static void
	_rfc_idx_add( rfc_index *p_idx , void *p_data , int p_pos , void **p_all , int p_n );
/* remove item */
static int
	_rfc_idx_remove( rfc_index *p_idx , int p_pos , void **p_all , int p_n );
/* remove item & shift positions */
static void
	_rfc_idx_remove_shift( rfc_index *p_idx , int p_pos , int p_count );
/* add item & shift positions */
static void
	_rfc_idx_add_shift( rfc_index *p_idx , void *p_data , int p_pos , void **p_all , int p_n );

/* find <Void> item */
static int
	_rfc_idx_find_v( rfc_index *p_idx , const void *p_data , void **p_all , int p_n , int *p_index );
/* find <String> item */
static int
	_rfc_idx_find_s( rfc_index *p_idx , const char *p_data , void **p_all , int p_n , int *p_index );
/* find <Long> item */
static int
	_rfc_idx_find_l( rfc_index *p_idx , long p_data , void **p_all , int p_n , int *p_index );
/* find <Pointer to string> item */
static int
	_rfc_idx_find_p( rfc_index *p_idx , const char *p_data , void **p_all , int p_n , int *p_index );
/* find <Generic pointer to data> item */
static int
	_rfc_idx_find_g( rfc_index *p_idx , const void *p_data , void **p_all , int p_n , int *p_index );

/* find nearest item in index */
static int
	_rfc_idx_find_near( rfc_index *p_idx , const void *p_data , void **p_all , int p_n , short p_first );

/* get array position by index position */
static int
	_rfc_idx_get_pos( rfc_index *p_idx , int p_index );
/* resize index space */
static void
	_rfc_idx_resize( rfc_index *p_idx , int p_n );
/* clear index data */
static void
	_rfc_idx_remove_all( rfc_index *p_idx );

/*#######################################################*/
/*#######################################################*/
/* array functions */

/* construction */
rfc_array *
	rfc_arr_create( int p_indexes )
{
	rfc_array *l_arr;

	l_arr = ( rfc_array * )calloc( 1 , sizeof( rfc_array ) );
	l_arr -> s_a = RFC_ARRAY_BLOCK;
	l_arr -> s_p = ( void ** )calloc( l_arr -> s_a , sizeof( void * ) );
	l_arr -> s_i_n = p_indexes;

	return( l_arr );
}

void
	rfc_arr_destroy( rfc_array *p_arr )
{
	if( p_arr -> s_ref-- )
		return;

	rfc_arr_init( p_arr );
	free( p_arr );
}

void				
	rfc_arr_ref( rfc_array *p_arr )
{
	p_arr -> s_ref++;
}

/*#######################################################*/
/*#######################################################*/
/* operations */
/* set index to array ('V'oid,'S'tring,'L'ong,'P'ointer to string) */
void
	rfc_arr_index_set( rfc_array *p_arr , int p_index , int p_offset , int p_size , char p_type )
{
	if( p_arr -> s_n > 0 )
		return;

	/* ensure space exists */
	rfc_arr_allocate( p_arr , 1 );
	p_arr -> s_i[ p_index ] = _rfc_idx_create( p_offset , p_size , p_type );
}

/* add index to array */
int
	rfc_arr_index_add( rfc_array *p_arr , int p_offset , int p_size , char p_type )
{
	rfc_index *l_idx;
	int k , n;
	int l_act;
	void *l_data;

	if(	p_arr -> s_i_n == RFC_ARRAY_MAX_INDEX )
		return( -1 );

	if( p_arr -> s_actual != p_arr -> s_n )
		return( -1 );

	/* ensure space exists */
	rfc_arr_allocate( p_arr , 1 );

	l_idx = _rfc_idx_create( p_offset , p_size , p_type );
	p_arr -> s_i[ p_arr -> s_i_n ] = l_idx;

	_rfc_idx_resize( l_idx , p_arr -> s_a );

	if( p_arr -> s_n == 0 )
		return( p_arr -> s_i_n++ );

	/* add data to index */
	n = p_arr -> s_n + p_arr -> s_d;
	l_act = 0;
	for( k = 0; k < n; k++ )
		{
			l_data = p_arr -> s_p[ k ];
			if( l_data == NULL )
				continue;

			_rfc_idx_add( l_idx , l_data , k , p_arr -> s_p , l_act++ );
		}
	
	return( p_arr -> s_i_n++ );
}

/* remove index from array */
void
	rfc_arr_index_remove( rfc_array *p_arr , int p_index )
{
	rfc_index *l_idx;
	int k;

	if( p_index < 0 || p_index >= p_arr -> s_i_n )
		return;

	l_idx = p_arr -> s_i[ p_index ];
	if( l_idx == NULL )
		return;

	_rfc_idx_destroy( l_idx );
	for( k = p_index + 1; k < p_arr -> s_i_n ; k++ )
		p_arr -> s_i[ k - 1 ] = p_arr -> s_i[ k ];
	p_arr -> s_i[ --p_arr -> s_i_n ] = NULL;

	if( p_arr -> s_i_n == 0 )
		p_arr -> s_actual = p_arr -> s_n;
}

/* add data to array */
int
	rfc_arr_add( rfc_array *p_arr , void *p_data )
{
	int k;
	int l_pos;

	/* check allocation */
	if( p_arr -> s_a == ( p_arr -> s_n + p_arr -> s_d ) )
		rfc_arr_allocate( p_arr , p_arr -> s_a + 1 );

	l_pos = p_arr -> s_n;

	/* check deleted */
	if( p_arr -> s_d > 0 )
		{
			for( k = 0; k < p_arr -> s_n + p_arr -> s_d; k++ )
				if( p_arr -> s_p[ k ] == NULL )
					break;
			p_arr -> s_d--;
			l_pos = k;
		}
	else
		p_arr -> s_p[ p_arr -> s_n ] = NULL;

	/* reindex */
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_add( p_arr -> s_i[ k ] , p_data , l_pos , p_arr -> s_p , p_arr -> s_actual );

	p_arr -> s_n++;
	p_arr -> s_actual++;
	p_arr -> s_p[ l_pos ] = p_data;

	return( l_pos );
}

/* set data to array */
int
	rfc_arr_set( rfc_array *p_arr , int p_pos , void *p_data )
{
	int k;

	if( p_pos < 0 )
		return( -1 );

	/* reallocate */
	if( p_pos >= p_arr -> s_a )
		rfc_arr_allocate( p_arr , p_pos + 1 );

	/* check after margin */
	if( p_pos >= ( p_arr -> s_n + p_arr -> s_d ) )
		{
			/* clear area - set as deleted */
			memset( &p_arr -> s_p[ p_arr -> s_n + p_arr -> s_d ] , 0 , sizeof( void * ) * ( p_pos - p_arr -> s_n - p_arr -> s_d + 1 ) );
			p_arr -> s_d += p_pos - p_arr -> s_n - p_arr -> s_d;
		}
	else
		{
			/* remove old pointer */
			if( p_arr -> s_p[ p_pos ] != NULL )
				{
					rfc_arr_remove( p_arr , p_pos );
					if( p_pos < p_arr -> s_n + p_arr -> s_d )
						p_arr -> s_d--;
				}
			else
				p_arr -> s_d--;
		}

	/* reindex */
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_add( p_arr -> s_i[ k ] , p_data , p_pos , p_arr -> s_p , p_arr -> s_actual );

	p_arr -> s_n++;
	p_arr -> s_actual++;
	p_arr -> s_p[ p_pos ] = p_data;

	return( p_pos );
}

/* remove by position */
void
	rfc_arr_remove( rfc_array *p_arr , int p_pos )
{
	if( p_pos < 0 || p_pos >= ( p_arr -> s_n + p_arr -> s_d ) )
		return;

	if( p_arr -> s_p[ p_pos ] == NULL )
		return;

	rfc_arr_remove_indexes( p_arr , p_pos );
	rfc_arr_remove_item( p_arr , p_pos );
}

/* remove item from array only */
void
	rfc_arr_remove_item( rfc_array *p_arr , int p_pos )
{
	if( p_pos < 0 )
		return;

	p_arr -> s_p[ p_pos ] = NULL;

	p_arr -> s_n--;
	if( p_pos != ( p_arr -> s_n + p_arr -> s_d ) )
		p_arr -> s_d++;
}

/* remove item by pointer */
int
	rfc_arr_remove_data( rfc_array *p_arr , void *p_data )
{
	int k , n;

	if( p_data == NULL )
		return( -1 );
	n = p_arr -> s_n + p_arr -> s_d;
	for( k = 0; k < n; k++ )
		if( p_arr -> s_p[ k ] == p_data )
			{
				rfc_arr_remove( p_arr , k );
				return( k );
			}
	
	if( k == p_arr -> s_n )
		return( -1 );
	return( 0 );
}

/* remove item & shift positions */
void
	rfc_arr_remove_shift( rfc_array *p_arr , int p_pos )
{
	int k , n;

	if( p_pos < 0 ||
		p_pos >= rfc_arr_margin( p_arr ) )
		return;

	/* remove from indexes */
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_remove_shift( p_arr -> s_i[ k ] , p_pos , p_arr -> s_actual );
	p_arr -> s_actual--;
	p_arr -> s_n--;

	/* shift positions */
	n = p_arr -> s_n + p_arr -> s_d;
	for( k = p_pos; k < n; k++ )
		p_arr -> s_p[ k ] = p_arr -> s_p[ k + 1 ];
}

/* insert item & shift positions */
void
	rfc_arr_add_shift( rfc_array *p_arr , int p_pos , void *p_data )
{
	int k;

	/* shift positions */
	if( ( p_arr -> s_n + p_arr -> s_d ) == p_arr -> s_a )
		rfc_arr_allocate( p_arr , p_arr -> s_a + 1 );

	for( k = p_arr -> s_n + p_arr -> s_d; k > p_pos; k-- )
		p_arr -> s_p[ k ] = p_arr -> s_p[ k - 1 ];

	p_arr -> s_p[ p_pos ] = p_data;
	p_arr -> s_n++;

	/* shift in indexes */
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_add_shift( p_arr -> s_i[ k ] , p_data , p_pos , p_arr -> s_p , p_arr -> s_actual );

	p_arr -> s_actual++;
}

/* clear array */
void
	rfc_arr_remove_all( rfc_array *p_arr )
{
	int k;

	/* destroy */
	free( p_arr -> s_p );

	p_arr -> s_p = NULL;
	p_arr -> s_n = 0;
	p_arr -> s_a = 0;
	p_arr -> s_d = 0;
	p_arr -> s_actual = 0;

	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_remove_all( p_arr -> s_i[ k ] );

	/* init */
	rfc_arr_allocate( p_arr , 1 );
}

/* allocate array memory to given count */
void
	rfc_arr_allocate( rfc_array *p_arr , int p_count )
{
	int k;

	if( p_arr -> s_a >= p_count )
		return;

	/* align */
	if( p_count % RFC_ARRAY_BLOCK )
		p_count += RFC_ARRAY_BLOCK - ( p_count % RFC_ARRAY_BLOCK );

	/* reallocate */
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_resize( p_arr -> s_i[ k ] , p_count );

	if( p_arr -> s_a )
		p_arr -> s_p = ( void ** )realloc( p_arr -> s_p , p_count * sizeof( void * ) );
	else
		p_arr -> s_p = ( void ** )calloc( p_count , sizeof( void * ) );
	p_arr -> s_a = p_count;
}

/* clear array without reallocate memory */
void
	rfc_arr_clear( rfc_array *p_arr )
{
	p_arr -> s_n = p_arr -> s_d = p_arr -> s_actual = 0;
}

/* clear array with free intenal memory without destroy struct */
void
	rfc_arr_init( rfc_array *p_arr )
{
	int k;

	if( p_arr -> s_p != NULL )
		free( p_arr -> s_p );
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_destroy( p_arr -> s_i[ k ] );
	memset( p_arr , 0 , sizeof( rfc_array ) );
}

/* remove item by position with free memory */
void
	rfc_arr_free_pos( rfc_array *p_arr , int p_pos )
{
	void *l_data;

	l_data = rfc_arr_get( p_arr , p_pos );
	if( l_data == NULL )
		return;

	rfc_arr_remove( p_arr , p_pos );
	free( l_data );
}

/* clear array with free memory */
void
	rfc_arr_free_all( rfc_array *p_arr )
{
	int k , n;
	void *l_data;

	n = rfc_arr_margin( p_arr );
	for( k = 0; k < n; k++ )
		{
			l_data = rfc_arr_get( p_arr , k );
			if( l_data != NULL )
				free( l_data );
		}

	p_arr -> s_n = 0;
	p_arr -> s_d = 0;
	p_arr -> s_actual = 0;
}

/* find data by index */
void *
	rfc_arr_find( rfc_array *p_arr , int p_index , const void *p_data )
{
	int l_k;

	l_k = rfc_arr_find_id( p_arr , p_index , p_data );
	if( l_k < 0 )
		return( NULL );

	return( p_arr -> s_p[ l_k ] );
}

/* find position by index */
int
	rfc_arr_find_id( rfc_array *p_arr , int p_index , const void *p_data )
{
	int l_k;

	l_k = -1;
	switch( p_arr -> s_i[ p_index ] -> s_type )
		{
			case 'V' : l_k = _rfc_idx_find_v( p_arr -> s_i[ p_index ] , p_data , p_arr -> s_p , p_arr -> s_actual , NULL ); break;
			case 'S' : l_k = _rfc_idx_find_s( p_arr -> s_i[ p_index ] , ( const char * )p_data , p_arr -> s_p , p_arr -> s_actual , NULL ); break;
			case 'L' : l_k = _rfc_idx_find_l( p_arr -> s_i[ p_index ] , *( const long * )p_data , p_arr -> s_p , p_arr -> s_actual , NULL ); break;
			case 'P' : l_k = _rfc_idx_find_p( p_arr -> s_i[ p_index ] , ( const char * )p_data , p_arr -> s_p , p_arr -> s_actual , NULL ); break;
			case 'G' : l_k = _rfc_idx_find_g( p_arr -> s_i[ p_index ] , p_data , p_arr -> s_p , p_arr -> s_actual , NULL ); break;
		}
	return( l_k );
}

/* find index position */
int
	rfc_arr_find_index( rfc_array *p_arr , int p_index , const void *p_data )
{
	int l_k;
	int l_index;

	l_k = -1;
	switch( p_arr -> s_i[ p_index ] -> s_type )
		{
			case 'V' : l_k = _rfc_idx_find_v( p_arr -> s_i[ p_index ] , p_data , p_arr -> s_p , p_arr -> s_actual , &l_index ); break;
			case 'S' : l_k = _rfc_idx_find_s( p_arr -> s_i[ p_index ] , ( const char * )p_data , p_arr -> s_p , p_arr -> s_actual , &l_index ); break;
			case 'L' : l_k = _rfc_idx_find_l( p_arr -> s_i[ p_index ] , *( const long * )p_data , p_arr -> s_p , p_arr -> s_actual , &l_index ); break;
			case 'P' : l_k = _rfc_idx_find_p( p_arr -> s_i[ p_index ] , ( const char * )p_data , p_arr -> s_p , p_arr -> s_actual , &l_index ); break;
			case 'G' : l_k = _rfc_idx_find_g( p_arr -> s_i[ p_index ] , p_data , p_arr -> s_p , p_arr -> s_actual , &l_index ); break;
		}

	if( l_k < 0 )
		return( -1 );

	return( l_index );
}

/* find index position range - return match count */
int
	rfc_arr_find_range( rfc_array *p_arr , int p_index , const void *p_data , int *p_idx_start , int *p_idx_stop )
{
	int l_k;
	rfc_index *l_idx;
	int l_idx_from;
	int l_idx_to;

	if( p_index < 0 ||
		p_index >= p_arr -> s_i_n )
		return( -1 );
	l_idx = p_arr -> s_i[ p_index ];
	if( l_idx == NULL )
		return( -1 );

	l_idx_from = _rfc_idx_find_near( l_idx , p_data , p_arr -> s_p , p_arr -> s_actual , 1 );
	l_idx_to = _rfc_idx_find_near( l_idx , p_data , p_arr -> s_p , p_arr -> s_actual , 0 );
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

/* find index position subkey range - return match count */
int
	rfc_arr_find_subrange( rfc_array *p_arr , int p_index , const void *p_data , int *p_idx_start , int *p_idx_stop , int p_size )
{
	int l_k;
	rfc_index *l_idx;
	int l_save_size;
	int l_idx_size;

	if( p_index < 0 ||
		p_index >= p_arr -> s_i_n )
		return( -1 );
	l_idx = p_arr -> s_i[ p_index ];
	if( l_idx == NULL )
		return( -1 );

	l_idx_size = l_save_size = l_idx -> s_size;
	if( l_idx -> s_type == 'S' ||
		l_idx -> s_type == 'P' )
		l_idx_size = p_size;

	if( p_size < l_idx_size )
		l_idx -> s_size = p_size;
	l_k = rfc_arr_find_range( p_arr , p_index , p_data , p_idx_start , p_idx_stop ); 
	l_idx -> s_size = l_save_size;

	return( l_k );
}

/* find first index position for item data >= p_data by sort order */
int
	rfc_arr_find_first( rfc_array *p_arr , int p_index , const void *p_data )
{
	rfc_index *l_idx;

	if( p_index < 0 ||
		p_index >= p_arr -> s_i_n )
		return( -1 );
	l_idx = p_arr -> s_i[ p_index ];
	if( l_idx == NULL )
		return( -1 );
	return( _rfc_idx_find_near( l_idx , p_data , p_arr -> s_p , p_arr -> s_actual , 1 ) );
}

/* find last index position for item data <= p_data by sort order */
int
	rfc_arr_find_last( rfc_array *p_arr , int p_index , const void *p_data )
{
	rfc_index *l_idx;

	if( p_index < 0 ||
		p_index >= p_arr -> s_i_n )
		return( -1 );
	l_idx = p_arr -> s_i[ p_index ];
	if( l_idx == NULL )
		return( -1 );
	return( _rfc_idx_find_near( l_idx , p_data , p_arr -> s_p , p_arr -> s_actual , 0 ) );
}

/* remove data from indexes */
void
	rfc_arr_remove_indexes( rfc_array *p_arr , int p_pos )
{
	int k;

	if( p_pos < 0 )
		return;

	/* reindex */
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_remove( p_arr -> s_i[ k ] , p_pos , p_arr -> s_p , p_arr -> s_actual );

	p_arr -> s_actual--;
}

/* reappend data to indexes */
void
	rfc_arr_reindex( rfc_array *p_arr , int p_pos )
{
	int k;

	/* reindex */
	for( k = 0; k < p_arr -> s_i_n; k++ )
		_rfc_idx_add( p_arr -> s_i[ k ] , p_arr -> s_p[ p_pos ] , p_pos , p_arr -> s_p , p_arr -> s_actual );

	p_arr -> s_actual++;
}

/* return number of non-deleted items */
int
	rfc_arr_count( rfc_array *p_arr )
{
	return( p_arr -> s_n );
}

/* return max number of items */
int
	rfc_arr_margin( rfc_array *p_arr )
{
	return( p_arr -> s_n + p_arr -> s_d );
}

/* return number of indexed items */
int
	rfc_arr_actual( rfc_array *p_arr )
{
	return( p_arr -> s_actual );
}

/* get item by position */
void *
	rfc_arr_get( rfc_array *p_arr , int p_pos )
{
	return( p_arr -> s_p[ p_pos ] );
}

/* get array position by index position */
int
	rfc_arr_get_index( rfc_array *p_arr , int p_index , int p_pos )
{
	if( p_pos < 0 || p_pos >= p_arr -> s_actual )
		return( -1 );

	return( _rfc_idx_get_pos( p_arr -> s_i[ p_index ] , p_pos ) );
}

/*#######################################################*/
/*#######################################################*/
/* rfc_index */

/* index functions */
/* construction */
static rfc_index *
	_rfc_idx_create( int p_offset , int p_size , char p_type )
{
	rfc_index *l_idx;

	l_idx = ( rfc_index * )calloc( 1 , sizeof( rfc_index ) );
	l_idx -> s_offset = p_offset;
	if( p_type == 'L' ||
		p_type == 'P' )
		p_size = 4;
	l_idx -> s_size = p_size;
	l_idx -> s_type = p_type;

	l_idx -> s_data = ( int * )calloc( RFC_ARRAY_BLOCK , sizeof( int ) );

	return( l_idx );
}

static void
	_rfc_idx_destroy( rfc_index *p_idx )
{
	free( p_idx -> s_data );
	free( p_idx );
}

/*#######################################################*/
/*#######################################################*/
/* operations */

/* append item to index */
static void
	_rfc_idx_add( rfc_index *p_idx , void *p_data , int p_pos , void **p_all , int p_n )
{
	void *l_p;
	int *l_data;
	int l_from;
	int l_to;
	int l_ok;
	int l_res;
	int l_k;
	void *l_v;
	int n;
	int *l_x;

	l_p = ( ( char * )p_data ) + p_idx -> s_offset;
	if( p_idx -> s_type == 'P' ||
		p_idx -> s_type == 'G' )
		l_p = *( char ** )l_p;
	l_data = p_idx -> s_data;

	l_from = 0;
	l_to = p_n - 1;
	l_ok = -1;

	/* check margins */
	if( p_n == 0 )
		{
			l_data[ 0 ] = p_pos;
			return;
		}

	switch( p_idx -> s_type )
		{
			case 'V' : l_res = memcmp( l_p , ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset , p_idx -> s_size ); break;
			case 'S' : l_res = strcmp( ( char * )l_p , ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset ); break;
			case 'L' : l_res = ( *( long * )l_p ) - ( *( long * )( ( ( char * )p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset ) ); break;
			case 'P' : l_res = strcmp( ( const char * )l_p , *( char ** )( ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset ) ); break;
			case 'G' : l_res = memcmp( l_p , *( void ** )( ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset ) , p_idx -> s_size ); break;
		}
	if( l_res >= 0 )
		{
			l_data[ p_n ] = p_pos;
			return;
		}

	switch( p_idx -> s_type )
		{
			case 'V' : l_res = memcmp( l_p , ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset , p_idx -> s_size ); break;
			case 'S' : l_res = strcmp( ( char * )l_p , ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset ); break;
			case 'L' : l_res = ( *( long * )l_p ) - ( *( long * )( ( ( char * )p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset ) ); break;
			case 'P' : l_res = strcmp( ( const char * )l_p , *( char ** )( ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset ) ); break;
			case 'G' : l_res = memcmp( l_p , *( void ** )( ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset ) , p_idx -> s_size ); break;
		}
	if( l_res <= 0 )
		l_ok = 0;

	if( l_ok < 0 )
		{
			while( l_to > l_from + 1 )
				{
					l_k = ( l_to + l_from ) / 2;
					l_v = ( char * )( p_all[ l_data[ l_k ] ] ) + p_idx -> s_offset;

					switch( p_idx -> s_type )
						{
							case 'V' : l_res = memcmp( l_p , l_v , p_idx -> s_size ); break;
							case 'S' : l_res = strcmp( ( char * )l_p , ( char * )l_v ); break;
							case 'L' : l_res = ( *( long * )l_p ) - ( *( long * )l_v ); break;
							case 'P' : l_res = strcmp( ( const char * )l_p , *( char ** )l_v ); break;
							case 'G' : l_res = memcmp( l_p , *( void ** )l_v , p_idx -> s_size ); break;
						}
					if( l_res == 0 )
						{
							l_ok = l_k;
							break;
						}

					if( l_res > 0 )
						l_from = l_k;
					else
						l_to = l_k;
				}

			if( l_ok < 0 )
				l_ok = l_to;
		}

	/* shift from l_ok */
	n = p_n - l_ok;
	l_x = l_data + p_n;
	while( n-- )
		{
			*l_x = *( l_x - 1 );
			l_x--;
		}

	l_data[ l_ok ] = p_pos;
}

/* remove item */
static int
	_rfc_idx_remove( rfc_index *p_idx , int p_pos , void **p_all , int p_n )
{
	void *l_x;
	int l_pos;
	int l_k;
	int *l_data;

	l_x = ( char * )( p_all[ p_pos ] ) + p_idx -> s_offset;
	switch( p_idx -> s_type )
		{
			case 'V' :
				if( _rfc_idx_find_v( p_idx , l_x , p_all , p_n , &l_pos ) < 0 )
					return( -1 );
				break;
			case 'S' :
				if( _rfc_idx_find_s( p_idx , ( char * )l_x , p_all , p_n , &l_pos ) < 0 )
					return( -1 );
				break;
			case 'L' :
				if( _rfc_idx_find_l( p_idx , *( long * )l_x , p_all , p_n , &l_pos ) < 0 )
					return( -1 );
				break;
			case 'P' :
				if( _rfc_idx_find_p( p_idx , *( char ** )l_x , p_all , p_n , &l_pos ) < 0 )
					return( -1 );
				break;
			case 'G' :
				if( _rfc_idx_find_g( p_idx , *( void ** )l_x , p_all , p_n , &l_pos ) < 0 )
					return( -1 );
				break;
		}

	/* find index */
	l_data = p_idx -> s_data;
	l_k = l_pos;
	while( l_k >= 0 )
		if( l_data[ l_k ] == p_pos )
			break;
		else
			l_k--;

	if( l_k < 0 )
		{
			l_k = l_pos;
			while( l_k < p_n )
				if( l_data[ l_k ] == p_pos )
					break;
				else
					l_k++;
		}

	/* remove at l_k - shift */
	memmove( &l_data[ l_k ] , &l_data[ l_k + 1 ] , ( p_n - l_k - 1 ) * sizeof( int ) );

	return( l_k );
}

/* remove item & shift positions */
static void
	_rfc_idx_remove_shift( rfc_index *p_idx , int p_pos , int p_count )
{
	int *l_get;
	int *l_set;
	int k;

	l_get = p_idx -> s_data;
	l_set = p_idx -> s_data;
	for( k = 0; k < p_count; k++ )
		{
			int l_pos = *l_get++;
			if( l_pos == p_pos )
				continue;

			if( l_pos < p_pos )
				{
					l_set++;
					continue;
				}

			*l_set++ = --l_pos;
		}
}

/* add item & shift positions */
static void
	_rfc_idx_add_shift( rfc_index *p_idx , void *p_data , int p_pos , void **p_all , int p_n )
{
	int k;
	int *l_data;

	l_data = p_idx -> s_data;

	/* shift data */
	for( k = 0; k < p_n; k++ )
		if( l_data[ k ] >= p_pos )
			l_data[ k ]++;

	_rfc_idx_add( p_idx , p_data , p_pos , p_all , p_n );
}

/* find <Void> item */
static int
	_rfc_idx_find_v( rfc_index *p_idx , const void *p_data , void **p_all , int p_n , int *p_index )
{
	const void *l_p;
	int l_from;
	int l_to;
	int l_ok;
	void *l_v;
	int l_res;
	int *l_data;
	int l_k;

	l_p = p_data;

	l_from = 0;
	l_to = p_n - 1;
	l_ok = -1;
	l_data = p_idx -> s_data;

	/* check margins */
	if( p_n == 0 )
		return( -1 );

	l_v = ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset;
	l_res = memcmp( l_p , l_v , p_idx -> s_size );
	if( l_res > 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = l_to;
			return( l_data[ l_to ] );
		}

	l_v = ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset;
	l_res = memcmp( l_p , l_v , p_idx -> s_size );
	if( l_res < 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = 0;
			return( l_data[ 0 ] );
		}

	if( l_ok < 0 )
		{
			while( l_to > l_from )
				{
					l_k = ( l_to + l_from ) / 2;
					l_v = ( char * )( p_all[ l_data[ l_k ] ] ) + p_idx -> s_offset;

					l_res = memcmp( l_p , l_v , p_idx -> s_size );
					if( l_res == 0 )
						{
							if( p_index != NULL )
								*p_index = l_k;
							return( l_data[ l_k ] );
						}

					if( l_res > 0 )
						{
							if( l_from == l_k )
								return( -1 );
							l_from = l_k;
						}
					else
						{
							if( l_to == l_k )
								return( -1 );
							l_to = l_k;
						}
				}

			if( l_ok < 0 )
				l_ok = l_to;
		}

	return( -1 );
}

/* find <String> item */
static int
	_rfc_idx_find_s( rfc_index *p_idx , const char *p_data , void **p_all , int p_n , int *p_index )
{
	const char *l_p;
	int l_from;
	int l_to;
	int l_ok;
	int *l_data;
	char *l_v;
	int l_res;
	int l_k;

	l_p = p_data;

	l_from = 0;
	l_to = p_n - 1;
	l_ok = -1;
	l_data = p_idx -> s_data;

	// check margins
	if( p_n == 0 )
		return( -1 );

	l_v = ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset;
	l_res = strcmp( l_p , l_v );
	if( l_res > 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = l_to;
			return( l_data[ l_to ] );
		}

	l_v = ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset;
	l_res = strcmp( l_p , l_v );
	if( l_res < 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = 0;
			return( l_data[ 0 ] );
		}

	if( l_ok < 0 )
		{
			while( l_to > l_from )
				{
					l_k = ( l_to + l_from ) / 2;
					l_v = ( char * )( p_all[ l_data[ l_k ] ] ) + p_idx -> s_offset;

					l_res = strcmp( l_p , l_v );
					if( l_res == 0 )
						{
							if( p_index != NULL )
								*p_index = l_k;
							return( l_data[ l_k ] );
						}

					if( l_res > 0 )
						{
							if( l_from == l_k )
								return( -1 );
							l_from = l_k;
						}
					else
						{
							if( l_to == l_k )
								return( -1 );
							l_to = l_k;
						}
				}

			if( l_ok < 0 )
				l_ok = l_to;
		}

	return( -1 );
}

/* find <Long> item */
static int
	_rfc_idx_find_l( rfc_index *p_idx , long p_data , void **p_all , int p_n , int *p_index )
{
	long l_p;
	int l_from;
	int l_to;
	int l_ok;
	int *l_data;
	long *l_v;
	int l_res;
	int l_k;

	l_p = p_data;

	l_from = 0;
	l_to = p_n - 1;
	l_ok = -1;
	l_data = p_idx -> s_data;

	/* check margins */
	if( p_n == 0 )
		return( -1 );

	l_v = ( long * )( ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset );
	l_res = l_p - *l_v;
	if( l_res > 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = l_to;
			return( l_data[ l_to ] );
		}

	l_v = ( long * )( ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset );
	l_res = l_p - *l_v;
	if( l_res < 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = 0;
			return( l_data[ 0 ] );
		}

	if( l_ok < 0 )
		{
			while( l_to > l_from )
				{
					l_k = ( l_to + l_from ) / 2;
					l_v = ( long * )( ( char * )( p_all[ l_data[ l_k ] ] ) + p_idx -> s_offset );

					l_res = l_p - *l_v;
					if( l_res == 0 )
						{
							if( p_index != NULL )
								*p_index = l_k;
							return( l_data[ l_k ] );
						}

					if( l_res > 0 )
						{
							if( l_from == l_k )
								return( -1 );
							l_from = l_k;
						}
					else
						{
							if( l_to == l_k )
								return( -1 );
							l_to = l_k;
						}
				}

			if( l_ok < 0 )
				l_ok = l_to;
		}

	return( -1 );
}

/* find <Pointer to string> item */
static int
	_rfc_idx_find_p( rfc_index *p_idx , const char *p_data , void **p_all , int p_n , int *p_index )
{
	const char *l_p;
	int l_from;
	int l_to;
	int l_ok;
	int *l_data;
	char *l_v;
	int l_res;
	int l_k;

	l_p = p_data;

	l_from = 0;
	l_to = p_n - 1;
	l_ok = -1;
	l_data = p_idx -> s_data;

	// check margins
	if( p_n == 0 )
		return( -1 );

	l_v = *( char ** )( ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset );
	l_res = strcmp( l_p , l_v );
	if( l_res > 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = l_to;
			return( l_data[ l_to ] );
		}

	l_v = *( char ** )( ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset );
	l_res = strcmp( l_p , l_v );
	if( l_res < 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = 0;
			return( l_data[ 0 ] );
		}

	if( l_ok < 0 )
		{
			while( l_to > l_from )
				{
					l_k = ( l_to + l_from ) / 2;
					l_v = *( char ** )( ( char * )( p_all[ l_data[ l_k ] ] ) + p_idx -> s_offset );

					l_res = strcmp( l_p , l_v );
					if( l_res == 0 )
						{
							if( p_index != NULL )
								*p_index = l_k;
							return( l_data[ l_k ] );
						}

					if( l_res > 0 )
						{
							if( l_from == l_k )
								return( -1 );
							l_from = l_k;
						}
					else
						{
							if( l_to == l_k )
								return( -1 );
							l_to = l_k;
						}
				}

			if( l_ok < 0 )
				l_ok = l_to;
		}

	return( -1 );
}

/* find <Generic pointer> item */
static int
	_rfc_idx_find_g( rfc_index *p_idx , const void *p_data , void **p_all , int p_n , int *p_index )
{
	const void *l_p;
	int l_from;
	int l_to;
	int l_ok;
	void *l_v;
	int l_res;
	int *l_data;
	int l_k;

	l_p = p_data;

	l_from = 0;
	l_to = p_n - 1;
	l_ok = -1;
	l_data = p_idx -> s_data;

	/* check margins */
	if( p_n == 0 )
		return( -1 );

	l_v = *( void ** )( ( char * )( p_all[ l_data[ l_to ] ] ) + p_idx -> s_offset );
	l_res = memcmp( l_p , l_v , p_idx -> s_size );
	if( l_res > 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = l_to;
			return( l_data[ l_to ] );
		}

	l_v = *( void ** )( ( char * )( p_all[ l_data[ 0 ] ] ) + p_idx -> s_offset );
	l_res = memcmp( l_p , l_v , p_idx -> s_size );
	if( l_res < 0 )
		return( -1 );

	if( l_res == 0 )
		{
			if( p_index != NULL )
				*p_index = 0;
			return( l_data[ 0 ] );
		}

	if( l_ok < 0 )
		{
			while( l_to > l_from )
				{
					l_k = ( l_to + l_from ) / 2;
					l_v = *( void ** )( ( char * )( p_all[ l_data[ l_k ] ] ) + p_idx -> s_offset );

					l_res = memcmp( l_p , l_v , p_idx -> s_size );
					if( l_res == 0 )
						{
							if( p_index != NULL )
								*p_index = l_k;
							return( l_data[ l_k ] );
						}

					if( l_res > 0 )
						{
							if( l_from == l_k )
								return( -1 );
							l_from = l_k;
						}
					else
						{
							if( l_to == l_k )
								return( -1 );
							l_to = l_k;
						}
				}

			if( l_ok < 0 )
				l_ok = l_to;
		}

	return( -1 );
}

/* get array position by index position */
static int
	_rfc_idx_get_pos( rfc_index *p_idx , int p_index )
{
	return( p_idx -> s_data[ p_index ] );
}

/* resize index space */
static void
	_rfc_idx_resize( rfc_index *p_idx , int p_n )
{
	p_idx -> s_data = ( int * )realloc( p_idx -> s_data , p_n * sizeof( int ) );
}

/* clear index data */
static void
	_rfc_idx_remove_all( rfc_index *p_idx )
{
	/* destroy */
	free( p_idx -> s_data );

	/* init */
	p_idx -> s_data = ( int * )calloc( RFC_ARRAY_BLOCK , sizeof( int ) );
}

/* find nearest item in index */
static int
	_rfc_idx_find_near( rfc_index *p_idx , const void *p_data , void **p_all , int p_n , short p_first )
{
	const void *l_p;
	int *l_data;
	int l_from;
	int l_to;
	int l_res;
	int l_k;
	void *l_v;
	int l_size;
	int l_offset;

	l_size = p_idx -> s_size;
	l_offset = p_idx -> s_offset;

	l_p = p_data;
	l_data = p_idx -> s_data;

	l_from = 0;
	l_to = p_n - 1;

	/* check margins */
	if( p_n == 0 )
		return( -1 );

	switch( p_idx -> s_type )
		{
			case 'V' : l_res = memcmp( l_p , ( char * )( p_all[ l_data[ l_to ] ] ) + l_offset , l_size ); break;
			case 'S' : l_res = strcmp( ( char * )l_p , ( char * )( p_all[ l_data[ l_to ] ] ) + l_offset ); break;
			case 'L' : l_res = ( *( long * )l_p ) - ( *( long * )( ( ( char * )p_all[ l_data[ l_to ] ] ) + l_offset ) ); break;
			case 'P' : l_res = strcmp( ( const char * )l_p , *( char ** )( ( char * )( p_all[ l_data[ l_to ] ] ) + l_offset ) ); break;
			case 'G' : l_res = memcmp( l_p , *( void ** )( ( char * )( p_all[ l_data[ l_to ] ] ) + l_offset ) , l_size ); break;
		}
	if( p_first )
		{
			if( l_res > 0 )
				return( -1 );
			if( p_n == 1 )
				return( 0 );
		}
	else
		{
			if( l_res >= 0 )
				return( l_to );
			if( p_n == 1 )
				return( -1 );
		}

	switch( p_idx -> s_type )
		{
			case 'V' : l_res = memcmp( l_p , ( char * )( p_all[ l_data[ 0 ] ] ) + l_offset , l_size ); break;
			case 'S' : l_res = strcmp( ( char * )l_p , ( char * )( p_all[ l_data[ 0 ] ] ) + l_offset ); break;
			case 'L' : l_res = ( *( long * )l_p ) - ( *( long * )( ( ( char * )p_all[ l_data[ 0 ] ] ) + l_offset ) ); break;
			case 'P' : l_res = strcmp( ( const char * )l_p , *( char ** )( ( char * )( p_all[ l_data[ 0 ] ] ) + l_offset ) ); break;
			case 'G' : l_res = memcmp( l_p , *( void ** )( ( char * )( p_all[ l_data[ 0 ] ] ) + l_offset ) , l_size ); break;
		}
	if( l_res <= 0 && p_first )
		return( 0 );
	if( l_res < 0 && !p_first )
		return( -1 );

	while( l_to > l_from + 1 )
		{
			l_k = ( l_to + l_from ) / 2;
			l_v = ( char * )( p_all[ l_data[ l_k ] ] ) + l_offset;

			switch( p_idx -> s_type )
				{
					case 'V' : l_res = memcmp( l_p , l_v , l_size ); break;
					case 'S' : l_res = strcmp( ( char * )l_p , ( char * )l_v ); break;
					case 'L' : l_res = ( *( long * )l_p ) - ( *( long * )l_v ); break;
					case 'P' : l_res = strcmp( ( const char * )l_p , *( char ** )l_v ); break;
					case 'G' : l_res = memcmp( l_p , *( void ** )l_v , l_size ); break;
				}
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

