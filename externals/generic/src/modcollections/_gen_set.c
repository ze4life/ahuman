/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

#define RFC_SET_MINITEMS			8

/* append items */
static void
	_rfc_set_addcrossitems( rfc_set *p_set , rfc_setitem *p_regfrom , rfc_setitem *p_regto , rfc_setitem *p_item , int p_from , int p_to );
/* append item to position */
static void
	_rfc_set_additem( rfc_set *p_set , int p_regtype , const void *p_value , int p_pos );
/* internal remove items */
static void
	_rfc_set_removeitems( rfc_set *p_set , int p_from , int p_count );
/* find previous item */
static int
	_rfc_set_getprevequal( rfc_set *p_set , const void *p_value );

/*#######################################################*/
/*#######################################################*/

/* create set */
rfc_set *
	rfc_set_create( int p_type )
{
	rfc_set *l_set;

	if( p_type == RFC_EXT_TYPECHAR )
		p_type = RFC_EXT_TYPESTRING;
	l_set = ( rfc_set * )calloc( 1 , sizeof( rfc_set ) );
	l_set -> s_type = p_type;
	l_set -> s_enum = -1;

	return( l_set );
}

/* create set as copy */
rfc_set *
	rfc_set_createcopy( rfc_set *p_set )
{
	rfc_set *l_set;

	l_set = rfc_set_create( p_set -> s_type );
	if( !p_set -> s_n )
		return( l_set );
	
	/* copy data */
	l_set -> s_a = l_set -> s_n = p_set -> s_n;
	l_set -> s_item = ( rfc_setitem * )malloc( l_set -> s_a * sizeof( rfc_setitem ) );
	memcpy( l_set -> s_item , p_set -> s_item , l_set -> s_a * sizeof( rfc_setitem ) );

	return( l_set );
}

/* create set as union */
rfc_set *
	rfc_set_createunion( rfc_set *p_set1 , rfc_set *p_set2 )
{
	rfc_set *l_set;

	/* check equal types */
	if( p_set1 -> s_type != p_set2 -> s_type )
		return( NULL );

	/* get max set */
	if( p_set1 -> s_n < p_set2 -> s_n )
		{
			l_set = p_set1;
			p_set1 = p_set2;
			p_set2 = l_set;
		}

	/* create set as copy of p_set1 */
	l_set = rfc_set_createcopy( p_set1 );

	/* append items from p_set2 */
	rfc_set_addset( l_set , p_set2 );

	return( l_set );
}

/* create set as intersect */
rfc_set *
	rfc_set_createcross( rfc_set *p_set1 , rfc_set *p_set2 )
{
	rfc_set *l_set;
	int k , n;
	rfc_setitem *l_items;
	rfc_setitem *l_item1;
	rfc_setitem *l_item2;
	int l_from;
	int l_to;

	/* check equal types */
	if( p_set1 -> s_type != p_set2 -> s_type )
		return( NULL );

	/* get min set */
	if( p_set1 -> s_n > p_set2 -> s_n )
		{
			l_set = p_set1;
			p_set1 = p_set2;
			p_set2 = l_set;
		}

	/* create empty set */
	l_set = rfc_set_create( p_set1 -> s_type );

	/* check one of sets is empty */
	if( rfc_set_isempty( p_set1 ) ||
		rfc_set_isempty( p_set2 ) )
		return( l_set );

	/* scan first set */
	l_items = p_set1 -> s_item;
	n = p_set1 -> s_n;
	for( k = 0; k < n; k++ , l_items++ )
		{
			/* process single item */
			if( l_items -> s_regtype == RFC_SET_ONE )
				{
					if( rfc_set_isin( p_set2 , &l_items -> s_data ) )
						rfc_set_add( l_set , &l_items -> s_data );
					continue;
				}

			/* process region */
			l_item1 = l_items++;
			l_item2 = l_items;

			/* get first & last from p_set2 in region */
			l_to = _rfc_set_getprevequal( p_set2 , &l_item2 -> s_data );
			if( l_to < 0 )
				continue;
			l_from = _rfc_set_getprevequal( p_set2 , &l_item1 -> s_data );

			/* append items */
			_rfc_set_addcrossitems( l_set , l_item1 , l_item2 , p_set2 -> s_item , l_from , l_to );
		}

	return( l_set );
}

/* create set as union except intersect */
rfc_set *
	rfc_set_createouter( rfc_set *p_set1 , rfc_set *p_set2 )
{
	rfc_set *l_set;
	rfc_set *l_insertsect;

	/* check equal types */
	if( p_set1 -> s_type != p_set2 -> s_type )
		return( NULL );

	/* union sets */
	l_set = rfc_set_createunion( p_set1 , p_set2 );

	/* get intersect */
	l_insertsect = rfc_set_createcross( p_set1 , p_set2 );

	/* set result */
	rfc_set_removeset( l_set , l_insertsect );

	/* destroy intersect */
	rfc_set_destroy( l_insertsect );

	return( l_set );
}

/* create set as first except intersect */
rfc_set *
	rfc_set_createleft( rfc_set *p_set1 , rfc_set *p_set2 )
{
	rfc_set *l_set;
	rfc_set *l_insertsect;

	/* check equal types */
	if( p_set1 -> s_type != p_set2 -> s_type )
		return( NULL );

	/* create as copy of p_set1 */
	l_set = rfc_set_createcopy( p_set1 );

	/* get intersect */
	l_insertsect = rfc_set_createcross( p_set1 , p_set2 );

	/* set result */
	rfc_set_removeset( l_set , l_insertsect );

	/* destroy intersect */
	rfc_set_destroy( l_insertsect );

	return( l_set );
}

