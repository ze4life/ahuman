/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

#define RFC_MAP_MINITEMS		8

/*#######################################################*/
/*#######################################################*/
/* complex key map */

/* make key */
static void
	_rfc_map_makekey( rfc_map *p_map , rfc_mapentry *p_e , const void **p_key )
{
	int k , n;
	short *l_isnum;

	n = p_map -> s_axis_n;
	l_isnum = p_map -> s_axis_isnum;

	for( k = 0; k < n; k++ , l_isnum++ , p_key++ )
		if( *l_isnum )
			p_e -> s_key[ k ].u_l = ( int )*p_key;
		else
			p_e -> s_key[ k ].u_s = ( const char * )*p_key;
}

/* compare keys */
static int
	_rfc_map_cmp( rfc_map *p_map , rfc_mapentry *p_e1 , rfc_mapentry *p_e2 )
{
	int k , n;
	int l_e1n;
	int l_e2n;
	int l_res;

	/* compare items by keys */
	n = p_map -> s_axis_n;
	for( k = 0; k < n; k++ )
		if( p_map -> s_axis_isnum[ k ] )
			{
				l_e1n = p_e1 -> s_key[ k ].u_l;
				l_e2n = p_e2 -> s_key[ k ].u_l;
				if( l_e1n > l_e2n )
					return( 1 );
				if( l_e1n < l_e2n )
					return( -1 );
			}
		else
			{
				l_res = strcmp( p_e1 -> s_key[ k ].u_s , p_e2 -> s_key[ k ].u_s );
				if( l_res > 0 )
					return( 1 );
				if( l_res < 0 )
					return( -1 );
			}

	return( 0 );
}

/* find position */
static short
	_rfc_map_find( rfc_map *p_map , rfc_mapentry *p_e , int *p_pos )
{
	int l_from;
	int l_to;
	int l_pos;
	int l_res;

	l_from = 0;
	l_to = p_map -> s_n - 1;

	/* check empty */
	if( l_to < 0 )
		{
			*p_pos = 0;
			return( 0 );
		}

	/* check from */
	if( ( l_res = _rfc_map_cmp( p_map , p_e , p_map -> s_p[ l_from ] ) ) <= 0 )
		{
			*p_pos = l_from;
			if( l_res )
				return( 0 );
			return( 1 );
		}

	/* check to */
	if( ( l_res = _rfc_map_cmp( p_map , p_e , p_map -> s_p[ l_to ] ) ) >= 0 )
		{
			if( l_res )
				{
					*p_pos = l_to + 1;
					return( 0 );
				}
			*p_pos = l_to;
			return( 1 );
		}

	/* cicle */
	while( l_from < l_to )
		{
			if( ( l_from + 1 ) == l_to )
				break;

			l_pos = ( l_from + l_to ) / 2;
			l_res = _rfc_map_cmp( p_map , p_e , p_map -> s_p[ l_pos ] );
			if( !l_res )
				{
					*p_pos = l_pos;
					return( 1 );
				}

			if( l_res < 0 )
				l_to = l_pos;
			else
				l_from = l_pos;
		}

	*p_pos = l_to;
	return( 0 );
}

/*#######################################################*/
/*#######################################################*/

/* create map */
rfc_map * 
	rfc_map_create( int p_type , int p_keys , ... /*short p_isnum1 , ... , short p_isnum<p_keys> */ )
{
	va_list l_va;
	rfc_map *l_map;

	/* pass to valist version */
	va_start( l_va , p_keys );
	if( p_type == RFC_EXT_TYPECHAR )
		p_type = RFC_EXT_TYPESTRING;
	l_map = rfc_map_create_va( p_type , p_keys , l_va );
	va_end( l_va );

	return( l_map );			
}

