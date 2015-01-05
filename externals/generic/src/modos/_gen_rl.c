/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

#define	LIB_INDEX_EXT	0
#define	LIB_INDEX_NAME	1

#define PRC_INDEX_NAME	0

#define REF_INDEX_REF	0
#define REF_INDEX_LIB	1
#define REF_INDEX_ALL	2

/*#######################################################*/
/*#######################################################*/
/* library pool functions */

static short
	_rfc_dlp_lib_load( const char *p_start , rfc_lib_info *p_lib );
static void
	_rfc_dlp_lib_unload( rfc_lib_info *p_lib );

/*#######################################################*/
/*#######################################################*/
/* construction */

/* create library pool with start in directory <p_start> */
rfc_dllpool *
	rfc_dlp_create( const char *p_start )
{
	rfc_dllpool *l_dlp;
	int l_len;
	int l_app;

	l_dlp = ( rfc_dllpool * )calloc( 1 , sizeof( rfc_dllpool ) );

	l_dlp -> s_lib = rfc_arr_create( 2 );
	rfc_arr_index_set( l_dlp -> s_lib , LIB_INDEX_EXT , offsetof( rfc_lib_info , s_ext ) , sizeof( int ) , 'L' );
	rfc_arr_index_set( l_dlp -> s_lib , LIB_INDEX_NAME , offsetof( rfc_lib_info , s_name ) , 0 , 'S' );

	l_dlp -> s_prc = rfc_arr_create( 1 );
	rfc_arr_index_set( l_dlp -> s_prc , PRC_INDEX_NAME , 0 , 1 , 'S' );

	l_dlp -> s_ref = rfc_arr_create( 3 );
	rfc_arr_index_set( l_dlp -> s_ref , REF_INDEX_REF , offsetof( rfc_lib_ref , s_ref ) , sizeof( void * ) , 'L' );
	rfc_arr_index_set( l_dlp -> s_ref , REF_INDEX_LIB , offsetof( rfc_lib_ref , s_lib ) , sizeof( void * ) , 'L' );
	rfc_arr_index_set( l_dlp -> s_ref , REF_INDEX_ALL , 0 , sizeof( void * ) + sizeof( int ) , 'V' );

	if( p_start == NULL )
		return( l_dlp );

	l_len = strlen( p_start );
	l_app = 0;
#ifdef _WIN32
	if( p_start[ l_len - 1 ] != '\\' )
#else
	if( p_start[ l_len - 1 ] != '/' )
#endif
		l_app++;
	l_dlp -> s_path = ( char * )malloc( l_len + 1 + l_app );
	strcpy( l_dlp -> s_path , p_start );
	if( l_app > 0 )
		{
#ifdef _WIN32
			l_dlp -> s_path[ l_len++ ] = '\\';
#else
			l_dlp -> s_path[ l_len++ ] = '/';
#endif
			l_dlp -> s_path[ l_len ] = 0;
		}

	return( l_dlp );
}

void
	rfc_dlp_destroy( rfc_dllpool *p_dlp )
{
	int n;
	int k;
	rfc_lib_procname *l_n;

	/* unload & delete libraries */
	n = rfc_arr_margin( p_dlp -> s_lib );
	for( k = 0; k < n; k++ )
		rfc_dlp_lib_remove( p_dlp , k );

	/* free procedures */
	n = rfc_arr_margin( p_dlp -> s_prc );
	for( k = 0; k < n; k++ )
		{
			l_n = ( rfc_lib_procname * )rfc_arr_get( p_dlp -> s_prc , k );
			if( l_n == NULL )
				continue;
			free( l_n );
		}

	/* remove path */
	if( p_dlp -> s_path )
		free( p_dlp -> s_path );

	rfc_arr_destroy( p_dlp -> s_lib );
	rfc_arr_destroy( p_dlp -> s_prc );
	rfc_arr_destroy( p_dlp -> s_ref );

	free( p_dlp );
}