/* destroy set */
void
	rfc_set_destroy( rfc_set *p_set )
{
	if( p_set -> s_ref-- )
		return;

	/* init */
	rfc_set_init( p_set );

	/* free set */
	free( p_set );
}

/* reference set */
void
	rfc_set_ref( rfc_set *p_set )
{
	p_set -> s_ref++;
}

/* clear set without free memory */
void
	rfc_set_clear( rfc_set *p_set )
{
	p_set -> s_n = 0;
	p_set -> s_enum = -1;
}

/* remove all items with free memory */
void
	rfc_set_init( rfc_set *p_set )
{
	int k , n;
	rfc_setitem *l_item;

	/* clear set */
	rfc_set_clear( p_set );

	/* remove strings */
	if( p_set -> s_type == RFC_EXT_TYPESTRING )
		{
			n = p_set -> s_a;
			l_item = p_set -> s_item;
			for( k = 0; k < n; k++ , l_item++ )
				if( l_item -> s_data.u_s != NULL )
					rfc_str_drop( l_item -> s_data.u_s );
		}

	/* free item data */
	if( p_set -> s_a )
		{
			free( p_set -> s_item );
			p_set -> s_item = NULL;
			p_set -> s_a = 0;
		}
}

/* allocate item memory to given count */
void
	rfc_set_allocate( rfc_set *p_set , int p_count )
{
	if( p_count < RFC_SET_MINITEMS )
		p_count = RFC_SET_MINITEMS;
	if( p_count < p_set -> s_a )
		return;

	/* align count */
	if( !p_set -> s_a )
		{
			/* allocate new */
			p_set -> s_a = p_count;
			p_set -> s_item = ( rfc_setitem * )calloc( p_set -> s_a , sizeof( rfc_setitem ) );
			return;
		}

	/* reallocate */
	p_count = p_set -> s_a;
	p_set -> s_a *= 2;
	p_set -> s_item = ( rfc_setitem * )realloc( p_set -> s_item , p_set -> s_a * sizeof( rfc_setitem ) );
	memset( &p_set -> s_item[ p_count ] , 0 , p_count * sizeof( rfc_setitem ) );
}

void
	rfc_set_add_d( rfc_set *p_set , short p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				rfc_set_add( p_set , &p_value );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_add( p_set , &l_v );
				break;
		}
}

void
	rfc_set_add_l( rfc_set *p_set , int p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				rfc_set_add( p_set , &p_value );
				break;
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPELONG , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_add( p_set , &l_v );
				break;
		}
}

void
	rfc_set_add_m( rfc_set *p_set , RFC_INT64 p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				rfc_set_add( p_set , &p_value );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEMONEY , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_add( p_set , &l_v );
				break;
		}
}

void
	rfc_set_add_f( rfc_set *p_set , double p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				rfc_set_add( p_set , &p_value );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEDOUBLE , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_add( p_set , &l_v );
				break;
		}
}

void
	rfc_set_add_s( rfc_set *p_set , const char *p_value )
{
	if( p_set -> s_type == RFC_EXT_TYPESTRING ||
		p_set -> s_type == RFC_EXT_TYPECHAR )
		rfc_set_add( p_set , &p_value );
}

void
	rfc_set_add_p( rfc_set *p_set , void *p_value )
{
	if( p_set -> s_type == RFC_EXT_TYPEPTR )
		rfc_set_add( p_set , &p_value );
}

void
	rfc_set_addreg_d( rfc_set *p_set , int p_regtype , short p_vfrom , short p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				rfc_set_addreg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPESHORT , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPESHORT , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_set_addreg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_addreg_l( rfc_set *p_set , int p_regtype , int p_vfrom , int p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				rfc_set_addreg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPELONG , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPELONG , &l_v2 , p_set -> s_type , NULL , NULL );
				rfc_set_addreg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_addreg_m( rfc_set *p_set , int p_regtype , RFC_INT64 p_vfrom , RFC_INT64 p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				rfc_set_addreg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPEMONEY , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPEMONEY , &l_v2 , p_set -> s_type , NULL , NULL );
				rfc_set_addreg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_addreg_f( rfc_set *p_set , int p_regtype , double p_vfrom , double p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				rfc_set_addreg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPEDOUBLE , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPEDOUBLE , &l_v2 , p_set -> s_type , NULL , NULL );
				rfc_set_addreg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_addreg_s( rfc_set *p_set , int p_regtype , const char *p_vfrom , const char *p_vto )
{
	if( p_set -> s_type == RFC_EXT_TYPESTRING ||
		p_set -> s_type == RFC_EXT_TYPECHAR )
		rfc_set_addreg( p_set , p_regtype , &p_vfrom , &p_vto );
}

void
	rfc_set_addreg_p( rfc_set *p_set , int p_regtype , void *p_vfrom , void *p_vto )
{
	if( p_set -> s_type == RFC_EXT_TYPEPTR )
		rfc_set_addreg( p_set , p_regtype , &p_vfrom , &p_vto );
}

/* add set */
void
	rfc_set_addset( rfc_set *p_set , rfc_set *p_value )
{
	int n;
	rfc_setitem *l_item;

	/* check equal types */
	if( p_set -> s_type != p_value -> s_type )
		return;

	/* append all items from value */
	n = p_value -> s_n;
	for( l_item = p_value -> s_item; n--; l_item++ )
		{
			/* if single item */
			if( l_item -> s_regtype == RFC_SET_ONE )
				rfc_set_add( p_set , &l_item -> s_data );
			else
				{
					/* append region */
					rfc_set_addreg( p_set , l_item[0].s_regtype | l_item[1].s_regtype , &l_item[0].s_data , &l_item[1].s_data );
					l_item++;
					n--;
				}
		}
}

void
	rfc_set_remove_d( rfc_set *p_set , short p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				rfc_set_remove( p_set , &p_value );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_remove( p_set , &l_v );
				break;
		}
}

