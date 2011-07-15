/*#######################################################*/
/*#######################################################*/

/* standard headers */
#include <windows.h>
#include <process.h>
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

/* lock semaphore */
int rfc_int_semlock( RFC_SEM p_sem )
{
	HANDLE wh[2];
	wh[0] = p_sem.sem;
	wh[1] = p_sem.ie;

	if( WaitForMultipleObjectsEx( 2 , wh , FALSE , INFINITE , FALSE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
}

/* release semaphore */
void rfc_int_semunlock( RFC_SEM p_sem )
{
	ReleaseSemaphore( p_sem.sem , 1 , NULL );
}

/* create semaphore */
RFC_SEM rfc_int_semcreate()
{
	RFC_SEM sem;
	sem.sem = CreateSemaphore( NULL , 1 , 1 , NULL );
	sem.ie = CreateEvent( NULL , TRUE , FALSE , NULL );
	return( sem );
}

void		rfc_int_semstop( RFC_SEM p_sem ) {
	SetEvent( p_sem.ie );
}

/* destroy semaphore */
void rfc_int_semdestroy( RFC_SEM p_sem )
{
	rfc_int_semstop( p_sem );
	CloseHandle( p_sem.sem );
	CloseHandle( p_sem.ie );
}

/* resource pool */
RFC_RPL		rfc_int_poolcreate( int count /* -1 if not limited */ ) {
	RFC_RPL rpl;
	if( count < 0 )
		count = 0x7FFFFFFF;

	rpl.sem = CreateSemaphore( NULL , 0 , count , NULL );
	rpl.ie = CreateEvent( NULL , TRUE , FALSE , NULL );
	return( rpl );
}

int			rfc_int_poolget( RFC_RPL p_rpl ) {
	HANDLE wh[2];
	wh[0] = p_rpl.sem;
	wh[1] = p_rpl.ie;

	if( WaitForMultipleObjectsEx( 2 , wh , FALSE , INFINITE , FALSE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
}

int			rfc_int_poolput( RFC_RPL p_rpl ) {
	int last;
	ReleaseSemaphore( p_rpl.sem , 1 , ( LPLONG )&last );
	return( last + 1 );
}

void		rfc_int_poolstop( RFC_RPL p_rpl ) {
	SetEvent( p_rpl.ie );
}

void		rfc_int_pooldestroy( RFC_RPL p_rpl ) {
	rfc_int_poolstop( p_rpl );
	CloseHandle( p_rpl.sem );
	CloseHandle( p_rpl.ie );
}
