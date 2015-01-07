/*#######################################################*/
/*#######################################################*/

/* standard headers */
#ifdef _WIN32

#include <windows.h>
#include <process.h>

#else

#include <pthread.h>
#include <semaphore.h>

typedef struct {
	pthread_cond_t cond;
	int value;
} RFC_UNIX_SEMDATA;

#endif

#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

/* lock semaphore */
int rfc_int_semlock( RFC_SEM p_sem ) {
#ifdef _WIN32
	HANDLE wh[2];
	wh[0] = p_sem.sem;
	wh[1] = p_sem.ie;

	if( WaitForMultipleObjectsEx( 2 , wh , FALSE , INFINITE , FALSE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
#else
	/* access to value */
	if( pthread_mutex_lock( ( pthread_mutex_t * )p_sem.ie ) )
		return( -1 );

	/* check closed */
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )p_sem.sem;
	if( sm -> value < 0 ) {
		pthread_mutex_unlock( ( pthread_mutex_t * )p_sem.ie );
		return( 0 );
	}

	/* check free */
	if( sm -> value ) {
		sm -> value = 0;
		pthread_mutex_unlock( ( pthread_mutex_t * )p_sem.ie );
		return( 0 );
	}

	/* wait for signal */
	while( sm -> value == 0 ) {
		if( pthread_cond_wait( &sm -> cond , ( pthread_mutex_t * )p_sem.ie ) )
			return( -1 );
	}

	if( sm -> value > 0 )
		sm -> value = 0;

	pthread_mutex_unlock( ( pthread_mutex_t * )p_sem.ie );
	return( 0 );
#endif
}

/* release semaphore */
void rfc_int_semunlock( RFC_SEM p_sem ) {
#ifdef _WIN32
	ReleaseSemaphore( p_sem.sem , 1 , NULL );
#else
	/* access to value */
	if( pthread_mutex_lock( ( pthread_mutex_t * )p_sem.ie ) )
		return;

	/* set free */
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )p_sem.sem;
	if( sm -> value >= 0 )
		sm -> value = 1;
	pthread_mutex_unlock( ( pthread_mutex_t * )p_sem.ie );
	pthread_cond_signal( &sm -> cond );
#endif
}

/* create semaphore */
RFC_SEM rfc_int_semcreate() {
#ifdef _WIN32
	RFC_SEM sem;
	sem.sem = CreateSemaphore( NULL , 1 , 1 , NULL );
	sem.ie = CreateEvent( NULL , TRUE , FALSE , NULL );
	return( sem );
#else
	RFC_SEM sem;
	sem.sem = ( RFC_HND )malloc( sizeof( RFC_UNIX_SEMDATA ) );
	sem.ie = ( RFC_HND )malloc( sizeof( pthread_mutex_t ) );
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )sem.sem;
	pthread_cond_init( &sm -> cond , NULL );
	sm -> value = 1;
	pthread_mutex_init( ( pthread_mutex_t * )sem.ie , NULL );
	return( sem );
#endif
}

void		rfc_int_semstop( RFC_SEM p_sem ) {
#ifdef _WIN32
	SetEvent( p_sem.ie );
#else
	/* access to value */
	if( pthread_mutex_lock( ( pthread_mutex_t * )p_sem.ie ) )
		return;

	/* set busy */
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )p_sem.sem;
	sm -> value = -1;
	pthread_mutex_unlock( ( pthread_mutex_t * )p_sem.ie );
	pthread_cond_broadcast( &sm -> cond );
#endif
}

/* destroy semaphore */
void rfc_int_semdestroy( RFC_SEM p_sem )
{
#ifdef _WIN32
	rfc_int_semstop( p_sem );
	CloseHandle( p_sem.sem );
	CloseHandle( p_sem.ie );
#else
	rfc_int_semstop( p_sem );
	free( ( RFC_UNIX_SEMDATA * )p_sem.sem );
	free( ( pthread_mutex_t * )p_sem.ie );
#endif
}

