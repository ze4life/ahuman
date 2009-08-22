
#include "aiknowledge_impl.h"

/*#########################################################################*/
/*#########################################################################*/

AITokenImpl::AITokenImpl( const char *p_name , int p_orderPos )
{
	name = p_name;
	orderPos = p_orderPos;
}

AITokenImpl::~AITokenImpl()
{
}

const char *AITokenImpl::getText()
{
	return( name );
}