void
	rfc_set_remove_l( rfc_set *p_set , int p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				rfc_set_remove( p_set , &p_value );
				break;
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPELONG , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_remove( p_set , &l_v );
				break;
		}
}

void
	rfc_set_remove_m( rfc_set *p_set , RFC_INT64 p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				rfc_set_remove( p_set , &p_value );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEMONEY , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_remove( p_set , &l_v );
				break;
		}
}

void
	rfc_set_remove_f( rfc_set *p_set , double p_value )
{
	RFC_INT64 l_v;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				rfc_set_remove( p_set , &p_value );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEDOUBLE , &l_v , p_set -> s_type , NULL , NULL );
				rfc_set_remove( p_set , &l_v );
				break;
		}
}

void
	rfc_set_remove_s( rfc_set *p_set , const char *p_value )
{
	if( p_set -> s_type == RFC_EXT_TYPESTRING ||
		p_set -> s_type == RFC_EXT_TYPECHAR )
		rfc_set_remove( p_set , &p_value );
}

void
	rfc_set_remove_p( rfc_set *p_set , void *p_value )
{
	if( p_set -> s_type == RFC_EXT_TYPEPTR )
		rfc_set_remove( p_set , &p_value );
}

void
	rfc_set_removereg_d( rfc_set *p_set , int p_regtype , short p_vfrom , short p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				rfc_set_removereg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPESHORT , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPESHORT , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_set_removereg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_removereg_l( rfc_set *p_set , int p_regtype , int p_vfrom , int p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				rfc_set_removereg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPELONG , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPELONG , &l_v2 , p_set -> s_type , NULL , NULL );
				rfc_set_removereg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_removereg_m( rfc_set *p_set , int p_regtype , RFC_INT64 p_vfrom , RFC_INT64 p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				rfc_set_removereg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPEMONEY , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPEMONEY , &l_v2 , p_set -> s_type , NULL , NULL );
				rfc_set_removereg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_removereg_f( rfc_set *p_set , int p_regtype , double p_vfrom , double p_vto )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				rfc_set_removereg( p_set , p_regtype , &p_vfrom , &p_vto );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPEDOUBLE , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPEDOUBLE , &l_v2 , p_set -> s_type , NULL , NULL );
				rfc_set_removereg( p_set , p_regtype , &l_v1 , &l_v2 );
				break;
		}
}

void
	rfc_set_removereg_s( rfc_set *p_set , int p_regtype , const char *p_vfrom , const char *p_vto )
{
	if( p_set -> s_type == RFC_EXT_TYPESTRING ||
		p_set -> s_type == RFC_EXT_TYPECHAR )
		rfc_set_removereg( p_set , p_regtype , &p_vfrom , &p_vto );
}

void
	rfc_set_removereg_p( rfc_set *p_set , int p_regtype , void *p_vfrom , void *p_vto )
{
	if( p_set -> s_type == RFC_EXT_TYPEPTR )
		rfc_set_removereg( p_set , p_regtype , &p_vfrom , &p_vto );
}

/* remove set */
void
	rfc_set_removeset( rfc_set *p_set , rfc_set *p_value )
{
	int n;
	rfc_setitem *l_item;

	/* check equal types */
	if( p_set -> s_type != p_value -> s_type )
		return;

	/* remove all items from value */
	n = p_value -> s_n;
	for( l_item = p_value -> s_item; n--; l_item++ )
		{
			/* if single item */
			if( l_item -> s_regtype == RFC_SET_ONE )
				rfc_set_remove( p_set , &l_item -> s_data );
			else
				{
					/* append region */
					rfc_set_removereg( p_set , l_item[0].s_regtype | l_item[1].s_regtype , &l_item[0].s_data , &l_item[1].s_data );
					l_item++;
					n--;
				}
		}
}

/* get item count */
int
	rfc_set_itemcount( rfc_set *p_set )
{
	return( p_set -> s_n );
}

/* get item by index */
const rfc_setitem *
	rfc_set_getitem( rfc_set *p_set , int p_pos )
{
	return( &p_set -> s_item[ p_pos ] );
}

