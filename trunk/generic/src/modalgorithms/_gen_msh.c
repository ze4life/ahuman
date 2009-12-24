/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

static short
	_rfc_msh_skipdef( rfc_blob *p_blob , int *p_offset );

/*#######################################################*/
/*#######################################################*/
/* routines */

rfc_msh *
	rfc_msh_create( short p_bloballoc )
{
	rfc_msh *l_msh;
	
	l_msh = ( rfc_msh * )calloc( 1 , sizeof( rfc_msh ) );
	l_msh -> s_def.s_items.s_type = RFC_EXT_TYPEPTR;
	l_msh -> s_def.s_dataown = p_bloballoc;

	return( l_msh );
}

void
	rfc_msh_destroy( rfc_msh *p_msh )
{
	int k , n;
	rfc_msh_itemdef *l_p;

	/* free item def */
	n = rfc_msh_item_count( p_msh );
	for( k = 0; k < n; k++ )
		{
			l_p = rfc_msh_item_get( p_msh , k );
			free( l_p );
		}
	rfc_lst_init( &p_msh -> s_def.s_items );

	/* free data */
	if( p_msh -> s_def.s_dataown )
		rfc_blob_free( &p_msh -> s_data );
	free( p_msh );
}

/* set RPC data */
int
	rfc_msh_item_create( rfc_msh *p_msh , const char *p_name , int p_valtype )
{
	rfc_msh_itemdef *l_p;
	RFC_TYPE l_v;

	l_p = ( rfc_msh_itemdef * )calloc( 1 , sizeof( rfc_msh_itemdef ) );
	l_p -> s_name = p_name;
	l_p -> s_type = p_valtype;
	l_p -> s_kind = RFC_MSH_KIND_VALUE;
	l_v.u_p = l_p;

	return( rfc_lst_add( &p_msh -> s_def.s_items , &l_v ) );
}

rfc_msh_itemdef *
	rfc_msh_item_get( rfc_msh *p_msh , int p_pos )
{
	RFC_TYPE *l_v;
	
	l_v = rfc_lst_get( &p_msh -> s_def.s_items , p_pos );
	return( ( rfc_msh_itemdef * )l_v -> u_p );
}

int
	rfc_msh_item_count( rfc_msh *p_msh )
{
	return( rfc_lst_count( &p_msh -> s_def.s_items ) );
}

short
	rfc_msh_setitem_value( rfc_msh *p_msh , int p_pos , RFC_TYPE *p_val )
{
	RFC_TYPE l_v;
	rfc_msh_itemdef *l_item;

	l_item = rfc_msh_item_get( p_msh , p_pos );

	/* position */
	l_v.u_l = p_pos;
	rfc_blob_add( &p_msh -> s_data , RFC_EXT_TYPELONG , &l_v );

	/* data */
	rfc_blob_add( &p_msh -> s_data , l_item -> s_type , p_val );
	return( 1 );
}

short
	rfc_msh_setitem_list( rfc_msh *p_msh , int p_pos , rfc_list *p_list )
{
	RFC_TYPE l_v;
	int k , n;
	RFC_TYPE *l_pv;
	rfc_msh_itemdef *l_item;

	/* fill item if first row */
	if( !p_msh -> s_def.s_nrows )
		{
			l_item = rfc_msh_item_get( p_msh , p_pos );

			/* set props */
			l_item -> s_type = p_list -> s_type;
			l_item -> s_kind = RFC_MSH_KIND_VALUELIST;
		}

	/* position */
	l_v.u_l = p_pos;
	rfc_blob_add( &p_msh -> s_data , RFC_EXT_TYPELONG , &l_v );

	/* count */
	n = rfc_lst_count( p_list );
	l_v.u_l = n;
	rfc_blob_add( &p_msh -> s_data , RFC_EXT_TYPELONG , &l_v );

	/* data */
	for( k = 0; k < n; k++ )
		{
			l_pv = rfc_lst_get( p_list , k );
			rfc_blob_add( &p_msh -> s_data , p_list -> s_type , l_pv );
		}
	return( 1 );
}

