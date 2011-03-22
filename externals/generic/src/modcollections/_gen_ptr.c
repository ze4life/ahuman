/*#######################################################*/
/*#######################################################*/

/* standard headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

/* create pointer array */
rfc_ptrmap *
	rfc_map_ptrcreate()
{
	return( ( rfc_ptrmap * )calloc( 1 , sizeof( rfc_ptrmap ) ) );
}

void
	rfc_map_ptralloc( rfc_ptrmap *p_p , int p_a )
{
	if( p_a <= p_p -> s_a )
		return;

	p_p -> s_a = p_a;
	p_p -> s_p = ( rfc_ptrmapentry * )realloc( p_p -> s_p , sizeof( rfc_ptrmapentry ) * p_p -> s_a );
}

/* create string array */
rfc_strmap *
	rfc_map_strcreate()
{
	return( ( rfc_strmap * )calloc( 1 , sizeof( rfc_strmap ) ) );
}

void
	rfc_map_stralloc( rfc_strmap *p_p , int p_a )
{
	if( p_a <= p_p -> s_a )
		return;

	p_p -> s_a = p_a;
	p_p -> s_p = ( rfc_strmapentry * )realloc( p_p -> s_p , sizeof( rfc_strmapentry ) * p_p -> s_a );
}

/* drop pointer array */
void
	rfc_map_ptrdrop( rfc_ptrmap *p_p )
{
	if( p_p -> s_ref-- )
		return;

	rfc_map_ptrinit( p_p );
	free( p_p );
}

/* reference map */
void
	rfc_map_ptrref( rfc_ptrmap *p_p )
{
	p_p -> s_ref++;
}

/* drop string array */
void
	rfc_map_strdrop( rfc_strmap *p_p )
{
	if( p_p -> s_ref-- )
		return;

	rfc_map_strinit( p_p );
	free( p_p );
}

/* reference map */
void
	rfc_map_strref( rfc_strmap *p_p )
{
	p_p -> s_ref++;
}

/* check pointer exists in array */
int
	rfc_map_ptrcheck( rfc_ptrmap *p_p , void *p_d , unsigned long *p_v )
{
	rfc_ptrmapentry *l_pp;
	char *l_d;
	int l_from , l_to , l_mid;
	char *l_p;

	/* find pointer by value */
	l_pp = p_p -> s_p;
	l_d = ( char * )p_d;
	l_from = 0;
	l_to = p_p -> s_n - 1;

	/* check margins */
	/* no items */
	if( l_to < 0 )
		return( -1 );

	/* check last */
	l_p = ( char * )l_pp[ l_to ].s_x;
	if( l_d == l_p )
		{
			*p_v = l_pp[ l_to ].s_y;
			return( l_to );
		}
	if( l_d > l_p )
		return( -1 );

	/* only one item */
	if( l_to == 0 )
		return( -1 );

	/* check first */
	l_p = ( char * )l_pp[ l_from ].s_x;
	if( l_d == l_p )
		{
			*p_v = l_pp[ l_from ].s_y;
			return( l_from );
		}
	if( l_d < l_p )
		return( -1 );

	while( ( l_to - l_from ) > 1 )
		{
			l_mid = ( l_from + l_to ) / 2;
			l_p = ( char * )l_pp[ l_mid ].s_x;
			if( l_d == l_p )
				{
					*p_v = l_pp[ l_mid ].s_y;
					return( l_mid );
				}

			if( l_d > l_p )
				l_from = l_mid;
			else
				l_to = l_mid;
		}

	return( -1 );
}

/* check string exists in array */
int
	rfc_map_strcheck( rfc_strmap *p_p , const char *p_d , void **p_v )
{
	rfc_strmapentry *l_pp;
	int l_res;
	int l_from , l_to , l_mid;

	/* find pointer by value */
	l_pp = p_p -> s_p;
	l_from = 0;
	l_to = p_p -> s_n - 1;

	/* check margins */
	/* no items */
	if( l_to < 0 )
		return( -1 );

	/* check last */
	l_res = strcmp( p_d , l_pp[ l_to ].s_x );
	if( l_res == 0 )
		{
			*p_v = l_pp[ l_to ].s_y;
			return( l_to );
		}
	if( l_res > 0 )
		return( -1 );

	/* only one item */
	if( l_to == 0 )
		return( -1 );

	/* check first */
	l_res = strcmp( p_d , l_pp[ l_from ].s_x );
	if( l_res == 0 )
		{
			*p_v = l_pp[ l_from ].s_y;
			return( l_from );
		}
	if( l_res < 0 )
		return( -1 );

	while( ( l_to - l_from ) > 1 )
		{
			l_mid = ( l_from + l_to ) / 2;
			l_res = strcmp( p_d , l_pp[ l_mid ].s_x );
			if( l_res == 0 )
				{
					*p_v = l_pp[ l_mid ].s_y;
					return( l_mid );
				}

			if( l_res > 0 )
				l_from = l_mid;
			else
				l_to = l_mid;
		}

	return( -1 );
}

