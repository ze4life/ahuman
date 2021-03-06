/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/
/* routines */

#define RFC_CB_MINITEMS			8

/* find & append key */
static rfc_cubekey *
	_rfc_cb_findaddkey( rfc_cube *p_cb , const void **p_keyval );
/* find item position in key ptr order */
static int
	_rfc_cb_getadditempos( rfc_cube *p_cb , rfc_cubekey *p_key );
/* get key position in key order */
static int
	_rfc_cb_getkeypos( rfc_cube *p_cb , rfc_cubekey *p_key );
/* get key position to add - return 1 if exists */
static short
	_rfc_cb_findaddkeypos( rfc_cube *p_cb , const void **p_keyval , int *p_pos );
/* allocate key space */
static void
	_rfc_cb_keyalloc( rfc_cube *p_cb , int p_count );
/* set key element by sort */
static void
	_rfc_cb_setkeyel( rfc_cube *p_cb , int p_el , rfc_cubekey *p_key );
/* compare keys */
static int
	_rfc_cb_keycmp( rfc_cube *p_cb , rfc_cubekey *p_key1 , rfc_cubekey *p_key2 );
/* compare values with key */
static int
	_rfc_cb_keyvalcmp( rfc_cube *p_cb , const void **p_keyval , rfc_cubekey *p_key );
/* find add key element position - numeric */
static int
	_rfc_cb_findaddkeyelpos_l( rfc_cubekey **p_sort , int p_el , int p_n , int p_val );
/* find add key element position - string */
static int
	_rfc_cb_findaddkeyelpos_s( rfc_cubekey **p_sort , int p_el , int p_n , const char *p_val );
/* find key position in element array - numeric */
static int
	_rfc_cb_findkeyelpos_l( rfc_cubekey **p_sort , int p_el , int p_n , int p_val , rfc_cubekey *p_key );
/* find key position in element array - string */
static int
	_rfc_cb_findkeyelpos_s( rfc_cubekey **p_sort , int p_el , int p_n , const char *p_val , rfc_cubekey *p_key );
/* sort pointer function */
static int
	_rfc_cb_sortptr( const void *p_e1 , const void *p_e2 );
/* get first walk key */
static int
	_rfc_cb_getfirstelkey( rfc_cube *p_cb , int p_el );
/* find first/last element order item - numeric */
static int
	_rfc_cb_findorder_l( rfc_cube *p_cb , int p_el , int p_keyval , short p_last );
/* find first/last element order item - string */
static int
	_rfc_cb_findorder_s( rfc_cube *p_cb , int p_el , const char *p_keyval , short p_last );
/* filter walk */
static int
	_rfc_cb_walktook( rfc_cube *p_cb , int p_from , int p_to );
/* walk from current to key element */
static short
	_rfc_cb_walk( rfc_cube *p_cb , int p_el );
/* get first/last item index by key */
static int
	_rfc_cb_getkeyitem( rfc_cube *p_cb , const rfc_cubekey *p_key , short p_last );

/*#######################################################*/
/*#######################################################*/
/* cube functions */

/* create cube */
rfc_cube *
	rfc_cb_create( int p_type , int p_keyels , ... /*, short s_isnum1 , ... , short s_isnum<p_keyels> */ )
{
	va_list l_va;
	rfc_cube *l_cb;

	va_start( l_va , p_keyels );
	if( p_type == RFC_EXT_TYPECHAR )
		p_type = RFC_EXT_TYPESTRING;
	l_cb = rfc_cb_create_va( p_type , p_keyels , l_va );
	va_end( l_va );

	return( l_cb );			
}

rfc_cube *
	rfc_cb_create_a( int p_type , int p_keyels , const short *p_isnum )
{
	rfc_cubekeyel *l_el;
	rfc_cube *l_cb;

	if( p_type == RFC_EXT_TYPECHAR )
		p_type = RFC_EXT_TYPESTRING;

	/* allocate memory */
	l_cb = ( rfc_cube * )calloc( 1 , sizeof( rfc_cube ) + sizeof( rfc_cubekeyel ) * p_keyels );
	l_el = l_cb -> s_keyel = ( rfc_cubekeyel * )&l_cb[ 1 ];
	l_cb -> s_type = p_type;
	l_cb -> s_keyel_n = p_keyels;
	l_cb -> s_walk_el = -1;
	l_cb -> s_walk_enumdist = -1;
	l_cb -> s_walk_enumkey = -1;
	l_cb -> s_walk_enumitem = -1;

	/* set key element numeric flags */
	for( ; p_keyels--; l_el++ )
		l_el -> s_isnum = *p_isnum++;

	return( l_cb );
}

rfc_cube *
	rfc_cb_create_va( int p_type , int p_keyels , va_list p_isnum )
{
	rfc_cubekeyel *l_el;
	rfc_cube *l_cb;

	/* allocate memory */
	l_cb = ( rfc_cube * )calloc( 1 , sizeof( rfc_cube ) + sizeof( rfc_cubekeyel ) * p_keyels );
	l_el = l_cb -> s_keyel = ( rfc_cubekeyel * )&l_cb[ 1 ];
	l_cb -> s_type = p_type;
	l_cb -> s_keyel_n = p_keyels;
	l_cb -> s_walk_el = -1;
	l_cb -> s_walk_enumdist = -1;
	l_cb -> s_walk_enumkey = -1;
	l_cb -> s_walk_enumitem = -1;

	/* set key element numeric flags */
	for( ; p_keyels--; l_el++ )
		l_el -> s_isnum = va_arg( p_isnum , int );

	return( l_cb );
}

/* destroy cube */
void
	rfc_cb_destroy( rfc_cube *p_cb )
{
	if( p_cb -> s_ref-- )
		return;

	/* init cube */
	rfc_cb_init( p_cb );

	/* free cube */
	free( p_cb );
}

/* reference cube */
void
	rfc_cb_ref( rfc_cube *p_cb )
{
	p_cb -> s_ref++;
}

/* clear cube without free memory */
void
	rfc_cb_clear( rfc_cube *p_cb )
{
	int k , n;

	/* free keys */
	n = p_cb -> s_key_n;
	for( k = 0; k < n; k++ )
		free( p_cb -> s_key[ k ] );
	p_cb -> s_key_n = 0;
	p_cb -> s_walk_n = 0;
	p_cb -> s_walk_el = -1;
	p_cb -> s_walk_enumdist = -1;
	p_cb -> s_walk_enumkey = -1;
	p_cb -> s_walk_enumitem = -1;

	/* free items */
	p_cb -> s_item_n = 0;
	rfc_map_ptrclear( &p_cb -> s_ext );
}