short
	rfc_set_isin_d( rfc_set *p_set , short p_value )
{
	RFC_INT64 l_v;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				l_res = rfc_set_isin( p_set , &p_value );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPESHORT , &l_v , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isin( p_set , &l_v );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isin_l( rfc_set *p_set , int p_value )
{
	RFC_INT64 l_v;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				l_res = rfc_set_isin( p_set , &p_value );
				break;
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPELONG , &l_v , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isin( p_set , &l_v );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isin_m( rfc_set *p_set , RFC_INT64 p_value )
{
	RFC_INT64 l_v;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				l_res = rfc_set_isin( p_set , &p_value );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEMONEY , &l_v , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isin( p_set , &l_v );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isin_f( rfc_set *p_set , double p_value )
{
	RFC_INT64 l_v;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				l_res = rfc_set_isin( p_set , &p_value );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_value , RFC_EXT_TYPEDOUBLE , &l_v , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isin( p_set , &l_v );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isin_s( rfc_set *p_set , const char *p_value )
{
	if( p_set -> s_type == RFC_EXT_TYPESTRING ||
		p_set -> s_type == RFC_EXT_TYPECHAR )
		return( rfc_set_isin( p_set , &p_value ) );
	return( 0 );
}

short
	rfc_set_isin_p( rfc_set *p_set , void *p_value )
{
	if( p_set -> s_type == RFC_EXT_TYPEPTR )
		return( rfc_set_isin( p_set , &p_value ) );
	return( 0 );
}

short
	rfc_set_isregin_d( rfc_set *p_set , int p_regtype , short p_vfrom , short p_vto , short p_partial )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPESHORT :
				l_res = rfc_set_isregin( p_set , p_regtype , &p_vfrom , &p_vto , p_partial );
				break;
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPESHORT , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPESHORT , &l_v1 , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isregin( p_set , p_regtype , &l_v1 , &l_v2 , p_partial );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isregin_l( rfc_set *p_set , int p_regtype , int p_vfrom , int p_vto , short p_partial )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPELONG :
			case RFC_EXT_TYPEMOMENT :
			case RFC_EXT_TYPETIMET :
				l_res = rfc_set_isregin( p_set , p_regtype , &p_vfrom , &p_vto , p_partial );
				break;
			case RFC_EXT_TYPEMONEY :
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPELONG , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPELONG , &l_v2 , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isregin( p_set , p_regtype , &l_v1 , &l_v2 , p_partial );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isregin_m( rfc_set *p_set , int p_regtype , RFC_INT64 p_vfrom , RFC_INT64 p_vto , short p_partial )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEMONEY :
				l_res = rfc_set_isregin( p_set , p_regtype , &p_vfrom , &p_vto , p_partial );
				break;
			case RFC_EXT_TYPEDOUBLE :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPEMONEY , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPEMONEY , &l_v2 , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isregin( p_set , p_regtype , &l_v1 , &l_v2 , p_partial );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isregin_f( rfc_set *p_set , int p_regtype , double p_vfrom , double p_vto , short p_partial )
{
	RFC_INT64 l_v1;
	RFC_INT64 l_v2;
	short l_res;

	/* check type */
	switch( p_set -> s_type )
		{
			case RFC_EXT_TYPEDOUBLE :
				l_res = rfc_set_isregin( p_set , p_regtype , &p_vfrom , &p_vto , p_partial );
				break;
			case RFC_EXT_TYPEMONEY :
				rfc_type_cnv( &p_vfrom , RFC_EXT_TYPEDOUBLE , &l_v1 , p_set -> s_type , NULL , NULL );
				rfc_type_cnv( &p_vto , RFC_EXT_TYPEDOUBLE , &l_v2 , p_set -> s_type , NULL , NULL );
				l_res = rfc_set_isregin( p_set , p_regtype , &l_v1 , &l_v2 , p_partial );
				break;
			default :
				return( 0 );
		}
	return( l_res );
}

short
	rfc_set_isregin_s( rfc_set *p_set , int p_regtype , const char *p_vfrom , const char *p_vto , short p_partial )
{
	if( p_set -> s_type == RFC_EXT_TYPESTRING ||
		p_set -> s_type == RFC_EXT_TYPECHAR )
		return( rfc_set_isregin( p_set , p_regtype , &p_vfrom , &p_vto , p_partial ) );
	return( 0 );
}

short
	rfc_set_isregin_p( rfc_set *p_set , int p_regtype , void *p_vfrom , void *p_vto , short p_partial )
{
	if( p_set -> s_type == RFC_EXT_TYPEPTR )
		return( rfc_set_isregin( p_set , p_regtype , &p_vfrom , &p_vto , p_partial ) );
	return( 0 );
}

/* check set in set */
short
	rfc_set_issetin( rfc_set *p_set , rfc_set *p_value , short p_partial )
{
	int n;
	rfc_setitem *l_item;

	/* check equal types */
	if( p_set -> s_type != p_value -> s_type )
		return( 0 );

	/* check all items from value */
	n = p_value -> s_n;
	for( l_item = p_value -> s_item; n--; l_item++ )
		{
			/* if single item */
			if( l_item -> s_regtype == RFC_SET_ONE )
				{
					if( rfc_set_isin( p_set , &l_item -> s_data ) )
						{
							if( p_partial )
								return( 1 );
						}
					else
						{
							if( !p_partial )
								return( 0 );
						}
				}
			else
				{
					/* check region */
					if( rfc_set_isregin( p_set , l_item[0].s_regtype | l_item[1].s_regtype , &l_item[0].s_data , &l_item[1].s_data , p_partial ) )
						{
							if( p_partial )
								return( 1 );
						}
					else
						{
							if( !p_partial )
								return( 0 );
						}
					l_item++;
					n--;
				}
		}
	return( 1 );
}

/* check set is empty */
short
	rfc_set_isempty( rfc_set *p_set )
{
	return( ( p_set -> s_n )? 0 : 1 );
}

/* add item to set */
void
	rfc_set_add( rfc_set *p_set , const void *p_value )
{
	int l_pos;
	rfc_setitem *l_item;
	int l_cmp;

	/* get min item */
	l_pos = _rfc_set_getprevequal( p_set , p_value );
	if( l_pos < 0 )
		{
			/* append item to head */
			_rfc_set_additem( p_set , RFC_SET_ONE , p_value , 0 );
			return;
		}
			
	/* compare items */
	l_item = &p_set -> s_item[ l_pos ];
	l_cmp = rfc_type_cmp( p_set -> s_type , p_value , &l_item -> s_data );

	/* if not equal */
	if( l_cmp )
		{
			/* in region */
			if( l_item -> s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) )
				return;

			/* insert after */
			_rfc_set_additem( p_set , RFC_SET_ONE , p_value , l_pos + 1 );
			return;
		}
			
	/* equal */
	/* if start of region */
	if( l_item -> s_regtype == RFC_SET_MINEXC )
		{
			/* make region type including */
			l_item -> s_regtype = RFC_SET_MININC;

			/* check prev region - union if equal */
			if( l_pos )
				if( !rfc_type_cmp( p_set -> s_type , p_value , &l_item[-1].s_data ) )
					_rfc_set_removeitems( p_set , l_pos - 1 , 2 );
		}
	else
	/* if end of region */
	if( l_item -> s_regtype == RFC_SET_MAXEXC )
		{
			/* make region type including */
			l_item -> s_regtype = RFC_SET_MAXINC;

			/* check next region - union if equal */
			if( ++l_pos < p_set -> s_n )
				if( !rfc_type_cmp( p_set -> s_type , p_value , &l_item[1].s_data ) )
					_rfc_set_removeitems( p_set , l_pos - 1 , 2 );
			return;
		}

	/* contains the same item - ignore */
}

/* remove item from set */
void
	rfc_set_remove( rfc_set *p_set , const void *p_value )
{
	int l_pos;
	rfc_setitem *l_item;
	int l_cmp;

	/* get min item */
	l_pos = _rfc_set_getprevequal( p_set , p_value );
	if( l_pos < 0 )
		return;

	/* compare items */
	l_item = &p_set -> s_item[ l_pos ];
	l_cmp = rfc_type_cmp( p_set -> s_type , p_value , &l_item -> s_data );

	/* if not equal */
	if( l_cmp )
		{
			/* if in region */
			if( l_item -> s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) )
				{
					/* split region */
					_rfc_set_additem( p_set , RFC_SET_MAXEXC , p_value , l_pos + 1 );
					_rfc_set_additem( p_set , RFC_SET_MINEXC , p_value , l_pos + 2 );
				}
			/* else ignore */
			return;
		}

	/* equal */
	/* if the same item - remove it */
	if( l_item -> s_regtype == RFC_SET_ONE )
		{
			_rfc_set_removeitems( p_set , l_pos , 1 );
			return;
		}

	/* if excluding end of region */
	if( l_item -> s_regtype & (RFC_SET_MAXEXC|RFC_SET_MINEXC) )
		return;

	/* make excluding */
	l_item -> s_regtype = ( l_item -> s_regtype == RFC_SET_MININC )? RFC_SET_MINEXC : RFC_SET_MAXEXC;
}

/* check item in set */
short
	rfc_set_isin( rfc_set *p_set , const void *p_value )
{
	int l_pos;
	rfc_setitem *l_item;
	int l_cmp;

	/* get min item */
	l_pos = _rfc_set_getprevequal( p_set , p_value );
	if( l_pos < 0 )
		return( 0 );

	/* compare items */
	l_item = &p_set -> s_item[ l_pos ];
	l_cmp = rfc_type_cmp( p_set -> s_type , p_value , &l_item -> s_data );

	/* not equal - in set if in region */
	if( l_cmp )
		return( ( l_item -> s_regtype & (RFC_SET_MININC|RFC_SET_MINEXC) )? 1 : 0 );

	/* equal - not in set if excluding */
	return( ( l_item -> s_regtype & (RFC_SET_MINEXC|RFC_SET_MAXEXC) )? 0 : 1 );
}

/* add item region to set */
void
	rfc_set_addreg( rfc_set *p_set , int p_regtype , const void *p_vfrom , const void *p_vto )
{
	int l_a;
	int l_b;
	rfc_setitem *l_item;

	l_a = _rfc_set_getprevequal( p_set , p_vfrom );
	l_b = _rfc_set_getprevequal( p_set , p_vto );

	/* set top margin */
	if( l_a < 0 )
		_rfc_set_additem( p_set , p_regtype & (RFC_SET_MININC|RFC_SET_MINEXC) , p_vfrom , l_a = 0 );
	else
		{
			l_item = &p_set -> s_item[ l_a ];
			if( rfc_type_cmp( p_set -> s_type , &l_item -> s_data , p_vfrom ) )
				{
					if( !( l_item -> s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) ) )
						_rfc_set_additem( p_set , p_regtype & (RFC_SET_MININC|RFC_SET_MINEXC) , p_vfrom , ++l_a );
				}
			else
				{
					switch( l_item -> s_regtype )
						{
							case RFC_SET_ONE :
								l_item -> s_regtype = RFC_SET_MININC;
								break;
							case RFC_SET_MINEXC :
								if( p_regtype & RFC_SET_MININC )
									{
										l_item -> s_regtype = RFC_SET_MININC;
										/* check prev */
										if( l_a > 0 )
											if( !rfc_type_cmp( p_set -> s_type , &l_item[ -1 ].s_data , p_vfrom ) )
												l_a -= 2;
									}
								break;
							case RFC_SET_MAXINC :
								l_a--;
								break;
							case RFC_SET_MAXEXC :
								if( p_regtype & RFC_SET_MININC )
									l_a--;
								else
									{
										/* check next */
										if( ++l_a < p_set -> s_n )
											if( rfc_type_cmp( p_set -> s_type , &l_item[ 1 ].s_data , p_vfrom ) )
												_rfc_set_additem( p_set , p_regtype & (RFC_SET_MININC|RFC_SET_MINEXC) , p_vfrom , l_a );
									}
								break;
						}
				}
		}

	/* set bottom margin */
	if( l_b == l_a )
		_rfc_set_additem( p_set , p_regtype & (RFC_SET_MAXINC|RFC_SET_MAXEXC) , p_vto , ++l_b );
	else
		{
			l_item = &p_set -> s_item[ l_b ];
			if( rfc_type_cmp( p_set -> s_type , &l_item -> s_data , p_vto ) )
				{
					l_b++;
					if( !( l_item -> s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) ) )
						_rfc_set_additem( p_set , p_regtype & (RFC_SET_MAXINC|RFC_SET_MAXEXC) , p_vto , l_b );
				}
			else
				{
					switch( l_item -> s_regtype )
						{
							case RFC_SET_ONE :
								l_item -> s_regtype = RFC_SET_MAXINC;
								break;
							case RFC_SET_MININC :
								l_b++;
								break;
							case RFC_SET_MINEXC :
								if( p_regtype & RFC_SET_MAXINC )
									l_b++;
								else
									{
										/* check prev */
										if( !rfc_type_cmp( p_set -> s_type , &l_item[ -1 ].s_data , p_vto ) )
											l_b--;
										else
											_rfc_set_additem( p_set , p_regtype & (RFC_SET_MAXINC|RFC_SET_MAXEXC) , p_vto , l_b );
									}
								break;
							case RFC_SET_MAXEXC :
								if( p_regtype & RFC_SET_MAXINC )
									{
										/* check next */
										if( l_b < ( p_set -> s_n - 1 ) ) {
											if( rfc_type_cmp( p_set -> s_type , &l_item[ 1 ].s_data , p_vto ) )
												l_item -> s_regtype = RFC_SET_MAXINC;
											else
												l_b -=2;
										}
									}
								break;
						}
				}
		}

	/* remove items between l_a & l_b excluding */
	if( l_a < --l_b )
		_rfc_set_removeitems( p_set , l_a , l_b - l_a );
}

