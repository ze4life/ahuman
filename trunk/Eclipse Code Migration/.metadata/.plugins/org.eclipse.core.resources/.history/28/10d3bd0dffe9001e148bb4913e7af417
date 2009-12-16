/*#######################################################*/
/*#######################################################*/

/* std headers */
#include <__gen.h>

#define RFC_LST_MINITEMS			8

/*#######################################################*/
/*#######################################################*/

/* create list */
rfc_list *
	rfc_lst_create( int p_type )
{
	rfc_list *l_lst;

	if( p_type == RFC_EXT_TYPECHAR )
		p_type = RFC_EXT_TYPESTRING;
	l_lst = ( rfc_list * )calloc( 1 , sizeof( rfc_list ) );
	l_lst -> s_type = p_type;

	return( l_lst );
}

/* destroy list */
void
	rfc_lst_destroy( rfc_list *p_lst )
{
	if( p_lst -> s_ref-- )
		return;

	rfc_lst_init( p_lst );
	free( p_lst );
}

/* reference list */
void
	rfc_lst_ref( rfc_list *p_lst )
{
	p_lst -> s_ref++;
}

/* clear array without reallocate memory */
void
	rfc_lst_clear( rfc_list *p_lst )
{
	p_lst -> s_n = 0;
}

/* clear list with free intenal memory without destroy struct */
void
	rfc_lst_init( rfc_list *p_lst )
{
	int k , n;
	rfc_string l_s;

	/* free strings */
	if( p_lst -> s_type == RFC_EXT_TYPESTRING )
		{
			n = p_lst -> s_a;
			for( k = 0; k < n; k++ )
				if( ( l_s = p_lst -> s_p[ k ].u_s ) != NULL )
					rfc_str_drop( l_s );
		}

	/* free buffer */
	if( p_lst -> s_p != NULL )
		{
			free( p_lst -> s_p );
			p_lst -> s_p = NULL;
			p_lst -> s_n = p_lst -> s_a = 0;
		}
}

/* allocate list memory to given count */
void
	rfc_lst_allocate( rfc_list *p_lst , int p_count )
{
	/* check already has */
	if( p_count <= p_lst -> s_a )
		return;

	/* align */
	if( p_count < RFC_LST_MINITEMS )
		p_count = RFC_LST_MINITEMS;
	else
	if( p_count % RFC_LST_MINITEMS )
		p_count = p_count - ( p_count % RFC_LST_MINITEMS ) + RFC_LST_MINITEMS;

	if( p_lst -> s_a )
		{
			/* reallocate */
			p_lst -> s_p = ( RFC_TYPE * )realloc( p_lst -> s_p , p_count * sizeof( RFC_TYPE ) );
			/* nullify tail */
			memset( &p_lst -> s_p[ p_lst -> s_n ] , 0 , sizeof( RFC_TYPE ) * ( p_count - p_lst -> s_a ) );
		}
	else
		p_lst -> s_p = ( RFC_TYPE * )calloc( p_count , sizeof( RFC_TYPE ) );

	p_lst -> s_a = p_count;
}

/* return item count */
int
	rfc_lst_count( rfc_list *p_lst )
{
	return( p_lst -> s_n );
}

/* append item to end of list */
int
	rfc_lst_add( rfc_list *p_lst , RFC_TYPE *p_data )
{
	rfc_lst_allocate( p_lst , p_lst -> s_n + 1 );
	rfc_type_set( p_lst -> s_type , &p_lst -> s_p[ p_lst -> s_n ] , p_data , NULL );
	return( p_lst -> s_n++ );
}

/* remove item by position */
void
	rfc_lst_remove( rfc_list *p_lst , int p_index )
{
	RFC_INT64 l_v;

	if( p_index < 0 ||
		p_index >= p_lst -> s_n )
		return;

	/* shift tail */
	p_lst -> s_n--;
	if( p_index < p_lst -> s_n )
		{
			l_v = p_lst -> s_p[ p_index ].u_m;
			memmove( &p_lst -> s_p[ p_index ] , &p_lst -> s_p[ p_index + 1 ] , sizeof( RFC_TYPE ) * ( p_lst -> s_n - p_index ) );
			p_lst -> s_p[ p_lst -> s_n ].u_m = l_v;
		}
}

/* get item by position */
RFC_TYPE *
	rfc_lst_get( rfc_list *p_lst , int p_index )
{
	if( p_index < 0 ||
		p_index >= p_lst -> s_n )
		return( NULL );
	return( &p_lst -> s_p[ p_index ] );
}