/* resource pool */
RFC_RPL		rfc_int_poolcreate( int count /* -1 if not limited */ ) {
#ifdef _WIN32
	RFC_RPL rpl;
	if( count < 0 )
		count = 0x7FFFFFFF;

	rpl.sem = CreateSemaphore( NULL , 0 , count , NULL );
	rpl.ie = CreateEvent( NULL , TRUE , FALSE , NULL );
	return( rpl );
#else
	RFC_RPL sem;
	if( count < 0 )
		count = 0x7FFFFFFF;

	sem.sem = ( RFC_HND )malloc( sizeof( RFC_UNIX_SEMDATA ) );
	sem.ie = ( RFC_HND )malloc( sizeof( pthread_mutex_t ) );
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )sem.sem;
	pthread_cond_init( &sm -> cond , NULL );
	sm -> value = count;
	pthread_mutex_init( ( pthread_mutex_t * )sem.ie , NULL );
	return( sem );
#endif
}

int			rfc_int_poolget( RFC_RPL p_rpl ) {
#ifdef _WIN32
	HANDLE wh[2];
	wh[0] = p_rpl.sem;
	wh[1] = p_rpl.ie;

	if( WaitForMultipleObjectsEx( 2 , wh , FALSE , INFINITE , FALSE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
#else
	/* access to value */
	if( pthread_mutex_lock( ( pthread_mutex_t * )p_rpl.ie ) )
		return( -1 );

	/* check closed */
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )p_rpl.sem;
	if( sm -> value < 0 ) {
		pthread_mutex_unlock( ( pthread_mutex_t * )p_rpl.ie );
		return( 0 );
	}

	/* check free */
	if( sm -> value ) {
		sm -> value--;
		pthread_mutex_unlock( ( pthread_mutex_t * )p_rpl.ie );
		return( 0 );
	}

	/* wait for signal */
	while( sm -> value == 0 ) {
		if( pthread_cond_wait( &sm -> cond , ( pthread_mutex_t * )p_rpl.ie ) )
			return( -1 );
	}

	if( sm -> value > 0 )
		sm -> value--;

	pthread_mutex_unlock( ( pthread_mutex_t * )p_rpl.ie );
	return( 0 );
#endif
}

int			rfc_int_poolput( RFC_RPL p_rpl ) {
	int last;
#ifdef _WIN32
	ReleaseSemaphore( p_rpl.sem , 1 , ( LPLONG )&last );
#else
	/* access to value */
	if( pthread_mutex_lock( ( pthread_mutex_t * )p_rpl.ie ) )
		return( -1 );

	/* set free */
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )p_rpl.sem;
	last = sm -> value;
	if( sm -> value > 0 )
		sm -> value++;
	pthread_mutex_unlock( ( pthread_mutex_t * )p_rpl.ie );
	pthread_cond_signal( &sm -> cond );
#endif
	return( last + 1 );
}

void		rfc_int_poolstop( RFC_RPL p_rpl ) {
#ifdef _WIN32
	SetEvent( p_rpl.ie );
#else
	/* access to value */
	if( pthread_mutex_lock( ( pthread_mutex_t * )p_rpl.ie ) )
		return;

	/* set stopped */
	RFC_UNIX_SEMDATA *sm = ( RFC_UNIX_SEMDATA * )p_rpl.sem;
	sm -> value = -1;
	pthread_mutex_unlock( ( pthread_mutex_t * )p_rpl.ie );
	pthread_cond_broadcast( &sm -> cond );
#endif
}

void		rfc_int_pooldestroy( RFC_RPL p_rpl ) {
#ifdef _WIN32
	rfc_int_poolstop( p_rpl );
	CloseHandle( p_rpl.sem );
	CloseHandle( p_rpl.ie );
#else
	rfc_int_poolstop( p_rpl );
	free( ( RFC_UNIX_SEMDATA * )p_rpl.sem );
	free( ( pthread_mutex_t * )p_rpl.ie );
#endif
}
