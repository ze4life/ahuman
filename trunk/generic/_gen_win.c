/*#######################################################*/
/*#######################################################*/
/* windows operations */

/* standard headers */
#include <windows.h>
#include <process.h>
#include <__gen.h>

#include "stacktrace/printStackTrace.h"

/*#######################################################*/
/*#######################################################*/
/* module handle */
RFC_HND
	rfc_hmodule = ( RFC_HND )NULL;

/* semaphore & event operations */

/* lock semaphore */
int rfc_hnd_semlock( RFC_HND p_hnd )
{
	if( WaitForSingleObject( p_hnd , INFINITE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
}

/* release semaphore */
void rfc_hnd_semunlock( RFC_HND p_hnd )
{
	ReleaseSemaphore( p_hnd , 1 , NULL );
}

/* create semaphore */
RFC_HND rfc_hnd_semcreate()
{
	return( CreateSemaphore( NULL , 1 , 1 , NULL ) );
}

/* destroy semaphore */
void rfc_hnd_semdestroy( RFC_HND p_hnd )
{
	CloseHandle( p_hnd );
}

/* wait to event signaled */
int rfc_hnd_waitevent( RFC_HND p_hnd )
{
	if( WaitForSingleObject( p_hnd , INFINITE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
}

/* create event */
RFC_HND rfc_hnd_evcreate()
{
	return( CreateEvent( NULL , TRUE , FALSE , NULL ) );
}

/* destroy event */
void rfc_hnd_evdestroy( RFC_HND p_hnd )
{
	CloseHandle( p_hnd );
}

/* set signaled state to event */
void rfc_hnd_evsignal( RFC_HND p_hnd )
{
	SetEvent( p_hnd );
}

/* clear signaled state of event */
void rfc_hnd_evreset( RFC_HND p_hnd )
{
	ResetEvent( p_hnd );
}

/* create mutex */
RFC_HND		rfc_hnd_mutcreate( void )
{
	return( CreateMutex( NULL , FALSE , NULL ) );
}

/* destroy mutex */
void		rfc_hnd_mutdestroy( RFC_HND p_hnd )
{
	CloseHandle( p_hnd );
}

/* lock mutex */
void		rfc_hnd_mutlock( RFC_HND p_hnd )
{
	WaitForSingleObject( p_hnd , INFINITE );
}

/* unlock mutex */
void		rfc_hnd_mutunlock( RFC_HND p_hnd )
{
	ReleaseMutex( p_hnd );
}

/*#######################################################*/
/*#######################################################*/
/* threads */

/* wait to exit thread */
int rfc_thr_waitexit( RFC_THREAD *p_hnd )
{
	if( WaitForSingleObject( p_hnd -> s_ih , INFINITE ) != WAIT_OBJECT_0 )
		return( -1 );

	CloseHandle( p_hnd -> s_ih );
	return( 0 );
}

/* execution thread */
int rfc_thr_process( RFC_THREAD *p_thread , void *p_arg , RFC_THRFUNC p_action )
{
	p_thread -> s_ih = ( RFC_HND )_beginthreadex( NULL , 0 , p_action , p_arg , 1 , &p_thread -> s_ip );
	if( p_thread -> s_ih == 0 )
		return( -1 );
	return( 0 );
}

/* exit thread */
void rfc_thr_threxit( int p_exitcode )
{
	_endthreadex( p_exitcode );
}

/* sleep current thread */
void rfc_thr_sleep( int p_sec )
{
	Sleep( p_sec * 1000 );
}

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
			sl -> moduleName = strcpy( p , moduleName );
			p += strlen( moduleName ) + 1;
		}
	if( className != NULL )
		{
			sl -> className = strcpy( p , className );
			p += strlen( className ) + 1;
		}
	if( functionName != NULL )
		{
			sl -> functionName = strcpy( p , functionName );
			p += strlen( functionName ) + 1;
		}
	if( message != NULL )
		{
			sl -> message = strcpy( p , message );
			p += strlen( message ) + 1;
		}

	v.u_p = sl;
	rfc_lst_add( &stack -> levels , &v );
}

rfc_threadstack *rfc_thr_stackget( int skipLevels )
{
	rfc_threadstack *stack = ( rfc_threadstack * )calloc( 1 , sizeof( rfc_threadstack ) );
	stack -> levels.s_type = RFC_EXT_TYPEPTR;
	stack -> extraLevels = skipLevels + 2;

	if( !getStackTrace( stack , rfc_thr_onfillstack ) )
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

int rfc_thr_increment( int *pv )
{
	return( ( int )InterlockedIncrement( ( LPLONG )pv ) );
}

/*#######################################################*/
/*#######################################################*/
/* library management */

RFC_HND rfc_lib_load( const char *p_lib )
{
	return( LoadLibrary( p_lib ) );
}

RFC_PROC rfc_lib_getfunc( RFC_HND p_lib , const char *p_func )
{
	return( ( RFC_PROC )GetProcAddress( p_lib , p_func ) );
}

void rfc_lib_unload( RFC_HND p_lib )
{
	FreeLibrary( p_lib );
}

/*#######################################################*/
/*#######################################################*/
/* environment */

void rfc_env_gethostname( char *p_name , int p_size )
{
	GetComputerName( p_name , &p_size );
}

/*#######################################################*/
/*#######################################################*/

/* translate from unicode using codepage */
short
	rfc_str_setcp( char *p_s , const unsigned short *p_v , int p_cp )
{
	int l_len;

	l_len = rfc_wstr_len( p_v );
	if( !WideCharToMultiByte( p_cp , 0 , p_v , l_len , p_s , l_len , NULL , NULL ) )
		return( 0 );

	p_s[ l_len ] = 0;
	return( 1 );
}

/* translate from ansi using codepage */
short
	rfc_wstr_setcp( unsigned short *p_s , const char *p_v , int p_cp )
{
	int l_len;

	l_len = strlen( p_v );
	if( !MultiByteToWideChar( p_cp , 0 , p_v , l_len , p_s , l_len ) )
		return( 0 );

	p_s[ l_len ] = 0;
	return( 1 );
}