/*#######################################################*/
/*#######################################################*/
/* operations */
/* library control */
/* add library information */
int
	rfc_dlp_lib_add( rfc_dllpool *p_dlp , const char *p_path , 
		int p_ext , 
		const char *p_name )
{
	char *l_x1;
	char *l_x2;
	short l_addext;
	int l_len_p;
	int l_len_n;
	rfc_lib_info *l_lib;

	if( p_path == NULL )
		return( -1 );

	if( *p_path == 0 )
		return( -1 );

	/* check identity */
	if( p_ext >= 0 )
		if( rfc_arr_find( p_dlp -> s_lib , LIB_INDEX_EXT , &p_ext ) != NULL )
			return( -1 );

	if( p_name )
		if( *p_name )
			if( rfc_arr_find( p_dlp -> s_lib , LIB_INDEX_NAME , p_name ) != NULL )
				return( -1 );

	/* check append default extension - .dll */
	l_x1 = strrchr( p_path , '\\' );
	l_x2 = strrchr( p_path , '.' );
	l_addext = 1;
	if( l_x2 != NULL )
		{
			l_addext = 0;
			if( l_x2 != NULL &&
				l_x2 < l_x1 )
				l_addext = 1;
		}

	l_len_p = strlen( p_path );
	l_len_n = ( p_name )? strlen( p_name ) : 0;

	l_lib = ( rfc_lib_info * )malloc( sizeof( rfc_lib_info ) + l_len_p + 1 + l_len_n + ( ( l_addext )? 4 : 0 ) );
	l_lib -> s_ext = p_ext;
	l_lib -> s_procs = NULL;

	l_lib -> s_procs_n = 0;
	l_lib -> s_lib = ( RFC_HND )NULL;
	l_lib -> s_state = 'V';
	l_lib -> s_path = ( ( char * )( l_lib + 1 ) ) + l_len_n;
	l_lib -> s_count = 0;

	strcpy( l_lib -> s_path , p_path );
	if( l_addext )
		strcpy( l_lib -> s_path + l_len_p , ".DLL" );
	if( p_name )
		strcpy( l_lib -> s_name , p_name );
	else
		*l_lib -> s_name = 0;

	return( rfc_arr_add( p_dlp -> s_lib , l_lib ) );
}

/* remove library */
int
	rfc_dlp_lib_remove( rfc_dllpool *p_dlp , int p_id )
{
	rfc_lib_info *l_lib;

	if( p_id < 0 || 
		p_id >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( -1 );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp-> s_lib , p_id );
	if( l_lib == NULL )
		return( -1 );

	/* free all library references */
	rfc_dlp_lib_deref_lib( p_dlp , p_id );

	/* free library information */
	if( l_lib -> s_procs != NULL )
		free( l_lib -> s_procs );

	rfc_arr_remove( p_dlp -> s_lib , p_id );
	free( l_lib );
	
	return( p_id );
}