rfc_map *
	rfc_map_create_a( int p_type , int p_keys , const short *p_isnum )
{
	rfc_map *l_map;
	int k;

	if( p_keys <= 0 )
		return( NULL );

	if( p_type == RFC_EXT_TYPECHAR )
		p_type = RFC_EXT_TYPESTRING;

	/* create struct */
	l_map = ( rfc_map * )calloc( 1 , sizeof( rfc_map ) + sizeof( short ) * p_keys );
	l_map -> s_type = p_type;
	l_map -> s_axis_n = p_keys;
	l_map -> s_axis_isnum = ( short * )&l_map[ 1 ];

	/* fill axis types */
	for( k = 0; k < p_keys; k++ )
		l_map -> s_axis_isnum[ k ] = ( p_isnum[ k ] )? 1 : 0;

	return( l_map );
}

rfc_map * 
	rfc_map_create_va( int p_type , int p_keys , va_list p_isnum )
{
	rfc_map *l_map;
	int k;

	if( p_keys <= 0 )
		return( NULL );

	if( p_type == RFC_EXT_TYPECHAR )
		p_type = RFC_EXT_TYPESTRING;

	/* create struct */
	l_map = ( rfc_map * )calloc( 1 , sizeof( rfc_map ) + sizeof( short ) * p_keys );
	l_map -> s_type = p_type;
	l_map -> s_axis_n = p_keys;
	l_map -> s_axis_isnum = ( short * )&l_map[ 1 ];

	/* fill axis types */
	for( k = 0; k < p_keys; k++ )
		l_map -> s_axis_isnum[ k ] = ( va_arg( p_isnum , int ) )? 1 : 0;

	return( l_map );
}

/* destroy map */
void
	rfc_map_drop( rfc_map *p_map )
{
	if( p_map -> s_ref-- )
		return;

	/* drop data */
	rfc_map_init( p_map );

	/* free struct */
	free( p_map );
}

/* reference map */
void
	rfc_map_ref( rfc_map *p_map )
{
	p_map -> s_ref++;
}

/* clear map without free memory */
void
	rfc_map_clear( rfc_map *p_map )
{
	int k , n;

	/* remove all item data */
	n = p_map -> s_n;
	for( k = 0; k < n; k++ )
		{
			free( p_map -> s_p[ k ] );
			p_map -> s_p[ k ] = NULL;
		}
	p_map -> s_n = 0;
}

/* remove all items with free memory */
void
	rfc_map_init( rfc_map *p_map )
{
	rfc_map_clear( p_map );

	/* remove allocation pointers */
	if( p_map -> s_a )
		{
			free( p_map -> s_p );
			p_map -> s_p = NULL;
			p_map -> s_a = 0;
		}
}

/* allocate item memory to given count */
void
	rfc_map_allocate( rfc_map *p_map , int p_count )
{
	if( p_count < RFC_MAP_MINITEMS )
		p_count = RFC_MAP_MINITEMS;
	if( p_count <= p_map -> s_a )
		return;

	/* align count */
	if( !p_map -> s_a )
		{
			/* allocate new */
			p_map -> s_a = p_count;
			p_map -> s_p = ( rfc_mapentry ** )calloc( p_map -> s_a , sizeof( rfc_mapentry * ) );
			return;
		}

	/* reallocate */
	while( p_map -> s_a < p_count )
		p_map -> s_a *= 2;

	p_count = p_map -> s_a / 2;
	p_map -> s_p = ( rfc_mapentry ** )realloc( p_map -> s_p , p_map -> s_a * sizeof( rfc_mapentry * ) );
	memset( &p_map -> s_p[ p_count ] , 0 , p_count * sizeof( rfc_mapentry * ) );
}

/* add item to map */
int
	rfc_map_add( rfc_map *p_map , const RFC_TYPE *p_value , ... /* {const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;
	int l_res;

	/* pass to valist */
	va_start( l_va , p_value );
	l_res = rfc_map_add_va( p_map , p_value , l_va );
	va_end( l_va );

	return( l_res );
}

extern int
	rfc_map_add_va( rfc_map *p_map , const RFC_TYPE *p_value , va_list p_key )
{
	const void *l_data[ RFC_MAP_MAXKEYS ];
	int k , n;

	/* fill array from arguments */
	n = p_map -> s_axis_n;
	for( k = 0; k < n; k++ )
		l_data[ k ] = va_arg( p_key , const void * );

	/* pass to array */
	return( rfc_map_add_a( p_map , p_value , l_data ) );
}

