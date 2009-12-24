/*#######################################################*/
/*#######################################################*/

/* std headers */
#include <__gen.h>

/*#######################################################*/
/*#######################################################*/
/* routines */

/* find phys index by key */
static int
	_rfc_hm_findidx( rfc_huge *p_hm , int p_key );
/* find (create) subarray element on index by key */
static rfc_huge *
	_rfc_hm_findelsub( rfc_huge *p_hm , int p_key , short p_create );
/* find (create) value element on index by key */
static rfc_hugeel *
	_rfc_hm_findelval( rfc_huge *p_hm , int p_key , short p_create );
/* get append index */
static int
	_rfc_hm_getaddidx( rfc_huge *p_hm , int p_key );
/* append index */
static int
	_rfc_hm_addidx( rfc_huge *p_hm , int p_key );
/* find element by key */
static rfc_hugeel *
	_rfc_hm_findel( rfc_huge *p_hm , int p_key );

/* sort functions */
static int
	_rfc_hm_sort_d( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 );
static int
	_rfc_hm_sort_l( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 );
static int
	_rfc_hm_sort_m( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 );
static int
	_rfc_hm_sort_f( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 );
static int
	_rfc_hm_sort_s( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 );
static int
	_rfc_hm_sort_p( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 );

/*#######################################################*/
/*#######################################################*/
/* huge map functions */

/* create huge map array */
rfc_huge *
	rfc_hm_create( int p_datatype /* RFC_EXT_TYPE... value */, rfc_hm_delete f_delete )
{
	rfc_huge *l_hm;

	if( p_datatype == RFC_EXT_TYPECHAR )
		p_datatype = RFC_EXT_TYPESTRING;

	l_hm = ( rfc_huge * )calloc( 1 , sizeof( rfc_huge ) );
	l_hm -> s_type = p_datatype;
	l_hm -> s_key = 0;
	l_hm -> s_fdelete = f_delete;

	return( l_hm );
}

/* destroy huge map array */
void
	rfc_hm_destroy( rfc_huge *p_hm )
{
	/* if has parent - remove from it */
	if( p_hm -> s_parent != NULL )
		{
			rfc_hm_remove( p_hm -> s_parent , p_hm -> s_key );
			return;
		}

	if( p_hm -> s_ref-- )
		return;

	/* free data */
	rfc_hm_init( p_hm );

	/* free array */
	free( p_hm );
}

/* reference huge map array */
void
	rfc_hm_ref( rfc_huge *p_hm )
{
	p_hm -> s_ref++;
}

/* remove all array allocations */
void
	rfc_hm_init( rfc_huge *p_hm )
{
	int n;
	rfc_hugeel *l_el;

	/* remove all items */
	l_el = p_hm -> s_map;
	n = p_hm -> s_n;
	for( ; n--; l_el++ )
		{
			/* if subarray */
			if( l_el -> s_sub )
				{
					/* free parent reference */
					l_el -> s_data.u_h -> s_parent = NULL;
					l_el -> s_data.u_h -> s_key = 0;

					/* destroy element */
					rfc_hm_destroy( l_el -> s_data.u_h );
				}
			else
				{
					/* call delete callback if any */
					if( p_hm -> s_fdelete )
						p_hm -> s_fdelete( p_hm, l_el -> s_data.u_v.u_p );
					/* free string if any */
					if( p_hm -> s_type == RFC_EXT_TYPESTRING &&
						l_el -> s_data.u_v.u_s != NULL )
						rfc_str_drop( l_el -> s_data.u_v.u_s );
				}
		}

	/* free data */
	if( p_hm -> s_a )
		{
			free( p_hm -> s_map );
			p_hm -> s_map = NULL;
			p_hm -> s_a = 0;
			p_hm -> s_n = 0;
		}
}