short
	rfc_msh_setitem_rec( rfc_msh *p_msh , int p_pos , rfc_msh *p_rec )
{
	RFC_TYPE l_v;
	rfc_msh_itemdef *l_item;

	/* fill item if first row */
	if( !p_msh -> s_def.s_nrows )
		{
			l_item = rfc_msh_item_get( p_msh , p_pos );

			/* set props */
			l_item -> s_type = RFC_EXT_TYPENONE;
			l_item -> s_kind = RFC_MSH_KIND_MSH;
		}

	/* position */
	l_v.u_l = p_pos;
	rfc_blob_add( &p_msh -> s_data , RFC_EXT_TYPELONG , &l_v );

	/* fill all */
	rfc_msh_writeblob( p_rec , &p_msh -> s_data , 0 );
	return( 1 );
}

short
	rfc_msh_writeblob( rfc_msh *p_msh , rfc_blob *p_blob , int p_head_size )
{
	int k , n;
	RFC_TYPE l_v;
	rfc_msh_itemdef *l_p;

	/* prepare blob size */
	if( !p_blob -> s_size )
		rfc_blob_realloc( p_blob , RFC_MSH_MINSIZE );

	/* reserve head size */
	if( p_head_size )
		rfc_blob_reserve( p_blob , p_head_size );

	/* definition */
	n = rfc_msh_item_count( p_msh );

	/* count */
	l_v.u_l = n;
	rfc_blob_add( p_blob , RFC_EXT_TYPELONG , &l_v );

	for( k = 0; k < n; k++ )
		{
			l_p = rfc_msh_item_get( p_msh , k );

			/* index */
			l_v.u_l = k;
			rfc_blob_add( p_blob , RFC_EXT_TYPELONG , &l_v );

			/* name */
			l_v.u_c = l_p -> s_name;
			rfc_blob_add( p_blob , RFC_EXT_TYPECHAR , &l_v );

			/* kind */
			l_v.u_l = l_p -> s_kind;
			rfc_blob_add( p_blob , RFC_EXT_TYPELONG , &l_v );

			/* type */
			l_v.u_l = l_p -> s_type;
			rfc_blob_add( p_blob , RFC_EXT_TYPELONG , &l_v );
		}

	/* row count */
	l_v.u_l = p_msh -> s_def.s_nrows;
	rfc_blob_add( p_blob , RFC_EXT_TYPELONG , &l_v );

	/* block */
	l_v.u_o = p_msh -> s_data;
	rfc_blob_add( p_blob , RFC_EXT_TYPEBLOB , &l_v );

	return( 1 );
}

short
	rfc_msh_addrow( rfc_msh *p_msh )
{
	RFC_TYPE l_v;

	/* add row end mark */
	l_v.u_l = -1;
	rfc_blob_add( &p_msh -> s_data , RFC_EXT_TYPELONG , &l_v );

	/* increment rows */
	p_msh -> s_def.s_nrows++;

	return( 1 );
}

/* get RPC data */
RFC_MSH_RES
	rfc_msh_getitem_value( rfc_msh *p_msh , int p_pos , int p_valtype , RFC_TYPE *p_val )
{
	rfc_msh_itemdef *l_p;
	int l_offset;
	int l_size;

	/* find item */
	l_p = rfc_msh_item_get( p_msh , p_pos );
	if( l_p -> s_kind != RFC_MSH_KIND_VALUE )
		return( RFC_MSH_RES_FAIL );

	/* check empty */
	l_offset = l_p -> s_offset;
	if( !l_offset )
		return( RFC_MSH_RES_NODATA );

	/* read */
	l_size = rfc_blob_extract( &p_msh -> s_data , p_valtype , p_val , &l_offset );
	if( l_size < 0 )
		return( RFC_MSH_RES_FAIL );

	if( !l_size )
		return( RFC_MSH_RES_NODATA );

	return( RFC_MSH_RES_OK );
}

