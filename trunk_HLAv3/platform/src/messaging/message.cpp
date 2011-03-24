#include <ah_platform.h>

/*#########################################################################*/
/*#########################################################################*/

Message::Message( Message::MsgType p_baseType , const char *p_classType )
:	baseType( p_baseType ) ,
	classType( p_classType ) {
	session = NULL;
}

Message::~Message() {
}

XmlCall& Message::toXmlCall() {
	return( *( XmlCall * )this );
}