/* remove all array items without free memory */
void
	rfc_hm_clear( rfc_huge *p_hm )
{
	int n;
	rfc_hugeel *l_el;

	/* clear all item strings */
	l_el = p_hm -> s_map;
	n = p_hm -> s_n;
	for( ; n--; l_el++ )
		{
			/* if subarray */
			if( l_el -> s_sub )
				{
					rfc_hm_clear( l_el -> s_data.u_h );
				}
			else
				{
					/* call delete callback if any */
					if( p_hm -> s_fdelete )
						p_hm -> s_fdelete( NULL, l_el -> s_data.u_v.u_p );
					/* clear string if any */
					if( p_hm -> s_type == RFC_EXT_TYPESTRING &&
						l_el -> s_data.u_v.u_s != NULL )
						{
							rfc_str_clear( l_el -> s_data.u_v.u_s );
							l_el -> s_data.u_v.u_s = NULL;
						}
				}
		}

	/* set item count to 0 */
	p_hm -> s_n = 0;
}

/* allocate array items */
void
	rfc_hm_allocate( rfc_huge *p_hm , int p_count )
{
	if( p_count < 10 )
		p_count = 10;
	if( p_count < p_hm -> s_a )
		return;

	if( !p_hm -> s_a )
		{
			/* allocate new */
			p_hm -> s_a = p_count;
			p_hm -> s_map = ( rfc_hugeel * )calloc( p_hm -> s_a , sizeof( rfc_hugeel ) );
			return;
		}

	/* reallocate */
	p_count = p_hm -> s_a;
	p_hm -> s_a *= 2;
	p_hm -> s_map = ( rfc_hugeel * )realloc( p_hm -> s_map , p_hm -> s_a * sizeof( rfc_hugeel ) );
	memset( &p_hm -> s_map[ p_count ] , 0 , p_count * sizeof( rfc_hugeel ) );
}

/* remove key holes on current level */
void
	rfc_hm_squeeze( rfc_huge *p_hm )
{
	int k , n;
	rfc_hugeel *l_el;

	/* reenumerate items */
	l_el = p_hm -> s_map;
	n = p_hm -> s_n;
	for( k = 0; n--; k++ , l_el++ )
		{
			/* if subarray */
			if( l_el -> s_sub )
				l_el -> s_data.u_h -> s_key = k;
			l_el -> s_key = k;
		}
}

/* remove key holes recursive */
void
	rfc_hm_squeezeall( rfc_huge *p_hm )
{
	int k , n;
	rfc_hugeel *l_el;

	/* reenumerate items */
	l_el = p_hm -> s_map;
	n = p_hm -> s_n;
	for( k = 0; n--; k++ , l_el++ )
		{
			l_el -> s_key = k;

			/* if subarray */
			if( l_el -> s_sub )
				{
					l_el -> s_data.u_h -> s_key = k;
					rfc_hm_squeezeall( l_el -> s_data.u_h );
				}
		}
}

/* remove key */
void
	rfc_hm_remove( rfc_huge *p_hm , int p_idx )
{
	int l_pos;
	rfc_hugeel *l_el;
	RFC_INT64 l_data;

	/* find phys index */
	if( ( l_pos = _rfc_hm_findidx( p_hm , p_idx ) ) < 0 )
		return;

	l_el = &p_hm -> s_map[ l_pos ];

	/* destroy subarray if any */
	if( l_el -> s_sub )
		{
			l_el -> s_data.u_h -> s_parent = NULL;
			l_el -> s_data.u_h -> s_key = 0;
			rfc_hm_destroy( l_el -> s_data.u_h );

			l_el -> s_data.u_h = NULL;
			l_el -> s_sub = 0;
		}
	p_hm -> s_n--;

	/* shift items (this item copy to last) */
	if( l_pos < p_hm -> s_n )
		{
			l_data = l_el -> s_data.u_v.u_m;
			memmove( &p_hm -> s_map[ l_pos ] , &p_hm -> s_map[ l_pos + 1 ] , ( p_hm -> s_n - l_pos ) * sizeof( rfc_hugeel ) );
			l_el = &p_hm -> s_map[ p_hm -> s_n ];
			l_el -> s_data.u_v.u_m = l_data;
			l_el -> s_sub = 0;
		}
}

/* set current level array element */
void
	rfc_hm_set( rfc_huge *p_hm , int p_idx , const void *p_value )
{
	rfc_hugeel *l_el;

	/* find element */
	if( ( l_el = _rfc_hm_findelval( p_hm , p_idx , 1 ) ) == NULL )
		return;

	/* set data by type */
	rfc_type_set( p_hm -> s_type , &l_el -> s_data.u_v , p_value , NULL );
}