/* remove item region from set */
void
	rfc_set_removereg( rfc_set *p_set , int p_regtype , const void *p_vfrom , const void *p_vto )
{
	int l_a;
	int l_b;
	rfc_setitem *l_item;

	l_b = _rfc_set_getprevequal( p_set , p_vto );
	if( l_b < 0 )
		return;
	l_a = _rfc_set_getprevequal( p_set , p_vfrom );

	/* set top margin */
	if( l_a < 0 )
		l_a = 0;
	else
		{
			l_item = &p_set -> s_item[ l_a ];
			if( rfc_type_cmp( p_set -> s_type , &l_item -> s_data , p_vfrom ) )
				{
					l_a++;
					if( l_item -> s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) )
						_rfc_set_additem( p_set , ( p_regtype & RFC_SET_MININC )? RFC_SET_MAXEXC : RFC_SET_MAXINC , p_vfrom , l_a++ );
				}
			else
				{
					switch( l_item -> s_regtype )
						{
							case RFC_SET_ONE :
								if( p_regtype & RFC_SET_MINEXC )
									l_a++;
								break;
							case RFC_SET_MININC :
								if( p_regtype & RFC_SET_MINEXC )
									{
										l_item -> s_regtype = RFC_SET_ONE;
										l_a++;
									}
								break;
							case RFC_SET_MAXEXC :
								l_a++;
								break;
							case RFC_SET_MAXINC :
								if( p_regtype & RFC_SET_MININC )
									l_item -> s_regtype = RFC_SET_MAXEXC;
								l_a++;
								break;
						}
				}
		}

	/* set bottom margin */
	l_item = &p_set -> s_item[ l_b ];
	if( rfc_type_cmp( p_set -> s_type , &l_item -> s_data , p_vto ) )
		{
			if( l_item -> s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) )
				_rfc_set_additem( p_set , ( p_regtype & RFC_SET_MININC )? RFC_SET_MINEXC : RFC_SET_MININC , p_vto , l_b + 1 );
		}
	else
		{
			switch( l_item -> s_regtype )
				{
					case RFC_SET_ONE :
						if( p_regtype & RFC_SET_MAXEXC )
							l_b--;
						break;
					case RFC_SET_MINEXC :
						l_b--;
						break;
					case RFC_SET_MININC :
						if( p_regtype & RFC_SET_MAXINC )
							l_item -> s_regtype = RFC_SET_MINEXC;
						l_b--;
						break;
					case RFC_SET_MAXINC :
						if( p_regtype & RFC_SET_MAXEXC )
							{
								l_item -> s_regtype = RFC_SET_ONE;
								l_b--;
							}
						break;
				}
		}

	/* remove items between l_a & l_b including */
	if( ++l_b > l_a )
		_rfc_set_removeitems( p_set , l_a , l_b - l_a );
}