/* add reference to library */
RFC_HND
	rfc_dlp_lib_ref( rfc_dllpool *p_dlp , int p_id , void *p_ref )
{
	rfc_lib_ref l_find;
	rfc_lib_info *l_lib;
	rfc_lib_ref *l_ref;

	l_find.s_lib = p_id;
	l_find.s_ref = p_ref;

	if( p_id < 0 || 
		p_id >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( ( RFC_HND )NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_id );
	if( l_lib == NULL )
		return( 0 );

	if( l_lib -> s_lib == ( RFC_HND )NULL )
		if( !_rfc_dlp_lib_load( p_dlp -> s_path , l_lib ) )
			return( ( RFC_HND )NULL );

	l_lib -> s_count++;

	l_ref = ( rfc_lib_ref * )rfc_arr_find( p_dlp -> s_ref , REF_INDEX_ALL , &l_find );
	if( l_ref == NULL )
		{
			l_ref = ( rfc_lib_ref * )malloc( sizeof( rfc_lib_ref ) );
			l_ref -> s_ref = p_ref;
			l_ref -> s_lib = p_id;
			l_ref -> s_count = 0;

			rfc_arr_add( p_dlp -> s_ref , l_ref );
		}

	l_ref -> s_count++;

	return( l_lib -> s_lib );
}

/* remove reference from library */
void
	rfc_dlp_lib_deref( rfc_dllpool *p_dlp , int p_id , void *p_ref )
{
	rfc_lib_ref l_find;
	int l_id;
	rfc_lib_ref *l_ref;
	rfc_lib_info *l_lib;

	l_find.s_lib = p_id;
	l_find.s_ref = p_ref;

	l_id = rfc_arr_find_id( p_dlp -> s_ref , REF_INDEX_ALL , &l_find );
	if( l_id < 0 )
		return;

	l_ref = ( rfc_lib_ref * )rfc_arr_get( p_dlp -> s_ref , l_id );
	if( l_ref == NULL )
		return;

	l_ref -> s_count--;
	if( l_ref -> s_count > 0 )
		return;

	rfc_arr_remove( p_dlp -> s_ref , l_id );
	free( l_ref );

	// check library references
	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_id );
	l_lib -> s_count--;
	if( l_lib -> s_count > 0 )
		return;

	_rfc_dlp_lib_unload( l_lib );
}

/* remove all references from library */
void
	rfc_dlp_lib_deref_lib( rfc_dllpool *p_dlp , int p_id )
{
	int l_idx;
	rfc_array *l_a;
	int n;
	int k;
	int l_pos;
	rfc_lib_ref *l_ref;
	rfc_lib_info *l_lib;

	l_idx = rfc_arr_find_index( p_dlp -> s_ref , REF_INDEX_LIB , &p_id );
	if( l_idx < 0 )
		return;

	l_a = rfc_arr_create( 0 );

	/* get indexes up */
	n = rfc_arr_count( p_dlp -> s_ref );
	for( k = l_idx - 1; k >= 0; k-- )
		{
			l_pos = rfc_arr_get_index( p_dlp -> s_ref , REF_INDEX_LIB , k );
			l_ref = ( rfc_lib_ref * )rfc_arr_get( p_dlp -> s_ref , l_pos );
			if( l_ref -> s_lib != p_id )
				break;

			rfc_arr_add( l_a , ( void * )l_pos );
		}
	/* get indexes down */
	for( k = l_idx; k < n; k++ )
		{
			l_pos = rfc_arr_get_index( p_dlp -> s_ref , REF_INDEX_LIB , k );
			l_ref = ( rfc_lib_ref * )rfc_arr_get( p_dlp -> s_ref , l_pos );
			if( l_ref -> s_lib != p_id )
				break;

			rfc_arr_add( l_a , ( void * )l_pos );
		}

	/* remove references */
	n = rfc_arr_margin( l_a );
	for( k = 0; k < n; k++ )
		{
			l_pos = ( int )rfc_arr_get( l_a , k );
			l_ref = ( rfc_lib_ref * )rfc_arr_get( p_dlp -> s_ref , l_pos );
			rfc_arr_remove( p_dlp -> s_ref , l_pos );
			free( l_ref );
		}

	/* unload library */
	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_id );
	_rfc_dlp_lib_unload( l_lib );

	l_lib -> s_count = 0;
	rfc_arr_destroy( l_a );
}