/* add pointer to array */
static int
	rfc_map_ptradd_internal( rfc_ptrmap *p_p , void *p_d , unsigned long p_v , short p_update )
{
	rfc_ptrmapentry *l_pp;
	char *l_d;
	int l_from , l_to , l_mid;
	int l_where;
	char *l_p;

	/* find pointer by value */
	l_pp = p_p -> s_p;
	l_d = ( char * )p_d;
	l_from = 0;
	l_to = p_p -> s_n - 1;

	/* check margins */
	/* no items */
	if( l_to < 0 )
		l_where = 0;
	else
		{
			/* check last */
			l_p = ( char * )l_pp[ l_to ].s_x;
			if( l_d >= l_p )
				{
					if( l_d == l_p )
						{
							if( p_update )
								{
									l_pp[ l_to ].s_y = p_v;
									return( l_to );
								}
							return( -1 );
						}
					l_where = l_to + 1;
				}
			else
				{
					/* only one item */
					if( l_to == 0 )
						l_where = 0;
					else
						{
							/* check first */
							l_p = ( char * )l_pp[ l_from ].s_x;
							if( l_d <= l_p )
								{
									if( l_d == l_p )
										{
											if( p_update )
												{
													l_pp[ l_from ].s_y = p_v;
													return( l_from );
												}
											return( -1 );
										}
									l_where = 0;
								}
							else
								{
									while( ( l_to - l_from ) > 1 )
										{
											l_mid = ( l_from + l_to ) / 2;
											l_p = ( char * )l_pp[ l_mid ].s_x;
											if( l_d == l_p )
												{
													if( p_update )
														{
															l_pp[ l_mid ].s_y = p_v;
															return( l_mid );
														}
													return( -1 );
												}

											if( l_d > l_p )
												l_from = l_mid;
											else
												l_to = l_mid;
										}
									l_where = l_to;
								}
						}
				}
		}

	/* enlarge array size */
	if( p_p -> s_n == p_p -> s_a )
		{
			if( l_pp == NULL )
				{
					p_p -> s_a = 4;
					l_pp = ( rfc_ptrmapentry * )malloc( sizeof( rfc_ptrmapentry ) * p_p -> s_a );
				}
			else
				{
					p_p -> s_a <<= 1;
					l_pp = ( rfc_ptrmapentry * )realloc( l_pp , sizeof( rfc_ptrmapentry ) * p_p -> s_a );
				}
			p_p -> s_p = l_pp;
		}

	/* shift from l_where to n */
	for( l_from = p_p -> s_n; l_from > l_where; l_from-- )
		l_pp[ l_from ] = l_pp[ l_from - 1 ];

	/* set new pointer */
	l_pp[ l_where ].s_x = l_d;
	l_pp[ l_where ].s_y = p_v;
	p_p -> s_n++;

	return( l_where );
}

int
	rfc_map_ptradd( rfc_ptrmap *p_p , void *p_d , unsigned long p_v )
{
	return( rfc_map_ptradd_internal( p_p , p_d , p_v , 0 ) );
}

int
	rfc_map_ptrsetkey( rfc_ptrmap *p_p , void *p_d , unsigned long p_v )
{
	return( rfc_map_ptradd_internal( p_p , p_d , p_v , 1 ) );
}

