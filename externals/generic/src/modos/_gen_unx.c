/*#######################################################*/
/*#######################################################*/
/* unix operations */

/* standard headers */
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

#ifndef pthread_mutexattr_default
#define pthread_mutexattr_default NULL
#endif

typedef struct {
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	int value;
} RFC_UNIX_EVDATA;

/*#######################################################*/
/*#######################################################*/
/* semaphore & event operations */

/* lock semaphore */
int rfc_hnd_semlock( RFC_HND p_hnd ) {
	return( sem_wait( ( sem_t * )p_hnd ) );
}

/* release semaphore */
void rfc_hnd_semunlock( RFC_HND p_hnd ) {
	sem_post( ( sem_t * )p_hnd );
}

/* create semaphore */
RFC_HND rfc_hnd_semcreate() {
	RFC_HND l_hnd;
	l_hnd = ( RFC_HND )malloc( sizeof( sem_t ) );
	sem_init( ( sem_t * )l_hnd , 0 , 1 );
	return( l_hnd );
}

/* destroy semaphore */
void rfc_hnd_semdestroy( RFC_HND p_hnd ) {
	sem_destroy( ( sem_t * )p_hnd );
	free( ( sem_t * )p_hnd );
}

/* wait event signaled */
short rfc_hnd_waitevent( RFC_HND p_hnd , int p_timeout_ms ) {
	RFC_UNIX_EVDATA *l_ev;
	short l_res;
	l_ev = ( RFC_UNIX_EVDATA * )p_hnd;
	pthread_mutex_lock( &l_ev -> mutex );
	pthread_cond_wait( &l_ev -> cond , &l_ev -> mutex );
	l_res = l_ev -> value;
	pthread_mutex_unlock( &l_ev -> mutex );

	if( l_res > 0 )
		return( 0 );
	return( -1 );
}

/* create event */
RFC_HND rfc_hnd_evcreate() {
	RFC_UNIX_EVDATA *l_ev;

	l_ev = ( RFC_UNIX_EVDATA * )malloc( sizeof( RFC_UNIX_EVDATA ) );
	pthread_cond_init( &l_ev -> cond , NULL );
	pthread_mutex_init( &l_ev -> mutex , NULL );
	l_ev -> value = 0;
	return( ( RFC_HND )l_ev );
}

/* destroy event */
void rfc_hnd_evdestroy( RFC_HND p_hnd ) {
	RFC_UNIX_EVDATA *l_ev;
	l_ev = ( RFC_UNIX_EVDATA * )p_hnd;
	free( l_ev );
}

/* set signaled state to event */
void rfc_hnd_evsignal( RFC_HND p_hnd ) {
	RFC_UNIX_EVDATA *l_ev;
	l_ev = ( RFC_UNIX_EVDATA * )p_hnd;
	pthread_mutex_lock( &l_ev -> mutex );
	l_ev -> value = 1;
	pthread_mutex_unlock( &l_ev -> mutex );
	pthread_cond_broadcast( &l_ev -> cond );
}

/* clear signaled state of event */
void rfc_hnd_evreset( RFC_HND p_hnd ) {
	RFC_UNIX_EVDATA *l_ev;
	l_ev = ( RFC_UNIX_EVDATA * )p_hnd;
	pthread_mutex_lock( &l_ev -> mutex );
	l_ev -> value = 0;
	pthread_mutex_unlock( &l_ev -> mutex );
}

/* create mutex */
RFC_HND		rfc_hnd_mutcreate( void ) {
	pthread_mutex_t *l_m;

	/* create mutex */
	l_m = ( pthread_mutex_t * )calloc( 1 , sizeof( pthread_mutex_t ) );
	pthread_mutex_init( l_m , pthread_mutexattr_default );

	return( ( RFC_HND )l_m );
}

/* destroy mutex */
void		rfc_hnd_mutdestroy( RFC_HND p_hnd ) {
	pthread_mutex_t *l_m;

	/* destroy mutex */
	l_m = ( pthread_mutex_t * )p_hnd;
	pthread_mutex_destroy( l_m );
	free( l_m );
}

/* lock mutex */
void		rfc_hnd_mutlock( RFC_HND p_hnd ) {
	pthread_mutex_lock( ( pthread_mutex_t * )p_hnd );
}

/* unlock mutex */
void		rfc_hnd_mutunlock( RFC_HND p_hnd ) {
	pthread_mutex_unlock( ( pthread_mutex_t * )p_hnd );
}

/*#######################################################*/
/*#######################################################*/
/* threads */

/* wait to exit thread */
int rfc_thr_waitexit( RFC_THREAD *p_thread )
{
/* HP UNIX */
#ifdef _HPUX_SOURCE
	pthread_attr_t l_status;
	if( !pthread_join( *p_thread , &l_status ) )
		return( 0 );
#define RFC_W_WAITEXIT_OK
#endif

/* POSIX standard - default */
#ifndef RFC_W_WAITEXIT_OK
	if( !pthread_join( *p_thread , NULL ) )
		return( 0 );
#endif

	return( -1 );
}

/* execution thread */
int rfc_thr_process( RFC_THREAD *p_thread , void *p_arg , void * ( *p_action )( void *p_arg ) )
{
	memset( p_thread , 0 , sizeof( RFC_THREAD ) );
/* specific to HP UNIX */
#ifdef _HPUX_SOURCE
	if( pthread_create( p_thread , pthread_attr_default , p_action , p_arg ) )
		return( -1 );
#define RFC_W_PROCESS_OK
#endif

/* POSIX standard - default */
#ifndef RFC_W_PROCESS_OK
	if( pthread_create( p_thread , NULL , p_action , p_arg ) )
		return( -1 );
#endif

	return( 0 );
}

/* exit thread */
void rfc_w_threxit( int p_exitcode )
{
	pthread_exit( ( void * )p_exitcode );
}

/* sleep current thread */
void rfc_thr_sleep( int p_sec )
{
	sleep( p_sec );
}

/*#######################################################*/
/*#######################################################*/
/* environment */

void rfc_env_gethostname( char *p_name , int p_size )
{
	gethostname( p_name , p_size );
}