/* remove all items with free memory */
void
	rfc_cb_init( rfc_cube *p_cb )
{
	int k , n;
	rfc_string l_s;

	/* clear cube */
	rfc_cb_clear( p_cb );

	/* remove keys */
	if( p_cb -> s_key_a )
		{
			free( p_cb -> s_key );
			p_cb -> s_key = NULL;

			/* free key element data */
			n = p_cb -> s_keyel_n;
			for( k = 0; k < n; k++ )
				{
					free( p_cb -> s_keyel[ k ].s_sort );
					p_cb -> s_keyel[ k ].s_sort = NULL;
				}
			p_cb -> s_key_a = 0;

			/* free walk data */
			free( p_cb -> s_walk );
		}

	/* remove items */
	if( p_cb -> s_type == RFC_EXT_TYPESTRING )
		{
			n = p_cb -> s_item_a;
			for( k = 0; k < n; k++ )
				{
					l_s = p_cb -> s_item[ k ].s_data.u_s;
					if( l_s != NULL )
						rfc_str_drop( l_s );
				}
		}
	if( p_cb -> s_item_a )
		{
			free( p_cb -> s_item );
			p_cb -> s_item = NULL;
			p_cb -> s_item_a = 0;
		}
	rfc_map_ptrinit( &p_cb -> s_ext );
}

/* allocate item memory to given count */
void
	rfc_cb_allocate( rfc_cube *p_cb , int p_count )
{
	if( p_count < RFC_CB_MINITEMS )
		p_count = RFC_CB_MINITEMS;
	if( p_count <= p_cb -> s_item_a )
		return;

	/* align count */
	if( !p_cb -> s_item_a )
		{
			/* allocate new */
			p_cb -> s_item_a = p_count;
			p_cb -> s_item = ( rfc_cubeitem * )calloc( p_cb -> s_item_a , sizeof( rfc_cubeitem ) );
			return;
		}

	/* reallocate */
	p_count = p_cb -> s_item_a;
	p_cb -> s_item_a *= 2;
	p_cb -> s_item = ( rfc_cubeitem * )realloc( p_cb -> s_item , p_cb -> s_item_a * sizeof( rfc_cubeitem ) );
	memset( &p_cb -> s_item[ p_count ] , 0 , p_count * sizeof( rfc_cubeitem ) );
}

/* add item to cube */
void
	rfc_cb_add( rfc_cube *p_cb , void *p_ext , const void *p_value , ... /*{const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;
	va_start( l_va , p_value );

	rfc_cb_add_va( p_cb , p_ext , p_value , l_va );
	va_end( l_va );
}

void
	rfc_cb_add_d( rfc_cube *p_cb , void *p_ext , short p_value , ... /*{const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;
	RFC_INT64 l_v;

	va_start( l_va , p_value );

	/* check type */
	switch( p_cb -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				rfc_cb_add_va( p_cb , p_ext , &p_value , l_va );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_cb -> s_type , NULL , NULL );
				rfc_cb_add_va( p_cb , p_ext , &l_v , l_va );
				break;
		}

	va_end( l_va );
}

void
	rfc_cb_add_l( rfc_cube *p_cb , void *p_ext , int p_value , ... /*{const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;
	RFC_INT64 l_v;

	va_start( l_va , p_value );

	/* check type */
	switch( p_cb -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				rfc_cb_add_va( p_cb , p_ext , &p_value , l_va );
				break;
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPELONG , &l_v , p_cb -> s_type , NULL , NULL );
				rfc_cb_add_va( p_cb , p_ext , &l_v , l_va );
				break;
		}

	va_end( l_va );
}
	
void
	rfc_cb_add_m( rfc_cube *p_cb , void *p_ext , RFC_INT64 p_value , ... /*{const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;
	RFC_INT64 l_v;

	va_start( l_va , p_value );

	/* check type */
	switch( p_cb -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				rfc_cb_add_va( p_cb , p_ext , &p_value , l_va );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEMONEY , &l_v , p_cb -> s_type , NULL , NULL );
				rfc_cb_add_va( p_cb , p_ext , &l_v , l_va );
				break;
		}

	va_end( l_va );
}

void
	rfc_cb_add_f( rfc_cube *p_cb , void *p_ext , double p_value , ... /*{const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;
	RFC_INT64 l_v;

	va_start( l_va , p_value );

	/* check type */
	switch( p_cb -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				rfc_cb_add_va( p_cb , p_ext , &p_value , l_va );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEDOUBLE , &l_v , p_cb -> s_type , NULL , NULL );
				rfc_cb_add_va( p_cb , p_ext , &l_v , l_va );
				break;
		}

	va_end( l_va );
}

void
	rfc_cb_add_s( rfc_cube *p_cb , void *p_ext , const char *p_value , ... /*{const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;

	va_start( l_va , p_value );

	if( p_cb -> s_type == RFC_EXT_TYPESTRING ||
		p_cb -> s_type == RFC_EXT_TYPECHAR )
		rfc_cb_add_va( p_cb , p_ext , &p_value , l_va );
	va_end( l_va );
}

void
	rfc_cb_add_p( rfc_cube *p_cb , void *p_ext , void *p_value , ... /*{const char *|int} p_keyval1 , ... , {const char *|int} p_keyval<s_keyel_n> */ )
{
	va_list l_va;

	va_start( l_va , p_value );

	if( p_cb -> s_type == RFC_EXT_TYPEPTR )
		rfc_cb_add_va( p_cb , p_ext , &p_value , l_va );
	va_end( l_va );
}

void
	rfc_cb_add_a( rfc_cube *p_cb , void *p_ext , const void *p_value , const void **p_keyval )
{
	rfc_cubekey *l_key;
	int l_pos;
	RFC_INT64 l_v;
	rfc_cubeitem *l_item;
	unsigned l_id;
	int k , n;

	/* check ext unique */
	if( rfc_map_ptrcheck( &p_cb -> s_ext , p_ext , ( unsigned long * )&l_pos ) >= 0 )
		p_ext = NULL;

	/* find (and append) key */
	l_key = _rfc_cb_findaddkey( p_cb , p_keyval );

	/* append item */
	rfc_cb_allocate( p_cb , p_cb -> s_item_n + 1 );
	l_pos = _rfc_cb_getadditempos( p_cb , l_key );

	/* modify item positions because of inserting into */
	l_id = ( unsigned )l_pos;
	n = p_cb -> s_ext.s_n;
	for( k = 0; k < n; k++ )
		if( p_cb -> s_ext.s_p[ k ].s_y >= l_id )
			p_cb -> s_ext.s_p[ k ].s_y++;

	/* append ext pointer */
	if( p_ext != NULL )
		rfc_map_ptradd( &p_cb -> s_ext , p_ext , l_pos );

	/* shift tail */
	l_item = &p_cb -> s_item[ l_pos ];
	if( l_pos < p_cb -> s_item_n )
		{
			l_v = p_cb -> s_item[ p_cb -> s_item_n ].s_data.u_m;
			memmove( &p_cb -> s_item[ l_pos + 1 ] , &p_cb -> s_item[ l_pos ] , sizeof( rfc_cubeitem ) * ( p_cb -> s_item_n - l_pos ) );
			l_item -> s_data.u_m = l_v;
		}
			
	/* set item data */
	l_item -> s_key = l_key;
	l_item -> s_ext = p_ext;
	l_key -> s_head.s_ref++;
	
	rfc_type_set( p_cb -> s_type , &l_item -> s_data , p_value , NULL );
	p_cb -> s_item_n++;
}