/* add string to array */
static int
	rfc_map_stradd_internal( rfc_strmap *p_p , const char *p_d , void *p_v , short p_update )
{
	rfc_strmapentry *l_pp;
	int l_res;
	int l_from , l_to , l_mid;
	int l_where;

	/* find pointer by value */
	l_pp = p_p -> s_p;
	l_from = 0;
	l_to = p_p -> s_n - 1;

	/* check margins */
	/* no items */
	if( l_to < 0 )
		l_where = 0;
	else
		{
			/* check last */
			l_res = strcmp( p_d , l_pp[ l_to ].s_x );
			if( l_res >= 0 )
				{
					if( !l_res )
						{
							if( p_update )
								{
									l_pp[ l_to ].s_y = p_v;
									return( l_to );
								}
							return( -1 );
						}
					l_where = l_to + 1;
				}
			else
				{
					/* only one item */
					if( l_to == 0 )
						l_where = 0;
					else
						{
							/* check first */
							l_res = strcmp( p_d , l_pp[ l_from ].s_x );
							if( l_res <= 0 )
								{
									if( !l_res )
										{
											if( p_update )
												{
													l_pp[ l_from ].s_y = p_v;
													return( l_from );
												}
											return( -1 );
										}
									l_where = 0;
								}
							else
								{
									while( ( l_to - l_from ) > 1 )
										{
											l_mid = ( l_from + l_to ) / 2;
											l_res = strcmp( p_d , l_pp[ l_mid ].s_x );
											if( !l_res )
												{
													if( p_update )
														{
															l_pp[ l_mid ].s_y = p_v;
															return( l_mid );
														}
													return( -1 );
												}

											if( l_res > 0 )
												l_from = l_mid;
											else
												l_to = l_mid;
										}
									l_where = l_to;
								}
						}
				}
		}

	/* enlarge array size */
	if( p_p -> s_n == p_p -> s_a )
		{
			if( l_pp == NULL )
				{
					p_p -> s_a = 4;
					l_pp = ( rfc_strmapentry * )malloc( sizeof( rfc_strmapentry ) * p_p -> s_a );
				}
			else
				{
					p_p -> s_a <<= 1;
					l_pp = ( rfc_strmapentry * )realloc( l_pp , sizeof( rfc_strmapentry ) * p_p -> s_a );
				}
			p_p -> s_p = l_pp;
		}

	/* shift from l_where to n */
	for( l_from = p_p -> s_n; l_from > l_where; l_from-- )
		l_pp[ l_from ] = l_pp[ l_from - 1 ];

	/* set new pointer */
	l_from = strlen( p_d ) + 1;
	l_pp[ l_where ].s_x = ( char * )malloc( l_from );
	memcpy( l_pp[ l_where ].s_x , p_d , l_from );
	l_pp[ l_where ].s_y = p_v;
	p_p -> s_n++;

	return( l_where );
}

int
	rfc_map_stradd( rfc_strmap *p_p , const char *p_d , void *p_v )
{
	return( rfc_map_stradd_internal( p_p , p_d , p_v , 0 ) );
}

int
	rfc_map_strsetkey( rfc_strmap *p_p , const char *p_d , void *p_v )
{
	return( rfc_map_stradd_internal( p_p , p_d , p_v , 1 ) );
}

/* remove pointer from array */
unsigned long
	rfc_map_ptrremove( rfc_ptrmap *p_p , void *p_d )
{
	int l_where;
	unsigned long l_save;

	l_where = rfc_map_ptrcheck( p_p , p_d , &l_save );
	if( l_where < 0 )
		return( 0 );

	rfc_map_ptrremovepos( p_p , l_where );

	return( l_save );
}

unsigned long
	rfc_map_ptrremovepos( rfc_ptrmap *p_p , int p_pos )
{
	int k , n;
	rfc_ptrmapentry *l_pp;
	unsigned long l_save;

	/* get by position */
	if( p_pos < 0 ||
		p_pos >= p_p -> s_n )
		return( 0 );

	/* get current value */
	l_save = p_p -> s_p[ p_pos ].s_y;

	/* shift pointers */
	n = --p_p -> s_n;
	l_pp = p_p -> s_p;
	for( k = p_pos; k < n; k++ )
		l_pp[ k ] = l_pp[ k + 1 ];

	l_pp[ n ].s_x = NULL;
	l_pp[ n ].s_y = 0;

	return( l_save );
}

/* remove string from array */
void *
	rfc_map_strremove( rfc_strmap *p_p , const char *p_d )
{
	int l_where;
	void *l_save;

	l_where = rfc_map_strcheck( p_p , p_d , ( void ** )&l_save );
	if( l_where < 0 )
		return( NULL );

	rfc_map_strremovepos( p_p , l_where );

	return( l_save );
}

void *
	rfc_map_strremovepos( rfc_strmap *p_p , int p_pos )
{
	void *l_save;
	rfc_strmapentry *l_pp;
	int k , n;

	/* get by position */
	if( p_pos < 0 ||
		p_pos >= p_p -> s_n )
		return( NULL );

	/* get current value */
	l_save = p_p -> s_p[ p_pos ].s_y;

	/* free string */
	l_pp = p_p -> s_p;
	free( l_pp[ p_pos ].s_x );

	/* shift pointers */
	n = --p_p -> s_n;
	l_pp = p_p -> s_p;
	for( k = p_pos; k < n; k++ )
		l_pp[ k ] = l_pp[ k + 1 ];

	l_pp[ n ].s_x = NULL;
	l_pp[ n ].s_y = NULL;

	return( l_save );
}

/* clear array */
void
	rfc_map_ptrclear( rfc_ptrmap *p_p )
{
	p_p -> s_n = 0;
}

/* clear array */
void
	rfc_map_strclear( rfc_strmap *p_p )
{
	int k , n;
	if( p_p -> s_a == 0 )
		return;

	/* free strings */
	n = p_p -> s_n;
	for( k = 0; k < n; k++ )
		free( p_p -> s_p[ k ].s_x );

	/* free array */
	p_p -> s_n = 0;
}