void
	rfc_hm_set_d( rfc_huge *p_hm , int p_idx , short p_value )
{
	RFC_INT64 l_v;
	switch( p_hm -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				rfc_hm_set( p_hm , p_idx , &p_value );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_hm -> s_type , NULL , NULL );
				rfc_hm_set( p_hm , p_idx , &l_v );
				break;
		}
}

void
	rfc_hm_set_l( rfc_huge *p_hm , int p_idx , int p_value )
{
	RFC_INT64 l_v;
	switch( p_hm -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				rfc_hm_set( p_hm , p_idx , &p_value );
				break;

			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_hm -> s_type , NULL , NULL );
				rfc_hm_set( p_hm , p_idx , &l_v );
				break;
		}
}

void
	rfc_hm_set_m( rfc_huge *p_hm , int p_idx , RFC_INT64 p_value )
{
	RFC_INT64 l_v;
	switch( p_hm -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				rfc_hm_set( p_hm , p_idx , &p_value );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_hm -> s_type , NULL , NULL );
				rfc_hm_set( p_hm , p_idx , &l_v );
				break;
		}
}

void
	rfc_hm_set_f( rfc_huge *p_hm , int p_idx , double p_value )
{
	RFC_INT64 l_v;
	switch( p_hm -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				rfc_hm_set( p_hm , p_idx , &p_value );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_hm -> s_type , NULL , NULL );
				rfc_hm_set( p_hm , p_idx , &l_v );
				break;
		}
}

void
	rfc_hm_set_s( rfc_huge *p_hm , int p_idx , const char *p_value )
{
	if( p_hm -> s_type == RFC_EXT_TYPESTRING ||
		p_hm -> s_type == RFC_EXT_TYPECHAR )
		rfc_hm_set( p_hm , p_idx , &p_value );
}

void
	rfc_hm_set_p( rfc_huge *p_hm , int p_idx , void *p_value )
{
	if( p_hm -> s_type == RFC_EXT_TYPEPTR )
		rfc_hm_set( p_hm , p_idx , &p_value );
}

/* get current level subarray */
rfc_huge *
	rfc_hm_getsub( rfc_huge *p_hm , int p_idx )
{
	/* get element (create subarray if needed) */
	return( _rfc_hm_findelsub( p_hm , p_idx , 1 ) );
}

/* get current level array element */
const rfc_hugeel *
	rfc_hm_get( rfc_huge *p_hm , int p_idx )
{
	int l_pos;
	if( ( l_pos = _rfc_hm_findidx( p_hm , p_idx ) ) < 0 )
		return( NULL );

	return( &p_hm -> s_map[ l_pos ] );
}

short
	rfc_hm_get_d( rfc_huge *p_hm , int p_idx )
{
	rfc_hugeel *l_el;

	/* find element */
	if( ( l_el = _rfc_hm_findelval( p_hm , p_idx , 0 ) ) == NULL )
		return( ( short )0 );

	if( p_hm -> s_type == RFC_EXT_TYPESHORT )
		return( l_el -> s_data.u_v.u_d );
	return( ( short )0 );
}

int
	rfc_hm_get_l( rfc_huge *p_hm , int p_idx )
{
	rfc_hugeel *l_el;

	/* find element */
	if( ( l_el = _rfc_hm_findelval( p_hm , p_idx , 0 ) ) == NULL )
		return( ( int )0 );

	switch( p_hm -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				return( l_el -> s_data.u_v.u_d );
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				return( l_el -> s_data.u_v.u_l );
		}

	return( ( int )0 );
}

RFC_INT64
	rfc_hm_get_m( rfc_huge *p_hm , int p_idx )
{
	rfc_hugeel *l_el;
	RFC_INT64 l_v;

	/* find element */
	if( ( l_el = _rfc_hm_findelval( p_hm , p_idx , 0 ) ) == NULL )
		return( ( RFC_INT64 )0 );

	switch( p_hm -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				return( l_el -> s_data.u_v.u_m );
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &l_el -> s_data , p_hm -> s_type , &l_v , RFC_EXT_TYPEMONEY , NULL , NULL );
				return( l_v );
		}

	return( ( RFC_INT64 )0 );
}