/* check item region in set */
short
	rfc_set_isregin( rfc_set *p_set , int p_regtype , const void *p_vfrom , const void *p_vto , short p_partial )
{
	int l_a;
	int l_b;
	rfc_setitem *l_item;
/*	int l_kind_a;*/
/*	int l_kind_b;*/

	/* find margins */
	l_b = _rfc_set_getprevequal( p_set , p_vto );
	if( l_b < 0 )
		return( 0 );
	l_a = _rfc_set_getprevequal( p_set , p_vfrom );
	if( l_a < 0 )
		return( p_partial );

	/* compare top */
	l_item = &p_set -> s_item[ l_a ];
	if( rfc_type_cmp( p_set -> s_type , &l_item -> s_data , p_vfrom ) )
		{
			if( l_item -> s_regtype & (RFC_SET_MININC|RFC_SET_MINEXC) )
				{
					if( p_partial )
						return( 1 );
/*					l_kind_a = 8;*/
				}
			else
				{
					if( !p_partial )
						return( 0 );
/*					l_kind_a = 9;*/
				}
		}
	else
		{
			switch( l_item -> s_regtype )
				{
					case RFC_SET_ONE :
						if( !p_partial )
							return( 0 );
						if( p_regtype & RFC_SET_MININC )
							return( 1 );
/*						l_kind_a = 1;*/
						break;
					case RFC_SET_MINEXC :
						if( p_regtype & RFC_SET_MININC )
							return( p_partial );
						if( p_partial )
							return( 1 );
/*						l_kind_a = 4;*/
						break;
					case RFC_SET_MININC :
						if( p_partial )
							return( 1 );
/*						l_kind_a = ( p_regtype & RFC_SET_MININC )? 2 : 3;*/
						break;
					case RFC_SET_MAXEXC :
						if( p_regtype & RFC_SET_MININC )
							if( !p_partial )
								return( 0 );
/*						l_kind_a = ( p_partial )? 7 : 6;*/
						if( !p_partial )
							{
								/* next must be equal */
								if( ++l_a >= p_set -> s_n )
									return( 0 );
								if( rfc_type_cmp( p_set -> s_type , &l_item[1].s_data , p_vfrom ) )
									return( 0 );
							}
						break;
					case RFC_SET_MAXINC :
						if( p_regtype & RFC_SET_MININC )
							return( p_partial );
						if( !p_partial )
							return( 0 );
/*						l_kind_a = 5;*/
						break;
				}
		}

	/* compare bottom */
	l_item = &p_set -> s_item[ l_b ];
	if( rfc_type_cmp( p_set -> s_type , &l_item -> s_data , p_vto ) )
		{
			if( l_item -> s_regtype & (RFC_SET_MININC|RFC_SET_MINEXC) )
				{
					if( p_partial )
						return( 1 );
/*					l_kind_b = 8;*/
					return( ( l_b == l_a )? 1 : 0 );
				}
			else
				{
					if( !p_partial )
						return( 0 );
/*					l_kind_b = ( l_item -> s_regtype == RFC_SET_ONE )? 7 : 9;*/
					return( ( l_a == l_b )? 0 : 1 );
				}
		}
	else
		{
			switch( l_item -> s_regtype )
				{
					case RFC_SET_ONE :
						if( p_regtype & RFC_SET_MAXINC )
							return( p_partial );
						if( !p_partial )
							return( 0 );
/*						l_kind_b = 1;*/
						break;
					case RFC_SET_MINEXC :
						if( p_regtype & RFC_SET_MAXINC )
							if( !p_partial )
								return( 0 );
/*						l_kind_b = ( p_partial )? 4 : 3;*/
						if( p_partial )
							break;
						/* prev must be equal */
						if( --l_b != l_a + 1 )
							return( 0 );
						if( rfc_type_cmp( p_set -> s_type , &l_item[-1].s_data , p_vto ) )
							return( 0 );
						return( 1 );
					case RFC_SET_MININC :
						if( p_regtype & RFC_SET_MAXINC )
							return( p_partial );
						if( !p_partial )
							return( 0 );
/*						l_kind_b = 2;*/
						break;
					case RFC_SET_MAXEXC :
						if( p_regtype & RFC_SET_MAXINC )
							return( p_partial );
						if( p_partial )
							return( 1 );
/*						l_kind_b = 6;*/
						return( ( l_b == l_a + 1 )? 1 : 0 );
					case RFC_SET_MAXINC :
						if( p_partial )
							return( 1 );
/*						l_kind_b = 5;*/
						return( ( l_b == l_a + 1 )? 1 : 0 );
				}
		}

	return( ( l_b > l_a + 1 )? 1 : 0 );
}

