/*#######################################################*/
/*#######################################################*/

/* standard headers */
#include <windows.h>
#include <process.h>
#include "__gen.h"

/*#######################################################*/
/*#######################################################*/

/* resource pool */
RFC_HND		rfc_pool_create( int count /* -1 if not limited */ ) {
	if( count < 0 )
		count = 0x0000FFFF;
	return( CreateSemaphore( NULL , 0 , count , NULL ) );
}

int			rfc_pool_get( RFC_HND p_hnd ) {
	if( WaitForSingleObject( p_hnd , INFINITE ) != WAIT_OBJECT_0 )
		return( -1 );

	return( 0 );
}

int			rfc_pool_put( RFC_HND p_hnd ) {
	int last;
	ReleaseSemaphore( p_hnd , 1 , (LPLONG )&last );
	return( last + 1 );
}

void		rfc_pool_destroy( RFC_HND p_hnd ) {
	CancelIoEx( p_hnd , NULL );
	CloseHandle( p_hnd );
}