double
	rfc_hm_get_f( rfc_huge *p_hm , int p_idx )
{
	rfc_hugeel *l_el;
	double l_v;

	/* find element */
	if( ( l_el = _rfc_hm_findelval( p_hm , p_idx , 0 ) ) == NULL )
		return( ( double )0 );

	switch( p_hm -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				return( l_el -> s_data.u_v.u_f );
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &l_el -> s_data , p_hm -> s_type , &l_v , RFC_EXT_TYPEDOUBLE , NULL , NULL );
				return( l_v );
		}

	return( ( double )0 );
}

const char *
	rfc_hm_get_s( rfc_huge *p_hm , int p_idx )
{
	rfc_hugeel *l_el;

	/* find element */
	if( ( l_el = _rfc_hm_findelval( p_hm , p_idx , 0 ) ) == NULL )
		return( NULL );

	if( p_hm -> s_type == RFC_EXT_TYPESTRING ||
		p_hm -> s_type == RFC_EXT_TYPECHAR )
		return( l_el -> s_data.u_v.u_s );
	return( NULL );
}

void *
	rfc_hm_get_p( rfc_huge *p_hm , int p_idx )
{
	rfc_hugeel *l_el;

	/* find element */
	if( ( l_el = _rfc_hm_findelval( p_hm , p_idx , 0 ) ) == NULL )
		return( NULL );

	if( p_hm -> s_type == RFC_EXT_TYPEPTR )
		return( l_el -> s_data.u_v.u_p );
	return( NULL );
}

rfc_huge *
	rfc_hm_get_h( rfc_huge *p_hm , int p_idx )
{
	/* get element - no create subarray */
	return( _rfc_hm_findelsub( p_hm , p_idx , 0 ) );
}

/* set any level array element by index parameters */
void
	rfc_hm_mset( rfc_huge *p_hm , int p_level , const void *p_value , ... /*int p_idx1 , ... , int p_idx<p_level> */ )
{
	va_list l_va;

	va_start( l_va , p_value );

	rfc_hm_mset_va( p_hm , p_level , p_value , l_va );
	va_end( l_va );
}

/* set any level array element by va_list */
void
	rfc_hm_mset_va( rfc_huge *p_hm , int p_level , const void *p_value , va_list p_idx )
{
	int k;
	int l_idx;

	l_idx = va_arg( p_idx , int );

	/* simple case - one level */
	if( !p_level )
		{
			rfc_hm_set( p_hm , l_idx , p_value );
			return;
		}

	/* simple case - non-zero index */
	if( l_idx )
		{
			/* find element */
			if( ( p_hm = _rfc_hm_findelsub( p_hm , l_idx , 1 ) ) == NULL )
				return;
			rfc_hm_mset_va( p_hm , --p_level , p_value , p_idx );
			return;
		}

	/* special case - zero indexes */
	for( k = 1; k <= p_level; k++ )
		{
			l_idx = va_arg( p_idx , int );
			if( !l_idx )
				break;
		}

	/* if all are zero indexes */
	if( k > p_level )
		{
			/* set to current subarray index 0 */
			rfc_hm_set( p_hm , 0 , p_value );
			return;
		}

	/* skip subarrays */
	p_level -= k;
	while( k-- )
		p_hm = _rfc_hm_findelsub( p_hm , 0 , 1 );

	/* if index is last */
	if( !p_level )
		{
			rfc_hm_set( p_hm , l_idx , p_value );
			return;
		}

	/* get non-zero subarray */
	p_hm = _rfc_hm_findelsub( p_hm , l_idx , 1 );

	/* set by remaining */
	rfc_hm_mset_va( p_hm , --p_level , p_value , p_idx );
}

/* set any level array element by index array */
void
	rfc_hm_mset_a( rfc_huge *p_hm , int p_level , const void *p_value , int *p_idx )
{
	/* remove trailing zero indexes */
	for( ; p_level; p_level-- )
		if( p_idx[ p_level ] )
			break;

	/* get subarray */
	for( ; p_level; p_level-- )
		p_hm = _rfc_hm_findelsub( p_hm , *p_idx++ , 1 );

	/* set by last index */
	rfc_hm_set( p_hm , *p_idx , p_value );
}