/* enumerate regions */
short
	rfc_set_enum( rfc_set *p_set , int *p_regtype , RFC_TYPE *p_from , RFC_TYPE *p_to )
{
	/* go to next */
	if( ++p_set -> s_enum >= p_set -> s_n )
		{
			p_set -> s_enum = -1;
			return( 0 );
		}

	/* single item */
	if( p_set -> s_item[ p_set -> s_enum ].s_regtype == RFC_SET_ONE )
		{
			*p_regtype = RFC_SET_REGMININC_MAXINC;
			p_to -> u_m = p_from -> u_m = p_set -> s_item[ p_set -> s_enum ].s_data.u_m;
			return( 1 );
		}

	*p_regtype = p_set -> s_item[ p_set -> s_enum ].s_regtype;
	p_from -> u_m = p_set -> s_item[ p_set -> s_enum++ ].s_data.u_m;

	/* breaked enumeration */
	if( *p_regtype & (RFC_SET_MAXEXC|RFC_SET_MAXINC) )
		{
			p_set -> s_enum = -1;
			return( 0 );
		}
			
	*p_regtype |= p_set -> s_item[ p_set -> s_enum ].s_regtype;
	p_to -> u_m = p_set -> s_item[ p_set -> s_enum ].s_data.u_m;

	return( 1 );
}

/* end enumeration */
void
	rfc_set_endenum( rfc_set *p_set )
{
	p_set -> s_enum = -1;
}

/*#######################################################*/
/*#######################################################*/

/* append item to position */
static void
	_rfc_set_additem( rfc_set *p_set , int p_regtype , const void *p_value , int p_pos )
{
	RFC_INT64 l_v;

	/* allocate */
	rfc_set_allocate( p_set , p_set -> s_n + 1 );

	/* shift if needed */
	if( p_pos < p_set -> s_n )
		{
			l_v = p_set -> s_item[ p_set -> s_n ].s_data.u_m;
			memmove( &p_set -> s_item[ p_pos + 1 ] , &p_set -> s_item[ p_pos ] , sizeof( rfc_setitem ) * ( p_set -> s_n - p_pos ) );
			p_set -> s_item[ p_pos ].s_data.u_m = l_v;
		}

	/* set item data */
	p_set -> s_item[ p_pos ].s_regtype = p_regtype;
	rfc_type_set( p_set -> s_type , &p_set -> s_item[ p_pos ].s_data , p_value , NULL );
}

