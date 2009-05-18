
#include <aiknowledge_impl.h>

/*#########################################################################*/
/*#########################################################################*/

AISentenseImpl::AISentenseImpl()
{
}

AISentenseImpl::~AISentenseImpl()
{
	tokens.clear();
}

void AISentenseImpl::addToken( AIToken *p_token )
{ 
	tokens.add( p_token ); 
}
