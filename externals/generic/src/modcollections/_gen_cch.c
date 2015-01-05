/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/
/* cache */

/* create cache */
rfc_cache *
	rfc_cache_create( int p_max, char p_type, rfc_cach_delete f_delete )
{
	rfc_cache *cache;

	cache = ( rfc_cache * )calloc( 1, sizeof( rfc_cache ) );

	cache -> s_max_cnt = p_max;
	cache -> s_key_type = p_type;
	cache -> s_head = NULL;
	cache -> s_tail = NULL;
	cache -> s_read_flag = 0;
	cache -> s_fdelete = f_delete;

	rfc_arr_index_add( &cache -> s_arr, 0, sizeof( char* ), p_type );

	return cache;
}

/* destroy cache */
void 
	rfc_cache_destroy( rfc_cache *p_cache )
{
	if( p_cache -> s_ref-- )
		return;

	rfc_cache_clear( p_cache );
	free( p_cache );
}

/* reference cache */
void 
	rfc_cache_ref( rfc_cache *p_cache )
{
	p_cache -> s_ref++;
}

/* remove all objects from cache without destroying rfc_cache structure */
void 
	rfc_cache_clear( rfc_cache *p_cache )
{
	int i, n;

	p_cache -> s_read_flag = 0;

	n = rfc_arr_margin( &p_cache -> s_arr );
	for( i = 0; i < n; i ++ )
	{
		rfc_cacheitem *item = ( rfc_cacheitem* )rfc_arr_get( &p_cache -> s_arr, i );
		if( item )
		{
			/* call delete callback if any */
			if( p_cache -> s_fdelete )
				p_cache -> s_fdelete( item -> s_data );
			if( p_cache -> s_key_type == 'S' )
				free( item -> s_key.u_s );
			free( item );
		}
	}

	rfc_arr_init( &p_cache -> s_arr );
}

/* place object into cache, string key */
void 
	rfc_cache_add_s( rfc_cache *p_cache, void *p_obj, const char *p_key )
{
	rfc_cacheitem *item;
	int	l_pos;

	/* check for wrong type */
	if( p_cache -> s_key_type != 'S' )
		return;

	l_pos = rfc_arr_find_id( &p_cache -> s_arr, 0, p_key );
	if( l_pos != -1 )
	{
		item = ( rfc_cacheitem* )rfc_arr_get( &p_cache -> s_arr, l_pos );
		if( p_cache -> s_fdelete )
			p_cache -> s_fdelete( item -> s_data );

		item -> s_data = p_obj;
		rfc_cache_get_s( p_cache , p_key );
		return;
	}

	item = ( rfc_cacheitem* )calloc( 1, sizeof( rfc_cacheitem ) );
	item -> s_prv = NULL;
	item -> s_nxt = p_cache -> s_head;

	item -> s_data = p_obj;
	item -> s_key.u_s = rfc_xstrdup( p_key );
	if( p_cache -> s_head )
		p_cache -> s_head -> s_prv = item;
	p_cache -> s_head = item;
	if( p_cache -> s_tail == NULL )
		p_cache -> s_tail = item;

	if( p_cache -> s_max_cnt != 0 && 
			rfc_arr_count( &p_cache -> s_arr ) >= p_cache -> s_max_cnt )
	{
		/* cache is full, remove tail item from array */
		rfc_cacheitem *tail = p_cache -> s_tail;

		rfc_arr_remove_data( &p_cache -> s_arr, tail );
		if( tail -> s_prv == NULL )
			p_cache -> s_head = NULL;
		else
			tail -> s_prv -> s_nxt = NULL;
		p_cache -> s_tail = tail -> s_prv;
		/* call delete callback if any */
		if( p_cache -> s_fdelete )
			p_cache -> s_fdelete( tail -> s_data );
		free( tail -> s_key.u_s );
		free( tail );
	}

	if( l_pos == -1 )
		rfc_arr_add( &p_cache -> s_arr, item );
	else
		rfc_cache_get_s( p_cache , p_key );
}

/* place object into cache, integer key */
void 
	rfc_cache_add_l( rfc_cache *p_cache, void *p_obj, int p_key )
{
	rfc_cacheitem *item;
	int	l_pos;

	/* check for wrong type */
	if( p_cache -> s_key_type != 'L' )
		return;

	l_pos = rfc_arr_find_id( &p_cache -> s_arr, 0, &p_key );
	if( l_pos != -1 )
	{
		item = ( rfc_cacheitem* )rfc_arr_get( &p_cache -> s_arr, l_pos );
		if( p_cache -> s_fdelete )
			p_cache -> s_fdelete( item -> s_data );

		item -> s_data = p_obj;
		rfc_cache_get_l( p_cache , p_key );
		return;
	}

	item = ( rfc_cacheitem* )calloc( 1, sizeof( rfc_cacheitem ) );
	item -> s_prv = NULL;
	item -> s_nxt = p_cache -> s_head;

	item -> s_data = p_obj;
	item -> s_key.u_l = p_key;

	if( p_cache -> s_head )
		p_cache -> s_head -> s_prv = item;
	p_cache -> s_head = item;
	if( p_cache -> s_tail == NULL )
		p_cache -> s_tail = item;

	if( p_cache -> s_max_cnt != 0 && 
			rfc_arr_count( &p_cache -> s_arr ) >= p_cache -> s_max_cnt )
	{
		/* cache is full, remove tail item from array */
		rfc_cacheitem *tail = p_cache -> s_tail;

		rfc_arr_remove_data( &p_cache -> s_arr, tail );
		if( tail -> s_prv == NULL )
			p_cache -> s_head = NULL;
		else
			tail -> s_prv -> s_nxt = NULL;
		p_cache -> s_tail = tail -> s_prv;
		/* call delete callback if any */
		if( p_cache -> s_fdelete )
			p_cache -> s_fdelete( tail -> s_data );
		free( tail );
	}

	rfc_arr_add( &p_cache -> s_arr, item );
}