/* internal remove items */
static void
	_rfc_set_removeitems( rfc_set *p_set , int p_from , int p_count )
{
	RFC_INT64 l_v;
	int l_n;

	l_n = p_set -> s_n - p_from - p_count;
	if( !l_n )
		{
			p_set -> s_n -= p_count;
			return;
		}

	/* if not string - simple move */
	if( p_set -> s_type != RFC_EXT_TYPESTRING )
		{
			memmove( &p_set -> s_item[ p_from ] , &p_set -> s_item[ p_from + p_count ] , l_n * sizeof( rfc_setitem ) );
			return;
		}

	/* remove by one with shift */
	while( p_count-- )
		{
			l_v = p_set -> s_item[ p_from + p_count ].s_data.u_m;
			memmove( &p_set -> s_item[ p_from + p_count ] , &p_set -> s_item[ p_from + p_count + 1 ] , l_n * sizeof( rfc_setitem ) );
			p_set -> s_item[ --p_set -> s_n ].s_data.u_m = l_v;
		}
}

/* find previous item */
static int
	_rfc_set_getprevequal( rfc_set *p_set , const void *p_value )
{
	int l_from;
	int l_to;
	rfc_setitem *l_item;
	int l_cmp;
	int l_pos;

	l_from = 0;
	l_to = p_set -> s_n - 1;
	if( l_to < 0 )
		return( -1 );

	l_item = p_set -> s_item;

	/* check margins */
	if( ( l_cmp = rfc_type_cmp( p_set -> s_type , p_value , &l_item[ l_from ].s_data ) ) <= 0 )
		{
			if( !l_cmp )
				return( l_from );
			return( -1 );
		}
	if( ( l_cmp = rfc_type_cmp( p_set -> s_type , p_value , &l_item[ l_to ].s_data ) ) >= 0 )
		return( l_to );

	/* binary search */
	while( l_from < l_to )
		{
			l_pos = ( l_from + l_to ) / 2;
			if( l_from == l_pos )
				break;
			if( !( l_cmp = rfc_type_cmp( p_set -> s_type , p_value , &l_item[ l_pos ].s_data ) ) )
				return( l_pos );
			if( l_cmp > 0 )
				l_from = l_pos;
			else
				l_to = l_pos;
		}
	return( l_from );
}

/* append items from cross */
static void
	_rfc_set_addcrossitems( rfc_set *p_set , rfc_setitem *p_regfrom , rfc_setitem *p_regto , rfc_setitem *p_items , int p_from , int p_to )
{
	short l_use_x;
	short l_use_y;

	/* process top margin */
	l_use_x = 0;
	if( p_from < 0 )
		p_from = 0;
	else
		{
			/* compare top */
			if( rfc_type_cmp( p_set -> s_type , &p_regfrom -> s_data , &p_items[ p_from ].s_data ) )
				{
					/* top before region */
					if( p_items[ p_from ].s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) )
						{
							l_use_x = 1;
							p_from++;
						}
				}
			else
				{
					/* equal */
					switch( p_items[ p_from ].s_regtype )
						{
							case RFC_SET_ONE :
								if( p_regfrom -> s_regtype == RFC_SET_MINEXC )
									p_from++;
								break;
							case RFC_SET_MININC :
								l_use_x = 1;
								p_from++;
								break;
							case RFC_SET_MAXEXC :
								p_from++;
								break;
							case RFC_SET_MAXINC :
								if( p_regfrom -> s_regtype == RFC_SET_MININC )
									rfc_set_add( p_set , &p_regfrom -> s_data );
								p_from++;
								break;
						}
				}
		}

	/* process bottom margin */
	l_use_y = 0;
	if( rfc_type_cmp( p_set -> s_type , &p_regto -> s_data , &p_items[ p_to ].s_data ) )
		{
			/* non-equal */
			if( p_items[ p_to ].s_regtype & (RFC_SET_MINEXC|RFC_SET_MININC) )
				{
					/* region from p_to to p_regto */
					l_use_y = 1;
				}
		}
	else
		{
			/* equal */
			switch( p_items[ p_to ].s_regtype )
				{
					case RFC_SET_ONE :
						if( p_regto -> s_regtype == RFC_SET_MAXEXC )
							p_to--;
						break;
					case RFC_SET_MINEXC :
						p_to--;
						break;
					case RFC_SET_MININC :
						if( p_regto -> s_regtype == RFC_SET_MAXEXC )
							rfc_set_add( p_set , &p_regto -> s_data );
						p_to--;
						break;
					case RFC_SET_MAXINC :
						if( p_regto -> s_regtype == RFC_SET_MAXEXC )
							{
								l_use_y = 1;
								p_to--;
							}
						break;
				}
		}

	/* check use */
	if( l_use_x && l_use_y && p_from == p_to + 1 )
		{
			rfc_set_addreg( p_set , p_regfrom -> s_regtype | p_regto -> s_regtype , &p_regfrom -> s_data , &p_regto -> s_data );
			return;
		}
	if( l_use_x )
		{
			rfc_set_addreg( p_set , p_regfrom -> s_regtype | p_items[ p_from ].s_regtype , &p_regfrom -> s_data , &p_items[ p_from ].s_data );
			p_from++;
		}
	if( l_use_y )
		{
			rfc_set_addreg( p_set , p_items[ p_to ].s_regtype | p_regto -> s_regtype , &p_items[ p_to ].s_data , &p_regto -> s_data );
			p_to--;
		}

	/* simply append all from p_from to p_to */
	while( p_from <= p_to )
		{
			/* single item */
			if( p_items[ p_from ].s_regtype == RFC_SET_ONE )
				{
					rfc_set_add( p_set , &p_items[ p_from ].s_data );
					p_from++;
					continue;
				}

			/* region */
			rfc_set_addreg( p_set , p_items[ p_from ].s_regtype | p_items[ p_from + 1 ].s_regtype , &p_items[ p_from ].s_data , &p_items[ p_from + 1 ].s_data );
			p_from += 2;
		}
}

