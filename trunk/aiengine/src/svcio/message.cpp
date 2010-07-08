#include "io_impl.h"

/*#########################################################################*/
/*#########################################################################*/

Message::Message()
{
	msgBaseType = MsgType_Text;
	session = NULL;
}

Message::~Message()
{
}

XmlCall& Message::toXmlCall()
{
	return( *( XmlCall * )this );
}