void
	rfc_cb_add_va( rfc_cube *p_cb , void *p_ext , const void *p_value , va_list p_va )
{
	const void *l_keyval[ RFC_CB_MAXKEYELS ];
	int k , n;

	n = p_cb -> s_keyel_n;
	for( k = 0; k < n; k++ )
		if( p_cb -> s_keyel[ k ].s_isnum )
			l_keyval[ k ] = ( const void * )va_arg( p_va , int );
		else
			l_keyval[ k ] = ( const void * )va_arg( p_va , const char * );

	rfc_cb_add_a( p_cb , p_ext , p_value , l_keyval );
}

/* remove item from cube */
void
	rfc_cb_remove( rfc_cube *p_cb , void *p_ext )
{
	int l_idx;
	int l_pos;
	RFC_INT64 l_v;
	rfc_cubekey *l_key;
	rfc_cubekey **l_sort;
	int k , n;
	unsigned l_id;

	/* find item with given ext */
	if( rfc_map_ptrcheck( &p_cb -> s_ext , p_ext , ( unsigned long * )&l_pos ) < 0 )
		return;

	/* remove ext data */
	rfc_map_ptrremove( &p_cb -> s_ext , p_ext );
	n = p_cb -> s_ext.s_n;
	l_id = ( unsigned )l_pos;
	for( k = 0; k < n; k++ )
		if( p_cb -> s_ext.s_p[ k ].s_y > l_id )
			p_cb -> s_ext.s_p[ k ].s_y--;

	/* save value & shift tail */
	l_key = p_cb -> s_item[ l_pos ].s_key;
	p_cb -> s_item_n--;
	if( l_pos < p_cb -> s_item_n )
		{
			l_v = p_cb -> s_item[ l_pos ].s_data.u_m;
			memmove( &p_cb -> s_item[ l_pos ] , &p_cb -> s_item[ l_pos + 1 ] , sizeof( rfc_cubeitem ) * ( p_cb -> s_item_n - l_pos ) );
			p_cb -> s_item[ p_cb -> s_item_n ].s_data.u_m = l_v;
		}
	
	/* dereference key */
	l_key -> s_head.s_ref--;
	if( l_key -> s_head.s_ref )
		return;

	/* find key position */
	l_idx = _rfc_cb_getkeypos( p_cb , l_key );

	/* remove key */
	p_cb -> s_key_n--;
	if( l_idx < p_cb -> s_key_n )
		memmove( &p_cb -> s_key[ l_idx ] , &p_cb -> s_key[ l_idx + 1 ] , sizeof( rfc_cubekey * ) * ( p_cb -> s_key_n - l_idx ) );

	/* remove key from elements */
	n = p_cb -> s_keyel_n;
	for( k = 0; k < n; k++ )
		{
			l_sort = p_cb -> s_keyel[ k ].s_sort;
			if( p_cb -> s_keyel[ k ].s_isnum )
				l_idx = _rfc_cb_findkeyelpos_l( l_sort , k , p_cb -> s_key_n + 1 , l_key -> s_els[ k ].u_l , l_key );
			else
				l_idx = _rfc_cb_findkeyelpos_s( l_sort , k , p_cb -> s_key_n + 1 , l_key -> s_els[ k ].u_s , l_key );
			if( l_idx < p_cb -> s_key_n )
				memmove( &l_sort[ l_idx ] , &l_sort[ l_idx + 1 ] , sizeof( rfc_cubekey * ) * ( p_cb -> s_key_n - l_idx ) );
		}

	/* free key data */
	free( l_key );
}

/* get item count */
int
	rfc_cb_itemcount( rfc_cube *p_cb )
{
	return( p_cb -> s_item_n );
}

/* get item by index */
const rfc_cubeitem *
	rfc_cb_getitem( rfc_cube *p_cb , int p_pos )
{
	return( &p_cb -> s_item[ p_pos ] );
}

/* walk from current to key element - return distribute count */
int
	rfc_cb_walk( rfc_cube *p_cb , int p_el )
{
	/* make walk */
	if( !_rfc_cb_walk( p_cb , p_el ) )
		return( 0 );

	return( rfc_cb_distcount( p_cb , p_el ) );
}

/* get current walk distribution next key element value - numeric */
short
	rfc_cb_distenum_l( rfc_cube *p_cb , int *p_vptr )
{
	rfc_cubekey **l_sort;
	int k , n;
	int l_data;
	int l_walk_el;

	/* check nothing in walk */
	if( !p_cb -> s_walk_n )
		return( 0 );

	l_walk_el = p_cb -> s_walk_el;
	l_sort = p_cb -> s_keyel[ l_walk_el ].s_sort;

	/* check start */
	if( p_cb -> s_walk_enumdist < 0 )
		{
			p_cb -> s_walk_enumdist = _rfc_cb_getfirstelkey( p_cb , l_walk_el );
			*p_vptr = l_sort[ p_cb -> s_walk_enumdist ] -> s_els[ l_walk_el ].u_l;
			return( 1 );
		}

	/* get next */
	l_data = l_sort[ p_cb -> s_walk_enumdist ] -> s_els[ l_walk_el ].u_l;
	n = p_cb -> s_key_n;
	for( k = p_cb -> s_walk_enumdist + 1; k < n; k++ )
		if( l_sort[ k ] -> s_head.s_mark )
			if( l_sort[ k ] -> s_els[ l_walk_el ].u_l != l_data )
				{
					/* found */
					*p_vptr = l_sort[ k ] -> s_els[ l_walk_el ].u_l;
					p_cb -> s_walk_enumdist = k;
					return( 1 );
				}

	/* not found */
	p_cb -> s_walk_enumdist = -1;
	return( 0 );
}