/* find item data */
int
	rfc_map_check( rfc_map *p_map , RFC_TYPE *p_value , ... /* {const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;
	int l_res;

	/* pass to valist */
	va_start( l_va , p_value );
	l_res = rfc_map_check_va( p_map , p_value , l_va );
	va_end( l_va );

	return( l_res );
}

int
	rfc_map_check_va( rfc_map *p_map , RFC_TYPE *p_value , va_list p_key )
{
	const void *l_data[ RFC_MAP_MAXKEYS ];
	int k , n;

	/* fill array from arguments */
	n = p_map -> s_axis_n;
	for( k = 0; k < n; k++ )
		l_data[ k ] = va_arg( p_key , const void * );

	/* pass to array */
	return( rfc_map_check_a( p_map , p_value , l_data ) );
}

/* remove item by position */
short
	rfc_map_remove( rfc_map *p_map , int p_pos , RFC_TYPE *p_value )
{
	if( p_pos < 0 ||
		p_pos >= p_map -> s_n )
		return( 0 );

	/* get current value */
	if( p_value != NULL ) {
		if( p_map -> s_type == RFC_EXT_TYPESTRING )
			p_value -> u_s = p_map -> s_p[ p_pos ] -> s_value.u_s;
		else
			rfc_type_set( p_map -> s_type , p_value , &p_map -> s_p[ p_pos ] -> s_value , NULL );
	}

	/* remove by position */
	free( p_map -> s_p[ p_pos ] );
	p_map -> s_n--;
	if( p_pos < p_map -> s_n )
		{
			memmove( &p_map -> s_p[ p_pos ] , &p_map -> s_p[ p_pos + 1 ] , sizeof( rfc_mapentry * ) * ( p_map -> s_n - p_pos ) );
			p_map -> s_p[ p_map -> s_n ] = NULL;
		}

	return( 1 );
}

/* item count */
int
	rfc_map_count( rfc_map *p_map )
{
	return( p_map -> s_n );
}

/* get by position */
const rfc_mapentry *
	rfc_map_get( rfc_map *p_map , int p_pos )
{
	if( p_pos < 0 ||
		p_pos >= p_map -> s_n )
		return( NULL );
	return( p_map -> s_p[ p_pos ] );
}

/* set item by position */
short
	rfc_map_set( rfc_map *p_map , int p_pos , RFC_TYPE *p_value )
{
	rfc_mapentry *l_e;
	rfc_mapentry *l_en;
	int l_sizen;
	const char *l_s;
	int k , n;
	char *l_x;
	char *l_xn;
	int l_slen;

	if( p_pos < 0 ||
		p_pos >= p_map -> s_n )
		return( 0 );

	/* set new value */
	l_e = p_map -> s_p[ p_pos ];
	
	/* if not string - simple */
	if( p_map -> s_type != RFC_EXT_TYPESTRING )
		{
			rfc_type_set( p_map -> s_type , &l_e -> s_value , p_value , NULL );
			return( 1 );
		}

	/* get new string */
	l_s = p_value -> u_s;
	if( l_s == NULL )
		l_s = "";

	/* check no need reallocation */
	l_slen = strlen( l_s );
	if( ( l_e -> s_value.u_s - ( char * )l_e ) + l_slen + 1 <= ( int )l_e -> s_size )
		{
			strcpy( l_e -> s_value.u_s , l_s );
			return( 1 );
		}
		
	/* reallocate entry */
	l_sizen = ( l_e -> s_value.u_s - ( char * )l_e ) + strlen( l_s ) + 1;
	l_en = ( rfc_mapentry * )realloc( l_e , l_sizen );
	l_en -> s_size = l_sizen;

	/* if the same address */
	if( l_e == l_en )
		{
			strcpy( l_e -> s_value.u_s , l_s );
			return( 1 );
		}

	l_x = ( char * )l_e;
	l_xn = ( char * )l_en;

	/* rebase pointers */
	n = p_map -> s_axis_n;
	for( k = 0; k < n; k++ )
		if( !p_map -> s_axis_isnum[ k ] )
			l_en -> s_key[ k ].u_s = l_xn + ( l_en -> s_key[ k ].u_s - l_x );

	l_en -> s_value.u_s = l_xn + ( l_en -> s_value.u_s - l_x );
	strcpy( l_en -> s_value.u_s , l_s );

	p_map -> s_p[ p_pos ] = l_en;

	return( 1 );
}

