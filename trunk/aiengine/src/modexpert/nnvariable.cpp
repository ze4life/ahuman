#include <aiexpert_impl.h>

/*#########################################################################*/
/*#########################################################################*/

const char *NNVariable::NAME = "NNVariable";

void NNVariable::createSerializeObject()
{
	SerializeObject *so = new SerializeObject( NAME );
	so -> setFactoryMethod( NNVariable::onCreate );
}