/* get current walk distribution next key element value - string */
short
	rfc_cb_distenum_s( rfc_cube *p_cb , const char **p_vptr )
{
	rfc_cubekey **l_sort;
	int k , n;
	const char *l_data;
	int l_walk_el;

	/* check nothing in walk */
	if( !p_cb -> s_walk_n )
		return( 0 );

	l_walk_el = p_cb -> s_walk_el;
	l_sort = p_cb -> s_keyel[ l_walk_el ].s_sort;

	/* check start */
	if( p_cb -> s_walk_enumdist < 0 )
		{
			p_cb -> s_walk_enumdist = _rfc_cb_getfirstelkey( p_cb , l_walk_el );
			*p_vptr = l_sort[ p_cb -> s_walk_enumdist ] -> s_els[ l_walk_el ].u_s;
			return( 1 );
		}

	/* get next */
	l_data = l_sort[ p_cb -> s_walk_enumdist ] -> s_els[ l_walk_el ].u_s;
	n = p_cb -> s_key_n;
	for( k = p_cb -> s_walk_enumdist + 1; k < n; k++ )
		if( l_sort[ k ] -> s_head.s_mark )
			if( strcmp( l_sort[ k ] -> s_els[ l_walk_el ].u_s , l_data ) )
				{
					/* found */
					*p_vptr = l_sort[ k ] -> s_els[ l_walk_el ].u_s;
					p_cb -> s_walk_enumdist = k;
					return( 1 );
				}

	/* not found */
	p_cb -> s_walk_enumdist = -1;
	return( 0 );
}

/* end enum distribution */
void
	rfc_cb_enddist( rfc_cube *p_cb )
{
	p_cb -> s_walk_enumdist = -1;
}

/* from current walk get key count */
int
	rfc_cb_walkkeycount( rfc_cube *p_cb )
{
	return( p_cb -> s_walk_n );
}

/* get current walk key element */
const rfc_cubekey *
	rfc_cb_walkkey( rfc_cube *p_cb , int p_index )
{
	return( p_cb -> s_walk[ p_index ] );
}

/* get key items */
int
	rfc_cb_keyitems( rfc_cube *p_cb , const rfc_cubekey *p_key , int *p_from , int *p_to )
{
	int l_from;
	int l_to;

	l_from = _rfc_cb_getkeyitem( p_cb , p_key , 0 );
	l_to = _rfc_cb_getkeyitem( p_cb , p_key , 1 );
	if( p_from != NULL )
		*p_from = l_from;
	if( p_to != NULL )
		*p_to = l_to;

	return( l_to - l_from + 1 );
}

/* from current walk get distribute count by given axis */
int
	rfc_cb_distcount( rfc_cube *p_cb , int p_el )
{
	int l_vd;
	const char *l_vs;
	int k , n;
	int l_r;
	rfc_cubekey **l_sort;
	short l_walk;
	short l_isnum;

	l_sort = p_cb -> s_keyel[ p_el ].s_sort;
	l_isnum = p_cb -> s_keyel[ p_el ].s_isnum;
	l_walk = ( p_cb -> s_walk_el < 0 )? 0 : 1;

	if( l_walk )
		{
			if( !p_cb -> s_walk_n )
				return( 0 );
			k = _rfc_cb_getfirstelkey( p_cb , p_el );
			if( l_isnum )
				l_vd = l_sort[ k ] -> s_els[ p_el ].u_l;
			else
				l_vs = l_sort[ k ] -> s_els[ p_el ].u_s;
		}
	else
		{
			if( !p_cb -> s_key_n )
				return( 0 );
			k = 0;
		}

	/* scan keys from next key */
	l_r = 1;
	k++;
	n = p_cb -> s_key_n;
	for( ; k < n; k++ )
		{
			/* skip not in walk */
			if( l_walk )
				if( !l_sort[ k ] -> s_head.s_mark )
					continue;

			/* check value */
			if( l_isnum )
				{
					if( l_sort[ k ] -> s_els[ p_el ].u_l == l_vd )
						continue;
					l_vd = l_sort[ k ] -> s_els[ p_el ].u_l;
				}
			else
				{
					if( !strcmp( l_sort[ k ] -> s_els[ p_el ].u_s , l_vs ) )
						continue;
					l_vs = l_sort[ k ] -> s_els[ p_el ].u_s;
				}
			l_r++;
		}

	return( l_r );
}

/* from current filter walk - return key existance */
int
	rfc_cb_walkto_l( rfc_cube *p_cb , int p_keyval )
{
	int l_from;
	int l_to;

	if( !p_cb -> s_walk_n )
		return( 0 );

	/* find first by order */
	l_from = _rfc_cb_findorder_l( p_cb , p_cb -> s_walk_el , p_keyval , 0 );
	if( l_from < 0 )
		{
			rfc_cb_endwalk( p_cb );
			return( 0 );
		}
	l_to = _rfc_cb_findorder_l( p_cb , p_cb -> s_walk_el , p_keyval , 1 );

	/* filter by walk */
	return( _rfc_cb_walktook( p_cb , l_from , l_to ) );
}

int
	rfc_cb_walkto_s( rfc_cube *p_cb , const char *p_keyval )
{
	int l_from;
	int l_to;

	if( !p_cb -> s_walk_n )
		return( 0 );

	/* find first by order */
	l_from = _rfc_cb_findorder_s( p_cb , p_cb -> s_walk_el , p_keyval , 0 );
	if( l_from < 0 )
		{
			rfc_cb_endwalk( p_cb );
			return( 0 );
		}
	l_to = _rfc_cb_findorder_s( p_cb , p_cb -> s_walk_el , p_keyval , 1 );

	/* filter by walk */
	return( _rfc_cb_walktook( p_cb , l_from , l_to ) );
}

/* walk from current with filter by given axis - return subtree item count */
int
	rfc_cb_fwalk_l( rfc_cube *p_cb , int p_keyel , int p_keyval )
{
	/* first walk */
	if( !_rfc_cb_walk( p_cb , p_keyel ) )
		return( 0 );

	/* then filter */
	return( rfc_cb_walkto_l( p_cb , p_keyval ) );
}

int
	rfc_cb_fwalk_s( rfc_cube *p_cb , int p_keyel , const char *p_keyval )
{
	/* first walk */
	if( !_rfc_cb_walk( p_cb , p_keyel ) )
		return( 0 );

	/* then filter */
	return( rfc_cb_walkto_s( p_cb , p_keyval ) );
}

/* walk from root with filter by all axes */
int
	rfc_cb_mfwalk( rfc_cube *p_cb , ... /*int p_el1 , {int|const char *} p_keyval1 , ... , int p_el<n> , {int|const char *} p_keyval<n> , -1 */ )
{
	va_list l_va;
	int l_res;

	va_start( l_va , p_cb );
	
	l_res = rfc_cb_mfwalk_va( p_cb , l_va );
	va_end( l_va );

	return( l_res );
}