/* get any level array element by index parameters */
const rfc_hugeel *
	rfc_hm_mget( rfc_huge *p_hm , int p_level , ... /*int p_idx1 , ... , int p_idx<p_level> */ )
{
	va_list l_va;
	const rfc_hugeel *l_el;

	va_start( l_va , p_level );

	l_el = rfc_hm_mget_va( p_hm , p_level , l_va );
	va_end( l_va );

	return( l_el );
}

/* get any level array element by va_list */
const rfc_hugeel *
	rfc_hm_mget_va( rfc_huge *p_hm , int p_level , va_list p_idx )
{
	int l_idx;
	rfc_hugeel *l_el;

	/* get subarray */
	while( p_level-- )
		{
			l_idx = va_arg( p_idx , int );
			if( ( l_el = _rfc_hm_findel( p_hm , l_idx ) ) == NULL )
				return( NULL );

			/* if subarray */
			if( l_el -> s_sub )
				{
					p_hm = l_el -> s_data.u_h;
					continue;
				}

			/* check trailing indexes are zeros */
			while( p_level-- )
				{
					l_idx = va_arg( p_idx , int );
					if( l_idx )
						return( NULL );
				}
			l_idx = va_arg( p_idx , int );
			if( l_idx )
				return( NULL );
			return( l_el );
		}

	/* get element */
	l_idx = va_arg( p_idx , int );
	return( _rfc_hm_findelval( p_hm , l_idx , 0 ) );
}

/* get any level array element by index array */
const rfc_hugeel *
	rfc_hm_mget_a( rfc_huge *p_hm , int p_level , int *p_idx )
{
	rfc_hugeel *l_el;

	while( p_level-- )
		{
			if( ( l_el = _rfc_hm_findel( p_hm , *p_idx++ ) ) == NULL )
				return( NULL );

			/* if subarray */
			if( l_el -> s_sub )
				{
					p_hm = l_el -> s_data.u_h;
					continue;
				}
					
			/* check trailing indexes are zeros */
			while( p_level-- )
				if( *p_idx++ )
					return( NULL );
			if( *p_idx )
				return( NULL );
			return( l_el );
		}

	/* get element */
	return( _rfc_hm_findelval( p_hm , *p_idx , 0 ) );
}

/* get any level subarray by index parameters */
rfc_huge *
	rfc_hm_mgetsub( rfc_huge *p_hm , int p_level , ... /*int p_idx1 , ... , int p_idx<p_level> */ )
{
	va_list l_va;

	va_start( l_va , p_level );

	p_hm = rfc_hm_mgetsub_va( p_hm , p_level , l_va );
	va_end( l_va );

	return( p_hm );
}

/* get any level subarray by va_list */
rfc_huge *
	rfc_hm_mgetsub_va( rfc_huge *p_hm , int p_level , va_list p_idx )
{
	int l_idx;

	p_level++;
	while( p_level-- )
		{
			l_idx = va_arg( p_idx , int );
			p_hm = _rfc_hm_findelsub( p_hm , l_idx , 1 );
		}

	return( p_hm );
}

/* get any level subarray by index array */
rfc_huge *
	rfc_hm_mgetsub_a( rfc_huge *p_hm , int p_level , int *p_idx )
{
	p_level++;
	while( p_level-- )
		p_hm = _rfc_hm_findelsub( p_hm , *p_idx++ , 1 );

	return( p_hm );
}

