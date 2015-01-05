/*#######################################################*/
/*#######################################################*/

/* enable normal memory routines */
#undef RFC_MEMCHECK

#include "__gen.h"

/*#######################################################*/
/*#######################################################*/
/* memory check routines */

#define RFC_MEMCHECK_MAX_ITEMS		0x00008000

/* memory data */
static void *
	g_memcheck_items[ RFC_MEMCHECK_MAX_ITEMS ];
static int
	g_memcheck_count = 0;

/*#######################################################*/
/*#######################################################*/

void *
	rfc_malloc( size_t p_count )
{
	return( g_memcheck_items[ g_memcheck_count++ ] = malloc( p_count ) );
}

void *
	rfc_calloc( size_t p_num , size_t p_count )
{
	return( g_memcheck_items[ g_memcheck_count++ ] = calloc( p_num , p_count ) );
}

void
	rfc_free( void *p_addr )
{
	int k;

	if( p_addr == NULL )
		{
			/* invalid - inform failed */
			fprintf( stderr , "free: null pointer\n" );
			return;
		}

	for( k = 0; k < g_memcheck_count; k++ )
		if( g_memcheck_items[ k ] == p_addr )
			break;

	if( k < g_memcheck_count )
		{
			g_memcheck_items[ k ] = NULL;
			free( p_addr );
		}
	else
		{
			/* not found - inform failed */
			fprintf( stderr , "free: invalid pointer - 0x%8.8X\n" , ( unsigned )p_addr );
		}
}

char *
	rfc_strdup( const char *p_src )
{
	if( p_src == NULL )
		{
			fprintf( stderr , "strdup: null pointer\n" );
			return( NULL );
		}

	return( ( char * )( g_memcheck_items[ g_memcheck_count++ ] = rfc_xstrdup( p_src ) ) );
}

void *
	rfc_realloc( void *p_src , size_t p_count )
{
	int k;

	if( p_src == NULL )
		{
			/* invalid - inform failed */
			fprintf( stderr , "realloc: null pointer\n" );
			return( NULL );
		}

	/* find pointer */
	for( k = 0; k < g_memcheck_count; k++ )
		if( g_memcheck_items[ k ] == p_src )
			return( g_memcheck_items[ k ] = realloc( p_src , p_count ) );

	/* not found - inform failed */
	fprintf( stderr , "realloc: invalid pointer - 0x%8.8X\n" , ( unsigned )p_src );
	return( NULL );
}

/* report inconsistancies */
void
	rfc_memcheck_report( void )
{
	int k;

	for( k = 0; k < g_memcheck_count; k++ )
		if( g_memcheck_items[ k ] != NULL )
			fprintf( stderr , "report: non-freed pointer 0x%8.8X [%d]\n" , ( unsigned )g_memcheck_items[ k ] , k );
}