int
	rfc_cb_mfwalk_a( rfc_cube *p_cb , int *p_el , const void **p_keyval )
{
	int l_el;
	int l_res;

	/* iterate walks */
	l_res = p_cb -> s_walk_n;
	for( ; *p_el >= 0; p_el++ , p_keyval++ )
		{
			l_el = *p_el;
			if( p_cb -> s_keyel[ l_el ].s_isnum )
				l_res = rfc_cb_fwalk_l( p_cb , l_el , ( int )*p_keyval );
			else
				l_res = rfc_cb_fwalk_s( p_cb , l_el , ( const char * )*p_keyval );
		}

	return( l_res );
}

int
	rfc_cb_mfwalk_va( rfc_cube *p_cb , va_list p_keyval )
{
	int l_el;
	int l_res;
	int l_vd;
	const char *l_vs;

	/* iterate walks */
	l_res = p_cb -> s_walk_n;
	for( ;; )
		{
			l_el = va_arg( p_keyval , int );
			if( l_el < 0 )
				break;

			if( p_cb -> s_keyel[ l_el ].s_isnum )
				{
					l_vd = va_arg( p_keyval , int );
					l_res = rfc_cb_fwalk_l( p_cb , l_el , l_vd );
				}
			else
				{
					l_vs = va_arg( p_keyval , const char * );
					l_res = rfc_cb_fwalk_s( p_cb , l_el , l_vs );
				}
		}

	return( l_res );
}

/* scan current walk subtree items - returns NULL on end */
const rfc_cubeitem *
	rfc_cb_scan( rfc_cube *p_cb )
{
	/* s_walk & s_item both sorted by key ptr */
	if( p_cb -> s_walk_enumkey < 0 )
		{
			/* empty walk */
			if( !p_cb -> s_walk_n )
				{
					p_cb -> s_walk_enumitem++;
					if( p_cb -> s_walk_enumitem >= p_cb -> s_item_n )
						{
							/* cancel walk */
							rfc_cb_endscan( p_cb );
							return( NULL );
						}
					return( &p_cb -> s_item[ p_cb -> s_walk_enumitem ] );
				}
		}

	/* check new item */
	if( p_cb -> s_walk_enumitem >= 0 )
		{
			p_cb -> s_walk_enumitem++;
			if( p_cb -> s_walk_enumitem >= p_cb -> s_item_n )
				{
					/* cancel walk */
					rfc_cb_endscan( p_cb );
					return( NULL );
				}
			/* check need new key */
			if( p_cb -> s_walk[ p_cb -> s_walk_enumkey ] != p_cb -> s_item[ p_cb -> s_walk_enumitem ].s_key )
				p_cb -> s_walk_enumitem = -1;
		}

	/* check new key */
	if( p_cb -> s_walk_enumitem < 0 )
		{
			p_cb -> s_walk_enumkey++;

			/* check no more keys */
			if( p_cb -> s_walk_enumkey >= p_cb -> s_walk_n )
				{
					/* cancel walk */
					rfc_cb_endscan( p_cb );
					return( NULL );
				}

			/* find first item on key */
			p_cb -> s_walk_enumitem = _rfc_cb_getkeyitem( p_cb , p_cb -> s_walk[ p_cb -> s_walk_enumkey ] , 0 );
		}

	return( &p_cb -> s_item[ p_cb -> s_walk_enumitem ] );
}

/* restart scan */
void
	rfc_cb_endscan( rfc_cube *p_cb )
{
	p_cb -> s_walk_enumkey = -1;
	p_cb -> s_walk_enumitem = -1;
}

/* cancel walk */
void
	rfc_cb_endwalk( rfc_cube *p_cb )
{
	int n;
	rfc_cubekey **l_walk;
	
	/* remove marks */
	n = p_cb -> s_walk_n;
	l_walk = p_cb -> s_walk;
	while( n-- )
		(*l_walk++) -> s_head.s_mark = 0;
	p_cb -> s_walk_n = 0;
	p_cb -> s_walk_el = -1;
	p_cb -> s_walk_enumdist = -1;
}

/*#######################################################*/
/*#######################################################*/
/* routines */

/* find & append key */
static rfc_cubekey *
	_rfc_cb_findaddkey( rfc_cube *p_cb , const void **p_keyval )
{
	int l_pos;
	rfc_cubekey *l_key;
	int l_size;
	int k , n;
	char *l_ptr;
	int l_start;

	/* find key position to add (if ok - key exists) */
	if( _rfc_cb_findaddkeypos( p_cb , p_keyval , &l_pos ) )
		return( p_cb -> s_key[ l_pos ] );

	/* create key */
	n = p_cb -> s_keyel_n;
	l_start = l_size = sizeof( rfc_cubekeyhead ) + sizeof( const char * ) * n;
	for( k = 0; k < n; k++ )
		if( !p_cb -> s_keyel[ k ].s_isnum )
			{
				l_size++;
				if( p_keyval[ k ] != NULL )
					l_size += strlen( ( const char * )p_keyval[ k ] );
			}
	l_key = ( rfc_cubekey * )calloc( 1 , l_size );
	l_ptr = ( ( char * )l_key ) + l_start;

	/* allocate key space */
	_rfc_cb_keyalloc( p_cb , p_cb -> s_key_n + 1 );

	/* set key values */
	for( k = 0; k < n; k++ )
		{
			/* set key element */
			if( p_cb -> s_keyel[ k ].s_isnum )
				l_key -> s_els[ k ].u_l = ( int )p_keyval[ k ];
			else
				{
					l_key -> s_els[ k ].u_s = l_ptr;
					if( p_keyval[ k ] != NULL )
						{
							strcpy( l_ptr , ( const char * )p_keyval[ k ] );
							l_ptr += strlen( ( const char * )p_keyval[ k ] );
						}
					l_ptr++;
				}
			/* set key element by sort */
			_rfc_cb_setkeyel( p_cb , k , l_key );
		}

	/* set key to array */
	if( l_pos < p_cb -> s_key_n )
		memmove( &p_cb -> s_key[ l_pos + 1 ] , &p_cb -> s_key[ l_pos ] , sizeof( rfc_cubekey * ) * ( p_cb -> s_key_n - l_pos ) );
	p_cb -> s_key[ l_pos ] = l_key;
	p_cb -> s_key_n++;

	return( l_key );
}

/* find item position in key ptr order */
static int
	_rfc_cb_getadditempos( rfc_cube *p_cb , rfc_cubekey *p_key )
{
	int l_from;
	int l_to;
	int l_pos;
	rfc_cubeitem *l_item;

	l_from = 0;
	l_to = p_cb -> s_item_n - 1;
	l_item = p_cb -> s_item;

	/* empty array */
	if( l_to < 0 )
		return( 0 );

	/* check margins */
	if( l_item[ l_from ].s_key >= p_key )
		return( l_from );
	if( l_item[ l_to ].s_key <= p_key )
		return( l_to + 1 );

	/* binary search */
	while( l_to > l_from )
		{
			l_pos = ( l_from + l_to ) / 2;
			if( l_pos == l_from )
				return( l_to );
			if( l_item[ l_pos ].s_key == p_key )
				return( l_pos );
			if( l_item[ l_pos ].s_key > p_key )
				l_to = l_pos;
			else
				l_from = l_pos;
		}
	return( l_to );
}