/* sort elements on given level by value */
void
	rfc_hm_sort( rfc_huge *p_hm , void *p_userdata , rfc_hm_compare f_compare )
{
	if( !p_hm -> s_n )
		return;

	/* set compare function */
	if( f_compare == NULL )
		{
			switch( p_hm -> s_type )
				{
					case RFC_EXT_TYPESHORT :
						f_compare = _rfc_hm_sort_d;
						break;
					case RFC_EXT_TYPELONG :
					case RFC_EXT_TYPEMOMENT :
					case RFC_EXT_TYPETIMET :
						f_compare = _rfc_hm_sort_l;
						break;
					case RFC_EXT_TYPEMONEY :
						f_compare = _rfc_hm_sort_m;
						break;
					case RFC_EXT_TYPEDOUBLE :
						f_compare = _rfc_hm_sort_f;
						break;
					case RFC_EXT_TYPESTRING :
					case RFC_EXT_TYPECHAR :
						f_compare = _rfc_hm_sort_s;
						break;
					case RFC_EXT_TYPEPTR :
						f_compare = _rfc_hm_sort_p;
						break;
				}
		}

	rfc_qsort( p_userdata , p_hm -> s_map , p_hm -> s_n , sizeof( rfc_hugeel ) , ( rfc_qsortcb )f_compare );
	rfc_hm_squeeze( p_hm );
}

/* sort elements recursive by value */
void
	rfc_hm_sortall( rfc_huge *p_hm , void *p_userdata , rfc_hm_compare f_compare )
{
	rfc_hugeel *l_el;
	int n;

	n = p_hm -> s_n;
	if( !n )
		return;

	/* set compare function */
	if( f_compare == NULL )
		{
			switch( p_hm -> s_type )
				{
					case RFC_EXT_TYPESHORT :
						f_compare = _rfc_hm_sort_d;
						break;
					case RFC_EXT_TYPELONG :
					case RFC_EXT_TYPEMOMENT :
					case RFC_EXT_TYPETIMET :
						f_compare = _rfc_hm_sort_l;
						break;
					case RFC_EXT_TYPEMONEY :
						f_compare = _rfc_hm_sort_m;
						break;
					case RFC_EXT_TYPEDOUBLE :
						f_compare = _rfc_hm_sort_f;
						break;
					case RFC_EXT_TYPESTRING :
					case RFC_EXT_TYPECHAR :
						f_compare = _rfc_hm_sort_s;
						break;
					case RFC_EXT_TYPEPTR :
						f_compare = _rfc_hm_sort_p;
						break;
				}
		}

	/* recursive sort by sublevels */
	for( l_el = p_hm -> s_map; n--; l_el++ )
		if( l_el -> s_sub )
			rfc_hm_sortall( l_el -> s_data.u_h , p_userdata , f_compare );

	/* sort this level */
	rfc_hm_sort( p_hm , p_userdata , f_compare );
}

/*#######################################################*/
/*#######################################################*/
/* huge map routines */

/* find (create) subarray element on index by key */
static rfc_huge *
	_rfc_hm_findelsub( rfc_huge *p_hm , int p_key , short p_create )
{
	int l_pos;
	rfc_hugeel *l_el;
	rfc_huge *l_hm;

	/* find phys index */
	if( ( l_pos = _rfc_hm_findidx( p_hm , p_key ) ) < 0 )
		{
			if( !p_create )
				return( NULL );

			/* append index */
			l_pos = _rfc_hm_addidx( p_hm , p_key );
		}

	/* if exists subarray */
	l_el = &p_hm -> s_map[ l_pos ];
	if( l_el -> s_sub )
		return( l_el -> s_data.u_h );

	/* if no create */
	if( !p_create )
		return( NULL );

	/* add item to new array */
	l_hm = rfc_hm_create( p_hm -> s_type , p_hm -> s_fdelete );
	l_hm -> s_parent = p_hm;
	l_hm -> s_key = p_key;
	rfc_hm_set( l_hm , 0 , &l_el -> s_data );

	/* set this element to array */
	if( p_hm -> s_type == RFC_EXT_TYPESTRING &&
		l_el -> s_data.u_v.u_s != NULL )
		rfc_str_drop( l_el -> s_data.u_v.u_s );
	l_el -> s_sub = 1;
	l_el -> s_data.u_h = l_hm;

	return( l_hm );
}

/* find (create) value element on index by key */
static rfc_hugeel *
	_rfc_hm_findelval( rfc_huge *p_hm , int p_key , short p_create )
{
	int l_pos;
	rfc_hugeel *l_el;

	/* find phys index */
	if( ( l_pos = _rfc_hm_findidx( p_hm , p_key ) ) < 0 )
		{
			if( !p_create )
				return( NULL );

			/* append index */
			l_pos = _rfc_hm_addidx( p_hm , p_key );
		}

	/* if exists subarray */
	l_el = &p_hm -> s_map[ l_pos ];
	if( l_el -> s_sub )
		return( _rfc_hm_findelval( l_el -> s_data.u_h , 0 , p_create ) );

	return( l_el );
}

