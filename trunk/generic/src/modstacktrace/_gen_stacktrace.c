#include "__gen.h"

#include "printStackTrace.h"

/*#######################################################*/
/*#######################################################*/

static void rfc_thr_onfillstack( void *ptr ,
	const char *moduleName , 
	const char *className , 
	const char *functionName , 
	const char *message )
{
	rfc_threadstack *stack;
	rfc_threadstacklevel *sl;
	char *p;
	int size;
	RFC_TYPE v;

	stack = ( rfc_threadstack * )ptr;

	// add level
	size = sizeof( rfc_threadstacklevel );
	if( moduleName != NULL )
		size += strlen( moduleName ) + 1;
	if( className != NULL )
		size += strlen( className ) + 1;
	if( functionName != NULL )
		size += strlen( functionName ) + 1;
	if( message != NULL )
		size += strlen( message ) + 1;

	sl = ( rfc_threadstacklevel * )calloc( 1 , size );
	p = ( ( char * )sl ) + sizeof( rfc_threadstacklevel );

	if( moduleName != NULL )
		{
			sl -> moduleName = p;
			size = strlen( moduleName ) + 1;
			strcpy( p , moduleName );
			p += size;
		}
	if( className != NULL )
		{
			sl -> className = p;
			size = strlen( className ) + 1;
			strcpy( p , className );
			p += size;
		}
	if( functionName != NULL )
		{
			sl -> functionName = p;
			size = strlen( functionName ) + 1;
			strcpy( p , functionName );
			p += size;
		}
	if( message != NULL )
		{
			sl -> message = p;
			size = strlen( message ) + 1;
			strcpy( p , message );
			p += size;
		}

	v.u_p = sl;
	rfc_lst_add( &stack -> levels , &v );
}

rfc_threadstack *rfc_thr_stackget( int skipLevels )
{
	return( rfc_thr_stackgetforthread( NULL , skipLevels ) );
}

rfc_threadstack *rfc_thr_stackgetforthread( RFC_HND thread , int skipLevels )
{
	rfc_threadstack *stack = ( rfc_threadstack * )calloc( 1 , sizeof( rfc_threadstack ) );
	stack -> levels.s_type = RFC_EXT_TYPEPTR;
	stack -> extraLevels = skipLevels + 2;

	if( !getThreadStackTrace( ( unsigned long )thread , stack , rfc_thr_onfillstack ) )
		stack -> brokenStack = 1;

	return( stack );
}

int	rfc_thr_stackfulldepth( rfc_threadstack *stack )
{
	return( rfc_lst_count( &stack -> levels ) );
}

int rfc_thr_stackdepth( rfc_threadstack *stack )
{
	return( rfc_lst_count( &stack -> levels ) - stack -> extraLevels );
}

rfc_threadstacklevel *rfc_thr_stacklevel( rfc_threadstack *stack , int level )
{
	RFC_TYPE *v;
	int levelUsed = level;

	if( levelUsed < 0 || levelUsed >= rfc_lst_count( &stack -> levels ) )
		return( NULL );

	v = rfc_lst_get( &stack -> levels , levelUsed );
	return( ( rfc_threadstacklevel * )v -> u_p );
}

void rfc_thr_stackfree( rfc_threadstack *stack )
{
	RFC_TYPE *v;
	rfc_threadstacklevel *sl;
	int k;
	int n = rfc_lst_count( &stack -> levels );
	for( k = 0; k < n; k++ )
		{
			v = rfc_lst_get( &stack -> levels , k );
			sl = ( rfc_threadstacklevel * )v -> u_p;
			free( sl );
		}
	free( stack );
}

short rfc_thr_stacknamebyaddr( void *p_addr , char *p_class , char *p_func )
{
	return( getModuleItemByAddr( p_addr , p_class , p_func ) );
}