void
	rfc_map_ptrinit( rfc_ptrmap *p_p )
{
	if( p_p -> s_a )
		{
			free( p_p -> s_p );
			p_p -> s_a = 0;
			p_p -> s_n = 0;
			p_p -> s_p = NULL;
		}
}

void
	rfc_map_strinit( rfc_strmap *p_p )
{
	int k , n;
	if( p_p -> s_a == 0 )
		return;

	/* free strings */
	n = p_p -> s_n;
	for( k = 0; k < n; k++ )
		free( p_p -> s_p[ k ].s_x );

	/* free array */
	free( p_p -> s_p );
	p_p -> s_a = 0;
	p_p -> s_n = 0;
	p_p -> s_p = NULL;
}

int
	rfc_map_ptrcount( rfc_ptrmap *p_p )
{
	return( p_p -> s_n );
}

int
	rfc_map_strcount( rfc_strmap *p_p )
{
	return( p_p -> s_n );
}

unsigned long
	rfc_map_ptrget( rfc_ptrmap *p_map , int p_pos )
{
	return( p_map -> s_p[ p_pos ].s_y );
}

/* set item by position */
short
	rfc_map_ptrsetpos( rfc_ptrmap *p_map , int p_pos , unsigned long p_value )
{
	/* get by position */
	if( p_pos < 0 ||
		p_pos >= p_map -> s_n )
		return( 0 );

	p_map -> s_p[ p_pos ].s_y = p_value;
	return( 1 );
}

void *
	rfc_map_strget( rfc_strmap *p_map , int p_pos )
{
	return p_map -> s_p[ p_pos ] . s_y;
}

/* set item by position */
short
	rfc_map_strsetpos( rfc_strmap *p_map , int p_pos , void *p_value )
{
	/* get by position */
	if( p_pos < 0 ||
		p_pos >= p_map -> s_n )
		return( 0 );

	p_map -> s_p[ p_pos ].s_y = p_value;
	return( 1 );
}

int
	rfc_map_ptrinsertpos( rfc_ptrmap *p_p , void *ptr )
{
	rfc_ptrmapentry *l_pp;
	char *l_d;
	int l_from , l_to , l_mid;
	char *l_p;

	/* find pointer by value */
	l_pp = p_p -> s_p;
	l_d = ( char * )ptr;
	l_from = 0;
	l_to = p_p -> s_n - 1;

	/* check margins */
	/* no items */
	if( l_to < 0 )
		return( 0 );

	/* check last */
	l_p = ( char * )l_pp[ l_to ].s_x;
	if( l_d == l_p )
		return( l_to );
	if( l_d > l_p )
		return( l_to + 1 );

	/* only one item */
	if( l_to == 0 )
		return( 0 );

	/* check first */
	l_p = ( char * )l_pp[ l_from ].s_x;
	if( l_d <= l_p )
		return( l_from );

	while( ( l_to - l_from ) > 1 )
		{
			l_mid = ( l_from + l_to ) / 2;
			l_p = ( char * )l_pp[ l_mid ].s_x;
			if( l_p == l_d )
				return( l_mid );

			if( l_d > l_p )
				l_from = l_mid;
			else
				l_to = l_mid;
		}

	return( l_to );
}

int
	rfc_map_strinsertpos( rfc_strmap *p_p , const char *ptr )
{
	rfc_strmapentry *l_pp;
	char *l_d;
	int l_from , l_to , l_mid , l_cmp;
	char *l_p;

	/* find pointer by value */
	l_pp = p_p -> s_p;
	l_d = ( char * )ptr;
	l_from = 0;
	l_to = p_p -> s_n - 1;

	/* check margins */
	/* no items */
	if( l_to < 0 )
		return( 0 );

	/* check last */
	l_p = ( char * )l_pp[ l_to ].s_x;
	l_cmp = strcmp( l_d , l_p );
	if( l_cmp == 0 )
		return( l_to );
	if( l_cmp > 0 )
		return( l_to + 1 );

	/* only one item */
	if( l_to == 0 )
		return( 0 );

	/* check first */
	l_p = ( char * )l_pp[ l_from ].s_x;
	l_cmp = strcmp( l_d , l_p );
	if( l_cmp <= 0 )
		return( l_from );

	while( ( l_to - l_from ) > 1 )
		{
			l_mid = ( l_from + l_to ) / 2;
			l_p = ( char * )l_pp[ l_mid ].s_x;
			l_cmp = strcmp( l_d , l_p );
			if( l_cmp == 0 )
				return( l_mid );

			if( l_cmp > 0 )
				l_from = l_mid;
			else
				l_to = l_mid;
		}

	return( l_to );
}