/* remove references from all libraries */
void
	rfc_dlp_lib_deref_ref( rfc_dllpool *p_dlp , void *p_ref )
{
	int l_idx;
	rfc_array *l_a;
	int n;
	int k;
	int l_pos;
	rfc_lib_ref *l_ref;
	rfc_lib_info *l_lib;

	l_idx = rfc_arr_find_index( p_dlp -> s_ref , REF_INDEX_REF , &p_ref );
	if( l_idx < 0 )
		return;

	l_a = rfc_arr_create( 0 );

	/* get indexes up */
	n = rfc_arr_count( p_dlp -> s_ref );
	for( k = l_idx - 1; k >= 0; k-- )
		{
			l_pos = rfc_arr_get_index( p_dlp -> s_ref , REF_INDEX_LIB , k );
			l_ref = ( rfc_lib_ref * )rfc_arr_get( p_dlp -> s_ref , l_pos );
			if( l_ref -> s_ref != p_ref )
				break;

			rfc_arr_add( l_a , ( void * )l_pos );
		}
	/* get indexes down */
	for( k = l_idx; k < n; k++ )
		{
			l_pos = rfc_arr_get_index( p_dlp -> s_ref , REF_INDEX_LIB , k );
			l_ref = ( rfc_lib_ref * )rfc_arr_get( p_dlp -> s_ref , l_pos );
			if( l_ref -> s_ref != p_ref )
				break;

			rfc_arr_add( l_a , ( void * )l_pos );
		}

	/* remove references */
	n = rfc_arr_margin( l_a );
	for( k = 0; k < n; k++ )
		{
			l_pos = ( int )rfc_arr_get( l_a , k );
			l_ref = ( rfc_lib_ref * )rfc_arr_get( p_dlp -> s_ref , l_pos );
			l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , l_ref -> s_lib );
			l_lib -> s_count -= l_ref -> s_count;
			rfc_arr_remove( p_dlp -> s_ref , l_pos );
			free( l_ref );

			if( l_lib -> s_count > 0 )
				continue;

			_rfc_dlp_lib_unload( l_lib );
		}

	rfc_arr_destroy( l_a );
}

/*#######################################################*/
/*#######################################################*/
/* library information */

/* find library by external ID */
int
	rfc_dlp_lib_find_ext( rfc_dllpool *p_dlp , int p_ext )
{
	return( rfc_arr_find_id( p_dlp -> s_lib , LIB_INDEX_EXT , &p_ext ) );
}

/* find library by name */
int
	rfc_dlp_lib_find_name( rfc_dllpool *p_dlp , const char *p_name )
{
	if( p_name == NULL )
		return( -1 );

	return( rfc_arr_find_id( p_dlp -> s_lib , LIB_INDEX_NAME , p_name ) );
}

/* get library path by ID */
const char *
	rfc_dlp_lib_getpath( rfc_dllpool *p_dlp , int p_id )
{
	rfc_lib_info *l_lib;

	if( p_id < 0 || 
		p_id >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_id );
	if( l_lib == NULL )
		return( NULL );

	return( l_lib -> s_path );
}

/* get full library path by ID */
rfc_string
	rfc_dlp_lib_getfull( rfc_dllpool *p_dlp , int p_id )
{
	rfc_lib_info *l_lib;
	rfc_string l_s;
	int l_len;

	if( p_id < 0 || 
		p_id >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_id );
	if( l_lib == NULL )
		return( NULL );

	/* adjust path with root */
	if( p_dlp -> s_path == NULL )
		{
			l_s = rfc_str_create( l_lib -> s_path , -1 , 0 );
			return( l_s );
		}
			
	l_len = strlen( p_dlp -> s_path );
	l_s = rfc_str_create( NULL , 0 , l_len + strlen( l_lib -> s_path ) + 1 );
	strcpy( l_s , p_dlp -> s_path );
	strcpy( l_s + l_len , l_lib -> s_path );

	return( l_s );
}

/* get library external ID by ID */
int
	rfc_dlp_lib_getext( rfc_dllpool *p_dlp , int p_id )
{
	rfc_lib_info *l_lib;

	if( p_id < 0 || 
		p_id >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( -1 );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_id );
	if( l_lib == NULL )
		return( -1 );

	return( l_lib -> s_ext );
}

/* get library code by ID */
const char *
	rfc_dlp_lib_getname( rfc_dllpool *p_dlp , int p_id )
{
	rfc_lib_info *l_lib;

	if( p_id < 0 || 
		p_id >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_id );
	if( l_lib == NULL )
		return( NULL );

	return( l_lib -> s_name );
}

