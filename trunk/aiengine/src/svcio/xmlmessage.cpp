#include "io_impl.h"

XmlMessage::XmlMessage( const char *txt )
:	TextMessage( Message::MsgType_Xml , NULL )
{
	TextMessage::setText( txt );
}

XmlMessage::XmlMessage( Xml p_xml )
:	TextMessage( Message::MsgType_Xml , NULL )
{
	xml = p_xml;
}

XmlMessage::~XmlMessage()
{
	if( xml.exists() )
		xml.destroy();
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
			xml = engine.readXml( TextMessage::getText() , contentType );
		}

	ASSERT( xml.getName().equals( contentType ) );
}

void XmlMessage::setMessageFromXml()
{
	TextMessage::setText( xml.serialize() );
}