/* find element by key */
static rfc_hugeel *
	_rfc_hm_findel( rfc_huge *p_hm , int p_key )
{
	int l_pos;

	if( ( l_pos = _rfc_hm_findidx( p_hm , p_key ) ) < 0 )
		return( NULL );
	return( &p_hm -> s_map[ l_pos ] );
}

/* sort functions */
static int
	_rfc_hm_sort_d( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 )
{
	if( p_e1 -> s_sub )
		p_e1 = _rfc_hm_findelval( p_e1 -> s_data.u_h , 0 , 0 );
	if( p_e2 -> s_sub )
		p_e2 = _rfc_hm_findelval( p_e2 -> s_data.u_h , 0 , 0 );
	if( p_e1 == NULL )
		{
			if( p_e2 == NULL )
				return( 0 );
			return( 1 );
		}
	if( p_e2 == NULL )
		return( -1 );
			
	return( p_e1 -> s_data.u_v.u_d - p_e2 -> s_data.u_v.u_d );
}

static int
	_rfc_hm_sort_l( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 )
{
	if( p_e1 -> s_sub )
		p_e1 = _rfc_hm_findelval( p_e1 -> s_data.u_h , 0 , 0 );
	if( p_e2 -> s_sub )
		p_e2 = _rfc_hm_findelval( p_e2 -> s_data.u_h , 0 , 0 );
	if( p_e1 == NULL )
		{
			if( p_e2 == NULL )
				return( 0 );
			return( 1 );
		}
	if( p_e2 == NULL )
		return( -1 );
			
	return( p_e1 -> s_data.u_v.u_l - p_e2 -> s_data.u_v.u_l );
}

static int
	_rfc_hm_sort_m( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 )
{
	if( p_e1 -> s_sub )
		p_e1 = _rfc_hm_findelval( p_e1 -> s_data.u_h , 0 , 0 );
	if( p_e2 -> s_sub )
		p_e2 = _rfc_hm_findelval( p_e2 -> s_data.u_h , 0 , 0 );
	if( p_e1 == NULL )
		{
			if( p_e2 == NULL )
				return( 0 );
			return( 1 );
		}
	if( p_e2 == NULL )
		return( -1 );
			
	if( p_e1 -> s_data.u_v.u_m > p_e2 -> s_data.u_v.u_m )
		return( 1 );
	if( p_e1 -> s_data.u_v.u_m < p_e2 -> s_data.u_v.u_m )
		return( -1 );
	return( 0 );
}

static int
	_rfc_hm_sort_f( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 )
{
	if( p_e1 -> s_sub )
		p_e1 = _rfc_hm_findelval( p_e1 -> s_data.u_h , 0 , 0 );
	if( p_e2 -> s_sub )
		p_e2 = _rfc_hm_findelval( p_e2 -> s_data.u_h , 0 , 0 );
	if( p_e1 == NULL )
		{
			if( p_e2 == NULL )
				return( 0 );
			return( 1 );
		}
	if( p_e2 == NULL )
		return( -1 );
			
	if( p_e1 -> s_data.u_v.u_f > p_e2 -> s_data.u_v.u_f )
		return( 1 );
	if( p_e1 -> s_data.u_v.u_f < p_e2 -> s_data.u_v.u_f )
		return( -1 );
	return( 0 );
}

static int
	_rfc_hm_sort_s( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 )
{
	if( p_e1 -> s_sub )
		p_e1 = _rfc_hm_findelval( p_e1 -> s_data.u_h , 0 , 0 );
	if( p_e2 -> s_sub )
		p_e2 = _rfc_hm_findelval( p_e2 -> s_data.u_h , 0 , 0 );
	if( p_e1 == NULL )
		{
			if( p_e2 == NULL )
				return( 0 );
			return( 1 );
		}
	if( p_e2 == NULL )
		return( -1 );

	if( p_e1 -> s_data.u_v.u_s == NULL )
		{
			if( p_e2 -> s_data.u_v.u_s == NULL )
				return( 0 );
			return( 1 );
		}
	if( p_e2 -> s_data.u_v.u_s == NULL )
		return( -1 );

	return( strcmp( p_e1 -> s_data.u_v.u_s , p_e2 -> s_data.u_v.u_s ) );
}

