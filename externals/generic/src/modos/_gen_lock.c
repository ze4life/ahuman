/*#######################################################*/
/*#######################################################*/

/* std headers */
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/
/* rfc_lock */

rfc_lock *
	rfc_lock_create( void )
{
	rfc_lock *l_p;

	l_p = ( rfc_lock * )calloc( 1 , sizeof( rfc_lock ) );
	l_p -> s_ex_sem = rfc_hnd_semcreate();
	l_p -> s_sh_sem = rfc_hnd_semcreate();
	l_p -> s_sh_count = 0;
	l_p -> s_mode = 0;

	return( l_p );
}

void
	rfc_lock_destroy( rfc_lock *p_lock )
{
	rfc_hnd_semdestroy( p_lock -> s_ex_sem );
	rfc_hnd_semdestroy( p_lock -> s_sh_sem );

	free( p_lock );
}

void
	rfc_lock_shared( rfc_lock *p_lock )
{
	/* lock count */
	rfc_hnd_semlock( p_lock -> s_sh_sem );

	/* check count */
	if( !p_lock -> s_sh_count )
		{
			rfc_hnd_semlock( p_lock -> s_ex_sem );
			p_lock -> s_mode = 2;
		}

	/* set shared lock */
	p_lock -> s_sh_count++;

	/* unlock count */
	rfc_hnd_semunlock( p_lock -> s_sh_sem );
}

void
	rfc_lock_exclusive( rfc_lock *p_lock )
{
	/* set exclusive lock */
	rfc_hnd_semlock( p_lock -> s_ex_sem );
	p_lock -> s_mode = 1;
}

void
	rfc_lock_release( rfc_lock *p_lock )
{
	/* unlock exclusive */
	if( p_lock -> s_mode == 1 )
		{
			p_lock -> s_mode = 0;
			rfc_hnd_semunlock( p_lock -> s_ex_sem );
			return;
		}

	rfc_hnd_semlock( p_lock -> s_sh_sem );

	/* unlock shared */
	p_lock -> s_sh_count--;
	if( !p_lock -> s_sh_count )
		{
			p_lock -> s_mode = 0;
			rfc_hnd_semunlock( p_lock -> s_ex_sem );
		}

	rfc_hnd_semunlock( p_lock -> s_sh_sem );
}

void
	rfc_lock_escalate( rfc_lock *p_lock )
{
	short l_wait;

	/* check current mode */
	if( p_lock -> s_mode == 1 )
		return;

	/* escalate from shared to exclusive */
	rfc_hnd_semlock( p_lock -> s_sh_sem );

	/* unlock shared */
	p_lock -> s_sh_count--;
	l_wait = 0;
	if( p_lock -> s_sh_count )
		l_wait = 1;
	else
		p_lock -> s_mode = 1;

	rfc_hnd_semunlock( p_lock -> s_sh_sem );

	/* lock exclusive */
	if( l_wait )
		{
			rfc_hnd_semlock( p_lock -> s_ex_sem );
			p_lock -> s_mode = 1;
		}
}
