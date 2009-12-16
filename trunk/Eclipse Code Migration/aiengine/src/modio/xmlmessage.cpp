#include "aiio_impl.h"

XmlMessage::XmlMessage( const char *txt )
{
	Message::msgBaseType = MsgType_Xml;
	Message::setText( txt );
}

XmlMessage::XmlMessage( Xml p_xml )
{
	Message::msgBaseType = MsgType_Xml;
	xml = p_xml;
}

XmlMessage::~XmlMessage()
{
	if( xml.exists() )
		{
			AIEngine& engine = AIEngine::getInstance();
			engine.destroyXmlDoc( xml );
		}
}

Xml XmlMessage::getXml()
{
	ASSERT( xml.exists() );
	return( xml );
}

void XmlMessage::setXmlFromMessage( const char *contentType )
{
	if( !xml.exists() )
		{
			AIEngine& engine = AIEngine::getInstance();
			xml = engine.readXml( Message::getText() , contentType );
		}

	ASSERT( xml.getName().equals( contentType ) );
}

void XmlMessage::setMessageFromXml()
{
	Message::setText( xml.serialize() );
}