static int
	_rfc_hm_sort_p( void *p_userdata , const rfc_hugeel *p_e1 , const rfc_hugeel *p_e2 )
{
	if( p_e1 -> s_sub )
		p_e1 = _rfc_hm_findelval( p_e1 -> s_data.u_h , 0 , 0 );
	if( p_e2 -> s_sub )
		p_e2 = _rfc_hm_findelval( p_e2 -> s_data.u_h , 0 , 0 );
	if( p_e1 == NULL )
		{
			if( p_e2 == NULL )
				return( 0 );
			return( 1 );
		}
	if( p_e2 == NULL )
		return( -1 );

	return( ( ( const char * )p_e1 -> s_data.u_v.u_p ) - ( ( const char * )p_e2 -> s_data.u_v.u_p ) );
}

/* find phys index by key */
static int
	_rfc_hm_findidx( rfc_huge *p_hm , int p_key )
{
	int l_from;
	int l_to;
	rfc_hugeel *l_el;
	int l_pos;

	l_from = 0;
	l_to = p_hm -> s_n - 1;
	l_el = p_hm -> s_map;

	if( l_to < 0 )
		return( -1 );

	/* binary search */
	if( l_el[ l_from ].s_key >= p_key )
		{
			if( l_el[ l_from ].s_key == p_key )
				return( l_from );
			return( -1 );
		}
	if( l_el[ l_to ].s_key <= p_key )
		{
			if( l_el[ l_to ].s_key == p_key )
				return( l_to );
			return( -1 );
		}

	while( l_to > l_from )
		{
			l_pos = ( l_to + l_from ) / 2;
			if( l_pos == l_from )
				return( -1 );
			if( l_el[ l_pos ].s_key == p_key )
				return( l_pos );

			if( l_el[ l_pos ].s_key < p_key )
				l_to = l_pos;
			else
				l_from = l_pos;
		}
	return( -1 );
}

/* append index */
static int
	_rfc_hm_getaddidx( rfc_huge *p_hm , int p_key )
{
	int l_from;
	int l_to;
	rfc_hugeel *l_el;
	int l_pos;

	l_from = 0;
	l_to = p_hm -> s_n - 1;
	l_el = p_hm -> s_map;

	if( l_to < 0 )
		return( 0 );

	/* binary search */
	if( l_el[ l_from ].s_key > p_key )
		return( 0 );
	if( l_el[ l_to ].s_key < p_key )
		return( l_to + 1 );

	while( l_to > l_from )
		{
			l_pos = ( l_to + l_from ) / 2;
			if( l_pos == l_from )
				return( l_to );

			if( l_el[ l_pos ].s_key < p_key )
				l_to = l_pos;
			else
				l_from = l_pos;
		}
	return( l_to );
}

/* append index */
static int
	_rfc_hm_addidx( rfc_huge *p_hm , int p_key )
{
	int l_pos;
	RFC_INT64 l_v;

	/* ensure space */
	rfc_hm_allocate( p_hm , p_hm -> s_n + 1 );

	/* find added index */
	l_pos = _rfc_hm_getaddidx( p_hm , p_key );

	/* shift data */
	if( l_pos < p_hm -> s_n )
		{
			l_v = p_hm -> s_map[ p_hm -> s_n ].s_data.u_v.u_m;
			memmove( &p_hm -> s_map[ l_pos + 1 ] , &p_hm -> s_map[ l_pos ] , sizeof( rfc_hugeel ) * ( p_hm -> s_n - l_pos ) );
			p_hm -> s_map[ l_pos ].s_data.u_v.u_m = l_v;
		}

	/* set key */
	p_hm -> s_map[ l_pos ].s_key = p_key;
	p_hm -> s_map[ l_pos ].s_sub = 0;
	p_hm -> s_n++;

	return( l_pos );
}

