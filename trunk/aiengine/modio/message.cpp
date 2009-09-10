#include "aiio_impl.h"

/*#########################################################################*/
/*#########################################################################*/

Message::Message()
{
	msgBaseType = MsgType_Text;
}

Message::~Message()
{
}

XmlCall& Message::toXmlCall()
{
	return( *( XmlCall * )this );
}

