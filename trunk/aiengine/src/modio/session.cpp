#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

SessionImpl::SessionImpl( int id )
{
	sessionId = id;
	dataLock = rfc_lock_create();
}

SessionImpl::~SessionImpl()
{
	rfc_lock_destroy( dataLock );
	objects.destroy();
}

int SessionImpl::getSessionId()
{
	return( sessionId );
}

void SessionImpl::setObject( Object *o , String name )
{
	rfc_lock_exclusive( dataLock );
	Object *oOld = objects.get( name );
	objects.add( name , o );
	rfc_lock_release( dataLock );

	ASSERT( oOld == NULL );
}

Object *SessionImpl::getObject( String name )
{
	rfc_lock_shared( dataLock );
	Object *o = objects.get( name );
	rfc_lock_release( dataLock );

	return( o );
}
