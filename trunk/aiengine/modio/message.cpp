
#include <aiio_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AIMessageImpl::AIMessageImpl( const String p_msg , const String p_type ) 
{ 
	message = p_msg; 
	type = p_type; 
}

const char *AIMessageImpl::getMessage()
{
	return( message );
}

const char *AIMessageImpl::getType()
{
	return( type );
}

const char *AIMessageImpl::getId()
{
	return( id );
}

void AIMessageImpl::setId( const char *p_id )
{
	id = p_id;
}