RFC_MSH_RES
	rfc_msh_getitem_list( rfc_msh *p_msh , int p_pos , rfc_list *p_list )
{
	rfc_msh_itemdef *l_p;
	int l_offset;
	int k , n;
	rfc_blob *l_blob;
	RFC_TYPE l_v;

	/* find item */
	l_p = rfc_msh_item_get( p_msh , p_pos );
	if( l_p -> s_kind != RFC_MSH_KIND_VALUELIST )
		return( RFC_MSH_RES_FAIL );

	/* check empty */
	l_offset = l_p -> s_offset;
	if( !l_offset )
		return( RFC_MSH_RES_NODATA );

	l_blob = &p_msh -> s_data;

	/* count */
	rfc_blob_extract( l_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
	n = l_v.u_l;
	rfc_lst_allocate( p_list , n );

	/* data */
	for( k = 0; k < n; k++ )
		{
			rfc_blob_extract( l_blob , p_list -> s_type , &l_v , &l_offset );
			rfc_lst_add( p_list , &l_v );
		}

	return( RFC_MSH_RES_OK );
}

RFC_MSH_RES
	rfc_msh_getitem_rec( rfc_msh *p_msh , int p_pos , rfc_msh **p_rec )
{
	rfc_msh *l_msh;
	rfc_msh_itemdef *l_p;
	int l_offset;

	/* find item */
	l_p = rfc_msh_item_get( p_msh , p_pos );
	if( l_p -> s_kind != RFC_MSH_KIND_MSH )
		return( RFC_MSH_RES_FAIL );

	/* check empty */
	l_offset = l_p -> s_offset;
	if( !l_offset )
		return( RFC_MSH_RES_NODATA );

	/* create */
	l_msh = *p_rec = rfc_msh_create( 0 );

	/* read */
	rfc_msh_readblob( l_msh , &p_msh -> s_data , &l_offset );

	return( RFC_MSH_RES_OK );
}

short
	rfc_msh_nextrow( rfc_msh *p_msh )
{
	RFC_TYPE l_v;
	int k , n;
	rfc_msh_itemdef *l_p;
	rfc_blob *l_blob;
	int l_offset;

	/* check all read */
	if( p_msh -> s_def.s_readrow >= p_msh -> s_def.s_nrows )
		return( 0 );

	/* read row data - set offsetes for items */
	p_msh -> s_def.s_readrow++;

	/* clear offsets */
	n = rfc_msh_item_count( p_msh );
	for( k = 0; k < n; k++ )
		{
			l_p = rfc_msh_item_get( p_msh , k );
			l_p -> s_offset = 0;
		}

	/* read up to -1 */
	l_blob = &p_msh -> s_data;
	l_offset = p_msh -> s_def.s_offset;
	while( 1 )
		{
			/* get position */
			rfc_blob_extract( l_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
			k = l_v.u_l;

			/* end of row */
			if( k < 0 )
				break;

			/* set offset */
			l_p = rfc_msh_item_get( p_msh , k );
			l_p -> s_offset = l_offset;

			switch( l_p -> s_kind )
				{
					/* single value */
					case RFC_MSH_KIND_VALUE :
						/* data */
						rfc_blob_extract( l_blob , 0 , NULL , &l_offset );
						break;
					/* value list */
					case RFC_MSH_KIND_VALUELIST :
						/* count */
						rfc_blob_extract( l_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
						n = l_v.u_l;
						/* data */
						for( k = 0; k < n; k++ )
							rfc_blob_extract( l_blob , 0 , NULL , &l_offset );
						break;
					/* embedded */
					case RFC_MSH_KIND_MSH :
						/* data */
						_rfc_msh_skipdef( l_blob , &l_offset );
						break;
				}
		}

	/* set new row offset */
	p_msh -> s_def.s_offset = l_offset;

	return( 1 );
}

short
	rfc_msh_readblob( rfc_msh *p_msh , rfc_blob *p_blob , int *p_offset )
{
	int k , n;
	RFC_TYPE l_v;
	int l_offset;
	const char *l_name;
	int l_kind;
	int l_type;
	int l_index;
	rfc_msh_itemdef *l_p;

	/* definition */
	/* count */
	l_offset = *p_offset;
	rfc_blob_extract( p_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
	n = l_v.u_l;

	for( k = 0; k < n; k++ )
		{
			/* index */
			rfc_blob_extract( p_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
			l_index = l_v.u_l;

			/* name */
			rfc_blob_extract( p_blob , RFC_EXT_TYPECHAR , &l_v , &l_offset );
			l_name = l_v.u_c;

			/* kind */
			rfc_blob_extract( p_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
			l_kind = l_v.u_l;

			/* type */
			rfc_blob_extract( p_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
			l_type = l_v.u_l;

			/* create item */
			l_index = rfc_msh_item_create( p_msh , l_name , l_type );
			l_p = rfc_msh_item_get( p_msh , l_index );
			l_p -> s_name = l_name;
			l_p -> s_kind = l_kind;
		}

	/* row count */
	rfc_blob_extract( p_blob , RFC_EXT_TYPELONG , &l_v , &l_offset );
	p_msh -> s_def.s_nrows = l_v.u_l;

	/* block */
	if( !rfc_blob_extract( p_blob , RFC_EXT_TYPEBLOB , &l_v , &l_offset ) )
		{
			p_msh -> s_data.s_ptr = NULL;
			p_msh -> s_data.s_size = 0;
		}
	else
		p_msh -> s_data = l_v.u_o;

	/* offset */
	*p_offset = l_offset;

	return( 1 );
}

short
	rfc_msh_setown( rfc_msh *p_msh )
{
	rfc_blob l_b;
	int k , n;
	rfc_msh_itemdef *l_p;
	int l_mem;
	char *l_s;

	if( p_msh -> s_def.s_dataown )
		return( 0 );

	if( p_msh -> s_data.s_size )
		{
			n = rfc_msh_item_count( p_msh );

			/* count additional memory for names */
			l_mem = 0;
			for( k = 0; k < n; k++ )
				{
					l_p = rfc_msh_item_get( p_msh , k );
					l_mem += strlen( l_p -> s_name ) + 1;
				}

			rfc_blob_alloc( &l_b , p_msh -> s_data.s_size + l_mem );
			rfc_blob_copy( &l_b , &p_msh -> s_data );

			/* refill base for item names */
			l_s = l_b.s_ptr + l_b.s_size;
			for( k = 0; k < n; k++ )
				{
					l_p = rfc_msh_item_get( p_msh , k );
					strcpy( l_s , l_p -> s_name );
					l_p -> s_name = l_s;
					l_s += strlen( l_s ) + 1;
				}

			p_msh -> s_data = l_b;
		}
	p_msh -> s_def.s_dataown = 1;

	return( 1 );
}

int
	rfc_msh_findname( rfc_msh *p_msh , const char *p_name )
{
	int k , n;
	rfc_msh_itemdef *l_p;

	n = rfc_msh_item_count( p_msh );
	for( k = 0; k < n; k++ )
		{
			l_p = rfc_msh_item_get( p_msh , k );
			if( !strcmp( p_name , l_p -> s_name ) )
				return( k );
		}
	return( -1 );
}

/*#######################################################*/
/*#######################################################*/

static short
	_rfc_msh_skipdef( rfc_blob *p_blob , int *p_offset )
{
	int k , n;
	RFC_TYPE l_v;

	/* item count */
	rfc_blob_extract( p_blob , RFC_EXT_TYPELONG , &l_v , p_offset );
	n = l_v.u_l;

	/* items def */
	for( k = 0; k < n; k++ )
		{
			/* index */
			rfc_blob_extract( p_blob , 0 , NULL , p_offset );

			/* name */
			rfc_blob_extract( p_blob , 0 , NULL , p_offset );

			/* kind */
			rfc_blob_extract( p_blob , 0 , NULL , p_offset );

			/* type */
			rfc_blob_extract( p_blob , 0 , NULL , p_offset );
		}

	/* row count */
	rfc_blob_extract( p_blob , 0 , NULL , p_offset );

	/* block */
	rfc_blob_extract( p_blob , 0 , NULL , p_offset );

	return( 1 );
}