/* retreive object from cache by string key id */
void *
	rfc_cache_get_s( rfc_cache *p_cache, const char *p_key )
{
	rfc_cacheitem *item;

	/* check for wrong type */
	if( p_cache -> s_key_type != 'S' )
		return NULL;

	item = ( rfc_cacheitem* )rfc_arr_find( &p_cache -> s_arr, 0, p_key );
	if( item == NULL )
		/* no item found */
		return NULL;

	if( item -> s_prv == NULL )
		/* it is first item in queue list */
		return item -> s_data;

	/* move item to the first place in queue list */
	item -> s_prv -> s_nxt = item -> s_nxt;
	if( item -> s_nxt )
		item -> s_nxt -> s_prv = item -> s_prv;
	item -> s_prv = NULL;
	item -> s_nxt = p_cache -> s_head;
	p_cache -> s_head -> s_prv = item;
	p_cache -> s_head = item;

	return item -> s_data;
}

/* retreive object from cache by integer key id */
void *
	rfc_cache_get_l( rfc_cache *p_cache, int p_key )
{
	rfc_cacheitem *item;

	/* check for wrong type */
	if( p_cache -> s_key_type != 'L' )
		return NULL;

	item = ( rfc_cacheitem* )rfc_arr_find( &p_cache -> s_arr, 0, &p_key );
	if( item == NULL )
		/* no item found */
		return NULL;

	if( item -> s_prv == NULL )
		/* it is first item in queue list */
		return item -> s_data;

	/* move item to the first place in queue list*/
	item -> s_prv -> s_nxt = item -> s_nxt;
	if( item -> s_nxt )
		item -> s_nxt -> s_prv = item -> s_prv;
	else
		/* set tail item */
		p_cache -> s_tail = item -> s_prv;
	item -> s_prv = NULL;
	item -> s_nxt = p_cache -> s_head;
	p_cache -> s_head -> s_prv = item;
	p_cache -> s_head = item;

	return item -> s_data;
}

/* delete object from cache by string key id */
void
	rfc_cache_remove_s( rfc_cache *p_cache, const char *p_key )
{
	rfc_cacheitem *item;
	int l_pos;

	/* check for wrong type */
	if( p_cache -> s_key_type != 'S' )
		return;

	l_pos = rfc_arr_find_id( &p_cache -> s_arr, 0, &p_key );
	if( l_pos == -1 )
		return;

	item = ( rfc_cacheitem* )rfc_arr_get( &p_cache -> s_arr, l_pos );

	/* free key string & call delete function */
	free( item -> s_key.u_s );
	if( p_cache -> s_fdelete )
		p_cache -> s_fdelete( item -> s_data );

	/* redirect list */
	if( item -> s_nxt != NULL )
		item -> s_nxt -> s_prv = item -> s_prv;
	if( item -> s_prv != NULL )
		item -> s_prv -> s_nxt = item -> s_nxt;

	if( p_cache -> s_head == item )
		p_cache -> s_head = item -> s_nxt;
	if( p_cache -> s_tail == item )
		p_cache -> s_tail = item -> s_prv;

	rfc_arr_remove( &p_cache -> s_arr, l_pos );
	free( item );
}

/* delete object from cache by integer key id */
void
	rfc_cache_remove_l( rfc_cache *p_cache, int p_key )
{
	rfc_cacheitem *item;
	int l_pos;

	/* check for wrong type */
	if( p_cache -> s_key_type != 'L' )
		return;

	l_pos = rfc_arr_find_id( &p_cache -> s_arr, 0, &p_key );
	if( l_pos == -1 )
		return;

	item = ( rfc_cacheitem* )rfc_arr_get( &p_cache -> s_arr, l_pos );

	/* call delete function */
	if( p_cache -> s_fdelete )
		p_cache -> s_fdelete( item -> s_data );

	/* redirect list */
	if( item -> s_nxt != NULL )
		item -> s_nxt -> s_prv = item -> s_prv;
	if( item -> s_prv != NULL )
		item -> s_prv -> s_nxt = item -> s_nxt;

	if( p_cache -> s_head == item )
		p_cache -> s_head = item -> s_nxt;
	if( p_cache -> s_tail == item )
		p_cache -> s_tail = item -> s_prv;

	rfc_arr_remove( &p_cache -> s_arr, l_pos );
	free( item );
}