/* set given list item data */
short
	rfc_lst_replace( rfc_list *p_lst , int p_index , RFC_TYPE *p_data )
{
	/* check index is in region */
	if( p_index < 0 ||
		p_index >= p_lst -> s_n  )
		return( 0 );

	/* set data by index */
	rfc_type_set( p_lst -> s_type , &p_lst -> s_p[ p_index ] , p_data , NULL );
	return( 1 );
}

/* short sort callback */
int
	rfc_lst_sort_cmp_d( void *p_userdata , const RFC_TYPE *p_e1 , const RFC_TYPE *p_e2 )
{
	return( p_e1 -> u_d - p_e2 -> u_d );
}

/* int sort callback */
int
	rfc_lst_sort_cmp_l( void *p_userdata , const RFC_TYPE *p_e1 , const RFC_TYPE *p_e2 )
{
	if( p_e1 -> u_l > p_e2 -> u_l )
		return( 1 );
	if( p_e1 -> u_l < p_e2 -> u_l )
		return( -1 );
	return( 0 );
}

/* double sort callback */
int
	rfc_lst_sort_cmp_f( void *p_userdata , const RFC_TYPE *p_e1 , const RFC_TYPE *p_e2 )
{
	if( p_e1 -> u_f > p_e2 -> u_f )
		return( 1 );
	if( p_e1 -> u_f < p_e2 -> u_f )
		return( -1 );
	return( 0 );
}

/* float sort callback */
int
	rfc_lst_sort_cmp_r( void *p_userdata , const RFC_TYPE *p_e1 , const RFC_TYPE *p_e2 )
{
	if( p_e1 -> u_r > p_e2 -> u_r )
		return( 1 );
	if( p_e1 -> u_r < p_e2 -> u_r )
		return( -1 );
	return( 0 );
}

/* money sort callback */
int
	rfc_lst_sort_cmp_m( void *p_userdata , const RFC_TYPE *p_e1 , const RFC_TYPE *p_e2 )
{
	if( p_e1 -> u_m > p_e2 -> u_m )
		return( 1 );
	if( p_e1 -> u_m < p_e2 -> u_m )
		return( -1 );
	return( 0 );
}

/* character sort callback */
int
	rfc_lst_sort_cmp_s( void *p_userdata , const RFC_TYPE *p_e1 , const RFC_TYPE *p_e2 )
{
	if( p_e1 -> u_s == NULL )
		{
			/* NULL equal to NULL */
			if( p_e2 -> u_s == NULL )
				return( 0 );
			/* NULL more than not NULL */
			return( 1 );
		}
	/* not NULL less than NULL */
	if( p_e2 -> u_s == NULL )
		return( -1 );
			
	return( strcmp( p_e1 -> u_s , p_e2 -> u_s ) );
}

/* sort list elements */
short
	rfc_lst_sort( rfc_list *p_lst , void *p_userdata , rfc_lst_compare f_compare )
{
	/* nothing to sort */
	if( p_lst -> s_n <= 1 )
		return( 1 );

	/* setup sort function */
	if( f_compare == NULL )
		{
			switch( p_lst -> s_type )
				{
					case RFC_EXT_TYPESHORT	:	f_compare = rfc_lst_sort_cmp_d; break;
					case RFC_EXT_TYPEPTR	:
					case RFC_EXT_TYPEMOMENT	:
					case RFC_EXT_TYPETIMET	:
					case RFC_EXT_TYPELONG	:	f_compare = rfc_lst_sort_cmp_l; break;
					case RFC_EXT_TYPEMONEY	:	f_compare = rfc_lst_sort_cmp_m; break;
					case RFC_EXT_TYPEDOUBLE	:	f_compare = rfc_lst_sort_cmp_f; break;
					case RFC_EXT_TYPEFLOAT	:	f_compare = rfc_lst_sort_cmp_r; break;
					case RFC_EXT_TYPECHAR	:
					case RFC_EXT_TYPESTRING	:	f_compare = rfc_lst_sort_cmp_s; break;
					default :					return( 0 );
				}
		}

	/* call sort */
	rfc_qsort( p_userdata , p_lst -> s_p , p_lst -> s_n , sizeof( RFC_TYPE ) , ( rfc_qsortcb )f_compare );
	return( 1 );
}