/*#######################################################*/
/*#######################################################*/
/* library procedures */
/* define procedure for library */
void
	rfc_dlp_prc_define( rfc_dllpool *p_dlp , const char *p_procname , int p_prc )
{
	int l_len;
	rfc_lib_procname *l_name;

	if( p_prc >= 0 && 
		p_prc < rfc_arr_margin( p_dlp -> s_prc ) )
		{
			/* if already defined */
			if( rfc_arr_get( p_dlp -> s_prc , p_prc ) != NULL )
				return;
		}

	if( p_procname == NULL )
		return;

	if( *p_procname == 0 )
		return;

	l_len = strlen( p_procname );
	l_name = ( rfc_lib_procname * )malloc( l_len + 1 );
	strcpy( l_name -> s_name , p_procname );

	rfc_arr_set( p_dlp -> s_prc , p_prc , l_name );
}

/* load proc in library - with reference control */
RFC_PROC
	rfc_dlp_prc_load( rfc_dllpool *p_dlp , int p_lib , void *p_ref , int p_prc )
{
	rfc_lib_info *l_lib;
	const char *l_name;
	rfc_lib_proc *l_p;
	short l_load;
	RFC_PROC l_h;

	if( p_lib < 0 || 
		p_lib >= rfc_arr_margin( p_dlp -> s_lib ) ||
		p_prc < 0 )
		return( NULL );

	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_lib );
	if( l_lib == NULL )
		return( NULL );

	if( p_prc >= l_lib -> s_procs_n )
		{
			/* new use of procedure */
			if( p_prc >= rfc_arr_margin( p_dlp -> s_prc ) )
				return( NULL );

			if( l_lib -> s_procs == NULL )
				l_lib -> s_procs = ( rfc_lib_proc * )calloc( p_prc + 1 , sizeof( rfc_lib_proc ) );
			else
				{
					l_lib -> s_procs = ( rfc_lib_proc * )realloc( l_lib -> s_procs , sizeof( rfc_lib_proc ) * ( p_prc + 1 ) );
					memset( &l_lib -> s_procs[ l_lib -> s_procs_n ] , 0 , sizeof( rfc_lib_proc ) * ( p_prc - l_lib -> s_procs_n + 1 ) );
				}
			l_lib -> s_procs_n = p_prc + 1;
		}

	if( ( l_name = ( const char * )rfc_arr_get( p_dlp -> s_prc , p_prc ) ) == NULL )
		return( NULL );

	l_p = &l_lib -> s_procs[ p_prc ];

	/* if already loaded */
	if( l_p -> s_state == 'N' )
		{
			rfc_dlp_lib_ref( p_dlp , p_lib , p_ref );
			return( l_p -> s_proc );
		}

	/* if cannot be loaded */
	if( l_p -> s_state == 'E' )
		return( NULL );

	/* try load library */
	l_load = 0;
	if( l_lib -> s_lib == ( RFC_HND )NULL ) {
		if( !_rfc_dlp_lib_load( p_dlp -> s_path , l_lib ) )
			return( NULL );
		else
			l_load = 1;
	}

	/* find proc handle */
	l_h = rfc_lib_getfunc( l_lib -> s_lib , l_name );

	/* success on load */
	if( l_h != ( RFC_HND )NULL ) 
		{
			l_p -> s_proc = l_h;
			l_p -> s_state = 'N';
			rfc_dlp_lib_ref( p_dlp , p_lib , p_ref );

			return( l_h );
		}

	/* not loaded */
	l_p -> s_state = 'E';

	/* unload library if was loaded */
	if( l_load )
		_rfc_dlp_lib_unload( l_lib );
	
	return( NULL );
}