/* get key position in key order */
static int
	_rfc_cb_getkeypos( rfc_cube *p_cb , rfc_cubekey *p_key )
{
	int l_from;
	int l_to;
	int l_pos;
	int l_res;
	rfc_cubekey **l_key;

	l_from = 0;
	l_to = p_cb -> s_key_n - 1;
	l_key = p_cb -> s_key;

	/* empty array */
	if( l_to < 0 )
		return( -1 );

	/* check margins */
	l_res = _rfc_cb_keycmp( p_cb , p_key , l_key[ l_from ] );
	if( l_res <= 0 )
		{
			if( l_res )
				return( -1 );
			return( l_from );
		}
	l_res = _rfc_cb_keycmp( p_cb , p_key , l_key[ l_to ] );
	if( l_res >= 0 )
		{
			if( l_res )
				return( -1 );
			return( l_to );
		}

	/* binary search */
	while( l_to > l_from )
		{
			l_pos = ( l_to + l_from ) / 2;
			if( l_pos == l_from )
				return( -1 );
			l_res = _rfc_cb_keycmp( p_cb , p_key , l_key[ l_pos ] );
			if( !l_res )
				return( l_pos );
			if( l_res < 0 )
				l_to = l_pos;
			else
				l_from = l_pos;
		}

	return( -1 );
}