int
	rfc_map_add_a( rfc_map *p_map , const RFC_TYPE *p_value , const void **p_key )
{
	rfc_mapentry l_key;
	int l_pos;
	int l_size;
	int k , n;
	const char *l_s;
	rfc_mapentry *l_item;
	char *l_w;

	/* make key */
	_rfc_map_makekey( p_map , &l_key , p_key );

	/* find append position */
	if( _rfc_map_find( p_map , &l_key , &l_pos ) )
		return( -1 );

	/* create entry */
	l_size = sizeof( RFC_TYPE ) + sizeof( unsigned int ) + sizeof( const char * ) * p_map -> s_axis_n;

	/* count key string data */
	n = p_map -> s_axis_n;
	for( k = 0; k < n; k++ )
		if( !p_map -> s_axis_isnum[ k ] )
			{
				if( ( l_s = l_key.s_key[ k ].u_s ) != NULL )
					l_size += strlen( l_s );
				l_size++;
			}

	/* count string data */
	if( p_map -> s_type == RFC_EXT_TYPESTRING )
		{
			if( p_value -> u_s != NULL )
				l_size += strlen( p_value -> u_s );
			l_size++;
		}

	l_item = ( rfc_mapentry * )calloc( 1 , l_size );
	l_item -> s_size = l_size;

	/* fill item */
	l_w = ( char * )l_item;
	l_w += sizeof( RFC_TYPE ) + sizeof( unsigned int ) + sizeof( const char * ) * p_map -> s_axis_n;

	/* fill key */
	for( k = 0; k < n; k++ )
		if( p_map -> s_axis_isnum[ k ] )
			l_item -> s_key[ k ].u_l = l_key.s_key[ k ].u_l;
		else
			{
				l_item -> s_key[ k ].u_s = l_w;
				if( ( l_s = l_key.s_key[ k ].u_s ) != NULL )
					{
						strcpy( l_w , l_s );
						l_w += strlen( l_s );
					}
				l_w++;
			}

	/* fill data */
	if( p_map -> s_type != RFC_EXT_TYPESTRING )
		rfc_type_set( p_map -> s_type , &l_item -> s_value , p_value , NULL );
	else
		{
			l_item -> s_value.u_s = l_w;
			if( ( l_s = p_value -> u_s ) != NULL )
				{
					l_item -> s_value.u_s = l_w;
					strcpy( l_w , l_s );
				}
		}

	/* append item */
	/* ensure space */
	rfc_map_allocate( p_map , p_map -> s_n + 1 );

	/* shift */
	if( l_pos < p_map -> s_n )
		memmove( &p_map -> s_p[ l_pos + 1 ] , &p_map -> s_p[ l_pos ] , sizeof( rfc_mapentry * ) * ( p_map -> s_n - l_pos ) );
	p_map -> s_p[ l_pos ] = l_item;
	p_map -> s_n++;

	return( l_pos );
}

int
	rfc_map_check_a( rfc_map *p_map , RFC_TYPE *p_value , const void **p_key )
{
	int l_pos;
	rfc_mapentry l_key;

	/* make key */
	_rfc_map_makekey( p_map , &l_key , p_key );

	/* find position */
	if( !_rfc_map_find( p_map , &l_key , &l_pos ) )
		return( -1 );

	/* get data by position */
	if( p_value != NULL )  {
		if( p_map -> s_type != RFC_EXT_TYPESTRING )
			rfc_type_set( p_map -> s_type , p_value , &p_map -> s_p[ l_pos ] -> s_value , NULL );
		else
			p_value -> u_c = p_map -> s_p[ l_pos ] -> s_value.u_s;
	}

	return( l_pos );
}