/* find proc in library - without reference control */
RFC_PROC
	rfc_dlp_prc_find( rfc_dllpool *p_dlp , int p_lib , int p_prc )
{
	rfc_lib_info *l_lib;
	rfc_lib_proc *l_p;
	RFC_PROC l_h;
	const char *l_name;

	if( p_lib < 0 || 
		p_lib >= rfc_arr_margin( p_dlp -> s_lib ) )
		return( NULL );

	/* get/check library */
	l_lib = ( rfc_lib_info * )rfc_arr_get( p_dlp -> s_lib , p_lib );
	if( l_lib == NULL )
		return( NULL );

	/* check library loaded */
	if( l_lib -> s_lib == ( RFC_HND )NULL )
		return( NULL );

	/* check proc */
	if( p_prc < 0 || 
		p_prc >= rfc_arr_margin( p_dlp -> s_prc ) )
		return( NULL );

	/* init proc array */
	if( p_prc >= l_lib -> s_procs_n )
		{
			if( l_lib -> s_procs == NULL )
				l_lib -> s_procs = ( rfc_lib_proc * )calloc( p_prc + 1 , sizeof( rfc_lib_proc ) );
			else
				{
					l_lib -> s_procs = ( rfc_lib_proc * )realloc( l_lib -> s_procs , sizeof( rfc_lib_proc ) * ( p_prc + 1 ) );
					memset( &l_lib -> s_procs[ l_lib -> s_procs_n ] , 0 , sizeof( rfc_lib_proc ) * ( p_prc - l_lib -> s_procs_n + 1 ) );
				}
			l_lib -> s_procs_n = p_prc + 1;
		}

	/* get proc */
	l_p = &l_lib -> s_procs[ p_prc ];
	if( l_p -> s_state == 'N' )
		return( l_p -> s_proc );

	/* if fail proc */
	if( l_p -> s_state == 'E' )
		return( NULL );

	/* try to load */
	if( ( l_name = ( char * )rfc_arr_get( p_dlp -> s_prc , p_prc ) ) == NULL )
		return( NULL );

	/* find proc handle */
	l_h = rfc_lib_getfunc( l_lib -> s_lib , l_name );

	/* success on load */
	if( l_h != ( RFC_HND )NULL ) 
		{
			l_p -> s_proc = l_h;
			l_p -> s_state = 'N';
			return( l_h );
		}

	/* not loaded */
	l_p -> s_state = 'E';

	return( NULL );
}

/*#######################################################*/
/*#######################################################*/
/* internal functions */

static short
	_rfc_dlp_lib_load( const char *p_start , rfc_lib_info *p_lib )
{
	char l_lib[ 1024 ];
	RFC_HND l_h;
	int n;
	int k;

	if( p_lib -> s_state != 'V' )
		return( 0 );

	*l_lib = 0;
	if( p_start )
		strcpy( l_lib , p_start );
	strcat( l_lib , p_lib -> s_path );

	l_h = rfc_lib_load( l_lib );

	/* if not loaded - set error */
	if( l_h == ( RFC_HND )NULL )
		{
			p_lib -> s_state = 'E';
			return( 0 );
		}

	/* init procs */
	p_lib -> s_state = 'N';
	p_lib -> s_lib = l_h;

	n = p_lib -> s_procs_n;
	for( k = 0; k < n; k++ )
		p_lib -> s_procs[ k ].s_state = 0;

	return( 1 );
}

static void
	_rfc_dlp_lib_unload( rfc_lib_info *p_lib )
{
	if( p_lib -> s_lib == ( RFC_HND )NULL )
		return;

	rfc_lib_unload( p_lib -> s_lib );
	p_lib -> s_state = 'V';
	p_lib -> s_lib = ( RFC_HND )NULL;

	/* exit procs */
	if( p_lib -> s_procs != NULL )
		memset( p_lib -> s_procs , 0 , sizeof( rfc_lib_proc ) * p_lib -> s_procs_n );
}

/*#######################################################*/
/*#######################################################*/