/* get key position to add - return 1 if exists */
static short
	_rfc_cb_findaddkeypos( rfc_cube *p_cb , const void **p_keyval , int *p_pos )
{
	int l_from;
	int l_to;
	int l_pos;
	int l_res;
	rfc_cubekey **l_key;

	l_from = 0;
	l_to = p_cb -> s_key_n - 1;
	l_key = p_cb -> s_key;

	/* empty array */
	if( l_to < 0 )
		{
			*p_pos = 0;
			return( 0 );
		}

	/* check margins */
	l_res = _rfc_cb_keyvalcmp( p_cb , p_keyval , l_key[ l_from ] );
	if( l_res <= 0 )
		{
			*p_pos = l_from;
			if( l_res )
				return( 0 );
			return( 1 );
		}
	l_res = _rfc_cb_keyvalcmp( p_cb , p_keyval , l_key[ l_to ] );
	if( l_res >= 0 )
		{
			if( l_res )
				{
					*p_pos = l_to + 1;
					return( 0 );
				}
			*p_pos = l_to;
			return( 1 );
		}

	/* binary search */
	while( l_to > l_from )
		{
			l_pos = ( l_to + l_from ) / 2;
			if( l_pos == l_from )
				break;
			l_res = _rfc_cb_keyvalcmp( p_cb , p_keyval , l_key[ l_pos ] );
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

/* allocate key space */
static void
	_rfc_cb_keyalloc( rfc_cube *p_cb , int p_count )
{
	int k , n;

	if( p_count < RFC_CB_MINITEMS )
		p_count = RFC_CB_MINITEMS;
	if( p_count <= p_cb -> s_key_a )
		return;

	n = p_cb -> s_keyel_n;

	/* align count */
	if( !p_cb -> s_key_a )
		{
			/* allocate new */
			p_cb -> s_key_a = p_count;
			p_cb -> s_key = ( rfc_cubekey ** )calloc( p_count , sizeof( rfc_cubekey * ) );
			for( k = 0; k < n; k++ )
				p_cb -> s_keyel[ k ].s_sort = ( rfc_cubekey ** )calloc( p_count , sizeof( rfc_cubekey * ) );
			p_cb -> s_walk = ( rfc_cubekey ** )calloc( p_count , sizeof( rfc_cubekey * ) );
			return;
		}

	/* reallocate */
	p_count = p_cb -> s_key_a;
	p_cb -> s_key_a *= 2;
	p_cb -> s_key = ( rfc_cubekey ** )realloc( p_cb -> s_key , p_cb -> s_key_a * sizeof( rfc_cubekey * ) );
	p_cb -> s_walk = ( rfc_cubekey ** )realloc( p_cb -> s_walk , p_cb -> s_key_a * sizeof( rfc_cubekey * ) );
	for( k = 0; k < n; k++ )
		p_cb -> s_keyel[ k ].s_sort = ( rfc_cubekey ** )realloc( p_cb -> s_keyel[ k ].s_sort , p_cb -> s_key_a * sizeof( rfc_cubekey * ) );
}

/* set key element by sort */
static void
	_rfc_cb_setkeyel( rfc_cube *p_cb , int p_el , rfc_cubekey *p_key )
{
	rfc_cubekeyel *l_keyel;
	int l_pos;
	rfc_cubekey **l_sort;
	int n;

	l_keyel = &p_cb -> s_keyel[ p_el ];
	l_sort = l_keyel -> s_sort;
	n = p_cb -> s_key_n;

	/* find add position */
	if( l_keyel -> s_isnum )
		l_pos = _rfc_cb_findaddkeyelpos_l( l_sort , p_el , n , p_key -> s_els[ p_el ].u_l );
	else
		l_pos = _rfc_cb_findaddkeyelpos_s( l_sort , p_el , n , p_key -> s_els[ p_el ].u_s );

	/* shift tail */
	if( l_pos < n )
		memmove( &l_sort[ l_pos + 1 ] , &l_sort[ l_pos ] , sizeof( rfc_cubekey * ) * ( n - l_pos ) );
	l_sort[ l_pos ] = p_key;
}

/* compare keys */
static int
	_rfc_cb_keycmp( rfc_cube *p_cb , rfc_cubekey *p_key1 , rfc_cubekey *p_key2 )
{
	int k , n;
	int l_res;

	n = p_cb -> s_keyel_n;
	for( k = 0; k < n; k++ )
		if( p_cb -> s_keyel[ k ].s_isnum )
			{
				l_res = p_key1 -> s_els[ k ].u_l - p_key2 -> s_els[ k ].u_l;
				if( l_res )
					return( l_res );
			}
		else
			{
				l_res = strcmp( p_key1 -> s_els[ k ].u_s , p_key2 -> s_els[ k ].u_s );
				if( l_res )
					return( l_res );
			}
	return( 0 );
}

/* compare values with key */
static int
	_rfc_cb_keyvalcmp( rfc_cube *p_cb , const void **p_keyval , rfc_cubekey *p_key )
{
	int k , n;
	int l_res;
	int l_vd;
	const char *l_vs;

	n = p_cb -> s_keyel_n;
	for( k = 0; k < n; k++ )
		if( p_cb -> s_keyel[ k ].s_isnum )
			{
				l_vd = ( int )p_keyval[ k ];
				l_res = l_vd - p_key -> s_els[ k ].u_l;
				if( l_res )
					return( l_res );
			}
		else
			{
				l_vs = ( const char * )p_keyval[ k ];
				if( l_vs == NULL )
					l_vs = "";
				l_res = strcmp( l_vs , p_key -> s_els[ k ].u_s );
				if( l_res )
					return( l_res );
			}
	return( 0 );
}

/* find add key element position - numeric */
static int
	_rfc_cb_findaddkeyelpos_l( rfc_cubekey **p_sort , int p_el , int p_n , int p_val )
{
	int l_from;
	int l_to;
	int l_pos;
	int l_res;

	if( p_n == 0 )
		return( 0 );

	l_from = 0;
	l_to = p_n - 1;
	
	/* check margins */
	l_res = p_val - p_sort[ l_from ] -> s_els[ p_el ].u_l;
	if( l_res <= 0 )
		return( 0 );
	l_res = p_val - p_sort[ l_to ] -> s_els[ p_el ].u_l;
	if( l_res >= 0 )
		return( l_to + 1 );

	/* binary search */
	while( l_from < l_to )
		{
			l_pos = ( l_from + l_to ) / 2;
			if( l_pos == l_from )
				break;
			l_res = p_val - p_sort[ l_pos ] -> s_els[ p_el ].u_l;
			if( !l_res )
				return( l_pos );
			if( l_res < 0 )
				l_to = l_pos;
			else
				l_from = l_pos;
		}
	return( l_to );
}

/* find add key element position - string */
static int
	_rfc_cb_findaddkeyelpos_s( rfc_cubekey **p_sort , int p_el , int p_n , const char *p_val )
{
	int l_from;
	int l_to;
	int l_pos;
	int l_res;

	if( p_n == 0 )
		return( 0 );

	l_from = 0;
	l_to = p_n - 1;
	
	/* check margins */
	l_res = strcmp( p_val , p_sort[ l_from ] -> s_els[ p_el ].u_s );
	if( l_res <= 0 )
		return( 0 );
	l_res = strcmp( p_val , p_sort[ l_to ] -> s_els[ p_el ].u_s );
	if( l_res >= 0 )
		return( l_to + 1 );

	/* binary search */
	while( l_from < l_to )
		{
			l_pos = ( l_from + l_to ) / 2;
			if( l_pos == l_from )
				break;
			l_res = strcmp( p_val , p_sort[ l_pos ] -> s_els[ p_el ].u_s );
			if( !l_res )
				return( l_pos );
			if( l_res < 0 )
				l_to = l_pos;
			else
				l_from = l_pos;
		}
	return( l_to );
}

/* find key position in element array - numeric */
static int
	_rfc_cb_findkeyelpos_l( rfc_cubekey **p_sort , int p_el , int p_n , int p_val , rfc_cubekey *p_key )
{
	int l_pos;
	int k;

	l_pos = _rfc_cb_findaddkeyelpos_l( p_sort , p_el , p_n , p_val );

	/* find from l_pos */
	if( l_pos < p_n )
		if( p_sort[ l_pos ] == p_key )
			return( l_pos );

	/* find in region */
	for( k = 1; k < p_n; k++ )
		{
			if( l_pos - k >= 0 )
				if( p_sort[ l_pos - k ] == p_key )
					return( l_pos - k );
			if( l_pos + k < p_n )
				if( p_sort[ l_pos + k ] == p_key )
					return( l_pos + k );
		}
	return( -1 );
}

/* find key position in element array - string */
static int
	_rfc_cb_findkeyelpos_s( rfc_cubekey **p_sort , int p_el , int p_n , const char *p_val , rfc_cubekey *p_key )
{
	int l_pos;
	int k;

	l_pos = _rfc_cb_findaddkeyelpos_s( p_sort , p_el , p_n , p_val );

	/* find from l_pos */
	if( l_pos < p_n )
		if( p_sort[ l_pos ] == p_key )
			return( l_pos );

	/* find in region */
	for( k = 1; k < p_n; k++ )
		{
			if( l_pos - k >= 0 )
				if( p_sort[ l_pos - k ] == p_key )
					return( l_pos - k );
			if( l_pos + k < p_n )
				if( p_sort[ l_pos + k ] == p_key )
					return( l_pos + k );
		}
	return( -1 );
}

/* sort pointer function */
static int
	_rfc_cb_sortptr( const void *p_e1 , const void *p_e2 )
{
	return( *( const char ** )p_e1 - *( const char ** )p_e2 );
}

/* get first walk key */
static int
	_rfc_cb_getfirstelkey( rfc_cube *p_cb , int p_el )
{
	int k , n;
	rfc_cubekey **l_sort;

	l_sort = p_cb -> s_keyel[ p_el ].s_sort;
	n = p_cb -> s_key_n;
	for( k = 0; k < n; k++ )
		if( l_sort[ k ] -> s_head.s_mark )
			return( k );
	return( -1 );
}

/* find first/last element order item - numeric */
static int
	_rfc_cb_findorder_l( rfc_cube *p_cb , int p_el , int p_keyval , short p_last )
{
	int l_from;
	int l_to;
	int l_pos;
	rfc_cubekey **l_sort;

	if( !p_cb -> s_walk_n )
		return( -1 );

	l_from = 0;
	l_to = p_cb -> s_key_n - 1;
	l_sort = p_cb -> s_keyel[ p_el ].s_sort;

	/* check margins */
	if( l_sort[ l_from ] -> s_els[ p_el ].u_l >= p_keyval )
		{
			if( l_sort[ l_from ] -> s_els[ p_el ].u_l != p_keyval )
				return( -1 );
			if( !p_last )
				return( l_from );
		}
	if( l_sort[ l_to ] -> s_els[ p_el ].u_l <= p_keyval )
		{
			if( l_sort[ l_to ] -> s_els[ p_el ].u_l != p_keyval )
				return( -1 );
			if( p_last )
				return( l_to );
		}

	/* binary search */
	while( l_from < l_to )
		{
			l_pos = ( l_from + l_to ) / 2;
			if( l_pos == l_from )
				break;

			if( p_last )
				{
					if( l_sort[ l_pos ] -> s_els[ p_el ].u_l <= p_keyval )
						l_from = l_pos;
					else
						l_to = l_pos;
				}
			else
				{
					if( l_sort[ l_pos ] -> s_els[ p_el ].u_l >= p_keyval )
						l_to = l_pos;
					else
						l_from = l_pos;
				}
		}
	if( p_last )
		{
			if( l_sort[ l_to ] -> s_els[ p_el ].u_l == p_keyval )
				return( l_to );
			if( l_from < l_to )
				if( l_sort[ l_from ] -> s_els[ p_el ].u_l == p_keyval )
					return( l_from );
		}
	else
		{
			if( l_sort[ l_from ] -> s_els[ p_el ].u_l == p_keyval )
				return( l_from );
			if( l_from < l_to )
				if( l_sort[ l_to ] -> s_els[ p_el ].u_l == p_keyval )
					return( l_to );
		}
	return( -1 );
}

/* find first/last element order item - string */
static int
	_rfc_cb_findorder_s( rfc_cube *p_cb , int p_el , const char *p_keyval , short p_last )
{
	int l_from;
	int l_to;
	int l_pos;
	rfc_cubekey **l_sort;
	int l_res;

	if( !p_cb -> s_walk_n )
		return( -1 );

	l_from = 0;
	l_to = p_cb -> s_key_n - 1;
	l_sort = p_cb -> s_keyel[ p_el ].s_sort;

	/* check margins */
	l_res = strcmp( l_sort[ l_from ] -> s_els[ p_el ].u_s , p_keyval );
	if( l_res >= 0 )
		{
			if( l_res )
				return( -1 );
			if( !p_last )
				return( l_from );
		}
	l_res = strcmp( l_sort[ l_to ] -> s_els[ p_el ].u_s , p_keyval );
	if( l_res <= 0 )
		{
			if( l_res )
				return( -1 );
			if( p_last )
				return( l_to );
		}

	/* binary search */
	while( l_from < l_to )
		{
			l_pos = ( l_from + l_to ) / 2;
			if( l_pos == l_from )
				break;

			l_res = strcmp( l_sort[ l_pos ] -> s_els[ p_el ].u_s , p_keyval );
			if( p_last )
				{
					if( l_res <= 0 )
						l_from = l_pos;
					else
						l_to = l_pos;
				}
			else
				{
					if( l_res >= 0 )
						l_to = l_pos;
					else
						l_from = l_pos;
				}
		}
	if( p_last )
		{
			if( !strcmp( l_sort[ l_to ] -> s_els[ p_el ].u_s , p_keyval ) )
				return( l_to );
			if( l_from < l_to )
				if( !strcmp( l_sort[ l_from ] -> s_els[ p_el ].u_s , p_keyval ) )
					return( l_from );
		}
	else
		{
			if( !strcmp( l_sort[ l_from ] -> s_els[ p_el ].u_s , p_keyval ) )
				return( l_from );
			if( l_from < l_to )
				if( !strcmp( l_sort[ l_to ] -> s_els[ p_el ].u_s , p_keyval ) )
					return( l_to );
		}
	return( -1 );
}

/* filter walk */
static int
	_rfc_cb_walktook( rfc_cube *p_cb , int p_from , int p_to )
{
	rfc_cubekey **l_sort;
	int k , n;
	rfc_cubekey **l_walk;
	int l_r;

	/* mark selected by walk axis */
	l_sort = p_cb -> s_keyel[ p_cb -> s_walk_el ].s_sort;
	for( ; p_from <= p_to; p_from++ )
		if( l_sort[ p_from ] -> s_head.s_mark )
			l_sort[ p_from ] -> s_head.s_mark++;

	/* squeeze walk */
	l_sort = l_walk = p_cb -> s_walk;
	n = p_cb -> s_walk_n;
	l_r = 0;
	for( k = 0; k < n; k++ , l_sort++ )
		if( --( (*l_sort) -> s_head.s_mark ) )
			{
				*l_walk++ = *l_sort;
				l_r++;
			}

	p_cb -> s_walk_n = l_r;

	/* cancel current item enum */
	p_cb -> s_walk_enumkey = -1;
	p_cb -> s_walk_enumitem = -1;

	return( l_r );
}

/* walk from current to key element */
static short
	_rfc_cb_walk( rfc_cube *p_cb , int p_el )
{
	rfc_cubekey **l_sort;
	int n;

	/* prevent duplicate walk */
	if( p_cb -> s_walk_el == p_el )
		return( 0 );

	/* for empty cube */
	if( !p_cb -> s_key_n )
		return( 0 );

	/* if start walk */
	if( p_cb -> s_walk_el < 0 )
		{
			l_sort = p_cb -> s_walk;
			/* get keys from index */
			memcpy( p_cb -> s_walk , p_cb -> s_keyel[ p_el ].s_sort , sizeof( rfc_cubekey * ) * p_cb -> s_key_n );
			/* sort by key ptr */
			qsort( p_cb -> s_walk , p_cb -> s_key_n , sizeof( rfc_cubekey * ) , _rfc_cb_sortptr );
			/* walk count is key count */
			n = p_cb -> s_walk_n = p_cb -> s_key_n;
			/* mark items */
			while( n-- )
				( *l_sort++ ) -> s_head.s_mark = 1;
		}
	p_cb -> s_walk_el = p_el;
	p_cb -> s_walk_enumdist = -1;
	return( 1 );
}

/* get first/last item index by key */
static int
	_rfc_cb_getkeyitem( rfc_cube *p_cb , const rfc_cubekey *p_key , short p_last )
{
	int l_from;
	int l_to;
	int l_pos;
	rfc_cubeitem *l_item;

	l_from = 0;
	l_to = p_cb -> s_item_n - 1;
	l_item = p_cb -> s_item;

	/* check margins */
	if( l_item[ l_from ].s_key >= p_key )
		{
			if( l_item[ l_from ].s_key != p_key )
				return( -1 );
			if( !p_last )
				return( l_from );
		}
	if( l_item[ l_to ].s_key <= p_key )
		{
			if( l_item[ l_to ].s_key != p_key )
				return( -1 );
			if( p_last )
				return( l_to );
		}

	/* binary search */
	while( l_from < l_to )
		{
			l_pos = ( l_from + l_to ) / 2;
			if( l_pos == l_from )
				break;
			if( p_last )
				{
					if( l_item[ l_pos ].s_key <= p_key )
						l_from = l_pos;
					else
						l_to = l_pos;
				}
			else
				{
					if( l_item[ l_pos ].s_key >= p_key )
						l_to = l_pos;
					else
						l_from = l_pos;
				}
		}
	if( p_last )
		{
			if( l_item[ l_to ].s_key == p_key )
				return( l_to );
			if( l_from < l_to )
				if( l_item[ l_from ].s_key == p_key )
					return( l_from );
		}
	else
		{
			if( l_item[ l_from ].s_key == p_key )
				return( l_from );
			if( l_from < l_to )
				if( l_item[ l_to ].s_key == p_key )
					return( l_to );
		}
	return( -1 );
}

